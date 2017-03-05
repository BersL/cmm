
/* write out a header file containing the token defines */
%defines "bison/cmmparser.h"

%{
	#include <string>
	#include <iostream>
	#include <vector>
	#include <list>
	#include <deque>
	#include "ast.h"
	#define yyloc (yyla.location)
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
	double double_value;
	std::string *str_value;
	cmm::Node *node_value;
	cmm::NIdentifier *identfier;
	cmm::NSpecifier *specifier;
	cmm::NVariableDeclaration *var_dec;
	cmm::NStatement *statement;
	cmm::NExpression *expr;
	cmm::NBlock *block;
	cmm::NInBlockStatement *inblock_stmt;

	std::deque<cmm::NVariableDeclaration*> *var_dec_list;
	std::deque<cmm::NVariableDecStatement*> *var_stmt_list;
	std::deque<cmm::NInBlockStatement*> *block_stmt_list;
	std::deque<cmm::NExpression*> *exp_list;
}

%token	END	     0	"end of file"
%token <int_value> INT	"integer literal"
%token <double_value> DOUBLE	"double literal"
%token <str_value> ID "identifier" TYPE "type specifier" VOID "void"
%token GREATER ">" LESS "<" GREATER_OR_EQUAL ">=" LESS_OR_EQUAL "<=" EQUAL "==" NOT_EQUAL "!="
%token AND "&&" OR "||"
%token STRUCT "struct" RETURN "return" IF "if" ELSE "else" WHILE "while"

%type <identfier> identifier
%type <node_value> program statement_list  
%type <statement> statement variable_declaration_statement struct_declaration_statement function_declaration_statement
%type <specifier> specifier
%type <var_dec> variable_declaration variable parameter_declaration
%type <var_dec_list> variable_declaration_list parameter_list
%type <var_stmt_list> variable_declaration_stmt_list
%type <block_stmt_list> block_statement_list
%type <block> block
%type <inblock_stmt> block_statement
%type <expr> expression numberic 
%type <exp_list> argument_list

%destructor { delete $$; } ID TYPE
%destructor { delete $$; } statement variable_declaration_list specifier identifier
%destructor { delete $$; } variable_declaration_stmt_list block_statement_list
%destructor { delete $$; } variable_declaration function_declaration parameter_list parameter_declaration block block_statement
%destructor { delete $$; } block_declaration_list block_declaration block_variable_list block_variable expression argument_list

%right '='
%left OR
%left AND
%left '+' '-'
%left '*' '/'
%left UPLUS UMINUS
%nonassoc '!'
%left '[' ']' '(' ')' '.'
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
		driver.program->statement_list.push_front(stmt);
		$$ = $2;
	}
	| {
		$$ = NULL;
	}
	;

statement :
	variable_declaration_statement {
		$$ = $1;
		$$->loc = $1->loc;
	}
	| struct_declaration_statement {
		$$ = $1;
		$$->loc = $1->loc;
	}
	| function_declaration_statement {
		$$ = $1;
		$$->loc = $1->loc;
	}
	|	error ';'
	// Done
	;

specifier : 
	TYPE {
		$$ = new cmm::NSpecifier($1);
		$$->loc = yyloc;
	}
	| STRUCT identifier {
		$$ = new cmm::NSpecifier($2);
		$$->loc = yyloc;
	}
	// Done
	;

variable_declaration_statement:
	specifier variable_declaration_list ';' {
		$$ = new cmm::NVariableDecStatement($1, $2);
		$$->loc = location($1->loc.begin, yyloc.end);
	}
	// Done
	;

variable_declaration_list :
	variable_declaration {
		$$ = new std::deque<cmm::NVariableDeclaration*>;
		$$->push_front($1);
	}
	|	variable_declaration ',' variable_declaration_list {
		$3->push_front($1);
		$$ = $3;
	}
	// Done
	;

variable_declaration :
	variable '=' expression {
		$$->assignmentExp = $3;
		$$ = $1;
		$$->loc = yyloc;
	}
	|	variable {
		$$ = $1;
		$$->loc = yyloc;
	}
	;
	// Done

variable :
	identifier {
		$$ = new cmm::NVariableDeclaration($1);
	}
	|	identifier '[' INT ']' {
		$$ = new cmm::NVariableDeclaration($1, $3);
	}
	;

variable_declaration_stmt_list :
	variable_declaration_statement variable_declaration_stmt_list {
		$2->push_front((cmm::NVariableDecStatement*)$1);
		$$ = $2;
	}
	|	variable_declaration_statement {
		$$ = new std::deque<cmm::NVariableDecStatement*>;
		$$->push_front((cmm::NVariableDecStatement*)$1);
	}
	// Done
	;

struct_declaration_statement :
	STRUCT identifier '{' variable_declaration_stmt_list '}' ';' {
		$$ = new cmm::NStructStatement($2, $4);
		$$->loc = $2->loc;
	}
	// Done
	;

identifier : 
	ID {
		$$ = new cmm::NIdentifier($1);
		$$->loc = yyloc;
	}
	// Done
	;

