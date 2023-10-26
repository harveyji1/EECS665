#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"
#include "types.hpp"
#include "name_analysis.hpp"
#include "type_analysis.hpp"

namespace drewno_mars{

TypeAnalysis * TypeAnalysis::build(NameAnalysis * nameAnalysis){
	//To emphasize that type analysis depends on name analysis
	// being complete, a name analysis must be supplied for 
	// type analysis to be performed.
	TypeAnalysis * typeAnalysis = new TypeAnalysis();
	auto ast = nameAnalysis->ast;	
	typeAnalysis->ast = ast;

	ast->typeAnalysis(typeAnalysis);
	if (typeAnalysis->hasError){
		return nullptr;
	}

	return typeAnalysis;

}

void ProgramNode::typeAnalysis(TypeAnalysis * ta){

	//pass the TypeAnalysis down throughout
	// the entire tree, getting the types for
	// each element in turn and adding them
	// to the ta object's hashMap
	for (auto global : *myGlobals){
		global->typeAnalysis(ta);
	}

	//The type of the program node will never
	// be needed. We can just set it to VOID
	//(Alternatively, we could make our type 
	// be error if the DeclListNode is an error)
	ta->nodeType(this, BasicType::produce(VOID));
}

void FnDeclNode::typeAnalysis(TypeAnalysis * ta){

	//HINT: you might want to change the signature for
	// typeAnalysis on FnBodyNode to take a second
	// argument which is the type of the current 
	// function. This will help you to know at a 
	// return statement whether the return type matches
	// the current function

	//Note: this function may need extra code

	const DataType * retType = myRetType->getType();
	for (auto stmt : *myBody){
		stmt->typeAnalysis(ta);
	}
}

void StmtNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Implement me in the subclass");
}

void AssignStmtNode::typeAnalysis(TypeAnalysis * ta){
	//TODO: Note that this function is incomplete. 
	// and needs additional code

	//Do typeAnalysis on the subexpressions
	myDst->typeAnalysis(ta);
	mySrc->typeAnalysis(ta);

	const DataType * tgtType = ta->nodeType(myDst);
	const DataType * srcType = ta->nodeType(mySrc);


	// As error returns null if subType is NOT an error type
	// otherwise, it returns the subType itself. It 
	// sort of serves as a way to cast the subtype
	if (tgtType->asError() || srcType->asError()){
		ta->nodeType(this, ErrorType::produce());
	}


	//While incomplete, this gives you one case for 
	// assignment: if the types are exactly the same
	// it is usually ok to do the assignment. One
	// exception is that if both types are function
	// names, it should fail type analysis
	if (tgtType == srcType){
		ta->nodeType(this, tgtType);
		return;
	}
	
	//Some functions are already defined for you to
	// report type errors. Note that these functions
	// also tell the typeAnalysis object that the
	// analysis has failed, meaning that main.cpp
	// will print "Type check failed" at the end
	ta->errAssignOpr(this->pos());


	// Here, we set the type of the assignment
	// to void to indicate no error was found.
	// This step is optional, since you'll never
	// use the type of a statement
	ta->nodeType(this, BasicType::produce(VOID));

}

void ExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void DeclNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void VarDeclNode::typeAnalysis(TypeAnalysis * ta){
	// VarDecls always pass type analysis, since they 
	// are never used in an expression. You may choose
	// to type them void (like this), as discussed in class
	ta->nodeType(this, BasicType::produce(VOID));
}

void ClassDefnNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(VOID));
}

void IDNode::typeAnalysis(TypeAnalysis * ta){
	// IDs never fail type analysis and always
	// yield the type of their symbol (which
	// depends on their definition)
	ta->nodeType(this, this->getSymbol()->getDataType());
}

void CallExpNode::typeAnalysis(TypeAnalysis * ta){
	
}

void CallStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void ExitStmtNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(CLASS));
}

void GiveStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void IfStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void PostDecStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void PostIncStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void TakeStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * ta){
	
}

void IntLitNode::typeAnalysis(TypeAnalysis * ta){
	// IntLits never fail their type analysis and always
	// yield the type INT
	ta->nodeType(this, BasicType::produce(INT));
}

void TypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(VOID));
}

void TrueNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(BOOL));
}

void StrLitNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(VOID));
}

void FalseNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(STRING));
}

void MemberFieldExpNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, this->myField->getSymbol()->getDataType());
}

void BinaryExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void AndNode::typeAnalysis(TypeAnalysis * ta){
	
}

void DivideNode::typeAnalysis(TypeAnalysis * ta){
	
}

void EqualsNode::typeAnalysis(TypeAnalysis * ta){
	
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * ta){
	
}

void GreaterNode::typeAnalysis(TypeAnalysis * ta){
	
}

void LessEqNode::typeAnalysis(TypeAnalysis * ta){
	
}

void LessNode::typeAnalysis(TypeAnalysis * ta){
	
}

void MinusNode::typeAnalysis(TypeAnalysis * ta){
	
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * ta){
	
}

void OrNode::typeAnalysis(TypeAnalysis * ta){
	
}

void PlusNode::typeAnalysis(TypeAnalysis * ta){
	
}

void TimesNode::typeAnalysis(TypeAnalysis * ta){
	
}

void UnaryExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void NegNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void NotNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

}
