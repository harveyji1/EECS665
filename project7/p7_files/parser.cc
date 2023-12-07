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
#line 158 "drewno_mars.yy"
                  {
		  (yylhs.value.transProgram) = new ProgramNode((yystack_[0].value.transDeclList));
		  *root = (yylhs.value.transProgram);
		  }
#line 598 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 164 "drewno_mars.yy"
                  { 
		  (yylhs.value.transDeclList) = (yystack_[1].value.transDeclList);
		  DeclNode * declNode = (yystack_[0].value.transDecl);
		  (yylhs.value.transDeclList)->push_back(declNode);
	  	  }
#line 608 "parser.cc"
    break;

  case 4: // globals: %empty
#line 170 "drewno_mars.yy"
                  {
		  (yylhs.value.transDeclList) = new std::list<DeclNode *>();
		  }
#line 616 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOL
#line 175 "drewno_mars.yy"
                  { 
		  (yylhs.value.transDecl) = (yystack_[1].value.transVarDecl);
		  }
#line 624 "parser.cc"
    break;

  case 6: // decl: classDecl
#line 179 "drewno_mars.yy"
                  {
		  }
#line 631 "parser.cc"
    break;

  case 7: // decl: fnDecl
#line 182 "drewno_mars.yy"
                  {
		  (yylhs.value.transDecl) = (yystack_[0].value.transFn);
		  }
#line 639 "parser.cc"
    break;

  case 8: // varDecl: id COLON type
#line 187 "drewno_mars.yy"
                  {
		  Position * p = new Position((yystack_[2].value.transID)->pos(), (yystack_[0].value.transType)->pos());
		  (yylhs.value.transVarDecl) = new VarDeclNode(p,(yystack_[2].value.transID), (yystack_[0].value.transType), nullptr);
		  }
#line 648 "parser.cc"
    break;

  case 9: // varDecl: id COLON type ASSIGN exp
#line 192 "drewno_mars.yy"
                  {
		  Position * p = new Position((yystack_[4].value.transID)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transVarDecl) = new VarDeclNode(p,(yystack_[4].value.transID), (yystack_[2].value.transType), (yystack_[0].value.transExp));
		  }
#line 657 "parser.cc"
    break;

  case 10: // type: primType
#line 198 "drewno_mars.yy"
                  {
		  (yylhs.value.transType) = (yystack_[0].value.transType);
		  }
#line 665 "parser.cc"
    break;

  case 11: // type: PERFECT primType
#line 202 "drewno_mars.yy"
                  {
		  Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transType)->pos());
		  (yylhs.value.transType) = new PerfectTypeNode(p, (yystack_[0].value.transType));
		  }
#line 674 "parser.cc"
    break;

  case 12: // primType: INT