function_declaration_statement:
	specifier identifier '(' parameter_list ')' block {
		$$ = new NFunctionDecStatement($1, $2, $4, $6);
		$$->loc = $2->loc;
	}
	| VOID identifier '(' parameter_list ')' block {
		$$ = new NFunctionDecStatement(NULL, $2, $4, $6);
		$$->loc = $2->loc;
	}
	// Done
	;

parameter_list : 
	parameter_declaration ',' parameter_list {
		$3->push_front($1);
		$$ = $3;
	}
	|	parameter_declaration {
		$$ = new std::deque<cmm::NVariableDeclaration*>;
		$$->push_front($1);
	}
	| VOID {
		$$ = NULL;
	}
	| {
		$$ = NULL;
	}
	// Done
	;

parameter_declaration : 
	specifier identifier {
		$$ = new NVariableDeclaration($1, $2);
		$$->loc = yyloc;
	}
	// Done
	;

block : 
	'{' variable_declaration_stmt_list block_statement_list '}' {
		$$ = new NBlock($2, $3);
		$$->loc = yyloc;
	}
	|	'{' block_statement_list '}' {
		$$ = new NBlock($2);
		$$->loc = yyloc;
	}
	|	'{' '}' {
		$$ = new NBlock();
		$$->loc = yyloc;
	}
	;

block_statement_list :	
	block_statement block_statement_list {
		if($1 != NULL)
			$2->push_front($1);
		$$ = $2;
	}
	|	block_statement {
		$$ = new std::deque<cmm::NInBlockStatement*>;
		if($1 != NULL)
			$$->push_front($1);
	}
	;


block_statement :	
	expression ';' {
		$$ = new NExpressionStatement($1);
		$$->loc = yyloc;
	}
	|	block {
		$$ = new NBlockStatement($1);
		$$->loc = yyloc;
	}
	|	RETURN expression ';' {
		$$ = new NReturnStatement($2);
		$$->loc = $2->loc;
	}
	|	RETURN ';' {
		$$ = new NReturnStatement(NULL);
		$$->loc = yyloc;
	}
	|	IF '(' expression ')' block_statement %prec LOWER_THAN_ELSE {
		$$ = new NIfStatement($3, $5, NULL);
		$$->loc = yyloc;
	}
	|	IF '(' expression ')' block_statement ELSE block_statement {
		$$ = new NIfStatement($3, $5, $7);
		$$->loc = yyloc;
	}
	|	WHILE '(' expression ')' block_statement {
		$$ = new NWhileStatement($3, $5);
		$$->loc = yyloc;
	}
	|	';' {
		$$ = NULL;
	}
	|	error ';'
	;

numberic :
	INT {
		$$ = new NLiteral($1);
		$$->loc = yyloc;
	}
	|	DOUBLE {
		$$ = new NLiteral($1);
		$$->loc = yyloc;
	}
	;

expression : 
	expression '=' expression {
		$$ = new NAssignmentExpression($1, $3);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression AND expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::And);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression OR expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Or);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression GREATER expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Greater);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression LESS expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Less);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression GREATER_OR_EQUAL expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::GreaterOrEqual);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression LESS_OR_EQUAL expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::LessOrEqual);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression EQUAL expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Equal);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression NOT_EQUAL expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::NotEqual);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression '+' expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Add);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression '-' expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Sub);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression '*' expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Mul);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	expression '/' expression {
		$$ = new NBinaryExpression($1, $3, cmm::NBinaryExpression::Div);
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	'(' expression ')' {
		$$ = $2;
		$$->loc = $2->loc;
	}
	|	'-' expression %prec UMINUS {
		$$ = new NUnaryExpression($2, cmm::NUnaryExpression::Neg);
		$$->loc = $2->loc;
	}
	|	'+' expression %prec UPLUS {
		$$ = $2;
		$$->loc = $2->loc;
	}
	|	'!' expression {
		$$ = new NUnaryExpression($2, cmm::NUnaryExpression::Not);
		$$->loc = $2->loc;
	}
	|	identifier '(' argument_list ')' {
		$$ = new NFunctionCallExpression($1, $3);
		$$->loc = location($1->loc.begin, yyloc.end);
	}
	|	identifier '(' ')' {
		$$ = new NFunctionCallExpression($1, NULL);
		$$->loc = $1->loc;
	}
	|	numberic {
		$$ = $1;
	}
	|	identifier {
		$$ = new NExpression($1);
		$$->loc = $1->loc;
	}
	|	expression '[' expression ']' {
		if($1->index) {
			if($1->member.empty()) {
				error($3->loc, "multidimensional array is not supported");
			}else{
				error($3->loc, "array in struct is not supported");
			}
			YYERROR;
		}
		$1->index = $3;
		$$ = $1;
		$$->loc = location($1->loc.begin, yyloc.end);;
		// TODO: throw error if index existed
	}
	|	expression '.' identifier {
		$1->member.push_back($3);
		$$ = $1;
		$$->loc = location($1->loc.begin, $3->loc.end);
	}
	|	error ')'
	;

argument_list : 
	expression ',' argument_list {
		$3->push_front($1);
		$$ = $3;
	}
	|	expression {
		$$ = new std::deque<cmm::NExpression*>;
		$$->push_front($1);
	}
	;

%%

void cmm::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}