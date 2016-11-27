
/* write out a header file containing the token defines */
%defines "include/cmmparser.h"

%{
	#include <string>
	#include <iostream>
	#include <vector>
	#include <list>
	#include <deque>
	#include "ast.h"
%}


%debug

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix "cmm"

/* set the parser's class identifier */
%define "parser_class_name" {Parser}

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

%union {
	int int_value;
	float float_value;
	std::string *str_value;
	cmm::Node *node_value;
	cmm::NIdentifier *identfier;
	cmm::NSpecifier *specifier;
	cmm::NVariableDeclaration *var_dec;
	cmm::NStatement *statement;
	cmm::NExpression *expression;
	cmm::NFunctionParameter *parameter;
	cmm::NBlock *block;
	cmm::NInBlockStatement *inblock_stmt;

	std::deque<cmm::NVariableDeclaration*> *var_dec_list;
	std::deque<cmm::NVariableDecStatement*> *var_stmt_list;
	std::deque<cmm::NInBlockStatement*> *block_stmt_list;
	std::deque<cmm::NFunctionParameter*> *param_list;
}

%token	END	     0	"end of file"
%token <int_value> INT
%token <float_value> FLOAT
%token <str_value> ID TYPE
%token SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT
%token LP RP LB RB LC RC
%token STRUCT RETURN IF ELSE WHILE

%type <identfier> identifier
%type <node_value> program statement_list  
%type <statement> statement variable_declaration_statement struct_declaration_statement function_declaration_statement
%type <specifier> specifier
%type <var_dec> variable_declaration variable
%type <var_dec_list> variable_declaration_list
%type <var_stmt_list> variable_declaration_stmt_list
%type <block_stmt_list> block_statement_list
%type <parameter> parameter_declaration
%type <param_list> parameter_list
%type <block> block
%type <inblock_stmt> block_statement

%type <expression> expression 
%type <node_value> argument_list

%destructor { delete $$; } ID TYPE
%destructor { delete $$; } statement variable_declaration_list specifier identifier
%destructor { delete $$; } variable_declaration_stmt_list block_statement_list
%destructor { delete $$; } variable_declaration function_declaration parameter_list parameter_declaration block block_statement
%destructor { delete $$; } block_declaration_list block_declaration block_variable_list block_variable expression argument_list

%left ASSIGNOP
%left PLUS MINUS
%left STAR
%left UMINUS

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start program

%{

#include "cmmdriver.h"
#include "cmmscanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%%
program	: 
	statement_list END
	;

statement_list : 
	statement statement_list {
		cmm::NStatement *stmt = (cmm::NStatement*)$1;
		driver.program.statement_list.push_front(stmt);
		$$ = $2;
	}
	| {
		$$ = NULL;
	}
	;

statement :
	variable_declaration_statement {
		$$ = $1;
	}
	| struct_declaration_statement {
		$$ = $1;
	}
	| function_declaration_statement {
		$$ = $1;
	}
	// Done
	;

specifier : 
	TYPE {
		$$ = new cmm::NSpecifier($1);
	}
	| STRUCT identifier {
		$$ = new cmm::NSpecifier($2);
	}
	// Done
	;

variable_declaration_statement:
	specifier variable_declaration_list SEMI {
		$$ = new cmm::NVariableDecStatement($1, $2);
	}
	// Done
	;

variable_declaration_list :
	variable_declaration {
		$$ = new std::deque<cmm::NVariableDeclaration*>;
		$$->push_front($1);
	}
	|	variable_declaration COMMA variable_declaration_list {
		$3->push_front($1);
		$$ = $3;
	}
	// Done
	;

variable_declaration :
	variable ASSIGNOP expression {
		$$->assignmentExp = $3;
		$$ = $1;
	}
	|	variable {
		$$ = $1;
	}
	;
	// Done

variable :
	identifier {
		$$ = new cmm::NVariableDeclaration($1);
	}
	|	identifier LB INT RB {
		$$ = new cmm::NVariableDeclaration($1, $3);
	}
	|	identifier DOT identifier {
		$$ = new cmm::NVariableDeclaration($1, $3);
	}
	// Done
	;

variable_declaration_stmt_list :
	variable_declaration_statement {
		$$ = new std::deque<cmm::NVariableDecStatement*>;
		$$->push_front((cmm::NVariableDecStatement*)$1);
	}
	| variable_declaration_statement variable_declaration_stmt_list {
		$2->push_front((cmm::NVariableDecStatement*)$1);
		$$ = $2;
	}
	// Done
	;

struct_declaration_statement :
	STRUCT identifier LC variable_declaration_stmt_list RC SEMI {
		$$ = new cmm::NStructStatement($2, $4);
	}
	// Done.
	;

identifier : 
	ID {
		$$ = new cmm::NIdentifier($1);
	}
	// Done
	;

function_declaration_statement:
	specifier identifier LP parameter_list RP block {
		$$ = new NFunctionDecStatement($1, $2, $4, $6);
	}
	// Done
	;

parameter_list : 
	parameter_declaration COMMA parameter_list {
		$3->push_front($1);
		$$ = $3;
	}
	|	parameter_declaration {
		$$ = new std::deque<cmm::NFunctionParameter*>;
		$$->push_front($1);
	}
	| {
		$$ = NULL;
	}
	// Done
	;

parameter_declaration : 
	specifier identifier {
		$$ = new NFunctionParameter($1, $2);
	}
	// Done
	;

block : 
	LC variable_declaration_stmt_list block_statement_list RC {
		$$ = new NBlock($2, $3);
	}
	|	LC block_statement_list RC {
		$$ = new NBlock($2);
	}
	|	LC RC {
		$$ = new NBlock();
	}
	;

block_statement_list :	
	block_statement block_statement_list {
		$2->push_front($1);
		$$ = $2;
	}
	|	block_statement {
		$$ = new std::deque<cmm::NInBlockStatement*>;
		$$->push_front($1);
	}
	;


block_statement :	
	expression SEMI {
		$$ = new NExpressionStatement($1);
	}
	|	block {
		$$ = new NBlockStatement($1);
	}
	|	RETURN expression SEMI {
		$$ = new NReturnStatement($2);
	}
	|	IF LP expression RP block_statement %prec LOWER_THAN_ELSE {
		$$ = new NIfStatement($3, $5, NULL);
	}
	|	IF LP expression RP block_statement ELSE block_statement {
		$$ = new NIfStatement($3, $5, $7);
	}
	|	WHILE LP expression RP block_statement {
		$$ = new NWhileStatement($3, $5);
	}
	;

expression : 
	expression ASSIGNOP expression
	|	expression AND expression
	|	expression OR expression
	|	expression RELOP expression
	|	expression PLUS expression
	|	expression MINUS expression
	|	expression STAR expression
	|	expression DIV expression
	|	LP expression RP
	|	MINUS expression %prec UMINUS
	|	NOT expression
	|	identifier LP argument_list RP
	|	identifier LP RP
	|	expression LB expression RB
	|	expression DOT identifier
	|	identifier
	|	INT {
		$$ = new NInteger($1);
	}
	|	FLOAT {
		$$ = new NFloat($1);
	}
	;

argument_list : 
	expression COMMA argument_list
	|	expression
	;

%%

void cmm::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}