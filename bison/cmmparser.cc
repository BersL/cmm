// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Take the name prefix into account.
#define yylex   cmmlex

// First part of user declarations.
#line 5 "bison/cmmsyntax.y" // lalr1.cc:404

	#include <string>
	#include <iostream>
	#include <vector>
	#include <list>
	#include <deque>
	#include "ast.h"

#line 47 "bison/cmmparser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "cmmparser.h"

// User implementation prologue.
#line 102 "bison/cmmsyntax.y" // lalr1.cc:412


#include "cmmdriver.h"
#include "cmmscanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex


#line 73 "bison/cmmparser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace cmm {
#line 159 "bison/cmmparser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (class Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 5: // ID

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.str_value); }
#line 412 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 6: // TYPE

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.str_value); }
#line 419 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 35: // statement

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.statement); }
#line 426 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 36: // specifier

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.specifier); }
#line 433 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 38: // variable_declaration_list

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_dec_list); }
#line 440 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 39: // variable_declaration

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_dec); }
#line 447 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 41: // variable_declaration_stmt_list

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_stmt_list); }
#line 454 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 43: // identifier

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.identfier); }
#line 461 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 45: // parameter_list

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.param_list); }
#line 468 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 46: // parameter_declaration

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.parameter); }
#line 475 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 47: // block

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.block); }
#line 482 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 48: // block_statement_list

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.block_stmt_list); }
#line 489 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 49: // block_statement

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.inblock_stmt); }
#line 496 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 50: // expression

#line 90 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 503 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 51: // argument_list

#line 90 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.node_value); }
#line 510 "bison/cmmparser.cc" // lalr1.cc:617
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 29 "bison/cmmsyntax.y" // lalr1.cc:745
{
    // initialize the initial location object
    yyla.location.begin.filename = yyla.location.end.filename = &driver.streamname;
}

#line 648 "bison/cmmparser.cc" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 3:
#line 121 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		cmm::NStatement *stmt = (cmm::NStatement*)(yystack_[1].value.statement);
		driver.program.statement_list.push_front(stmt);
		(yylhs.value.node_value) = (yystack_[0].value.node_value);
	}
#line 762 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 4:
#line 126 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.node_value) = NULL;
	}
#line 770 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 5:
#line 132 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 778 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 6:
#line 135 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 786 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 7:
#line 138 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 794 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 8:
#line 145 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.specifier) = new cmm::NSpecifier((yystack_[0].value.str_value));
	}
#line 802 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 9:
#line 148 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.specifier) = new cmm::NSpecifier((yystack_[0].value.identfier));
	}
#line 810 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 10:
#line 155 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new cmm::NVariableDecStatement((yystack_[2].value.specifier), (yystack_[1].value.var_dec_list));
	}
#line 818 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 11:
#line 162 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec_list) = new std::deque<cmm::NVariableDeclaration*>;
		(yylhs.value.var_dec_list)->push_front((yystack_[0].value.var_dec));
	}
#line 827 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 12:
#line 166 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.var_dec_list)->push_front((yystack_[2].value.var_dec));
		(yylhs.value.var_dec_list) = (yystack_[0].value.var_dec_list);
	}
#line 836 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 13:
#line 174 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec)->assignmentExp = (yystack_[0].value.expression);
		(yylhs.value.var_dec) = (yystack_[2].value.var_dec);
	}
#line 845 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 14:
#line 178 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = (yystack_[0].value.var_dec);
	}
#line 853 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 15:
#line 185 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[0].value.identfier));
	}
#line 861 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 16:
#line 188 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[3].value.identfier), (yystack_[1].value.int_value));
	}
#line 869 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 17:
#line 191 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[2].value.identfier), (yystack_[0].value.identfier));
	}
#line 877 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 18:
#line 198 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_stmt_list) = new std::deque<cmm::NVariableDecStatement*>;
		(yylhs.value.var_stmt_list)->push_front((cmm::NVariableDecStatement*)(yystack_[0].value.statement));
	}
#line 886 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 19:
#line 202 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.var_stmt_list)->push_front((cmm::NVariableDecStatement*)(yystack_[1].value.statement));
		(yylhs.value.var_stmt_list) = (yystack_[0].value.var_stmt_list);
	}
#line 895 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 20:
#line 210 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new cmm::NStructStatement((yystack_[4].value.identfier), (yystack_[2].value.var_stmt_list));
	}
#line 903 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 21:
#line 217 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.identfier) = new cmm::NIdentifier((yystack_[0].value.str_value));
	}
#line 911 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 22:
#line 224 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new NFunctionDecStatement((yystack_[5].value.specifier), (yystack_[4].value.identfier), (yystack_[2].value.param_list), (yystack_[0].value.block));
	}
#line 919 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 23:
#line 231 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.param_list)->push_front((yystack_[2].value.parameter));
		(yylhs.value.param_list) = (yystack_[0].value.param_list);
	}
