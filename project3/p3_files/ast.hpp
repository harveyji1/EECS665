#ifndef DREWNO_MARS_AST_HPP
#define DREWNO_MARS_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"
#include <cassert>


/* You'll probably want to add a bunch of ASTNode subclasses */

namespace drewno_mars{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/
class DeclNode;
class TypeNode;
class StmtNode;
class IDNode;
class ExpNode;
class IDNode;
class CallExpNode;
class ExpNode;
class VarDeclNode;
class IntTypeNode;
class BoolTypeNode;
class VoidTypeNode;
class BinaryExpNode;
class AndNode;
class DivideNode;
class EqualsNode;
class GreaterEqNode;
class LessEqNode;
class GreaterNode;
class LessNode;
class OrNode;
class MinusNode;
class NotEqualsNode;
class PlusNode;
class TimesNode;
class CallExpNode;
class FalseNode;
class IDNode;
class IntLitNode;
class StrLitNode;
class TrueNode;
class UnaryExpNode;
class NegNode;
class NotNode;
class ClassDefnNode;
class FnDeclNode;
class VarDeclNode;
class FormalDeclNode;
class StmtNode;
class AssignStmtNode;
class LocNode;

/** 
* class ASTNode
* Base class for all other AST Node types
**/
class ASTNode{
public:
	ASTNode(const Position * p) : myPos(p){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
	const Position * pos() { return myPos; }
	std::string posStr() { return pos()->span(); }
protected:
	const Position * myPos = nullptr;
};

/** 
* class ProgramNode
* Class that contains the entire abstract syntax tree for a program.
* Note the list of declarations encompasses all global declarations
* which includes (obviously) all global variables and struct declarations
* and (perhaps less obviously), all function declarations
**/
class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn) ;
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};