#line 208 "drewno_mars.yy"
                  { 
		  (yylhs.value.transType) = new IntTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 682 "parser.cc"
    break;

  case 13: // primType: BOOL
#line 212 "drewno_mars.yy"
                  {
		  (yylhs.value.transType) = new BoolTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 690 "parser.cc"
    break;

  case 14: // primType: VOID
#line 216 "drewno_mars.yy"
                  {
		  (yylhs.value.transType) = new VoidTypeNode((yystack_[0].value.transToken)->pos());
		  }
#line 698 "parser.cc"
    break;

  case 15: // classDecl: id COLON CLASS LCURLY classBody RCURLY SEMICOL
#line 221 "drewno_mars.yy"
                  {
		  std::cerr << "Member field access has"
			<< " been removed from the language";
		  exit(1);
		  }
#line 708 "parser.cc"
    break;

  case 16: // classBody: classBody varDecl SEMICOL
#line 228 "drewno_mars.yy"
                  {
		  }
#line 715 "parser.cc"
    break;

  case 17: // classBody: classBody fnDecl
#line 231 "drewno_mars.yy"
                  {
		  }
#line 722 "parser.cc"
    break;

  case 18: // classBody: %empty
#line 234 "drewno_mars.yy"
                  {
		  }
#line 729 "parser.cc"
    break;

  case 19: // fnDecl: id COLON LPAREN formals RPAREN type LCURLY stmtList RCURLY
#line 238 "drewno_mars.yy"
                  {
		  auto pos = new Position((yystack_[8].value.transID)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transFn) = new FnDeclNode(pos, (yystack_[8].value.transID), (yystack_[5].value.transFormalList), (yystack_[3].value.transType), (yystack_[1].value.transStmts));
		  }
#line 738 "parser.cc"
    break;

  case 20: // formals: %empty
#line 244 "drewno_mars.yy"
                  {
		  (yylhs.value.transFormalList) = new std::list<drewno_mars::FormalDeclNode *>();
		  }
#line 746 "parser.cc"
    break;

  case 21: // formals: formalsList
#line 248 "drewno_mars.yy"
                  {
		  (yylhs.value.transFormalList) = (yystack_[0].value.transFormalList);
		  }
#line 754 "parser.cc"
    break;

  case 22: // formalsList: formalDecl
#line 253 "drewno_mars.yy"
                  {
		  (yylhs.value.transFormalList) = new std::list<FormalDeclNode *>();
		  (yylhs.value.transFormalList)->push_back((yystack_[0].value.transFormal));
		  }
#line 763 "parser.cc"
    break;

  case 23: // formalsList: formalsList COMMA formalDecl
#line 258 "drewno_mars.yy"
                  {
		  (yylhs.value.transFormalList) = (yystack_[2].value.transFormalList);
		  (yylhs.value.transFormalList)->push_back((yystack_[0].value.transFormal));
		  }
#line 772 "parser.cc"
    break;

  case 24: // formalDecl: id COLON type
#line 264 "drewno_mars.yy"
                  {
		  const Position * pos = new Position((yystack_[2].value.transID)->pos(), (yystack_[1].value.transToken)->pos());
		  (yylhs.value.transFormal) = new FormalDeclNode(pos, (yystack_[2].value.transID), (yystack_[0].value.transType));
		  }
#line 781 "parser.cc"
    break;

  case 25: // stmtList: %empty
#line 270 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmts) = new std::list<StmtNode *>();
	   	  }
#line 789 "parser.cc"
    break;

  case 26: // stmtList: stmtList stmt SEMICOL
#line 274 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmts) = (yystack_[2].value.transStmts);
		  (yylhs.value.transStmts)->push_back((yystack_[1].value.transStmt));
	  	  }
#line 798 "parser.cc"
    break;

  case 27: // stmtList: stmtList blockStmt
#line 279 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmts) = (yystack_[1].value.transStmts);
		  (yylhs.value.transStmts)->push_back((yystack_[0].value.transStmt));
	  	  }
#line 807 "parser.cc"
    break;

  case 28: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 285 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new WhileStmtNode(p, (yystack_[4].value.transExp), (yystack_[1].value.transStmts));
		  }
#line 816 "parser.cc"
    break;

  case 29: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 290 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[6].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new IfStmtNode(p, (yystack_[4].value.transExp), (yystack_[1].value.transStmts));
		  }
#line 825 "parser.cc"
    break;

  case 30: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 295 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[10].value.transToken)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new IfElseStmtNode(p, (yystack_[8].value.transExp), (yystack_[5].value.transStmts), (yystack_[1].value.transStmts));
		  }
#line 834 "parser.cc"
    break;

  case 31: // stmt: varDecl
#line 301 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmt) = (yystack_[0].value.transVarDecl);
		  }
#line 842 "parser.cc"
    break;

  case 32: // stmt: loc ASSIGN exp
#line 305 "drewno_mars.yy"
                  {
		  const auto p = new Position((yystack_[2].value.transLoc)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transStmt) = new AssignStmtNode(p, (yystack_[2].value.transLoc), (yystack_[0].value.transExp)); 
		  }
#line 851 "parser.cc"
    break;

  case 33: // stmt: loc POSTDEC
#line 310 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new PostDecStmtNode(p, (yystack_[1].value.transLoc));
		  }
#line 860 "parser.cc"
    break;

  case 34: // stmt: loc POSTINC
#line 315 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transStmt) = new PostIncStmtNode(p, (yystack_[1].value.transLoc));
		  }
#line 869 "parser.cc"
    break;

  case 35: // stmt: GIVE exp
#line 320 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transStmt) = new GiveStmtNode(p, (yystack_[0].value.transExp));
		  }
#line 878 "parser.cc"
    break;

  case 36: // stmt: TAKE loc
