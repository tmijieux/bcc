#include <stdio.h>

#include "type.h"
#include "../symbol/symbol.h"
#include "../util/error.h"
#include "../expression/expression.h"
#include "../util/list.h"
#include "../util/hash_table.h"
#include "errorc.h"



static struct type *type_new(enum type_type t);

const struct type* type_undef;
const struct type* type_generic;

const struct type* type_bool;
const struct type* type_char;
const struct type* type_short;
const struct type* type_int;
const struct type* type_long;

const struct type* type_float;
const struct type* type_double;
const struct type* type_void;

static int type_precision__[] = {
    [TYPE_UNDEF] = -1,
    [TYPE_GENERIC] = -1,
    [TYPE_VOID] = -1,
    [TYPE_ARRAY] = -1,
    [TYPE_FUNCTION] = -1,

    [TYPE_BOOL] = 5,
    [TYPE_CHAR] = 10,
    [TYPE_SHORT] = 20,
    [TYPE_INT] = 30,
    [TYPE_LONG] = 40,

    [TYPE_FLOAT] = 50,
    [TYPE_DOUBLE] = 60
};

static size_t type_size__[] = {
    [TYPE_UNDEF] = 0,
    [TYPE_VOID] = 0,

    [TYPE_BOOL] = 1,
    [TYPE_CHAR] = 1,
    [TYPE_SHORT] = 2,
    [TYPE_INT] = 4,
    [TYPE_LONG] = 8,

    [TYPE_FLOAT] = 4,
    [TYPE_DOUBLE] = 8,
    [TYPE_ARRAY] = 8,

    [TYPE_FUNCTION] = 8,
    [TYPE_GENERIC] = 8,
};


static const struct type *
type_new_function_type(const struct type *return_value, const struct list *args);

static const struct type *
type_new_array_type(const struct type *values,
		    const struct expression  *array_size);
static const struct type *
type_new_array_type_reversed(const struct type *values,
			     const struct expression*array_size);

static struct hash_table *type_table;
/**
 *  This variable is used to remember the last type_name that was read
 *  to allow the program to know which type_name it should apply when
 *  it encounters a declarator
 */
const struct type *last_type_name = NULL;
const struct type *last_function_return_type = NULL;

/***************************************************/

static void init_type(const struct type **type_var,
                      const char *type_name,
                      enum type_type type_type)
{
    *type_var = type_new(type_type);
    ht_add_entry(type_table, type_name, (void*)*type_var);
}

void type_init(void)
{
    type_table = ht_create(0, NULL);

    init_type(&type_undef, "undef", TYPE_UNDEF);
    init_type(&type_generic, "generic", TYPE_GENERIC);

    init_type(&type_bool, "bool", TYPE_BOOL);
    init_type(&type_char, "char", TYPE_CHAR);
    init_type(&type_short, "short", TYPE_SHORT);
    init_type(&type_int, "int", TYPE_INT);
    init_type(&type_long, "long", TYPE_LONG);

    init_type(&type_float, "float", TYPE_FLOAT);
    init_type(&type_double, "double", TYPE_DOUBLE);
    init_type(&type_void, "void", TYPE_VOID);

    last_type_name = type_generic;
    last_function_return_type = type_generic;
}

/***************************************************/

int type_precision(const struct type *type)
{
    return type_precision__[type->type];
}

size_t type_size(const struct type * t)
{
    return type_size__[t->type];
}

/********************************************/

static struct type *type_new(enum type_type et)
{
    struct type *t = calloc(sizeof *t, 1);
    t->type = et;
    t->size = type_size(t);
    t->is_vector = false; // the default
    return t;
}

/**************************************************/

