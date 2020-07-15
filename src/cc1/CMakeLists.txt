
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)


BISON_TARGET(
  parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c
  COMPILE_FLAGS --defines=parser.tab.h)
FLEX_TARGET(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

set(
  CC1_SRC
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
  errorc.c
  main.c
  module.c
  function.c
  program.c
  symbol/symbol_table.c
  type/type.c
  type/type_codegen.c
  type/specifier.c
  type/pointer.c
  type/enumerator.c
  type/declarator.c
  type/struct.c
  symbol/symbol.c
  symbol/symbol_codegen.c
  expression/expression.c
  expression/expression_codegen.c
  statement/statement.c
  statement/statement_codegen.c
  constant/string_literal.c
  constant/constant.c
  misc/initializer.c
  )

add_executable(cc1 ${CC1_SRC})
target_link_libraries(cc1 util)
# required because of generated target:
target_include_directories(cc1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
