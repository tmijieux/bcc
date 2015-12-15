#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include "type.h"
#include "list.h"
#include "symbol.h"
#include "error.h"
#include "expression.h"

#define DEFINE_TYPE(ty)				\
    const struct type* type_##ty;		\
    const struct type* type_##ty##_v;		\

#define INIT_TYPE(ty, TY)				\
    type_##ty = type_new(TYPE_##TY);			\
    type_##ty##_v = type_new(TYPE_##TY);		\
    ((struct type*)type_##ty##_v)->is_vector = true;	\

static struct type *type_new(enum enum_type t);

DEFINE_TYPE(undef);
DEFINE_TYPE(generic);

DEFINE_TYPE(bool);
DEFINE_TYPE(byte);
DEFINE_TYPE(short);
DEFINE_TYPE(int);
DEFINE_TYPE(long);

DEFINE_TYPE(float);
DEFINE_TYPE(void);

static int type_precision__[] = {
    [TYPE_UNDEF] = -1,
    [TYPE_GENERIC] = -1,
    [TYPE_VOID] = -1,
    [TYPE_ARRAY] = -1,
    [TYPE_FUNCTION] = -1,

    [TYPE_BOOL] = 5,
    [TYPE_BYTE] = 10,
    [TYPE_SHORT] = 20,
    [TYPE_INT] = 30,
    [TYPE_LONG] = 40,
    
    [TYPE_FLOAT] = 50
};

static size_t type_size__[] = {
    [TYPE_UNDEF] = 0,
    [TYPE_VOID] = 0,
    
    [TYPE_BOOL] = 1,
    [TYPE_BYTE] = 1,
    [TYPE_SHORT] = 2,
    [TYPE_INT] = 4,
    [TYPE_LONG] = 8,
    
    [TYPE_FLOAT] = 4,
    [TYPE_ARRAY] = 8,

    [TYPE_FUNCTION] = 8,
    [TYPE_GENERIC] = 8,
};

/**
 *  This variable is used to remember the last type_name that was read
 *  to allow the program to know which type_name it should apply when
 *  it encounters a declarator
 */
const struct type *last_type_name = NULL;
const struct type *last_function_return_type;

/***************************************************/

__attribute__ ((constructor))
static void type_init(void)
{
    INIT_TYPE(undef, UNDEF);
    INIT_TYPE(generic, GENERIC);

    INIT_TYPE(bool, BOOL);
    INIT_TYPE(byte, BYTE);
    INIT_TYPE(short, SHORT);
    INIT_TYPE(int, INT);
    INIT_TYPE(long, LONG);
    
    INIT_TYPE(float, FLOAT);
    INIT_TYPE(void, VOID);
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

static struct type *type_new(enum enum_type et)
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
const struct type *
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

const struct type *type_new_array_type(const struct type *values,
				       const struct expression *array_size)
{
    struct type *ty = type_new(TYPE_ARRAY);

    ty->array_type.values = values;
    ty->array_type.array_size = array_size;
    return ty;
}

const struct type *	// list of symbols (should be type)
type_new_function_type(const struct type *return_value, struct list *argv)
{
    struct type *ty = type_new(TYPE_FUNCTION);
    ty->function_type.return_value = return_value;
    ty->function_type.argv = argv;
    ty->function_type.argc = list_size(argv);
    return ty;
}

static const char *type_arglist(struct list *l);

static const char *str_expression_size(const struct expression *expr)
{
    char *str = "";
    if (expr->expression_type == EXPR_CONSTANT) {
	if (expr->type == type_int) {
	    asprintf(&str, "%d x ", expr->constanti);
	}

	if (expr->type == type_long) {
	    asprintf(&str, "%ld x ", expr->constantl);
	}
    }
    if (expr->expression_type == EXPR_SYMBOL) {
	asprintf(&str, "%s x ", expr->symbol->name);
    }
    if (expr->expression_type == EXPR_UNDEF) {
	return "undef";
    }

    return str;
}

const char *type_printable(const struct type *t)
{
    char *printable = "";

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

    case TYPE_INT:
	printable = "int";
	break;

    case TYPE_FLOAT:
	printable = "float";
	break;
    case TYPE_LONG:
	printable = "long";
	break;

    case TYPE_ARRAY:
	asprintf(&printable, "array<%s%s>",
		 str_expression_size(t->array_type.array_size),
		 type_printable(t->array_type.values));
	break;

    case TYPE_FUNCTION:
	asprintf(&printable, "function (%s) --> %s",
		 type_arglist(t->function_type.argv),
		 type_printable(t->function_type.return_value));
	break;

    default:
	printable = "";
	break;
    }

    return printable;
}

static const char *type_arglist(struct list *l)
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
	struct list *l1 = t1->function_type.argv;
	struct list *l2 = t2->function_type.argv;
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
    return (type == type_byte || type == type_short ||
	    type == type_int || type == type_long || type == type_bool ||
	    type == type_float || type == type_generic);
}

bool type_is_integer(const struct type * type)
{
    return (type == type_bool || type == type_byte || type == type_short ||
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
