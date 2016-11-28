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
#line 101 "bison/cmmsyntax.y" // lalr1.cc:412


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

#line 85 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.str_value); }
#line 412 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 6: // TYPE

#line 85 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.str_value); }
#line 419 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 36: // statement

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.statement); }
#line 426 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 37: // specifier

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.specifier); }
#line 433 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 39: // variable_declaration_list

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_dec_list); }
#line 440 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 40: // variable_declaration

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_dec); }
#line 447 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 42: // variable_declaration_stmt_list

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.var_stmt_list); }
#line 454 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 44: // identifier

#line 86 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.identfier); }
#line 461 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 46: // parameter_list

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.param_list); }
#line 468 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 47: // parameter_declaration

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.parameter); }
#line 475 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 48: // block

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.block); }
#line 482 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 49: // block_statement_list

#line 87 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.block_stmt_list); }
#line 489 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 50: // block_statement

#line 88 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.inblock_stmt); }
#line 496 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 51: // expression

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
        { delete (yysym.value.expression); }
#line 503 "bison/cmmparser.cc" // lalr1.cc:617
        break;

      case 52: // argument_list

#line 89 "bison/cmmsyntax.y" // lalr1.cc:617
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
#line 120 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		cmm::NStatement *stmt = (cmm::NStatement*)(yystack_[1].value.statement);
		driver.program.statement_list.push_front(stmt);
		(yylhs.value.node_value) = (yystack_[0].value.node_value);
	}
#line 762 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 4:
#line 125 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.node_value) = NULL;
	}
#line 770 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 5:
#line 131 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 778 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 6:
#line 134 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 786 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 7:
#line 137 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = (yystack_[0].value.statement);
	}
#line 794 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 8:
#line 144 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.specifier) = new cmm::NSpecifier((yystack_[0].value.str_value));
	}
#line 802 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 9:
#line 147 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.specifier) = new cmm::NSpecifier((yystack_[0].value.identfier));
	}
#line 810 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 10:
#line 154 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new cmm::NVariableDecStatement((yystack_[2].value.specifier), (yystack_[1].value.var_dec_list));
	}
#line 818 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 11:
#line 161 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec_list) = new std::deque<cmm::NVariableDeclaration*>;
		(yylhs.value.var_dec_list)->push_front((yystack_[0].value.var_dec));
	}
#line 827 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 12:
#line 165 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.var_dec_list)->push_front((yystack_[2].value.var_dec));
		(yylhs.value.var_dec_list) = (yystack_[0].value.var_dec_list);
	}
#line 836 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 13:
#line 173 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec)->assignmentExp = (yystack_[0].value.expression);
		(yylhs.value.var_dec) = (yystack_[2].value.var_dec);
	}
#line 845 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 14:
#line 177 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = (yystack_[0].value.var_dec);
	}
#line 853 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 15:
#line 184 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[0].value.identfier));
	}
#line 861 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 16:
#line 187 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[3].value.identfier), (yystack_[1].value.int_value));
	}
#line 869 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 17:
#line 190 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_dec) = new cmm::NVariableDeclaration((yystack_[2].value.identfier), (yystack_[0].value.identfier));
	}
#line 877 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 18:
#line 197 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.var_stmt_list) = new std::deque<cmm::NVariableDecStatement*>;
		(yylhs.value.var_stmt_list)->push_front((cmm::NVariableDecStatement*)(yystack_[0].value.statement));
	}
#line 886 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 19:
#line 201 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.var_stmt_list)->push_front((cmm::NVariableDecStatement*)(yystack_[1].value.statement));
		(yylhs.value.var_stmt_list) = (yystack_[0].value.var_stmt_list);
	}
#line 895 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 20:
#line 209 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new cmm::NStructStatement((yystack_[4].value.identfier), (yystack_[2].value.var_stmt_list));
	}
#line 903 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 21:
#line 216 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.identfier) = new cmm::NIdentifier((yystack_[0].value.str_value));
	}
#line 911 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 22:
#line 223 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new NFunctionDecStatement((yystack_[5].value.specifier), (yystack_[4].value.identfier), (yystack_[2].value.param_list), (yystack_[0].value.block));
	}
#line 919 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 23:
#line 226 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.statement) = new NFunctionDecStatement(NULL, (yystack_[4].value.identfier), (yystack_[2].value.param_list), (yystack_[0].value.block));
	}
