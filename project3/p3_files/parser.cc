// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "frontend.hh"


// Unqualified %code blocks.
#line 34 "drewno_mars.yy"

   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex

#line 63 "parser.cc"


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


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



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
      *yycdebug_ << '\n';                       \
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
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "drewno_mars.yy"
namespace drewno_mars {
#line 137 "parser.cc"

  /// Build a parser object.
  Parser::Parser (drewno_mars::Scanner &scanner_yyarg, drewno_mars::ProgramNode** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
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

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: globals
#line 156 "drewno_mars.yy"
                  {
		  (yylhs.value.transProgram) = new ProgramNode((yystack_[0].value.transDeclList));
		  *root = (yylhs.value.transProgram);
		  }
#line 598 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 162 "drewno_mars.yy"
                  { 
		  (yylhs.value.transDeclList) = (yystack_[1].value.transDeclList);
		  DeclNode * declNode = (yystack_[0].value.transDecl);
		  (yylhs.value.transDeclList)->push_back(declNode);
	  	  }
#line 608 "parser.cc"
    break;

  case 4: // globals: %empty
#line 168 "drewno_mars.yy"
                  {
		  (yylhs.value.transDeclList) = new std::list<DeclNode *>();
		  }
#line 616 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOL
#line 173 "drewno_mars.yy"
                  {
		  (yylhs.value.transDecl) = (yystack_[1].value.transVarDecl);
		  }
#line 624 "parser.cc"
    break;

  case 6: // decl: classDecl
#line 176 "drewno_mars.yy"
                            { }
#line 630 "parser.cc"
    break;

  case 7: // decl: fnDecl
#line 177 "drewno_mars.yy"
                         { }
#line 636 "parser.cc"
    break;

  case 8: // varDecl: id COLON type
#line 180 "drewno_mars.yy"
                  {
		  const Position * p;
		  p = new Position((yystack_[2].value.transID)->pos(), (yystack_[1].value.transToken)->pos());
		  (yylhs.value.transVarDecl) = new VarDeclNode(p, (yystack_[2].value.transID), (yystack_[0].value.transType));
		  }
#line 646 "parser.cc"
    break;

  case 9: // varDecl: id COLON type ASSIGN exp
#line 186 "drewno_mars.yy"
                  {
		  }
#line 653 "parser.cc"
    break;

  case 10: // type: primType
#line 190 "drewno_mars.yy"
                  {
		  (yylhs.value.transType) = (yystack_[0].value.transType);
		  }
#line 661 "parser.cc"
    break;

  case 11: // type: id
#line 194 "drewno_mars.yy"
                  {
		  }
#line 668 "parser.cc"
    break;

  case 12: // type: PERFECT primType
#line 197 "drewno_mars.yy"
                  {
		  }
#line 675 "parser.cc"
    break;

  case 13: // type: PERFECT id
#line 200 "drewno_mars.yy"
                  {
		  }
#line 682 "parser.cc"
    break;

  case 14: // primType: INT
#line 204 "drewno_mars.yy"
                  { 
		  (yylhs.value.transType) = new IntTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 690 "parser.cc"
    break;

  case 15: // primType: BOOL
#line 208 "drewno_mars.yy"
                  {
		  }
#line 697 "parser.cc"
    break;

  case 16: // primType: VOID
#line 211 "drewno_mars.yy"
                  {
		  }
#line 704 "parser.cc"
    break;

  case 17: // classDecl: id COLON CLASS LCURLY classBody RCURLY SEMICOL
#line 215 "drewno_mars.yy"
                  {
		  }
#line 711 "parser.cc"
    break;

  case 18: // classBody: classBody varDecl SEMICOL
#line 219 "drewno_mars.yy"
                  {
		  }
#line 718 "parser.cc"
    break;

  case 19: // classBody: classBody fnDecl
#line 222 "drewno_mars.yy"
                  {
		  }
#line 725 "parser.cc"
    break;

  case 20: // classBody: %empty
#line 225 "drewno_mars.yy"
                  {
		  }
#line 732 "parser.cc"
    break;

  case 21: // fnDecl: id COLON LPAREN formals RPAREN type LCURLY stmtList RCURLY
#line 229 "drewno_mars.yy"
                  {
		  }
#line 739 "parser.cc"
    break;

  case 22: // formals: %empty
#line 233 "drewno_mars.yy"
                  {
		  }
#line 746 "parser.cc"
    break;

  case 23: // formals: formalsList
#line 236 "drewno_mars.yy"
                  {
		  }
#line 753 "parser.cc"
    break;

  case 24: // formalsList: formalDecl
#line 240 "drewno_mars.yy"
                  {
		  }
#line 760 "parser.cc"
    break;

  case 25: // formalsList: formalsList COMMA formalDecl
#line 243 "drewno_mars.yy"
                  {
		  }
#line 767 "parser.cc"
    break;

  case 26: // formalDecl: id COLON type
#line 247 "drewno_mars.yy"
                  {
		  }
#line 774 "parser.cc"
    break;

  case 27: // stmtList: %empty
#line 251 "drewno_mars.yy"
                  {
	   	  }
#line 781 "parser.cc"
    break;

  case 28: // stmtList: stmtList stmt SEMICOL
#line 254 "drewno_mars.yy"
                  {
	  	  }
#line 788 "parser.cc"
    break;

  case 29: // stmtList: stmtList blockStmt
#line 257 "drewno_mars.yy"
                  {
	  	  }
#line 795 "parser.cc"
    break;

  case 30: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 261 "drewno_mars.yy"
                  {
		  }
#line 802 "parser.cc"
    break;

  case 31: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 264 "drewno_mars.yy"
                  {
		  }
#line 809 "parser.cc"
    break;

  case 32: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 267 "drewno_mars.yy"
                  {
		  }
#line 816 "parser.cc"
    break;

  case 33: // stmt: varDecl
#line 271 "drewno_mars.yy"
                  {
		  }
#line 823 "parser.cc"
    break;

  case 34: // stmt: loc ASSIGN exp
#line 274 "drewno_mars.yy"
                  {
		  }
#line 830 "parser.cc"
    break;

  case 35: // stmt: loc POSTDEC
#line 277 "drewno_mars.yy"
                  {
		  }
#line 837 "parser.cc"
    break;

  case 36: // stmt: loc POSTINC
#line 280 "drewno_mars.yy"
                  {
		  }
#line 844 "parser.cc"
    break;

  case 37: // stmt: GIVE exp
#line 283 "drewno_mars.yy"
                  {
		  }
#line 851 "parser.cc"
    break;

  case 38: // stmt: TAKE loc
#line 286 "drewno_mars.yy"
                  {
		  }
#line 858 "parser.cc"
    break;

  case 39: // stmt: RETURN exp
#line 289 "drewno_mars.yy"
                  {
		  }
#line 865 "parser.cc"
    break;

  case 40: // stmt: RETURN
#line 292 "drewno_mars.yy"
                  {
		  }
#line 872 "parser.cc"
    break;

  case 41: // stmt: EXIT
#line 295 "drewno_mars.yy"
                  {
		  }
#line 879 "parser.cc"
    break;

  case 42: // stmt: callExp
#line 298 "drewno_mars.yy"
                  { 
		  }
#line 886 "parser.cc"
    break;

  case 43: // exp: exp DASH exp
#line 302 "drewno_mars.yy"
                  {
		  }
#line 893 "parser.cc"
    break;

  case 44: // exp: exp CROSS exp
#line 305 "drewno_mars.yy"
                  {
		  }
#line 900 "parser.cc"
    break;

  case 45: // exp: exp STAR exp
#line 308 "drewno_mars.yy"
                  {
		  }
#line 907 "parser.cc"
    break;

  case 46: // exp: exp SLASH exp
#line 311 "drewno_mars.yy"
                  {
		  }
#line 914 "parser.cc"
    break;

  case 47: // exp: exp AND exp
#line 314 "drewno_mars.yy"
                  {
		  }
#line 921 "parser.cc"
    break;

  case 48: // exp: exp OR exp
#line 317 "drewno_mars.yy"
                  {
		  }
#line 928 "parser.cc"
    break;

  case 49: // exp: exp EQUALS exp
#line 320 "drewno_mars.yy"
                  {
		  }
#line 935 "parser.cc"
    break;

  case 50: // exp: exp NOTEQUALS exp
#line 323 "drewno_mars.yy"
                  {
		  }
#line 942 "parser.cc"
    break;

  case 51: // exp: exp GREATER exp
#line 326 "drewno_mars.yy"
                  {
		  }
#line 949 "parser.cc"
    break;

  case 52: // exp: exp GREATEREQ exp
#line 329 "drewno_mars.yy"
                  {
		  }
#line 956 "parser.cc"
    break;

  case 53: // exp: exp LESS exp
#line 332 "drewno_mars.yy"
                  {
		  }
#line 963 "parser.cc"
    break;

  case 54: // exp: exp LESSEQ exp
#line 335 "drewno_mars.yy"
                  {
		  }
#line 970 "parser.cc"
    break;

  case 55: // exp: NOT exp
#line 338 "drewno_mars.yy"
                  {
		  }
#line 977 "parser.cc"
    break;

  case 56: // exp: DASH term
#line 341 "drewno_mars.yy"
                  {
		  }
#line 984 "parser.cc"
    break;

  case 57: // exp: term
#line 344 "drewno_mars.yy"
                  {
		  }
#line 991 "parser.cc"
    break;

  case 58: // callExp: loc LPAREN RPAREN
#line 348 "drewno_mars.yy"
                  {
		  }
#line 998 "parser.cc"
    break;

  case 59: // callExp: loc LPAREN actualsList RPAREN
#line 351 "drewno_mars.yy"
                  {
		  }
#line 1005 "parser.cc"
    break;

  case 60: // actualsList: exp
#line 355 "drewno_mars.yy"
                  {
		  }
#line 1012 "parser.cc"
    break;

  case 61: // actualsList: actualsList COMMA exp
#line 358 "drewno_mars.yy"
                  {
		  }
#line 1019 "parser.cc"
    break;

  case 62: // term: loc
#line 362 "drewno_mars.yy"
                  { 
		  }
#line 1026 "parser.cc"
    break;

  case 63: // term: INTLITERAL
#line 365 "drewno_mars.yy"
                  {
		  }
#line 1033 "parser.cc"
    break;

  case 64: // term: STRINGLITERAL
#line 368 "drewno_mars.yy"
                  {
		  }
#line 1040 "parser.cc"
    break;

  case 65: // term: TRUE
#line 371 "drewno_mars.yy"
                  {
		  }
#line 1047 "parser.cc"
    break;

  case 66: // term: FALSE
#line 374 "drewno_mars.yy"
                  {
		  }
#line 1054 "parser.cc"
    break;

  case 67: // term: MAGIC
#line 377 "drewno_mars.yy"
                  {
		  }
#line 1061 "parser.cc"
    break;

  case 68: // term: LPAREN exp RPAREN
#line 380 "drewno_mars.yy"
                  {
		  }
#line 1068 "parser.cc"
    break;

  case 69: // term: callExp
#line 383 "drewno_mars.yy"
                  {
		  }
#line 1075 "parser.cc"
    break;

  case 70: // loc: id
#line 387 "drewno_mars.yy"
                  {
		  (yylhs.value.transLoc) = (yystack_[0].value.transID);
		  }
#line 1083 "parser.cc"
    break;

  case 71: // loc: loc POSTDEC id
#line 391 "drewno_mars.yy"
                  {
		  }
#line 1090 "parser.cc"
    break;

  case 72: // id: ID
#line 395 "drewno_mars.yy"
                  {
		  const Position * pos = (yystack_[0].value.transIDToken)->pos();
		  (yylhs.value.transID) = new IDNode(pos, (yystack_[0].value.transIDToken)->value());
		  }
#line 1099 "parser.cc"
    break;


#line 1103 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

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
        std::string yyr;
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
              else
                goto append;

            append:
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

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -76;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -76,     4,   -10,   -76,   -76,   -76,   -14,   -76,   -76,    43,
     -76,    56,   -76,    33,   -76,   -10,     6,   -76,    51,   -76,
     -76,   -76,    22,    55,   -76,    57,   -76,   -76,   228,   -15,
      78,   -10,    78,   323,   -76,   -76,   228,   -76,   228,   -76,
     -76,   182,   -76,   -76,   -23,   -76,    29,    32,   -76,    63,
      58,   -76,   -76,   -76,   118,   -76,   228,   228,   228,   228,
     228,   228,   228,   228,   228,   228,   228,   228,   205,   -10,
     -76,   -76,    77,   -76,   -76,   295,   -17,   304,   304,   304,
     304,   304,   304,   212,   -17,   -76,   -76,   -76,   182,    -4,
     -76,   244,   228,   -76,   -76,   228,    48,   228,   -76,   -10,
      53,   -76,   -76,    42,   -76,     2,    75,   182,   182,   228,
     182,    59,   228,   -76,   228,   -10,   -76,    78,   135,   165,
     182,    65,    66,   -76,   -76,   246,   257,    74,   -76,    71,
     -76,   281,   -76
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    72,     3,     0,     6,     7,     0,
       5,     0,    15,     0,    14,    22,     0,    16,     8,    10,
      11,    20,     0,    23,    24,     0,    12,    13,     0,     0,
       0,     0,     0,     0,    66,    63,     0,    67,     0,    64,
      65,     9,    69,    57,    62,    70,     0,     0,    19,     0,
       0,    25,    26,    56,     0,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    18,     0,    27,    68,    47,    43,    49,    51,    52,
      53,    54,    50,    48,    44,    46,    45,    58,    60,     0,
      71,     0,     0,    59,    41,     0,     0,    40,    21,     0,
       0,    33,    29,     0,    42,     0,    70,    61,    37,     0,
      39,    38,     0,    28,     0,    35,    36,     0,     0,     0,
      34,     0,     0,    27,    27,     0,     0,    31,    30,     0,
      27,     0,    32
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -76,   -76,   -76,   -76,     3,   -20,    83,   -76,   -76,    73,
     -76,   -76,    69,   -64,   -76,   -76,   -21,   -73,   -76,    70,
     -75,    -2
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,   101,    18,    19,     7,    29,     8,
      22,    23,    24,    91,   102,   103,    41,    42,    89,    43,
      44,    45
  };

  const short
  Parser::yytable_[] =
  {
       9,    68,     4,    92,     3,     6,   114,     4,    69,    20,
      50,    12,    52,    25,    27,    54,   105,    55,   104,    46,
      66,    67,    10,     4,   111,    14,    68,    49,    20,    25,
      20,    93,    47,   115,   116,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    88,    17,    11,
     105,   105,   104,   104,    21,    28,   105,    30,   104,   125,
     126,    12,    31,    32,    13,    70,   131,    90,    71,    72,
      20,   107,   109,     4,   108,    14,   110,   112,   113,    73,
      15,   117,    12,    12,   129,    16,   123,   124,   118,   106,
      69,   119,   130,   120,     4,     4,    14,    14,    17,    26,
      51,    15,    48,    53,     0,     0,    16,    16,     0,     0,
       0,     0,     0,    90,     0,    20,     0,     0,     0,    17,
      17,    56,     0,   106,   106,     0,     0,    57,     0,   106,
      58,     0,     0,    59,    60,     0,     0,     0,    56,     0,
      61,    62,     0,     0,    57,    63,    64,    58,    65,     0,
      59,    60,     0,    74,     0,    66,    67,    61,    62,     0,
       0,     0,    63,    64,     0,    65,     0,     0,    56,     0,
     121,     0,    66,    67,    57,     0,     0,    58,     0,     0,
      59,    60,     0,     0,     0,    56,     0,    61,    62,     0,
       0,    57,    63,    64,    58,    65,     0,    59,    60,     0,
     122,     0,    66,    67,    61,    62,     0,     0,     0,    63,
      64,     0,    65,     0,    33,    56,     0,     0,    34,    66,
      67,    57,     4,     0,    58,    35,     0,    59,    60,    36,
      37,    38,     0,     0,    61,    62,     0,    33,     0,    63,
      87,    34,    65,     0,    39,     4,    40,     0,    35,    66,
      67,     0,    36,    37,    38,    94,     0,    94,    95,     0,
      95,     4,    96,     4,    96,     0,     0,    39,    94,    40,
       0,    95,     0,     0,     4,    96,     0,    97,    98,    97,
     127,     0,     0,     0,    99,     0,    99,   100,     0,   100,
      97,   128,    94,     0,     0,    95,     0,    99,     4,    96,
     100,     0,     0,     0,    57,     0,     0,    58,     0,     0,
      59,    60,     0,    57,    97,   132,    -1,    61,    62,    -1,
      -1,    99,    63,     0,   100,    65,    -1,    -1,     0,     0,
       0,    -1,    66,    67,    65,     0,    34,     0,     0,     0,
       4,    66,    67,    35,     0,     0,     0,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,    40
  };

  const short
  Parser::yycheck_[] =
  {
       2,    24,    17,     7,     0,     2,     4,    17,    31,    11,
      30,     5,    32,    15,    16,    36,    91,    38,    91,    34,
      37,    38,    36,    17,    99,    19,    24,    29,    30,    31,
      32,    35,    29,    31,    32,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    42,     6,
     125,   126,   125,   126,    21,     4,   131,    35,   131,   123,
     124,     5,     7,     6,     8,    36,   130,    69,    36,     6,
      72,    92,    24,    17,    95,    19,    97,    24,    36,    21,
      24,     6,     5,     5,    10,    29,    21,    21,   109,    91,
      31,   112,    21,   114,    17,    17,    19,    19,    42,    16,
      31,    24,    29,    33,    -1,    -1,    29,    29,    -1,    -1,
      -1,    -1,    -1,   115,    -1,   117,    -1,    -1,    -1,    42,
      42,     3,    -1,   125,   126,    -1,    -1,     9,    -1,   131,
      12,    -1,    -1,    15,    16,    -1,    -1,    -1,     3,    -1,
      22,    23,    -1,    -1,     9,    27,    28,    12,    30,    -1,
      15,    16,    -1,    35,    -1,    37,    38,    22,    23,    -1,
      -1,    -1,    27,    28,    -1,    30,    -1,    -1,     3,    -1,
      35,    -1,    37,    38,     9,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,    -1,    -1,     3,    -1,    22,    23,    -1,
      -1,     9,    27,    28,    12,    30,    -1,    15,    16,    -1,
      35,    -1,    37,    38,    22,    23,    -1,    -1,    -1,    27,
      28,    -1,    30,    -1,     9,     3,    -1,    -1,    13,    37,
      38,     9,    17,    -1,    12,    20,    -1,    15,    16,    24,
      25,    26,    -1,    -1,    22,    23,    -1,     9,    -1,    27,
      35,    13,    30,    -1,    39,    17,    41,    -1,    20,    37,
      38,    -1,    24,    25,    26,    11,    -1,    11,    14,    -1,
      14,    17,    18,    17,    18,    -1,    -1,    39,    11,    41,
      -1,    14,    -1,    -1,    17,    18,    -1,    33,    34,    33,
      34,    -1,    -1,    -1,    40,    -1,    40,    43,    -1,    43,
      33,    34,    11,    -1,    -1,    14,    -1,    40,    17,    18,
      43,    -1,    -1,    -1,     9,    -1,    -1,    12,    -1,    -1,
      15,    16,    -1,     9,    33,    34,    12,    22,    23,    15,
      16,    40,    27,    -1,    43,    30,    22,    23,    -1,    -1,
      -1,    27,    37,    38,    30,    -1,    13,    -1,    -1,    -1,
      17,    37,    38,    20,    -1,    -1,    -1,    24,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    41
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    45,    46,     0,    17,    47,    48,    51,    53,    65,
      36,     6,     5,     8,    19,    24,    29,    42,    49,    50,
      65,    21,    54,    55,    56,    65,    50,    65,     4,    52,
      35,     7,     6,     9,    13,    20,    24,    25,    26,    39,
      41,    60,    61,    63,    64,    65,    34,    48,    53,    65,
      49,    56,    49,    63,    60,    60,     3,     9,    12,    15,
      16,    22,    23,    27,    28,    30,    37,    38,    24,    31,
      36,    36,     6,    21,    35,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    35,    60,    62,
      65,    57,     7,    35,    11,    14,    18,    33,    34,    40,
      43,    48,    58,    59,    61,    64,    65,    60,    60,    24,
      60,    64,    24,    36,     4,    31,    32,     6,    60,    60,
      60,    35,    35,    21,    21,    57,    57,    34,    34,    10,
      21,    57,    34
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      49,    49,    49,    49,    50,    50,    50,    51,    52,    52,
      52,    53,    54,    54,    55,    55,    56,    57,    57,    57,
      58,    58,    58,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      64,    64,    65
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     1,     3,     5,
       1,     1,     2,     2,     1,     1,     1,     7,     3,     2,
       0,     9,     0,     1,     1,     3,     3,     0,     3,     2,
       7,     7,    11,     1,     3,     2,     2,     2,     2,     2,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     3,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "AND", "ASSIGN", "BOOL",
  "COLON", "COMMA", "CLASS", "DASH", "ELSE", "EXIT", "EQUALS", "FALSE",
  "GIVE", "GREATER", "GREATEREQ", "ID", "IF", "INT", "INTLITERAL",
  "LCURLY", "LESS", "LESSEQ", "LPAREN", "MAGIC", "NOT", "NOTEQUALS", "OR",
  "PERFECT", "CROSS", "POSTDEC", "POSTINC", "RETURN", "RCURLY", "RPAREN",
  "SEMICOL", "SLASH", "STAR", "STRINGLITERAL", "TAKE", "TRUE", "VOID",
  "WHILE", "$accept", "program", "globals", "decl", "varDecl", "type",
  "primType", "classDecl", "classBody", "fnDecl", "formals", "formalsList",
  "formalDecl", "stmtList", "blockStmt", "stmt", "exp", "callExp",
  "actualsList", "term", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   155,   155,   161,   168,   172,   176,   177,   179,   185,
     189,   193,   196,   199,   203,   207,   210,   214,   218,   221,
     225,   228,   233,   235,   239,   242,   246,   251,   253,   256,
     260,   263,   266,   270,   273,   276,   279,   282,   285,   288,
     291,   294,   297,   301,   304,   307,   310,   313,   316,   319,
     322,   325,   328,   331,   334,   337,   340,   343,   347,   350,
     354,   357,   361,   364,   367,   370,   373,   376,   379,   382,
     386,   390,   394
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
    };
    // Last valid token kind.
    const int code_max = 298;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "drewno_mars.yy"
} // drewno_mars
#line 1753 "parser.cc"

#line 400 "drewno_mars.yy"


void drewno_mars::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
