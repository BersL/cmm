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

SIGN [+-]?
DEC {SIGN}(([1-9][0-9]+)|[0-9])
OCT {SIGN}0[1-7][0-7]*
HEX {SIGN}0[xX](([1-9a-fA-F][0-9a-fA-F]+)|[0-9a-fA-F])
EXP {SIGN}[0-9]+([0-9.]*)?([Ee][+-]?[0-9]+)?
FLOAT {DEC}\.[0-9]+
ID [a-zA-Z_][[:alnum:]_]{0,31}
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|!=|==
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT \!
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
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
{FLOAT} {
	float value = atof(yytext);
	OUTPUT_TOKEN(FLOAT, value);
	yylval->float_value = value;
	return token::FLOAT;
}
{EXP} {
	float value = strtof(yytext, NULL);
	OUTPUT_TOKEN(FLOAT, value);
	yylval->float_value = value;
	return token::FLOAT;
}
{ID} {
	yylval->str_value = new std::string(yytext);
	OUTPUT_TOKEN(ID, *(yylval->str_value));
	return token::ID;
}
{RELOP} { OUTPUT_TOKEN(RELOP, ""); return token::RELOP; }
{AND} { OUTPUT_TOKEN(AND, ""); return token::AND; }
{OR} { OUTPUT_TOKEN(OR, ""); return token::OR; }
{ASSIGNOP} { OUTPUT_TOKEN(ASSIGNOP, ""); return token::ASSIGNOP; }
{SEMI} { OUTPUT_TOKEN(SEMI, ""); return token::SEMI; }
{COMMA} { OUTPUT_TOKEN(COMMA, ""); return token::COMMA; }
{PLUS} { OUTPUT_TOKEN(PLUS, ""); return token::PLUS; }
{MINUS} { OUTPUT_TOKEN(MINUS, ""); return token::MINUS; }
{STAR} { OUTPUT_TOKEN(STAR, ""); return token::STAR; }
{DIV} { OUTPUT_TOKEN(DIV, ""); return token::DIV; }
{DOT} { OUTPUT_TOKEN(DOT, ""); return token::DOT; }
{NOT} { OUTPUT_TOKEN(NOT, ""); return token::NOT; }
{LP} { OUTPUT_TOKEN(LP, ""); return token::LP; }
{RP} { OUTPUT_TOKEN(RP, ""); return token::RP; }
{LB} { OUTPUT_TOKEN(LB, ""); return token::LB; }
{RB} { OUTPUT_TOKEN(RB, ""); return token::RB; }
{LC} { OUTPUT_TOKEN(LC, ""); return token::LC; }
{RC} { OUTPUT_TOKEN(RC, ""); return token::RC; }

[ \t\r]+ {
    yylloc->step();
}
\n {
    yylloc->lines(yyleng); yylloc->step();
}
. { 
	std::cout<<"\033[1;31mToken Recognize Error at Line :\033[0m"<<yylineno
			 <<": Unknown Token: \'"<<yytext<<"\'"<<std::endl; 
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
