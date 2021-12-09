%{
#include "AST/ast.hpp"
#include "AST/AstDumper.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"

// My def
#include "AST/IdNode.hpp"
#include "AST/type.hpp"
#include "AST/scalar.h"
#include "AST/operator.hpp"
	
#include <cassert>
#include <errno.h>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

struct LiteralConstantNode {
	VarType *type;
	ConstantValueNode *const_node;
	
	LiteralConstantNode(VarType *type, ConstantValueNode *const_node) : type(type), const_node(const_node) {};
};

extern int32_t line_num;  /* declared in scanner.l */
extern char buffer[];     /* declared in scanner.l */
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */

static AstNode *root;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
	#include <vector>
	#include <string>
    class AstNode;
	class ProgramNode;
	class DeclNode;
	class VariableNode;
	class CompoundStatementNode;
	class ConstantValueNode;
	class IdNode;
	class VarType;
	class LiteralConstantNode;
	class FunctionNode;
	class ExpressionNode;
	class FunctionInvocationNode;
	class VariableReferenceNode;
	enum class Scalar;
	enum class Operator;
}

    /* For yylval */
%union {
    /* basic semantic value */
 	int value;
	double dval;
 	const char *identifier, *text;
	bool bool_type;
    AstNode *node;
	ProgramNode *program_node;
	DeclNode *decl_node;
	LiteralConstantNode *literal_constant;
	CompoundStatementNode *comp_node;
	FunctionNode *func_node;
	ExpressionNode *expr_node;
	FunctionInvocationNode *func_inv_node;
	VariableReferenceNode *var_ref_node;
	std::vector<int> *arr_dim_list;
	std::vector<IdNode*> *id_list;
	std::vector<AstNode*> *node_list;
	std::vector<DeclNode*> *decl_node_list;
	std::vector<CompoundStatementNode*> *comp_node_list;
	std::vector<FunctionNode*> *func_node_list;
	std::vector<ExpressionNode*> *expr_node_list;
	// ConstantValueNode *literal_constant; 
	VarType *var_type;
	Scalar scalar_type;
};

%type <identifier> ProgramName FunctionName 
%type <text> IntegerAndReal StringAndBoolean
%type <bool_type> NegOrNot
%type <var_type> Type ArrType 
%type <scalar_type> ScalarType ReturnType
%type <literal_constant> LiteralConstant
%type <arr_dim_list> ArrDecl
%type <id_list> IdList
%type <decl_node> Declaration FormalArg
%type <node> Simple Condition While For Return FunctionCall
%type <node> Statement  
%type <comp_node> CompoundStatement ElseOrNot 
%type <func_node> Function FunctionDeclaration FunctionDefinition
%type <expr_node> Expression
%type <func_inv_node> FunctionInvocation
%type <var_ref_node> VariableReference
%type <node_list> Statements StatementList
%type <decl_node_list> DeclarationList Declarations FormalArgs FormalArgList
%type <expr_node_list> ExpressionList Expressions ArrRefs ArrRefList 
%type <func_node_list> FunctionList Functions
/* Follow the order in scanner.l */

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY 
%token BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token <text> FALSE TRUE
%token PRINT READ

    /* Identifier */
%token <identifier> ID

    /* Literal */
%token <value> INT_LITERAL
%token <dval> REAL_LITERAL
%token <text> STRING_LITERAL

%%

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
		//debug
		//printf("Program\n");
        root = new ProgramNode(@1.first_line, @1.first_column,
                               $1, "void", $3, $4, $5);
    }
;

ProgramName:
    ID
;

DeclarationList:
    Epsilon {
		$$ = new std::vector<DeclNode*>;
		$$->clear();
		//printf("decl list size %d\n", $$->size());
	}
	|
    Declarations {
		//debug
		//printf("DeclarationList\n");
        $$ = $1;
	}
;

Declarations:
    Declaration {
		//debug
		//printf("Declarations\n");
        std::vector<DeclNode*> *decl = new std::vector<DeclNode*>;
		decl->push_back($1);
		$$ = decl;
	}
    |
    Declarations Declaration {
		$1->push_back($2);
		$$ = $1;
	}