/* build an array in reverse order
   i.e: given
   values = array< 10, array< 3, int > >
   and size  = 42 (42 must be wrapped inside an expression)

   return
   array< 10, array< 3, array< 42, int > > >

   --> it nest the newly created array inside the one it is given
   keeping the same basic type
*/
static const struct type *
type_new_array_type_reversed(const struct type *values,
			     const struct expression *array_size)
{
    struct type *ty = type_new(TYPE_ARRAY);

    if (!type_is_array(values)) {
	ty->array_type.values = values;
	ty->array_type.array_size = array_size;
	return ty;
    }

    ty->array_type.array_size = type_array_size(values);
    ty->array_type.values = type_new_array_type(type_array_values(values),
						array_size);
    return ty;
}

static const struct type *
type_new_array_type(const struct type *values,
                    const struct expression *array_size)
{
    struct type *ty = type_new(TYPE_ARRAY);

    ty->array_type.values = values;
    ty->array_type.array_size = array_size;
    return ty;
}

static const struct type *	// list of symbols (should be type)
type_new_function_type(const struct type *return_value, const struct list *argv)
{
    struct type *ty = type_new(TYPE_FUNCTION);
    ty->function_type.return_value = return_value;
    ty->function_type.argv = argv;
    ty->function_type.argc = list_size(argv);
    return ty;
}

static const struct type *	// list of symbols (should be type)
type_new_pointer_type(const struct pointer *ptr, const struct type *pointed_value)
{
    assert (NULL != ptr);

    const struct type *ty = pointed_value;
    do {
        struct type *tmp = type_new(TYPE_POINTER);
        tmp->pointer_type.pointed_type = ty;
        ty = tmp;
    } while (NULL != (ptr = pointer_get_sub_pointer(ptr)));
    return ty;
}

static const char *type_arglist(const struct list *l);

static const char *str_expression_size(const struct expression *expr)
{
    char *str = "";
    if (void_expression == expr)
        return "";
    if (expr->expression_type == EXPR_CONSTANT) {
	if (expr->type == type_int) {
	    asprintf(&str, "%d", expr->constant->integer.intv.signed_);
	}

	if (expr->type == type_long) {
	    asprintf(&str, "%ld", expr->constant->integer.longv.signed_);
	}
    }
    if (expr->expression_type == EXPR_SYMBOL) {
	asprintf(&str, "%s", expr->symbol->name);
    }
    if (expr->expression_type == EXPR_UNDEF) {
	return "undef";
    }

    return str;
}

const char *type_printable_aux(const struct type *t, char *printable);

const char *type_printable(const struct type *t)
{
    char *printable = "type_printable_unimplemented";

    switch (t->type) {
        case TYPE_UNDEF:
            printable = "undef";
            break;
        case TYPE_GENERIC:
            printable = "generic";
            break;
        case TYPE_VOID:
            printable = "void";
            break;
        case TYPE_BOOL:
            printable = "bool";
            break;
        case TYPE_CHAR:
            printable = "char";
            break;

        case TYPE_SHORT:
            printable = "short";
            break;
        case TYPE_INT:
            printable = "int";
            break;
        case TYPE_LONG:
            printable = "long";
            break;

        case TYPE_FLOAT:
            printable = "float";
            break;
        case TYPE_DOUBLE:
            printable = "double";
            break;

        case TYPE_ARRAY:
        case TYPE_FUNCTION:
        case TYPE_POINTER:
            return type_printable_aux(t, "");
            break;
        default:
            break;
    }
    return printable;
}

const char *type_printable_aux(const struct type *t, char *printable)
{
    switch (t->type) {
        case TYPE_ARRAY:
            asprintf(&printable, "%s[%s]", printable,
                     str_expression_size(t->array_type.array_size));
            return type_printable_aux(type_array_values(t), printable);
            break;
        case TYPE_FUNCTION:
            asprintf(&printable, "(%s)(%s)", printable,
                     type_arglist(t->function_type.argv));
            return type_printable_aux(type_function_return(t), printable);
            break;
        case TYPE_POINTER:
            asprintf(&printable, "*%s", printable);
            return type_printable_aux(type_pointer_star(t), printable);
            break;

        default:
            asprintf(&printable, "%s %s", type_printable(t), printable);
            return printable;
            break;
    }

    return printable;
}