#line 927 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 24:
#line 233 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.param_list)->push_front((yystack_[2].value.parameter));
		(yylhs.value.param_list) = (yystack_[0].value.param_list);
	}
#line 936 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 25:
#line 237 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.param_list) = new std::deque<cmm::NFunctionParameter*>;
		(yylhs.value.param_list)->push_front((yystack_[0].value.parameter));
	}
#line 945 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 26:
#line 241 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.param_list) = NULL;
	}
#line 953 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 27:
#line 244 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.param_list) = NULL;
	}
#line 961 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 28:
#line 251 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.parameter) = new NFunctionParameter((yystack_[1].value.specifier), (yystack_[0].value.identfier));
	}
#line 969 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 29:
#line 258 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock((yystack_[2].value.var_stmt_list), (yystack_[1].value.block_stmt_list));
	}
#line 977 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 30:
#line 261 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock((yystack_[1].value.block_stmt_list));
	}
#line 985 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 31:
#line 264 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block) = new NBlock();
	}
#line 993 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 32:
#line 270 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yystack_[0].value.block_stmt_list)->push_front((yystack_[1].value.inblock_stmt));
		(yylhs.value.block_stmt_list) = (yystack_[0].value.block_stmt_list);
	}
#line 1002 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 33:
#line 274 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.block_stmt_list) = new std::deque<cmm::NInBlockStatement*>;
		(yylhs.value.block_stmt_list)->push_front((yystack_[0].value.inblock_stmt));
	}
#line 1011 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 34:
#line 282 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NExpressionStatement((yystack_[1].value.expression));
	}
#line 1019 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 35:
#line 285 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NBlockStatement((yystack_[0].value.block));
	}
#line 1027 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 36:
#line 288 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NReturnStatement((yystack_[1].value.expression));
	}
#line 1035 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 37:
#line 291 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NIfStatement((yystack_[2].value.expression), (yystack_[0].value.inblock_stmt), NULL);
	}
#line 1043 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 38:
#line 294 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NIfStatement((yystack_[4].value.expression), (yystack_[2].value.inblock_stmt), (yystack_[0].value.inblock_stmt));
	}
#line 1051 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 39:
#line 297 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.inblock_stmt) = new NWhileStatement((yystack_[2].value.expression), (yystack_[0].value.inblock_stmt));
	}
#line 1059 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 56:
#line 319 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.expression) = new NInteger((yystack_[0].value.int_value));
	}
#line 1067 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 57:
#line 322 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.expression) = new NFloat((yystack_[0].value.float_value));
	}
#line 1075 "bison/cmmparser.cc" // lalr1.cc:859
    break;

  case 58:
#line 325 "bison/cmmsyntax.y" // lalr1.cc:859
    {
		(yylhs.value.expression) = NULL;
	}
#line 1083 "bison/cmmparser.cc" // lalr1.cc:859
    break;