#line 325 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transLoc)->pos());
		  (yylhs.value.transStmt) = new TakeStmtNode(p, (yystack_[0].value.transLoc));
		  }
#line 887 "parser.cc"
    break;

  case 37: // stmt: RETURN exp
#line 330 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transStmt) = new ReturnStmtNode(p, (yystack_[0].value.transExp));
		  }
#line 896 "parser.cc"
    break;

  case 38: // stmt: RETURN
#line 335 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmt) = new ReturnStmtNode((yystack_[0].value.transToken)->pos(), nullptr);
		  }
#line 904 "parser.cc"
    break;

  case 39: // stmt: EXIT
#line 339 "drewno_mars.yy"
                  {
		  (yylhs.value.transStmt) = new ExitStmtNode((yystack_[0].value.transToken)->pos());
		  }
#line 912 "parser.cc"
    break;

  case 40: // stmt: callExp
#line 343 "drewno_mars.yy"
                  { 
		  (yylhs.value.transStmt) = new CallStmtNode((yystack_[0].value.transCallExp)->pos(), (yystack_[0].value.transCallExp)); 
		  }
#line 920 "parser.cc"
    break;

  case 41: // exp: exp DASH exp
#line 348 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new MinusNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 929 "parser.cc"
    break;

  case 42: // exp: exp CROSS exp
#line 353 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new PlusNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 938 "parser.cc"
    break;

  case 43: // exp: exp STAR exp
#line 358 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new TimesNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 947 "parser.cc"
    break;

  case 44: // exp: exp SLASH exp
#line 363 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new DivideNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 956 "parser.cc"
    break;

  case 45: // exp: exp AND exp
#line 368 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new AndNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 965 "parser.cc"
    break;

  case 46: // exp: exp OR exp
#line 373 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new OrNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 974 "parser.cc"
    break;

  case 47: // exp: exp EQUALS exp
#line 378 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new EqualsNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 983 "parser.cc"
    break;

  case 48: // exp: exp NOTEQUALS exp
#line 383 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NotEqualsNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 992 "parser.cc"
    break;

  case 49: // exp: exp GREATER exp
#line 388 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new GreaterNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 1001 "parser.cc"
    break;

  case 50: // exp: exp GREATEREQ exp
#line 393 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new GreaterEqNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 1010 "parser.cc"
    break;

  case 51: // exp: exp LESS exp
#line 398 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new LessNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 1019 "parser.cc"
    break;

  case 52: // exp: exp LESSEQ exp
#line 403 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transExp)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new LessEqNode(p, (yystack_[2].value.transExp), (yystack_[0].value.transExp));
		  }
#line 1028 "parser.cc"
    break;

  case 53: // exp: NOT exp
#line 408 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NotNode(p, (yystack_[0].value.transExp));
		  }
#line 1037 "parser.cc"
    break;

  case 54: // exp: DASH term
#line 413 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[1].value.transToken)->pos(), (yystack_[0].value.transExp)->pos());
		  (yylhs.value.transExp) = new NegNode(p, (yystack_[0].value.transExp));
		  }
#line 1046 "parser.cc"
    break;

  case 55: // exp: term
#line 418 "drewno_mars.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transExp); }
#line 1052 "parser.cc"
    break;

  case 56: // callExp: loc LPAREN RPAREN
#line 421 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[2].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  std::list<ExpNode *> * noargs =
		    new std::list<ExpNode *>();
		  (yylhs.value.transCallExp) = new CallExpNode(p, (yystack_[2].value.transLoc), noargs);
		  }
#line 1063 "parser.cc"
    break;

  case 57: // callExp: loc LPAREN actualsList RPAREN
#line 428 "drewno_mars.yy"
                  {
		  const Position * p = new Position((yystack_[3].value.transLoc)->pos(), (yystack_[0].value.transToken)->pos());
		  (yylhs.value.transCallExp) = new CallExpNode(p, (yystack_[3].value.transLoc), (yystack_[1].value.transActuals));
		  }
#line 1072 "parser.cc"
    break;

  case 58: // actualsList: exp
#line 434 "drewno_mars.yy"
                  {
		  std::list<ExpNode *> * list =
		    new std::list<ExpNode *>();
		  list->push_back((yystack_[0].value.transExp));
		  (yylhs.value.transActuals) = list;
		  }
#line 1083 "parser.cc"
    break;

  case 59: // actualsList: actualsList COMMA exp