static const char *type_arglist(const struct list *l)
{
    char *arglist = "";
    int s = list_size(l);
    for (int i = 1; i <= s; ++i) {
	struct symbol *v = list_get(l, i);
	asprintf(&arglist, "%s%s%s",
		 arglist, i == 1 ? "" : ", ", type_printable(v->type));
    }
    return arglist;
}

bool type_equal(const struct type *t1, const struct type *t2)
{
    if (t1 == t2)
	return true;

    if (t1->type != t2->type) {
	if (t1 == type_generic || t2 == type_generic)
	    return true;
	return false;
    }

    if (t1->type == TYPE_FUNCTION) {
	if (!type_equal(t1->function_type.return_value,
			t2->function_type.return_value))
	    return false;
	const struct list *l1 = t1->function_type.argv;
	const struct list *l2 = t2->function_type.argv;
	unsigned int s;
	if ((s = list_size(l1)) != list_size(l2))
	    return false;
	for (unsigned int i = 1; i <= s; ++i) {
	    const struct type *s1 = ((struct symbol*)list_get(l1,i))->type;
	    const struct type *s2 = ((struct symbol*)list_get(l2,i))->type;
	    if (!type_equal(s1, s2))
		return false;
	}
    }

    if (t1->type == TYPE_ARRAY) {
	if (!type_equal(t1->array_type.values, t2->array_type.values))
	    return false;
    }

    return true;
}

bool type_is_basic(const struct type * type)
{
    return (type == type_char || type == type_short ||
	    type == type_int || type == type_long || type == type_bool ||
	    type == type_float || type == type_generic);
}

bool type_is_integer(const struct type * type)
{
    return (type == type_bool || type == type_char || type == type_short ||
	    type == type_int || type == type_long);
}

bool type_is_function(const struct type * ty)
{
    return (ty->type == TYPE_FUNCTION);
}

bool type_is_array(const struct type * ty)
{
    return (ty->type == TYPE_ARRAY);
}

bool type_is_pointer(const struct type * ty)
{
    return (TYPE_POINTER == ty->type);
}

int type_function_argc(const struct type *ty)
{
    assert(type_is_function(ty));
    return ty->function_type.argc;
}

const struct list *type_function_argv(const struct type *ty)
{
    assert(type_is_function(ty));
    return ty->function_type.argv;
}

const struct type *type_function_return(const struct type *ty)
{
    assert(type_is_function(ty));
    return ty->function_type.return_value;
}

const struct type *type_array_values(const struct type *ty)
{
    assert(type_is_array(ty));
    return ty->array_type.values;
}

const struct expression *type_array_size(const struct type *ty)
{
    assert(type_is_array(ty));
    return ty->array_type.array_size;
}

const struct type *type_pointer_star(const struct type *ty)
{
    assert( type_is_pointer(ty) );
    return ty->pointer_type.pointed_type;
}

static const struct type *type_get_or_create(const struct type *t)
{
    const struct type *already_existing = NULL;
    const char *key = type_printable(t);

    if (ht_get_entry(type_table, key, &already_existing) == 0)
        return already_existing;
    ht_add_entry(type_table, key, (void*)t);
    return t;
}

const struct type *type_get_pointer_type(const struct pointer *ptr,
                                         const struct type *type)
{
    assert(NULL != ptr);
    return type_get_or_create(type_new_pointer_type(ptr, type));
}

const struct type *
type_get_function_type(const struct type *return_type,
                       const struct list *type_param_list)
{
    return type_get_or_create(
        type_new_function_type(return_type, type_param_list));
}

const struct type *
type_get_array_type(const struct type *values,
                    const struct expression *const_expr_array_size)
{
    return type_get_or_create(
        type_new_array_type(values, const_expr_array_size));
}


const struct type *
type_get_array_type_reversed(const struct type *values,
                             const struct expression *const_expr_array_size)
{
    return type_get_or_create(
        type_new_array_type_reversed(values, const_expr_array_size));
}