#line 1087 "bison/cmmparser.cc" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -48;

  const signed char Parser::yytable_ninf_ = -34;

  const short int
  Parser::yypact_[] =
  {
      21,   -48,     7,     7,    14,    30,    21,     7,   -48,   -48,
     -48,   -48,    17,    23,   -48,   -48,   -48,    29,    33,    41,
     103,   134,    -1,   -48,     7,   121,    74,     7,   134,   -48,
       7,     7,    51,    63,     7,    -1,    77,   -48,   -23,   -48,
     -48,   121,   121,   121,    62,   271,    81,   -48,    90,   -48,
     -48,    84,   134,   -48,    93,    -2,   138,   271,   105,   121,
     121,   121,   121,   121,   121,   121,   121,     7,   121,   -48,
      84,    55,   -48,   -48,   -48,   -48,   -48,   157,    92,   271,
     271,   271,    45,   284,   284,    -2,   176,   -48,   271,   -48,
     121,    99,   101,   -48,    89,   -48,    91,    85,   195,   121,
     -48,   -48,   214,   121,   121,   108,   -48,   -48,   -48,   -48,
     -48,   233,   252,   -48,    89,    89,   117,   -48,    89,   -48
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       4,     8,     0,     0,     0,     0,     4,     0,     5,     6,
       7,    21,     0,     9,     1,     2,     3,     0,    11,    14,
      15,    27,     0,    10,     0,    58,     0,     0,    27,    26,
       0,     0,     0,    25,     0,    18,     0,    12,    15,    56,
      57,    58,    58,    58,    55,    13,     0,    17,     0,     9,
      28,     0,    27,    19,     0,    49,     0,    50,    58,    58,
      58,    58,    58,    58,    58,    58,    58,     0,    58,    16,
       0,    58,    23,    24,    20,    48,    52,    60,     0,    43,
      41,    42,    40,    44,    45,    46,     0,    54,    47,    22,
      58,     0,     0,    31,    58,    35,     0,    58,     0,    58,
      51,    53,     0,    58,    58,     0,    30,    32,    34,    59,
      36,     0,     0,    29,    58,    58,    37,    39,    58,    38
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -48,   -48,   127,   -48,     9,    13,   114,   -48,   -48,   -24,
     -48,    18,   -48,   -26,   -48,   -47,   -22,   -19,   -25,    43
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,    31,    35,    17,    18,    19,    36,
       9,    44,    10,    32,    33,    95,    96,    97,    98,    78
  };

  const signed char
  Parser::yytable_[] =
  {
      45,    26,    48,    27,    72,     1,    59,    60,    61,     7,
      30,    53,    11,     8,    14,     7,    55,    56,    57,     8,
      12,    13,    66,    89,    67,    20,    73,     1,     2,    68,
      15,    34,     3,    77,    79,    80,    81,    82,    83,    84,
      85,    86,    38,    88,    34,    47,    21,    94,    49,    50,
      22,    23,    38,    59,    60,    61,    24,    25,    39,    40,
      11,     1,    63,    64,    65,   102,    30,    90,    91,    66,
      92,    67,   105,    41,    77,   107,    68,    46,   111,   112,
      34,    51,    71,    93,    42,    87,    52,    43,    39,    40,
      11,    58,    39,    40,    11,   116,   117,    90,    91,   119,
      92,    90,    91,    41,    92,    54,    69,    41,    39,    40,
      11,    71,    71,   -33,    42,    74,    71,    43,    42,   106,
      70,    43,   100,    41,    39,    40,    11,    26,   103,    27,
     104,   118,    28,    16,    42,    76,   113,    43,    37,    41,
       1,    29,   109,     0,     0,    30,    59,    60,    61,     0,
      42,     0,     0,    43,    62,    63,    64,    65,     0,     0,
       0,     0,    66,     0,    67,    59,    60,    61,    75,    68,
       0,     0,     0,    62,    63,    64,    65,     0,     0,     0,
      99,    66,     0,    67,    59,    60,    61,     0,    68,     0,
       0,     0,    62,    63,    64,    65,     0,     0,     0,     0,
      66,   101,    67,    59,    60,    61,     0,    68,     0,     0,
       0,    62,    63,    64,    65,     0,     0,   108,     0,    66,
       0,    67,    59,    60,    61,     0,    68,     0,     0,     0,
      62,    63,    64,    65,     0,     0,   110,     0,    66,     0,
      67,    59,    60,    61,     0,    68,     0,     0,     0,    62,
      63,    64,    65,     0,     0,     0,     0,    66,     0,    67,
      59,    60,    61,   114,    68,     0,     0,     0,    62,    63,
      64,    65,     0,     0,     0,     0,    66,     0,    67,    59,
      60,    61,   115,    68,     0,     0,     0,    62,    63,    64,
      65,     0,    59,    60,    61,    66,     0,    67,     0,     0,
       0,     0,    68,    65,     0,     0,     0,     0,    66,     0,
      67,     0,     0,     0,     0,    68
  };

  const signed char
  Parser::yycheck_[] =
  {
      25,    24,    28,    26,    51,     6,     8,     9,    10,     0,
      11,    35,     5,     0,     0,     6,    41,    42,    43,     6,
       2,     3,    24,    70,    26,     7,    52,     6,     7,    31,
       0,    22,    11,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    24,    68,    35,    27,    29,    71,    30,    31,
      27,    22,    34,     8,     9,    10,    23,    16,     3,     4,
       5,     6,    17,    18,    19,    90,    11,    12,    13,    24,
      15,    26,    94,    18,    99,    97,    31,     3,   103,   104,
      71,    30,    27,    28,    29,    67,    23,    32,     3,     4,
       5,    29,     3,     4,     5,   114,   115,    12,    13,   118,
      15,    12,    13,    18,    15,    28,    25,    18,     3,     4,
       5,    27,    27,    28,    29,    22,    27,    32,    29,    28,
      30,    32,    30,    18,     3,     4,     5,    24,    29,    26,
      29,    14,    29,     6,    29,    30,    28,    32,    24,    18,
       6,     7,    99,    -1,    -1,    11,     8,     9,    10,    -1,
      29,    -1,    -1,    32,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    24,    -1,    26,     8,     9,    10,    30,    31,
      -1,    -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    24,    -1,    26,     8,     9,    10,    -1,    31,    -1,
      -1,    -1,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      24,    25,    26,     8,     9,    10,    -1,    31,    -1,    -1,
      -1,    16,    17,    18,    19,    -1,    -1,    22,    -1,    24,
      -1,    26,     8,     9,    10,    -1,    31,    -1,    -1,    -1,
      16,    17,    18,    19,    -1,    -1,    22,    -1,    24,    -1,
      26,     8,     9,    10,    -1,    31,    -1,    -1,    -1,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    -1,    26,
       8,     9,    10,    30,    31,    -1,    -1,    -1,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    24,    -1,    26,     8,
       9,    10,    30,    31,    -1,    -1,    -1,    16,    17,    18,
      19,    -1,     8,     9,    10,    24,    -1,    26,    -1,    -1,
      -1,    -1,    31,    19,    -1,    -1,    -1,    -1,    24,    -1,
      26,    -1,    -1,    -1,    -1,    31
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     6,     7,    11,    34,    35,    36,    37,    38,    43,
      45,     5,    44,    44,     0,     0,    35,    39,    40,    41,
      44,    29,    27,    22,    23,    16,    24,    26,    29,     7,
      11,    37,    46,    47,    37,    38,    42,    39,    44,     3,
       4,    18,    29,    32,    44,    51,     3,    44,    46,    44,
      44,    30,    23,    42,    28,    51,    51,    51,    29,     8,
       9,    10,    16,    17,    18,    19,    24,    26,    31,    25,
      30,    27,    48,    46,    22,    30,    30,    51,    52,    51,
      51,    51,    51,    51,    51,    51,    51,    44,    51,    48,
      12,    13,    15,    28,    42,    48,    49,    50,    51,    23,
      30,    25,    51,    29,    29,    49,    28,    49,    22,    52,
      22,    51,    51,    28,    30,    30,    50,    50,    14,    50
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    33,    34,    35,    35,    36,    36,    36,    37,    37,
      38,    39,    39,    40,    40,    41,    41,    41,    42,    42,
      43,    44,    45,    45,    46,    46,    46,    46,    47,    48,
      48,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      52
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     0,     1,     1,     1,     1,     2,
       3,     1,     3,     3,     1,     1,     4,     3,     1,     2,
       6,     1,     6,     6,     3,     1,     1,     0,     2,     4,
       3,     2,     2,     1,     2,     1,     3,     5,     7,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     3,     1,     1,     1,     0,     3,
       1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "INT", "FLOAT", "ID", "TYPE",
  "VOID", "RELOP", "AND", "OR", "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
  "'='", "'+'", "'-'", "'*'", "UMINUS", "LOWER_THAN_ELSE", "';'", "','",
  "'['", "']'", "'.'", "'{'", "'}'", "'('", "')'", "'/'", "'!'", "$accept",
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
       0,   116,   116,   120,   125,   131,   134,   137,   144,   147,
     154,   161,   165,   173,   177,   184,   187,   190,   197,   201,
     209,   216,   223,   226,   233,   237,   241,   244,   251,   258,
     261,   264,   270,   274,   282,   285,   288,   291,   294,   297,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   322,   325,   331,
     332
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
       2,     2,     2,    32,     2,     2,     2,     2,     2,     2,
      29,    30,    19,    17,    23,    18,    26,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    16,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    20,    21
    };
    const unsigned int user_token_number_max_ = 272;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // cmm
#line 1622 "bison/cmmparser.cc" // lalr1.cc:1167
#line 335 "bison/cmmsyntax.y" // lalr1.cc:1168


void cmm::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
