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
	class FunctionNode;
	class CompoundStatementNode;
	class ConstantValueNode;
	class IdNode;
	class VarType;
	class LiteralConstantNode;
	enum class Scalar;
}

    /* For yylval */
%union {
    /* basic semantic value */
 	int value;
	double dval;
 	char *identifier, *text;
	bool bool_type;
    AstNode *node;
	ProgramNode *program_node;
	DeclNode *decl_node;
	LiteralConstantNode *literal_constant;
	std::vector<int> *arr_dim_list;
	std::vector<IdNode*> *id_list;
	std::vector<AstNode*> *node_list;
	std::vector<DeclNode*> *decl_node_list;
	std::vector<FunctionNode*> *function_node_list;
	CompoundStatementNode *compound_statement_node;
	// ConstantValueNode *literal_constant; 
	VarType *var_type;
	Scalar scalar_type;
};

%type <identifier> ProgramName 
%type <text> StringAndBoolean
%type <bool_type> NegOrNot
%type <var_type> Type ArrType 
%type <scalar_type> ScalarType 
%type <node> Statement Simple Condition While For Return FunctionCall
%type <arr_dim_list> ArrDecl
%type <id_list> IdList
%type <node_list> Statements StatementList
%type <decl_node> Declaration
%type <decl_node_list> DeclarationList Declarations
%type <function_node_list> FunctionList
%type <compound_statement_node> CompoundStatement
%type <literal_constant> LiteralConstant
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
        //free($3);
        //free($4);
        //free($5);
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
		//free($$);
	}
	|
    Declarations {
		//debug
		//printf("DeclarationList\n");
        $$ = $1;
		//free($$);
		//free($1);
	}
;

Declarations:
    Declaration {
		//debug
		//printf("Declarations\n");
        std::vector<DeclNode*> *decl = new std::vector<DeclNode*>;
		decl->push_back($1);
		$$ = decl;
		//free($$);
		//free($1);
	}
    |
    Declarations Declaration {
		$1->push_back($2);
		$$ = $1;
		//free($$);
		//free($1);
		//free($2);
	}
;

FunctionList:
    Epsilon {
 		$$ = new std::vector<FunctionNode*>;
        $$->clear();
	}
    |
    Functions
;

Functions:
    Function
    |
    Functions Function
;

Function:
    FunctionDeclaration
    |
    FunctionDefinition
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon
    |
    FormalArgs
;

FormalArgs:
    FormalArg
    |
    FormalArgs SEMICOLON FormalArg
;

FormalArg:
    IdList COLON Type
;

IdList:
    ID {
		std::vector<IdNode*> *id = new std::vector<IdNode*>;
		IdNode *new_id = new IdNode(@1.first_line, @1.first_column, $1);  
		id->push_back(new_id);
		$$ = id;
		//free($$);
		//free($1);
	}
    |
    IdList COMMA ID {
		// TODO: record the location of id
		std::vector<IdNode*> *ids = $1;
		IdNode *new_id = new IdNode(@3.first_line, @3.first_column, $3);  
		ids->push_back(new_id);
		$$ = ids;
		//free($$);
		//free($1);
		//free($3);
	}
;

ReturnType:
    COLON ScalarType
    |
    Epsilon
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
		//free($$);
		//free($2);
		//free($4);
	}
	|
    VAR IdList COLON LiteralConstant SEMICOLON {
		$$ = new DeclNode(@1.first_line, @1.first_column,
								   $2, $4->type, $4->const_node);
		//free($$);
		//free($2);
		//free($4);
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
		//uint32_t val = $1 ? -$2: $2;
		//const_node = new ConstantValueNode(@2.first_line, @2.first_column, val);
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
		//double d_val = $1 ? -$2 : $2;
		//const_node = new ConstantValueNode(@2.first_line, @2.first_column, d_val);
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
		//if ($1 == "true" || $1 == "false") 
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
    INT_LITERAL
    |
    REAL_LITERAL
;

    /*
       Statements
                  */

Statement:
    CompoundStatement {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    Simple {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    Condition  {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    While {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    For {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    Return {
		$$ = $1;
		//free($$);	
		//free($1);	
	}
    |
    FunctionCall {
		$$ = $1;
		//nfree($$);	
		//free($1);	
	}
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
		$$ = new CompoundStatementNode(@1.first_line, @1.first_column,$2, $3);
		//free($$);
		//free($2);
		//free($3);
	}
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON
    |
    PRINT Expression SEMICOLON
    |
    READ VariableReference SEMICOLON
;

VariableReference:
    ID ArrRefList
;

ArrRefList:
    Epsilon
    |
    ArrRefs
;

ArrRefs:
    L_BRACKET Expression R_BRACKET
    |
    ArrRefs L_BRACKET Expression R_BRACKET
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF
;

ElseOrNot:
    ELSE
    CompoundStatement
    |
    Epsilon
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO
;

Return:
    RETURN Expression SEMICOLON
;

FunctionCall:
    FunctionInvocation SEMICOLON
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS
;

ExpressionList:
    Epsilon
    |
    Expressions
;

Expressions:
    Expression
    |
    Expressions COMMA Expression
;

StatementList:
    Epsilon {
		$$ = new std::vector<AstNode*>;
		//free($$);
	}
    |
    Statements {
		$$ = $1;
		//free($$);
		//free($1);
	}
;

Statements:
    Statement {
		std::vector<AstNode*> *statements = new std::vector<AstNode*>;
		statements->push_back($1);
		//free($$);
		//free($1);
	}
    |
    Statements Statement {
		$1->push_back($2);
		$$ = $1;
		//free($$);
		//free($1);
		//free($2);
	}
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS
    |
    MINUS Expression %prec UNARY_MINUS
    |
    Expression MULTIPLY Expression
    |
    Expression DIVIDE Expression
    |
    Expression MOD Expression
    |
    Expression PLUS Expression
    |
    Expression MINUS Expression
    |
    Expression LESS Expression
    |
    Expression LESS_OR_EQUAL Expression
    |
    Expression GREATER Expression
    |
    Expression GREATER_OR_EQUAL Expression
    |
    Expression EQUAL Expression
    |
    Expression NOT_EQUAL Expression
    |
    NOT Expression
    |
    Expression AND Expression
    |
    Expression OR Expression
    |
    IntegerAndReal
    |
    StringAndBoolean
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