#line 928 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 24:
#line 235 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.param_list) = new std::deque<cmm::NFunctionParameter*>;
		(yylhs.value.param_list)->push_front((yystack_[0].value.parameter));
	}
#line 937 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 25:
#line 239 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.param_list) = NULL;
	}
#line 945 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 26:
#line 246 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.parameter) = new NFunctionParameter((yystack_[1].value.specifier), (yystack_[0].value.identfier));
	}
#line 953 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 27:
#line 253 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock((yystack_[2].value.var_stmt_list), (yystack_[1].value.block_stmt_list));
	}
#line 961 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 28:
#line 256 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock((yystack_[1].value.block_stmt_list));
	}
#line 969 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 29:
#line 259 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock();
	}
#line 977 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 30:
#line 265 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.block_stmt_list)->push_front((yystack_[1].value.inblock_stmt));
		(yylhs.value.block_stmt_list) = (yystack_[0].value.block_stmt_list);
	}
#line 986 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 31:
#line 269 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block_stmt_list) = new std::deque<cmm::NInBlockStatement*>;
		(yylhs.value.block_stmt_list)->push_front((yystack_[0].value.inblock_stmt));
	}
#line 995 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 32:
#line 277 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NExpressionStatement((yystack_[1].value.expression));
	}
#line 1003 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 33:
#line 280 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NBlockStatement((yystack_[0].value.block));
	}
#line 1011 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 34:
#line 283 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NReturnStatement((yystack_[1].value.expression));
	}
#line 1019 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 35:
#line 286 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NIfStatement((yystack_[2].value.expression), (yystack_[0].value.inblock_stmt), NULL);
	}
#line 1027 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 36:
#line 289 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NIfStatement((yystack_[4].value.expression), (yystack_[2].value.inblock_stmt), (yystack_[0].value.inblock_stmt));
	}
#line 1035 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 37:
#line 292 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NWhileStatement((yystack_[2].value.expression), (yystack_[0].value.inblock_stmt));
	}
#line 1043 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 54:
#line 314 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.expression) = new NInteger((yystack_[0].value.int_value));
	}
#line 1051 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 55:
#line 317 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.expression) = new NFloat((yystack_[0].value.float_value));
	}
#line 1059 "bison/cmmparser.cc" // lalr1.cc:859
    break;


