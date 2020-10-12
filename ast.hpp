#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
//#include "ast/ast_functions.hpp"
#include "ast/scope.hpp"
#include "ast/program.hpp"
#include "ast/statement.hpp"
#include "ast/variableDeclaration.hpp"
#include "ast/functionDeclaration.hpp"
#include "ast/functionDefinition.hpp"
#include "ast/parameterList.hpp"
#include "ast/statementList.hpp"
#include "ast/whileLoop.hpp"
#include "ast/forLoop.hpp"
#include "ast/concreteParameterList.hpp"
#include "ast/arrayDeclaration.hpp"
#include "ast/caseList.hpp"
#include "ast/caseNode.hpp"
#include "ast/switchStatement.hpp"
#include "ast/enumerationSpecifier.hpp"
#include "ast/enumeratorList.hpp"
#include "ast/enumerator.hpp"


extern Program *parseAST(char* inputPath);

#endif