class StmtNode : public ASTNode{
public:
	StmtNode(const Position * p) : ASTNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

class ExpNode : public ASTNode{
public:
	ExpNode(const Position * p) : ASTNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

class DeclNode : public StmtNode{
public:
	DeclNode(const Position * p) : StmtNode(p) { }
	void unparse(std::ostream& out, int indent) override = 0;
};

class ClassDefnNode : public DeclNode {
	public:
	ClassDefnNode(const Position * p): DeclNode(p) { }
	void unparse(std::ostream& out, int indent) = 0;
};

class LocNode : public ExpNode{
public:
	LocNode(const Position * p)
	: ExpNode(p) {}
	void unparse(std::ostream& out, int indent) = 0;
};

/** An identifier. Note that IDNodes subclass
 * LocNode because they are a type of memory location. 
**/
class IDNode : public LocNode{
public:
	IDNode(const Position * p, std::string nameIn) : LocNode(p), name(nameIn){ }
	void unparse(std::ostream& out, int indent);
private:
	/** The name of the identifier **/
	std::string name;
};

/** A variable declaration
**/
class VarDeclNode : public DeclNode{
public:
	VarDeclNode(const Position * p, IDNode * inID, TypeNode * inType) 
	: DeclNode(p), myID(inID), myType(inType){
		assert (myType != nullptr);
		assert (myID != nullptr);
	}
	//add second constructor
	VarDeclNode(const Position * p, IDNode * inID, TypeNode * inType, ExpNode * inExp) 
	: DeclNode(p), myID(inID), myType(inType), myExp(inExp){
		assert (myType != nullptr);
		assert (myID != nullptr);
		assert (myExp != nullptr);
	}
	void unparse(std::ostream& out, int indent);
private:
	IDNode * myID;
	TypeNode * myType;
	ExpNode * myExp;
};

/** A memory location. LocNodes subclass ExpNode
 * because they can be used as part of an expression. 
**/


class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: ExpNode(p), myLhs(lhs), myRhs(rhs){
		assert (myLhs != nullptr);
		assert (myRhs != nullptr);
	}
	void unparse(std::ostream& out, int indent) override = 0;
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class AndNode : public BinaryExpNode{
public:
	AndNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class DivideNode : public BinaryExpNode{
public:
	DivideNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class EqualsNode : public BinaryExpNode{
public:
	EqualsNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class GreaterEqNode : public BinaryExpNode{
public:
	GreaterEqNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class GreaterNode : public BinaryExpNode{
public:
	GreaterNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class LessEqNode : public BinaryExpNode{
public:
	LessEqNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class LessNode : public BinaryExpNode{
public:
	LessNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class MinusNode : public BinaryExpNode{
public:
	MinusNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class NotEqualsNode : public BinaryExpNode{
public:
	NotEqualsNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class OrNode : public BinaryExpNode{
public:
	OrNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class PlusNode : public BinaryExpNode{
public:
	PlusNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class TimesNode : public BinaryExpNode{
public:
	TimesNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: BinaryExpNode(p, lhs, rhs), myLhs(lhs), myRhs(rhs) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode * myLhs;
	ExpNode * myRhs;
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(const Position * p , LocNode* dest) : StmtNode(p), m_dest(dest) { }
	AssignStmtNode(const Position * p , ExpNode* sourceExpr) : StmtNode(p), m_sourceExpr(sourceExpr) { }
	void unparse(std::ostream& out, int indent) override;
	LocNode* m_dest;
	ExpNode* m_sourceExpr;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(const Position * p, CallExpNode* func)
	: StmtNode(p), m_func(func){ }
	void unparse(std::ostream& out, int indent) override;
	CallExpNode* m_func;
};

class FormalDeclNode : public VarDeclNode{
public:
	FormalDeclNode(const Position * p, TypeNode * type, IDNode * id)
	: VarDeclNode(p, id, type),  myType(type), myId(id) { }
	void unparse(std::ostream& out, int indent) override;
private:
	TypeNode * myType;
	IDNode * myId;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(const Position * p, TypeNode * type, IDNode * id, std::list<FormalDeclNode * > * paramIn, std::list<StmtNode * > * funcBody)
	: DeclNode(p), myType(type), myId(id), parameters(paramIn), functionBody(funcBody) { }
	void unparse(std::ostream& out, int indent) override;
private:
	TypeNode * myType;
	IDNode * myId;
	std::list<FormalDeclNode * > *parameters;
	std::list<StmtNode * > *functionBody;
};


//Double Check this
class ExitStmtNode : public StmtNode{
public:
	ExitStmtNode(const Position * p) : StmtNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

//Double Check this
class GiveStmtNode : public StmtNode{
public:
	GiveStmtNode(const Position * p) : StmtNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(const Position * p , ExpNode * condition, std::list<StmtNode*>* tbody, std::list<StmtNode*>* fbody ) 
	: StmtNode(p), m_condition(condition), m_tbody(tbody) ,m_fbody(fbody) { }
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode* m_condition;
	std::list<StmtNode * > * m_tbody;
	std::list<StmtNode * > * m_fbody;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(const Position * p , ExpNode* condition , std::list<StmtNode*>* body) 
	: StmtNode(p), m_condition(condition), m_ifBody(body) { }
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode* m_condition;
	std::list<StmtNode * > * m_ifBody;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(const Position * p , LocNode* var) : StmtNode(p), m_var(var) { }
	void unparse(std::ostream& out, int indent) override;
	private:
	LocNode* m_var;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(const Position * p , LocNode* var) : StmtNode(p), m_var(var) { }
	void unparse(std::ostream& out, int indent) override;
	private:
		LocNode* m_var;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(const Position * p , ExpNode* expr) : StmtNode(p), m_expr(expr) { }
	ReturnStmtNode(const Position * p) : StmtNode(p) {}
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode* m_expr;
};

class TakeStmtNode : public StmtNode{
public:
	TakeStmtNode(const Position * p , LocNode* var) : StmtNode(p), m_var(var) { }
	void unparse(std::ostream& out, int indent) override;
	private:
		LocNode* m_var;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(const Position * p , ExpNode* condition, std::list<StmtNode*>* body ) 
	: StmtNode(p), m_condition(condition), m_whileBody(body) { }
	void unparse(std::ostream& out, int indent) override;
	private:
	ExpNode* m_condition;
	std::list<StmtNode * > * m_whileBody;
};



/** \class DeclNode
* Superclass for declarations (i.e. nodes that can be used to 
* declare a struct, function, variable, etc).  This base class will 
**/


/**  class ExpNode
* Superclass for expression nodes (i.e. nodes that can be used as
* part of an expression).  Nodes that are part of an expression
* should inherit from this abstract superclass.
**/

class TrueNode : public ExpNode{
public:
	TrueNode(const Position * p) : ExpNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class FalseNode : public ExpNode{
public:
	FalseNode(const Position * p) : ExpNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(const Position * p, std::string val) : ExpNode(p), stringVal(val) {}
	void unparse(std::ostream& out, int indent) override;
private:
	std::string stringVal;
};

class CallExpNode : public ExpNode{
public:
	CallExpNode(const Position * p, LocNode* name) : ExpNode(p), m_nameFunc(name){ }
	CallExpNode(const Position * p, LocNode* name, std::list<ExpNode*>* arg) : ExpNode(p), m_nameFunc(name), m_arg(arg) {}
	void unparse(std::ostream& out, int indent) override;
private:
	LocNode* m_nameFunc;
	std::list<ExpNode*>* m_arg;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(const Position * p, int val) : ExpNode(p), m_numval(val){ }
	void unparse(std::ostream& out, int indent) override;
private:
	int m_numval;
};

class MagicNode : public ExpNode{
public:
	MagicNode(const Position * p, int val) : ExpNode(p), m_magic(val){ }
	void unparse(std::ostream& out, int indent) override;
private:
	int m_magic;
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(const Position * p, ExpNode* expr) : ExpNode(p), m_expr(expr){ }
	void unparse(std::ostream& out, int indent) override = 0;
private:
	ExpNode* m_expr;
};

class NegNode : public UnaryExpNode{
public:
	NegNode(const Position * p, ExpNode* expr) : UnaryExpNode(p, expr) { }
	void unparse(std::ostream& out, int indent) override;
};

class NotNode  : public UnaryExpNode{
public:
	NotNode(const Position * p, ExpNode* expr) : UnaryExpNode(p, expr) { }
	void unparse(std::ostream& out, int indent) override;
};

/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in 
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(const Position * p) : ASTNode(p){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class ClassTypeNode : public TypeNode{
public:
	ClassTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class PerfectTypeNode : public TypeNode{
public:
	PerfectTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

//Double check this
class MemberFieldExpNode : public LocNode{
public:
	MemberFieldExpNode(const Position * p, LocNode* baseClass) : LocNode(p), m_baseClass(baseClass){}
	MemberFieldExpNode(const Position * p, IDNode* fieldName) : LocNode(p), m_fieldName(fieldName){}
private:
	LocNode* m_baseClass;
	IDNode* m_fieldName;
};

} //End namespace drewno_mars

#endif