#line 1063 "bison/cmmparser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -93;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -3,   -93,     3,    26,    27,    -3,     3,   -93,   -93,   -93,
     -93,    -5,   -93,   -93,   -93,    35,    38,    34,   -10,    -2,
     -93,     3,   105,     3,    -2,    48,     3,     3,    -2,    28,
     -93,     0,   -93,   -93,   105,   105,   105,    36,   211,   -93,
       3,    33,    49,    37,   -93,   -93,    53,   240,   211,   172,
      87,   105,   105,   105,   105,   105,   105,   105,   105,     3,
     105,   -93,    43,    -2,   -93,   -93,   -93,   -93,   145,    52,
     223,   211,   232,   232,   240,   211,   211,   211,   -93,   158,
      44,   -93,   -93,   105,   -93,   -93,   -93,   105,    55,    62,
      75,   -93,    58,    75,   118,   -93,   131,   105,   105,    59,
     -93,   -93,   -93,   -93,   185,   198,   -93,    75,    75,    56,
     -93,    75,   -93
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       4,     8,     0,     0,     0,     4,     0,     5,     6,     7,
      21,     9,     1,     2,     3,     0,    11,    14,    15,     0,
      10,     0,     0,     0,    25,     0,     0,     0,    18,     0,
      12,    15,    54,    55,     0,     0,     0,    53,    13,    17,
       0,     0,    24,     0,     9,    19,     0,    47,    48,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,    25,    16,    20,    46,    50,    57,     0,
      38,    41,    42,    43,    44,    45,    39,    40,    52,     0,
       0,    22,    23,     0,    49,    51,    29,     0,     0,     0,
       0,    33,     0,    31,     0,    56,     0,     0,     0,     0,
      28,    30,    32,    34,     0,     0,    27,     0,     0,    35,
      37,     0,    36
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -93,   -93,    80,   -93,     1,     5,    65,   -93,   -93,   -26,
     -93,    18,   -93,    25,   -93,    41,   -53,   -92,   -22,     6
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,     5,    27,    28,    15,    16,    17,    29,
       8,    37,     9,    41,    42,    91,    92,    93,    94,    69
  };

  const unsigned char
  Parser::yytable_[] =
  {
      38,     6,    45,     1,     1,     7,     6,    23,    10,    24,
       7,    25,    47,    48,    49,   109,   110,    23,    19,   112,
      11,    25,     2,    26,    18,    40,    12,    13,    68,    70,
      71,    72,    73,    74,    75,    76,    77,    99,    79,    31,
     101,    39,    20,    22,    44,    31,    21,    32,    33,    10,
       1,    43,    46,    62,    90,    50,    34,    63,    61,    64,
      65,    68,    35,    36,    40,    96,    80,    80,    86,    26,
      87,    88,    84,    89,    97,   104,   105,    78,    32,    33,
      10,    98,   100,   106,   111,    14,    30,    34,    82,    95,
      32,    33,    10,    35,    36,     0,     0,     0,    80,    34,
       0,    87,    88,    81,    89,    35,    36,    67,    32,    33,
      10,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,     0,    35,    36,   102,     0,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,   103,    60,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     0,
       0,     0,    60,    83,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,     0,    60,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,     0,    60,
      85,    51,    52,    53,    54,    55,    56,    57,    58,    59,
       0,     0,    66,    60,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,   107,    60,    51,    52,    53,
      54,    55,    56,    57,    58,    59,     0,     0,   108,    60,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     0,
       0,     0,    60,    52,    53,    54,    55,    56,    57,    58,
      59,     0,    52,     0,    60,    55,    56,    57,    58,    59,
      52,     0,     0,    60,    56,    57,    58,    59,     0,     0,
       0,    60
  };

  const signed char
  Parser::yycheck_[] =
  {
      22,     0,    28,     6,     6,     0,     5,    17,     5,    19,
       5,    21,    34,    35,    36,   107,   108,    17,    23,   111,
       2,    21,    25,    25,     6,    24,     0,     0,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    90,    60,    21,
      93,    23,     7,     9,    26,    27,     8,     3,     4,     5,
       6,     3,    24,    20,    80,    19,    12,     8,    40,    22,
       7,    83,    18,    19,    63,    87,    23,    23,    24,    25,
      26,    27,    20,    29,    19,    97,    98,    59,     3,     4,
       5,    19,    24,    24,    28,     5,    21,    12,    63,    83,
       3,     4,     5,    18,    19,    -1,    -1,    -1,    23,    12,
      -1,    26,    27,    62,    29,    18,    19,    20,     3,     4,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    -1,    18,    19,     7,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,     7,    21,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    21,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    21,
      22,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    20,    21,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    20,    21,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    21,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    21,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    10,    -1,    21,    13,    14,    15,    16,    17,
      10,    -1,    -1,    21,    14,    15,    16,    17,    -1,    -1,
      -1,    21
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,    25,    33,    34,    35,    36,    37,    42,    44,
       5,    43,     0,     0,    34,    38,    39,    40,    43,    23,
       7,     8,     9,    17,    19,    21,    25,    36,    37,    41,
      38,    43,     3,     4,    12,    18,    19,    43,    50,    43,
      36,    45,    46,     3,    43,    41,    24,    50,    50,    50,
      19,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      21,    43,    20,     8,    22,     7,    20,    20,    50,    51,
      50,    50,    50,    50,    50,    50,    50,    50,    43,    50,
      23,    47,    45,     8,    20,    22,    24,    26,    27,    29,
      41,    47,    48,    49,    50,    51,    50,    19,    19,    48,
      24,    48,     7,     7,    50,    50,    24,    20,    20,    49,
      49,    28,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    32,    33,    34,    34,    35,    35,    35,    36,    36,
      37,    38,    38,    39,    39,    40,    40,    40,    41,    41,
      42,    43,    44,    45,    45,    45,    46,    47,    47,    47,
      48,    48,    49,    49,    49,    49,    49,    49,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    51,    51
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,     1,     1,     1,     1,     2,
       3,     1,     3,     3,     1,     1,     4,     3,     1,     2,
       6,     1,     6,     3,     1,     0,     2,     4,     3,     2,
       2,     1,     2,     1,     3,     5,     7,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     4,
       3,     4,     3,     1,     1,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE",
  "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "DOT", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT",
  "RETURN", "IF", "ELSE", "WHILE", "UMINUS", "LOWER_THAN_ELSE", "$accept",
  "program", "statement_list", "statement", "specifier",
  "variable_declaration_statement", "variable_declaration_list",
  "variable_declaration", "variable", "variable_declaration_stmt_list",
  "struct_declaration_statement", "identifier",
  "function_declaration_statement", "parameter_list",
  "parameter_declaration", "block", "block_statement_list",
  "block_statement", "expression", "argument_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   117,   117,   121,   126,   132,   135,   138,   145,   148,
     155,   162,   166,   174,   178,   185,   188,   191,   198,   202,
     210,   217,   224,   231,   235,   239,   246,   253,   256,   259,
     265,   269,   277,   280,   283,   286,   289,   292,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   317,   323,   324
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
    };
    const unsigned int user_token_number_max_ = 286;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // cmm
#line 1586 "bison/cmmparser.cc" // lalr1.cc:1167
#line 327 "bison/cmmsyntax.y" // lalr1.cc:1168


void cmm::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
