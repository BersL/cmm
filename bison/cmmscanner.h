#pragma once

#ifndef YY_DECL
#define YY_DECL	\
	cmm::Parser::token_type	\
	cmm::Scanner::lex(	\
		cmm::Parser::semantic_type* yylval,	\
		cmm::Parser::location_type* yylloc	\
	)
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer CMMFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif
#include "ast.h"
#include "cmmparser.h"


namespace cmm {

class Scanner: public CMMFlexLexer {

public:
	Scanner(std::istream* arg_yyin = 0,
	    std::ostream* arg_yyout = 0);

	virtual ~Scanner();

	virtual Parser::token_type lex(
	Parser::semantic_type* yylval,
	Parser::location_type* yylloc
	);

	void set_debug(bool b);
};


}