#line 441 "drewno_mars.yy"
                  {
		  (yylhs.value.transActuals) = (yystack_[2].value.transActuals);
		  (yylhs.value.transActuals)->push_back((yystack_[0].value.transExp));
		  }
#line 1092 "parser.cc"
    break;

  case 60: // term: loc
#line 447 "drewno_mars.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transLoc); }
#line 1098 "parser.cc"
    break;

  case 61: // term: INTLITERAL
#line 449 "drewno_mars.yy"
                  { (yylhs.value.transExp) = new IntLitNode((yystack_[0].value.transIntToken)->pos(), (yystack_[0].value.transIntToken)->num()); }
#line 1104 "parser.cc"
    break;

  case 62: // term: STRINGLITERAL
#line 451 "drewno_mars.yy"
                  { (yylhs.value.transExp) = new StrLitNode((yystack_[0].value.transStrToken)->pos(), (yystack_[0].value.transStrToken)->str()); }
#line 1110 "parser.cc"
    break;

  case 63: // term: TRUE
#line 453 "drewno_mars.yy"
                  { (yylhs.value.transExp) = new TrueNode((yystack_[0].value.transToken)->pos()); }
#line 1116 "parser.cc"
    break;

  case 64: // term: FALSE
#line 455 "drewno_mars.yy"
                  { (yylhs.value.transExp) = new FalseNode((yystack_[0].value.transToken)->pos()); }
#line 1122 "parser.cc"
    break;

  case 65: // term: MAGIC
#line 457 "drewno_mars.yy"
                  { (yylhs.value.transExp) = new MagicNode((yystack_[0].value.transToken)->pos()); }
#line 1128 "parser.cc"
    break;

  case 66: // term: LPAREN exp RPAREN
#line 459 "drewno_mars.yy"
                  { (yylhs.value.transExp) = (yystack_[1].value.transExp); }
#line 1134 "parser.cc"
    break;

  case 67: // term: callExp
#line 461 "drewno_mars.yy"
                  { (yylhs.value.transExp) = (yystack_[0].value.transCallExp); }
#line 1140 "parser.cc"
    break;

  case 68: // loc: id
#line 464 "drewno_mars.yy"
                  {
		  (yylhs.value.transLoc) = (yystack_[0].value.transID);
		  }
#line 1148 "parser.cc"
    break;

  case 69: // loc: loc POSTDEC id
#line 468 "drewno_mars.yy"
                  {
		  std::cerr << "Member field access has"
			<< " been removed from the language";
		  exit(1);
		  }
#line 1158 "parser.cc"
    break;

  case 70: // id: ID
#line 475 "drewno_mars.yy"
                  {
		  const Position * pos = (yystack_[0].value.transIDToken)->pos();
		  (yylhs.value.transID) = new IDNode(pos, (yystack_[0].value.transIDToken)->value()); 
		  }
#line 1167 "parser.cc"
    break;


