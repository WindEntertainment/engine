project(wind-language)

set(HEADERS
    ./include/wind/language/language.hpp
    ./include/wind/language/tokenizer.hpp
    ./include/wind/language/lang_impl_def.hpp
    ./include/wind/language/nodes/Node.hpp
    ./include/wind/language/nodes/NodeCRTP.hpp
    ./include/wind/language/nodes/Expression.hpp
    ./include/wind/language/nodes/Value.hpp
    ./include/wind/language/nodes/Identifier.hpp
    ./include/wind/language/nodes/BinaryOperation.hpp
    ./include/wind/language/nodes/UnaryOperation.hpp
    ./include/wind/language/nodes/AssignStatement.hpp
    ./include/wind/language/nodes/VariableStatement.hpp
    ./include/wind/language/nodes/ClassMember.hpp
    ./include/wind/language/nodes/ClassStatement.hpp
    ./include/wind/language/nodes/FunctionArgumentStatement.hpp
    ./include/wind/language/nodes/FunctionStatement.hpp
    ./include/wind/language/nodes/ReturnStatement.hpp
    ./include/wind/language/lang_impl.hpp
)

set(SOURCES
    ./src/language.cpp
    ./src/ast/statement.cpp
    ./src/ast/classes.cpp
    ./src/ast/variable.cpp
    ./src/ast/function.cpp
    ./src/ast/return.cpp
    ./src/ast/functionArguments.cpp
    ./src/ast/assign.cpp
    ./src/ast/expression/expression.cpp
    ./src/ast/expression/binary_priority_0.cpp
    ./src/ast/expression/binary_priority_1.cpp
    ./src/ast/expression/binary_priority_2.cpp
    ./src/ast/expression/binary_priority_3.cpp
    ./src/ast/expression/parentheses.cpp
    ./src/ast/expression/unary.cpp
    ./src/ast/expression/identifier.cpp
    ./src/ast/expression/value.cpp
    ./src/ast/utils.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${HEADERS} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
target_link_libraries(${PROJECT_NAME} PUBLIC wind-utils)