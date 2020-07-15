
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(
  parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)
FLEX_TARGET(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

set(
  CC1_SRC
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
  codegen.h
  errorc.c errorc.h
  main.c
  function.c function.h
  module.c module.h
  program.c program.h
  scanner.h

  constant/constant.c
  constant/constant.h
  constant/string_literal.c
  constant/string_literal.h

  expression/expression.c
  expression/expression.h
  expression/expression_check.h
  expression/expression_codegen.c
  expression/expression_codegen.h

  misc/initializer.c
  misc/initializer.h

  statement/statement.c
  statement/statement.h
  statement/statement_codegen.c
  statement/statement_codegen.h

  symbol/symbol_table.c
  symbol/symbol_table.h
  symbol/symbol.c
  symbol/symbol.h
  symbol/symbol_codegen.c

  type/declarator.c
  type/declarator.h
  type/enumerator.c
  type/enumerator.h
  type/pointer.c
  type/pointer.h
  type/specifier.c
  type/specifier.h
  type/storage_class.h
  type/struct.c
  type/struct.h
  type/type.c
  type/type.h
  type/type_codegen.c

  )

add_executable(cc1 ${CC1_SRC})
target_link_libraries(cc1 util)
target_include_directories(cc1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR} # for header included by generated C files
  ${CMAKE_CURRENT_BINARY_DIR} # for parser.tab.h
  )