;

FunctionList:
    Epsilon {
 		$$ = new std::vector<FunctionNode*>;
        $$->clear();
	}
    |
    Functions { $$ = $1; }
;

Functions:
    Function {
		std::vector<FunctionNode*> *function = new std::vector<FunctionNode*>;
		function->push_back($1);
		$$ = function;
	}
    |
    Functions Function {
		std::vector<FunctionNode*> *function = $1;
		function->push_back($2);
		$$ = $1;
	}
;

Function:
    FunctionDeclaration { $$ = $1; }
    |
    FunctionDefinition { $$ = $1; }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
		FunctionNode *func_decl = new FunctionNode(@1.first_line, @1.first_column, $1, $3, $5);	
		$$ = func_decl;
	}
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END {
		FunctionNode *func_def = new FunctionNode(@1.first_line, @1.first_column, $1, $3, $5, $6);	
		$$ = func_def;
	}
;

FunctionName:
    ID { $$ = $1; }
;

FormalArgList:
    Epsilon {
		std::vector<DeclNode*> *formal_args = new std::vector<DeclNode*>;
		$$ = formal_args;
	}
    |
    FormalArgs {
		$$ = $1;	
	}
;

FormalArgs:
    FormalArg {
		std::vector<DeclNode*> *formal_args = new std::vector<DeclNode*>;
		formal_args->push_back($1);
		$$ = formal_args;
	}
    |
    FormalArgs SEMICOLON FormalArg {
		std::vector<DeclNode*> *formal_args = $1;
		formal_args->push_back($3);
		$$ = formal_args;
	}
;

FormalArg:
    IdList COLON Type {
        $$ = new DeclNode(@1.first_line, @1.first_column, $1, $3);
	}
;

IdList:
    ID {
		std::vector<IdNode*> *id = new std::vector<IdNode*>;
		IdNode *new_id = new IdNode(@1.first_line, @1.first_column, $1);  
		id->push_back(new_id);
		$$ = id;
	}
    |
    IdList COMMA ID {
		std::vector<IdNode*> *ids = $1;
		IdNode *new_id = new IdNode(@3.first_line, @3.first_column, $3);  
		ids->push_back(new_id);
		$$ = ids;
	}
;

ReturnType:
    COLON ScalarType { $$ = $2; }
    |
    Epsilon { $$ = Scalar::VOID_SC; }
;

    /*
       Data Types and Declarations
                                   */
Declaration:
    VAR IdList COLON Type SEMICOLON {
		//debug
		//printf("Declaration\n");
        $$ = new DeclNode(@1.first_line, @1.first_column,
                                   $2, $4);
	}
	|
    VAR IdList COLON LiteralConstant SEMICOLON {
		$$ = new DeclNode(@1.first_line, @1.first_column,
								   $2, $4->type, $4->const_node);
	}
;

Type:
    ScalarType {
		//debug
		//printf("Type\n");
        VarType *sc_type = new VarType($1);
		$$ = sc_type;
	}
    |
    ArrType {
		$$ = $1;
	}
;

ScalarType:
    INTEGER { 
		//debug
		//printf("ScalarType\n");
        $$ = Scalar::INTEGER_SC; }
    |
    REAL { $$ = Scalar::REAL_SC; }
    |
    STRING { $$ = Scalar::STRING_SC; }
    |
    BOOLEAN { $$ = Scalar::BOOLEAN_SC; }
;

ArrType:
    ArrDecl ScalarType {
		VarType *arr_type = new VarType($2, $1);
		$$ = arr_type;
	}
;

ArrDecl:
    ARRAY INT_LITERAL OF {
		std::vector<int> *arr_dim = new std::vector<int>;
		arr_dim->push_back($2);
		$$ = arr_dim;
	}
    |
    ArrDecl ARRAY INT_LITERAL OF  {
//		std::vector<int> *arr_dim = new std::vector<int>;
		$1->push_back($3);
		$$ = $1;
	}
;