#line 1171 "parser.cc"

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


  const signed char Parser::yypact_ninf_ = -118;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
    -118,     3,   -11,  -118,  -118,  -118,   -24,  -118,  -118,    11,
    -118,    47,  -118,     1,  -118,   -11,    40,  -118,    46,  -118,
    -118,    16,    50,  -118,    52,  -118,   230,   -15,    41,   -11,
      41,   325,  -118,  -118,   230,  -118,   230,  -118,  -118,   178,
    -118,  -118,   -10,  -118,    17,    20,  -118,    55,    42,  -118,
    -118,  -118,   101,  -118,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   210,   -11,  -118,  -118,
      49,  -118,  -118,   297,   -14,   306,   306,   306,   306,   306,
     306,   195,   -14,  -118,  -118,  -118,   178,    13,  -118,   246,
     230,  -118,  -118,   230,    38,   230,  -118,   -11,    51,  -118,
    -118,    43,  -118,    68,    71,   178,   178,   230,   178,    54,
     230,  -118,   230,   -11,  -118,    41,   131,   148,   178,    53,
      59,  -118,  -118,   248,   259,    78,  -118,    69,  -118,   283,
    -118
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    70,     3,     0,     6,     7,     0,
       5,     0,    13,     0,    12,    20,     0,    14,     8,    10,
      18,     0,    21,    22,     0,    11,     0,     0,     0,     0,
       0,     0,    64,    61,     0,    65,     0,    62,    63,     9,
      67,    55,    60,    68,     0,     0,    17,     0,     0,    23,
      24,    54,     0,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,    16,
       0,    25,    66,    45,    41,    47,    49,    50,    51,    52,
      48,    46,    42,    44,    43,    56,    58,     0,    69,     0,
       0,    57,    39,     0,     0,    38,    19,     0,     0,    31,
      27,     0,    40,     0,    68,    59,    35,     0,    37,    36,
       0,    26,     0,    33,    34,     0,     0,     0,    32,     0,
       0,    25,    25,     0,     0,    29,    28,     0,    25,     0,
      30
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -118,  -118,  -118,  -118,    -1,   -12,    77,  -118,  -118,    67,
    -118,  -118,    66,  -117,  -118,  -118,   -26,   -80,  -118,    65,
     -82,    -2
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,    99,    18,    19,     7,    27,     8,
      21,    22,    23,    89,   100,   101,    39,    40,    87,    41,
      42,    43
  };

  const short
  Parser::yytable_[] =
  {
       9,     6,     4,     3,   123,   124,     4,   103,    52,   102,
      53,   129,    10,    24,    66,   109,    48,    11,    50,    44,
      90,    67,    20,    64,    65,    47,    45,    24,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      86,   103,   103,   102,   102,    12,    12,   103,    91,   102,
      26,    28,    12,    68,    12,    13,    69,    29,    30,    14,
      14,    70,   107,    71,   105,    88,    14,   106,    14,   108,
      16,    15,   112,    15,   121,   110,    16,   115,    16,   111,
     122,   116,    17,    17,   117,    67,   118,   104,   127,    17,
     128,    17,    66,    25,    46,    49,    51,     0,     0,   113,
     114,     0,     0,     0,    54,     0,     0,     0,     0,     0,
      55,    88,     0,    56,     0,     0,    57,    58,     0,     0,
       0,   104,   104,    59,    60,     0,     0,   104,    61,    62,
       0,    63,     0,     0,    54,     0,    72,     0,    64,    65,
      55,     0,     0,    56,     0,     0,    57,    58,     0,     0,
       0,    54,     0,    59,    60,     0,     0,    55,    61,    62,
      56,    63,     0,    57,    58,     0,   119,     0,    64,    65,
      59,    60,     0,     0,     0,    61,    62,     0,    63,     0,
       0,    54,     0,   120,     0,    64,    65,    55,     0,     0,
      56,     0,     0,    57,    58,     0,     0,     0,    54,     0,
      59,    60,     0,     0,    55,    61,    62,    56,    63,     0,
      57,    58,     0,     0,     0,    64,    65,    59,    60,    31,
       0,     0,    61,    32,     0,    63,     0,     4,     0,     0,
      33,     0,    64,    65,    34,    35,    36,     0,     0,    31,
       0,     0,     0,    32,     0,    85,     0,     4,     0,    37,
      33,    38,     0,     0,    34,    35,    36,    92,     0,    92,
      93,     0,    93,     4,    94,     4,    94,     0,     0,    37,
      92,    38,     0,    93,     0,     0,     4,    94,     0,    95,
      96,    95,   125,     0,     0,     0,    97,     0,    97,    98,
       0,    98,    95,   126,    92,     0,     0,    93,     0,    97,
       4,    94,    98,     0,     0,     0,    55,     0,     0,    56,
       0,     0,    57,    58,     0,    55,    95,   130,    -1,    59,
      60,    -1,    -1,    97,    61,     0,    98,    63,    -1,    -1,
       0,     0,     0,    -1,    64,    65,    63,     0,    32,     0,
       0,     0,     4,    64,    65,    33,     0,     0,     0,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,     0,    38
  };

  const short
  Parser::yycheck_[] =
  {
       2,     2,    17,     0,   121,   122,    17,    89,    34,    89,
      36,   128,    36,    15,    24,    97,    28,     6,    30,    34,
       7,    31,    21,    37,    38,    27,    27,    29,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,   123,   124,   123,   124,     5,     5,   129,    35,   129,
       4,    35,     5,    36,     5,     8,    36,     7,     6,    19,
      19,     6,    24,    21,    90,    67,    19,    93,    19,    95,
      29,    24,     4,    24,    21,    24,    29,     6,    29,    36,
      21,   107,    42,    42,   110,    31,   112,    89,    10,    42,
      21,    42,    24,    16,    27,    29,    31,    -1,    -1,    31,
      32,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
       9,   113,    -1,    12,    -1,    -1,    15,    16,    -1,    -1,
      -1,   123,   124,    22,    23,    -1,    -1,   129,    27,    28,
      -1,    30,    -1,    -1,     3,    -1,    35,    -1,    37,    38,
       9,    -1,    -1,    12,    -1,    -1,    15,    16,    -1,    -1,
      -1,     3,    -1,    22,    23,    -1,    -1,     9,    27,    28,
      12,    30,    -1,    15,    16,    -1,    35,    -1,    37,    38,
      22,    23,    -1,    -1,    -1,    27,    28,    -1,    30,    -1,
      -1,     3,    -1,    35,    -1,    37,    38,     9,    -1,    -1,
      12,    -1,    -1,    15,    16,    -1,    -1,    -1,     3,    -1,
      22,    23,    -1,    -1,     9,    27,    28,    12,    30,    -1,
      15,    16,    -1,    -1,    -1,    37,    38,    22,    23,     9,
      -1,    -1,    27,    13,    -1,    30,    -1,    17,    -1,    -1,
      20,    -1,    37,    38,    24,    25,    26,    -1,    -1,     9,
      -1,    -1,    -1,    13,    -1,    35,    -1,    17,    -1,    39,
      20,    41,    -1,    -1,    24,    25,    26,    11,    -1,    11,
      14,    -1,    14,    17,    18,    17,    18,    -1,    -1,    39,
      11,    41,    -1,    14,    -1,    -1,    17,    18,    -1,    33,
      34,    33,    34,    -1,    -1,    -1,    40,    -1,    40,    43,
      -1,    43,    33,    34,    11,    -1,    -1,    14,    -1,    40,
      17,    18,    43,    -1,    -1,    -1,     9,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,     9,    33,    34,    12,    22,
      23,    15,    16,    40,    27,    -1,    43,    30,    22,    23,
      -1,    -1,    -1,    27,    37,    38,    30,    -1,    13,    -1,
      -1,    -1,    17,    37,    38,    20,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    41
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    45,    46,     0,    17,    47,    48,    51,    53,    65,
      36,     6,     5,     8,    19,    24,    29,    42,    49,    50,
      21,    54,    55,    56,    65,    50,     4,    52,    35,     7,
       6,     9,    13,    20,    24,    25,    26,    39,    41,    60,
      61,    63,    64,    65,    34,    48,    53,    65,    49,    56,
      49,    63,    60,    60,     3,     9,    12,    15,    16,    22,
      23,    27,    28,    30,    37,    38,    24,    31,    36,    36,
       6,    21,    35,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    35,    60,    62,    65,    57,
       7,    35,    11,    14,    18,    33,    34,    40,    43,    48,
      58,    59,    61,    64,    65,    60,    60,    24,    60,    64,
      24,    36,     4,    31,    32,     6,    60,    60,    60,    35,
      35,    21,    21,    57,    57,    34,    34,    10,    21,    57,
      34
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      49,    49,    50,    50,    50,    51,    52,    52,    52,    53,
      54,    54,    55,    55,    56,    57,    57,    57,    58,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      65
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     1,     3,     5,
       1,     2,     1,     1,     1,     7,     3,     2,     0,     9,
       0,     1,     1,     3,     3,     0,     3,     2,     7,     7,
      11,     1,     3,     2,     2,     2,     2,     2,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     3,
       1
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
       0,   157,   157,   163,   170,   174,   178,   181,   186,   191,
     197,   201,   207,   211,   215,   220,   227,   230,   234,   237,
     244,   247,   252,   257,   263,   270,   273,   278,   284,   289,
     294,   300,   304,   309,   314,   319,   324,   329,   334,   338,
     342,   347,   352,   357,   362,   367,   372,   377,   382,   387,
     392,   397,   402,   407,   412,   417,   420,   427,   433,   440,
     446,   448,   450,   452,   454,   456,   458,   460,   463,   467,
     474
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
#line 1821 "parser.cc"

#line 480 "drewno_mars.yy"


void drewno_mars::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
