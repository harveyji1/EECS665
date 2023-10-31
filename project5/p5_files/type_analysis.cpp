#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"
#include "types.hpp"
#include "name_analysis.hpp"
#include "type_analysis.hpp"
#include <iostream>

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
		global->typeAnalysis(ta, BasicType::produce(VOID));
	}

	//The type of the program node will never
	// be needed. We can just set it to VOID
	//(Alternatively, we could make our type 
	// be error if the DeclListNode is an error)
	ta->nodeType(this, BasicType::produce(VOID));
}

void FnDeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){

	//HINT: you might want to change the signature for
	// typeAnalysis on FnBodyNode to take a second
	// argument which is the type of the current 
	// function. This will help you to know at a 
	// return statement whether the return type matches
	// the current function

	//Note: this function may need extra code

	const DataType * retType = myRetType->getType();
	for (auto stmt : *myBody){
		stmt->typeAnalysis(ta, retType);
	}
}

void StmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	TODO("Implement me in the subclass");
}

void AssignStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
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
		return;
	}

	if(tgtType->asFn()){
		ta->errAssignOpd(myDst->pos());
		if(srcType->asFn()){
			ta->errAssignOpd(mySrc->pos());
		}
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	if (srcType->asFn() != nullptr){
		if (srcType->asFn()->getReturnType()->isVoid()){
			ta->errAssignOpd(mySrc->pos());
			ta->nodeType(this, ErrorType::produce());
			return;
		}
	}

	if (tgtType->asFn() || (srcType->asFn() && !mySrc->isFnCall()))
	{
		ta->errAssignOpd(mySrc->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	if (mySrc->isFnCall() && (tgtType == srcType->asFn()->getReturnType())) {
		ta->nodeType(this, tgtType);
		return;
	}


	//Done for testing, seems like mySrc->isFnCall() always returned false even if it is true
	//tried changing the function to virtual in ExpNode but that cause SegFaults

	// if (mySrc->isFnCall()){
	// 	ta->errAssignOpd(mySrc->pos());
	// 		ta->nodeType(this, ErrorType::produce());
	// 		return;
	// 	// if(srcType->asFn()->getReturnType()->isVoid()){
			
	// 	// }
	// }

	//While incomplete, this gives you one case for 
	// assignment: if the types are exactly the same
	// it is usually ok to do the assignment. One
	// exception is that if both types are function
	// names, it should fail type analysis

	// should be complete now ?
	if (tgtType == srcType){
		ta->nodeType(this, tgtType);
		return;
	}
	else{
		ta->errAssignOpr(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	
	//Some functions are already defined for you to
	// report type errors. Note that these functions
	// also tell the typeAnalysis object that the
	// analysis has failed, meaning that main.cpp
	// will print "Type check failed" at the end
	


	// Here, we set the type of the assignment
	// to void to indicate no error was found.
	// This step is optional, since you'll never
	// use the type of a statement
	ta->nodeType(this, BasicType::produce(VOID));

}

void ExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void DeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	TODO("Override me in the subclass");
}

void VarDeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	ta->nodeType(this, BasicType::produce(VOID));
}

void ClassDefnNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	ta->nodeType(this, BasicType::produce(VOID)); //think something is wrong here, with classes
}

void IDNode::typeAnalysis(TypeAnalysis * ta){
	// IDs never fail type analysis and always
	// yield the type of their symbol (which
	// depends on their definition)
	ta->nodeType(this, this->getSymbol()->getDataType());
}

void CallExpNode::typeAnalysis(TypeAnalysis * ta){
	bool error = false;
	SemSymbol * sym = myCallee->getSymbol();
	std::string myKind = sym->kindToString(sym->getKind());
	const DataType * fnType = sym->getDataType();
	if (myKind != "fn") {
		ta->errCallee(myCallee->pos());
		error = true;
	}
	else {
		const TypeList * formalTypes = fnType->asFn()->getFormalTypes();
		if (formalTypes->count() != myArgs->size())
		{
			ta->errArgCount(this->pos());
			ta->nodeType(this, ErrorType::produce());
		}
		else{
			ExpNode ** argArr = new ExpNode*[myArgs->size()];
			int arrPos = 0;
			for (auto arg : *myArgs) {
				argArr[arrPos] = arg;
				++arrPos;
			}
			
			arrPos = 0;
			const std::list<const DataType *> * types = formalTypes->getTypes(); 
			for (auto type : *types)
			{
				argArr[arrPos]->typeAnalysis(ta);
				auto argType = ta->nodeType(argArr[arrPos]);
				if (type != argType)
				{
					ta->errArgMatch(argArr[arrPos]->pos());
					error = true;
				}
				++arrPos;
			}
		}
	}
	if (error)
	{
		ta->nodeType(this, ErrorType::produce());
	}
	else {
		ta->nodeType(this, fnType->asFn()->getReturnType());
	}
}

void CallStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myCallExp->typeAnalysis(ta);
	ta->nodeType(this, ta->nodeType(myCallExp));
}

void ExitStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	ta->nodeType(this, BasicType::produce(CLASS));
}

void GiveStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	mySrc->typeAnalysis(ta);

	const DataType * SrcType = ta->nodeType(mySrc);

	if (SrcType->asFn() != nullptr)
	{
		ta->errOutputFn(mySrc->pos());
		ta->nodeType(this, ErrorType::produce());
	}

	if (SrcType->isVoid())
	{
		ta->errOutputVoid(mySrc->pos());
		ta->nodeType(this, ErrorType::produce());
	}

	if(SrcType->isClass()){
		ta->errOutputClass(mySrc->pos());
		ta->nodeType(this, ErrorType::produce());
	}

	if (SrcType->isBool() || SrcType->isInt() || SrcType->isString())
	{
		ta->nodeType(this, SrcType);
		return;
	}
	
}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myCond->typeAnalysis(ta);

	const DataType * CondType = ta->nodeType(myCond);

	if(CondType->asError()){
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	if (CondType->isBool())
	{
		for (auto stmtT : *myBodyTrue)
		{
			stmtT->typeAnalysis(ta,currentFnType);
		}
		for (auto stmtF : *myBodyFalse)
		{
			stmtF->typeAnalysis(ta,currentFnType);
		}
		ta->nodeType(this, BasicType::produce(VOID));
		return;
	}

	ta->errCond(myCond->pos());
	ta->nodeType(this, ErrorType::produce());
}

void IfStmtNode::typeAnalysis(TypeAnalysis * ta , const DataType * currentFnType){
	
	myCond->typeAnalysis(ta);

	const DataType * CondType = ta->nodeType(myCond);

	if(CondType->asError()){
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	if (CondType->isBool())
	{
		for (auto stmt : *myBody)
		{
			stmt->typeAnalysis(ta, BasicType::produce(VOID));
		}
		ta->nodeType(this, BasicType::produce(VOID));
		return;
	}

	ta->errCond(myCond->pos());
	ta->nodeType(this, ErrorType::produce());
}

void PostDecStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myLoc->typeAnalysis(ta);

	const DataType * LValType = ta->nodeType(myLoc);

	if (LValType->isInt() && LValType->asFn() == nullptr)
	{
		ta->nodeType(this, LValType);
		return;
	}
	
	ta->errMathOpd(myLoc->pos());
	ta->nodeType(this, ErrorType::produce());
}

void PostIncStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myLoc->typeAnalysis(ta);

	const DataType * LValType = ta->nodeType(myLoc);

	if (LValType->isInt() && LValType->asFn() == nullptr)
	{
		ta->nodeType(this, LValType);
		return;
	}
	
	ta->errMathOpd(myLoc->pos());
	ta->nodeType(this, ErrorType::produce());
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	const DataType * returnType;
	if (myExp)
	{
		myExp->typeAnalysis(ta);
		returnType = ta->nodeType(myExp);
	}
	else {
		returnType = BasicType::produce(VOID);
	}
	
	if (currentFnType->isVoid() && (returnType->isBool() || returnType->isInt()))
	{
		Position * p = new Position(myExp->pos(), myExp->pos());
		ta->extraRetValue(p);
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	if (!currentFnType->isVoid() && returnType->isVoid())
	{
		ta->errRetEmpty(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	if (returnType->asFn())
	{
		if (currentFnType != returnType->asFn()->getReturnType())
		{
			ta->errRetWrong(myExp->pos());
			ta->nodeType(this, ErrorType::produce());
			return;
		}
		ta->nodeType(this, ta->nodeType(myExp));
		return;
	}
	
	if (currentFnType != returnType)
	{
		ta->errRetWrong(myExp->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	
	
	ta->nodeType(this, ta->nodeType(myExp));
}

void TakeStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myDst->typeAnalysis(ta);

	const DataType * dstType = ta->nodeType(myDst);

	if (dstType->asFn() != nullptr)
	{
		ta->errReadFn(myDst->pos());
		ta->nodeType(this, ErrorType::produce());
	}

	if (dstType->isClass())
	{
		ta->errReadClass(myDst->pos());
		ta->nodeType(this, ErrorType::produce());
	}
	
	if (dstType->validVarType()){
		ta->nodeType(this, dstType);
		return;
	}
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * currentFnType){
	myCond->typeAnalysis(ta);

	const DataType * CondType = ta->nodeType(myCond);

	if (CondType->isBool() || currentFnType->isBool())
	{
		for (auto stmt : *myBody)
		{
			stmt->typeAnalysis(ta, currentFnType);
		}
		ta->nodeType(this, BasicType::produce(VOID));
		return;
	}
	ta->nodeType(this, ErrorType::produce());
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
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isBool())
		{
			ta->errLogicOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isBool() || !myExp1->isFnCall())
		{
			ta->errLogicOpd(this->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isBool())
		{
			ta->errLogicOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isBool() || !myExp2->isFnCall())
		{
			ta->errLogicOpd(this->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(BOOL));
}

void DivideNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(INT));
}

void EqualsNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);

	if (left->asFn() == nullptr)
	{
		if (right->asFn() == nullptr)
		{
			if (left == right)
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
		else {
			if (!myExp2->isFnCall())
			{
				ta->errEqOpd(myExp2->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
			
			if (left == right->asFn()->getReturnType())
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
	}
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);

	if (left->asFn() == nullptr)
	{
		if (right->asFn() == nullptr)
		{
			if (left == right)
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
		else {
			if (!myExp2->isFnCall())
			{
				ta->errEqOpd(myExp2->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
			
			if (left == right->asFn()->getReturnType())
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
	}
}

void GreaterNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errRelOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errRelOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(BOOL));
}

void LessEqNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errRelOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errRelOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(BOOL));
}

void LessNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errRelOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errRelOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(this->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(BOOL));
}

void MinusNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(INT));
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);

	if (left->asFn() == nullptr)
	{
		if (right->asFn() == nullptr)
		{
			if (left == right)
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
		else {
			if (!myExp2->isFnCall())
			{
				ta->errEqOpd(myExp2->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
			
			if (left == right->asFn()->getReturnType())
			{
				ta->nodeType(this, BasicType::produce(BOOL));
				return;
			}
			else {
				ta->errEqOpr(this->pos());
				ta->nodeType(this, ErrorType::produce());
				return;
			}
		}
	}
	
}

void OrNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isBool())
		{
			ta->errLogicOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isBool() || !myExp1->isFnCall())
		{
			ta->errLogicOpd(this->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isBool())
		{
			ta->errLogicOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isBool() || !myExp2->isFnCall())
		{
			ta->errLogicOpd(this->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(BOOL));
}

void PlusNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(INT));
}

void TimesNode::typeAnalysis(TypeAnalysis * ta){
	myExp1->typeAnalysis(ta);
	myExp2->typeAnalysis(ta);
	const DataType * left = ta->nodeType(myExp1);
	const DataType * right = ta->nodeType(myExp2);
	if (left->asFn() == nullptr)
	{
		if (!left->isInt())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	else {
		if (!left->asFn()->getReturnType()->isInt() || !myExp1->isFnCall())
		{
			ta->errMathOpd(myExp1->pos());
		}
	}
	if (right->asFn() == nullptr)
	{
		if (!right->isInt())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	else {
		if (!right->asFn()->getReturnType()->isInt() || !myExp2->isFnCall())
		{
			ta->errMathOpd(myExp2->pos());
		}
	}
	if (!ta->passed())
	{
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(INT));
}

void UnaryExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void NegNode::typeAnalysis(TypeAnalysis * ta){
	myExp->typeAnalysis(ta);

	const DataType * ExpType = ta->nodeType(myExp);

	//commented code creates segfault
	if (ExpType->isInt() /*|| ExpType->asFn()->getReturnType()->isInt()*/ )
	{
		ta->nodeType(this, ExpType);
		return;
	}

	// this fixes segfault

	if (ExpType->asFn() != nullptr)
	{
		if (ExpType->asFn()->getReturnType()->isInt()){
		ta->nodeType(this, ExpType);
		return;
		}
	}
	
	ta->errMathOpd(myExp->pos());
	ta->nodeType(this, ErrorType::produce());
}

void NotNode::typeAnalysis(TypeAnalysis * ta){
	myExp->typeAnalysis(ta);

	const DataType * ExpType = ta->nodeType(myExp);

	//commented code creates segfault
	if (ExpType->isInt() /*|| ExpType->asFn()->getReturnType()->isInt()*/ )
	{
		ta->nodeType(this, ExpType);
		return;
	}

	// this fixes segfault

	if (ExpType->asFn() != nullptr)
	{
		if (ExpType->asFn()->getReturnType()->isInt()){
		ta->nodeType(this, ExpType);
		return;
		}
	}
	
	ta->errLogicOpd(myExp->pos());
	ta->nodeType(this, ErrorType::produce());
}

}