LiteralConstant:
    NegOrNot INT_LITERAL {
		// literalconstantnode: type / constantnode
		VarType *lit_type = new VarType(Scalar::INTEGER_SC);
		ConstantValueNode *const_node; 
		if($1) {
			// negative
			const_node = new ConstantValueNode(@2.first_line, @2.first_column-1, uint32_t(-$2));
		}
		else {
			const_node = new ConstantValueNode(@2.first_line, @2.first_column, uint32_t($2));
		}

		LiteralConstantNode *lit_node = new LiteralConstantNode(lit_type, const_node);
		$$ = lit_node;
	}
    |
    NegOrNot REAL_LITERAL {
		VarType *lit_type = new VarType(Scalar::REAL_SC);
		ConstantValueNode *const_node; 
		if ($1) {
			const_node = new ConstantValueNode(@2.first_line, @2.first_column - 1, double(-$2));
		} else {
			const_node = new ConstantValueNode(@2.first_line, @2.first_column, double($2));
		}
		LiteralConstantNode *lit_node = new LiteralConstantNode(lit_type, const_node);
		$$ = lit_node;
	}
    |
    StringAndBoolean {
		VarType *lit_type;
		if (!strcmp($1, "true") || !strcmp($1, "false")) 
			lit_type = new VarType(Scalar::BOOLEAN_SC);
		else 
			lit_type = new VarType(Scalar::STRING_SC);
		ConstantValueNode *const_node = new ConstantValueNode(@1.first_line, @1.first_column, $1);
		LiteralConstantNode *lit_node = new LiteralConstantNode(lit_type, const_node);
		$$ = lit_node;
	}
;

NegOrNot:
    Epsilon { $$ = false; }
    |
    MINUS %prec UNARY_MINUS { $$ = true; }
;

StringAndBoolean:
    STRING_LITERAL { $$ = $1; }
    |
    TRUE { $$ = $1; }  
    |
    FALSE { $$ = $1; } 
;

IntegerAndReal:
    INT_LITERAL { $$ = std::to_string($1).c_str(); }
	|
    REAL_LITERAL { $$ = std::to_string($1).c_str(); }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement {
		//printf("find Statement!\n");
		$$ = $1;
	}
    |
    Simple {
		$$ = $1;
	}
    |
    Condition  {
		$$ = $1;
	}
    |
    While {
		$$ = $1;
	}
    |
    For {
		$$ = $1;
	}
    |
    Return {
		$$ = $1;
	}
    |
    FunctionCall {
		$$ = $1;
	}
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
		// for debug
		//printf("found compoundstatement! \n");
		$$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3);
	}
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON {
		$$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3);
	}
    |
    PRINT Expression SEMICOLON {
		$$ = new PrintNode(@1.first_line, @1.first_column, $2);
	}
    |
    READ VariableReference SEMICOLON {
		$$ = new ReadNode(@1.first_line, @1.first_column, $2);
	}
;

VariableReference:
    ID ArrRefList { $$ = new VariableReferenceNode(@1.first_line, @1.first_column, $1, $2); }
;

ArrRefList:
    Epsilon { $$ = new std::vector<ExpressionNode*>; }	
    |
    ArrRefs { $$ = $1; }
;

ArrRefs:
    L_BRACKET Expression R_BRACKET {
		std::vector<ExpressionNode*> *arr_dim = new std::vector<ExpressionNode*>;
		arr_dim->push_back($2);
		$$ = arr_dim;
	
	}	
    |
    ArrRefs L_BRACKET Expression R_BRACKET {
		$1->push_back($3);
		$$ = $1;	
	}	
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF {
		$$ = new IfNode(@1.first_line, @1.first_column, $2, $4, $5);
	}
;

