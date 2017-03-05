%{
	#include <iostream>
	#include <cstring>
	#include <string>
	#include "cmmscanner.h"
	#ifdef TOKEN_DEBUG
	#define OUTPUT_TOKEN(TYPE, value) \
			std::cout<<"Recognize "#TYPE" "<<(value)<<std::endl
	#else
	#define OUTPUT_TOKEN(TYPE, value)  
	#endif
	#define yyterminate() return token::END
	
	typedef cmm::Parser::token token;
	typedef cmm::Parser::token_type token_type;
%}
%option prefix="CMM"
%option c++
%option noyywrap
%option yylineno
%option debug
%option stack

%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

DEC (([1-9][0-9]+)|[0-9])
OCT 0[1-7][0-7]*
HEX 0[xX](([1-9a-fA-F][0-9a-fA-F]+)|[0-9a-fA-F])
EXP [0-9]+([0-9.]*)?([Ee][+-]?[0-9]+)?
DOUBLE {DEC}\.[0-9]+
ID [a-zA-Z_][[:alnum:]_]{0,31}
AND &&
OR \|\|
TYPE int|double
STRUCT struct
RETURN return
VOID void
IF if
ELSE else
WHILE while
COMMENT \/\/.*
COMMENT2 \/\*([^*]*\*[^/])*[^*]*\*\/

%%
%{
    // reset location
    yylloc->step();
%}
{COMMENT} /*Discard*/
{COMMENT2} /*Discard*/
{TYPE} { 
	yylval->str_value = new std::string(yytext);
	OUTPUT_TOKEN(TYPE, *(yylval->str_value)); 
	return token::TYPE;
}
{IF} { OUTPUT_TOKEN(IF, ""); return token::IF; }
{ELSE} { OUTPUT_TOKEN(ELSE, ""); return token::ELSE; }
{WHILE} { OUTPUT_TOKEN(WHILE, ""); return token::WHILE; }
{RETURN} { OUTPUT_TOKEN(RETURN, ""); return token::RETURN; }
{STRUCT} { OUTPUT_TOKEN(STRUCT, ""); return token::STRUCT; }
{VOID} { OUTPUT_TOKEN(VOID, ""); return token::VOID; }
{DEC} {
	int value = atoi(yytext);
	OUTPUT_TOKEN(INT, value);
	yylval->int_value = value;
	return token::INT;
}
{OCT} {
	int value = strtol(yytext, NULL, 8);
	OUTPUT_TOKEN(INT, value);
	yylval->int_value = value;
	return token::INT;
}
{HEX} {
	int value = strtol(yytext, NULL, 16);
	OUTPUT_TOKEN(INT, value);
	yylval->int_value = value;
	return token::INT;
}
{DOUBLE} {
	double value = atof(yytext);
	OUTPUT_TOKEN(DOUBLE, value);
	yylval->double_value = value;
	return token::DOUBLE;
}
{EXP} {
	double value = strtod(yytext, NULL);
	OUTPUT_TOKEN(DOUBLE, value);
	yylval->double_value = value;
	return token::DOUBLE;
}
{ID} {
	yylval->str_value = new std::string(yytext);
	OUTPUT_TOKEN(ID, *(yylval->str_value));
	return token::ID;
}
[=][=] { OUTPUT_TOKEN(EQUAL, ""); return token::EQUAL; }
[!][=] { OUTPUT_TOKEN(NOT_EQUAL, ""); return token::NOT_EQUAL; }
[>] { OUTPUT_TOKEN(GREATER, ""); return token::GREATER; }
[<] { OUTPUT_TOKEN(LESS, ""); return token::LESS; }
[>][=] { OUTPUT_TOKEN(GREATER_OR_EQUAL, ""); return token::GREATER; }
[<][=] { OUTPUT_TOKEN(LESS_OR_EQUAL, ""); return token::LESS_OR_EQUAL; }
{AND} { OUTPUT_TOKEN(AND, ""); return token::AND; }
{OR} { OUTPUT_TOKEN(OR, ""); return token::OR; }
[;,=.!] { return static_cast<token_type>(*yytext); }
[\+\-\*\/] {  return static_cast<token_type>(*yytext); }
[\(\)\{\}\[\]] {  return static_cast<token_type>(*yytext); }

[ \t\r]+ {
    yylloc->step();
}
\n {
    yylloc->lines(yyleng); yylloc->step();
}
. { 
	std::cout<<"\033[1;31mToken Recognize Error at Line "<<yylineno
			 <<":\033[0m Unknown Token: \'"<<yytext<<"\'"<<std::endl; 
	yyterminate(); 
}

%%

namespace cmm {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : CMMFlexLexer(in, out) {
}

Scanner::~Scanner(){
}

void Scanner::set_debug(bool b){
    yy_flex_debug = b;
}

}


#ifdef yylex
#undef yylex
#endif

int CMMFlexLexer::yylex()
{
	std::cerr << "in CMFlexLexer::yylex() !" << std::endl;
    return 0;
}