ElseOrNot:
    ELSE
    CompoundStatement { $$ = $2; }
    |
    Epsilon { $$ = NULL; }
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO {
		$$ = new WhileNode(@1.first_line, @1.first_column, $2, $4);
	}
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO {
		std::vector<IdNode*> *ids = new std::vector<IdNode*>; 
		IdNode *id = new IdNode(@2.first_line, @2.first_column, $2);
		ids->push_back(id);
		std::vector<int> *array_dim = new std::vector<int>;
		VarType *id_type = new VarType(Scalar::INTEGER_SC, array_dim);
		DeclNode *loop_var = new DeclNode(@2.first_line, @2.first_column, ids, id_type);
		VariableReferenceNode *var_ref = new VariableReferenceNode(@2.first_line, @2.first_column, $2);
		ExpressionNode *init_val = new ConstantValueNode(@4.first_line, @4.first_column, uint32_t($4));
		AssignmentNode *init_stmt = new AssignmentNode(@3.first_line, @3.first_column, var_ref, init_val);
		ConstantValueNode *cond = new ConstantValueNode(@6.first_line, @6.first_column, uint32_t($6));

		$$ = new ForNode(@1.first_line, @1.first_column, loop_var, init_stmt, cond, $8);
	}
;

Return:
    RETURN Expression SEMICOLON
;

FunctionCall:
    FunctionInvocation SEMICOLON
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
		$$ = new FunctionInvocationNode(@1.first_line, @1.first_column, $1, $3);
	}
;

ExpressionList:
    Epsilon { $$ = new std::vector<ExpressionNode*>; }
    |
    Expressions { $$ = $1; }
;

Expressions:
    Expression {
		$$ = new std::vector<ExpressionNode*>;
		$$->push_back($1);
	}
    |
    Expressions COMMA Expression {
		$1->push_back($3);
		$$ = $1;
	}
;

StatementList:
    Epsilon {
		// for debug
		//printf("found epsilon statementlist\n");
		$$ = new std::vector<AstNode*>;
        $$->clear();
	}
    |
    Statements {
		$$ = $1;
	}
;

Statements:
    Statement {
		std::vector<AstNode*> *statements = new std::vector<AstNode*>;
		statements->push_back($1);
		$$ = statements;
	}
    |
    Statements Statement {
		std::vector<AstNode*> *statements = $1;
		statements->push_back($2);
		$$ = $1;
	}
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS { $$ = $2; } 
	|
    MINUS Expression %prec UNARY_MINUS { 
		$$ = new UnaryOperatorNode(@1.first_line, @1.first_column, Operator::UNARY_MINUS, $2);
	}
	|
    Expression MULTIPLY Expression { 
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::MULTIPLY, $1, $3);
   	}
    |
    Expression DIVIDE Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::DIVIDE, $1, $3);
	}
    |
    Expression MOD Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::MOD, $1, $3);
	}
    |
    Expression PLUS Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::PLUS, $1, $3);
	}
    |
    Expression MINUS Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::MINUS, $1, $3);
	}
    |
    Expression LESS Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::LESS, $1, $3);
	}
    |
    Expression LESS_OR_EQUAL Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::LESS_OR_EQUAL, $1, $3);
	}
    |
    Expression GREATER Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::GREATER, $1, $3);
	}
    |
    Expression GREATER_OR_EQUAL Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::GREATER_OR_EQUAL, $1, $3);
	}
    |
    Expression EQUAL Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::EQUAL, $1, $3);
	}
    |
    Expression NOT_EQUAL Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::NOT_EQUAL, $1, $3);
	}
    |
    NOT Expression {
		$$ = new UnaryOperatorNode(@1.first_line, @1.first_column, Operator::NOT, $2);
	}
    |
    Expression AND Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::AND, $1, $3);
	}
    |
    Expression OR Expression {
		$$ = new BinaryOperatorNode(@2.first_line, @2.first_column, Operator::OR, $1, $3);
	}
    |
    IntegerAndReal {
		$$ = new ConstantValueNode(@1.first_line, @1.first_column, $1);
	}
	|
    StringAndBoolean {
		$$ = new ConstantValueNode(@1.first_line, @1.first_column, $1);
	}
	|
    VariableReference
    |
    FunctionInvocation
;

    /*
       misc
            */
Epsilon:
;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        perror("fopen() failed:");
    }

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        // root->print();
        AstDumper astdump;
		//debug
		//printf("About to accept\n");
		root->accept(astdump);
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
