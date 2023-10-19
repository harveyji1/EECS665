#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"

namespace drewno_mars{

//TODO here is a subset of the nodes needed to do nameAnalysis, 
// you should add the rest to allow for a complete treatment
// of any AST

bool ASTNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	bool res = true;
	ScopeTable * global = new ScopeTable();
	symTab->insert(global);
	for (auto global : *myGlobals){
		res = global->nameAnalysis(symTab) && res;
	}
	symTab->remove();
	return res;
}

bool VarDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	if (myType->getType().compare("void") == 0)
	{
		std::cerr << "FATAL " << myPos->begin() << ": Invalid type in declaration\n";
		return false;
	}	
	
	SemSymbol * varDeclSymbol = new SemSymbol(myID->getName(), std::string("var"), myType->getType());
	myID->attachSymbol(varDeclSymbol);
	nameAnalysisOk = symTab->insertSymbolIntoCurrentScope(varDeclSymbol);
	if (!nameAnalysisOk)
	{
		std::cerr << "FATAL " << myPos->begin() << ": Multiply declared identifier\n";
		return false;
	}

	//not quite printing the right thing

	TypeNode* typeNode = this->getTypeNode();
	ClassTypeNode* classType = dynamic_cast<ClassTypeNode*>(typeNode);
	if(classType){
			if(!classType->nameAnalysis(symTab)){
				nameAnalysisOk = false;
			}
	}

	return nameAnalysisOk;
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	std::string fnType("");
	std::string comma = "";
	fnType.append("(");
	for (auto formal : *myFormals) {
		fnType.append(comma + formal->getTypeNode()->getType());
		comma = ",";
	}
	fnType.append(")");
	fnType.append("->" + myRetType->getType());

	SemSymbol * fnDeclSymbol = new SemSymbol(myID->getName(), std::string("fn"), fnType);
	myID->attachSymbol(fnDeclSymbol);
	nameAnalysisOk = symTab->insertSymbolIntoCurrentScope(fnDeclSymbol);
	if (nameAnalysisOk)
	{
		ScopeTable * fnScope = new ScopeTable();
		symTab->insert(fnScope);
		for (auto formal : *myFormals) {
			nameAnalysisOk = formal->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				return false;
			}
		}
		for (auto stmt : *myBody) {
			nameAnalysisOk = stmt->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		symTab->remove();
		return true;
	}
	return nameAnalysisOk;
}

bool ClassDefnNode::nameAnalysis(SymbolTable * symTab){ 

	bool nameAnalysisOk = true;
	std::string classType(myID->getName());
	SemSymbol * classDeclSymbol = new SemSymbol(myID->getName(), std::string("class"), classType);
	nameAnalysisOk = symTab->insertSymbolIntoCurrentScope(classDeclSymbol);
	myID->attachSymbol(classDeclSymbol);
	ScopeTable* classScope = new ScopeTable();
	symTab->insert(classScope);
	

	if (nameAnalysisOk)
	{
		for (auto members : *myMembers) {
			nameAnalysisOk = members->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		classDeclSymbol->setAssociatedScope(classScope); //this line is causing the issue!
		symTab->remove();
	}
	return nameAnalysisOk;
	
}

bool ClassTypeNode::nameAnalysis(SymbolTable* symTab){
	std::string className = myID->getName();

	SemSymbol* classSymbol = symTab->searchscopes(className);
	if(!classSymbol || classSymbol->getKind() != "class"){
		std::cerr << "FATAL " << myPos->begin() << ": Multiply declared identifier\n";
		return false;
	}

	myID->attachSymbol(classSymbol);

	return true;

}

bool MemberFieldExpNode::nameAnalysis(SymbolTable* symTab){
	bool nameAnalysisOk = true;

	if(!(myBase->nameAnalysis(symTab))){
		std::cerr << "FATAL " << myPos->begin() << ": Undeclared identifier";
		nameAnalysisOk=false;
	}

	if(!(myField->nameAnalysis(symTab))){
		nameAnalysisOk=false;
		std::cerr << "FATAL " << myPos->begin() << ": member variable";
	}

	return nameAnalysisOk;
}

bool IntTypeNode::nameAnalysis(SymbolTable* symTab){
	// Name analysis may never even recurse down to IntTypeNode,
	// but if it does, just return true to indicate that 
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool BoolTypeNode::nameAnalysis(SymbolTable* symTab) {
	return true;
}

bool VoidTypeNode::nameAnalysis(SymbolTable* symTab) {
	return true;
}

bool CallExpNode::nameAnalysis(SymbolTable* symTab) {
	bool nameAnalysisOk = true;
	nameAnalysisOk = myCallee->nameAnalysis(symTab);
	if (nameAnalysisOk)
	{
		for (auto arg : *myArgs )
		{
			nameAnalysisOk = arg->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				return false;
			}
		}
	}
	return nameAnalysisOk;
}

bool CallStmtNode::nameAnalysis(SymbolTable* symTab) {
	return myCallExp->nameAnalysis(symTab);
}

void IDNode::attachSymbol(SemSymbol* sym) {
	mySymbol = sym;
}

bool IDNode::nameAnalysis(SymbolTable* symTab) {
	SemSymbol * existingSymbol = symTab->searchscopes(name);
	if (existingSymbol != nullptr)
	{
		mySymbol = existingSymbol;
		return true;
	}
	else {
		std::cerr << "FATAL " << myPos->begin() << ": Undeclared identifier\n";
		return false;
	}
}

bool AssignStmtNode::nameAnalysis(SymbolTable* symTab) {
	return myDst->nameAnalysis(symTab);
}

bool UnaryExpNode::nameAnalysis(SymbolTable* symTab) {
	return myExp->nameAnalysis(symTab);
}

bool BinaryExpNode::nameAnalysis(SymbolTable* symTab) {
	bool nameAnalysisOk = myExp1->nameAnalysis(symTab);
	if (nameAnalysisOk)
	{
		return myExp2->nameAnalysis(symTab);
	}
	return false;
}

bool TakeStmtNode::nameAnalysis(SymbolTable* symTab) {
	return myDst->nameAnalysis(symTab);
}

bool GiveStmtNode::nameAnalysis(SymbolTable* symTab) {
	return mySrc->nameAnalysis(symTab);
}

bool IfStmtNode::nameAnalysis(SymbolTable* symTab) {
	bool nameAnalysisOk = myCond->nameAnalysis(symTab);
	if (nameAnalysisOk)
	{
		ScopeTable * ifScope = new ScopeTable();
		symTab->insert(ifScope);
		for (auto stmt : *myBody) {
			nameAnalysisOk = stmt->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		symTab->remove();
		return true;
	}
	return false;
}

bool IfElseStmtNode::nameAnalysis(SymbolTable* symTab) {
	bool nameAnalysisOk = myCond->nameAnalysis(symTab);
	if (nameAnalysisOk)
	{
		ScopeTable * ifScope = new ScopeTable();
		symTab->insert(ifScope);
		for (auto stmt : *myBodyTrue) {
			nameAnalysisOk = stmt->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		symTab->remove();
		ScopeTable * elseScope = new ScopeTable();
		symTab->insert(elseScope);
		for (auto stmt : *myBodyFalse) {
			nameAnalysisOk = stmt->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		symTab->remove();
		return true;
	}
	return false;
}

bool WhileStmtNode::nameAnalysis(SymbolTable* symTab) {
	bool nameAnalysisOk = myCond->nameAnalysis(symTab);
	if (nameAnalysisOk)
	{
		ScopeTable * whileScope = new ScopeTable();
		symTab->insert(whileScope);
		for (auto stmt : *myBody) {
			nameAnalysisOk = stmt->nameAnalysis(symTab);
			if (!nameAnalysisOk)
			{
				symTab->remove();
				return false;
			}
		}
		symTab->remove();
		return true;
	}
	return false;
}

bool ReturnStmtNode::nameAnalysis(SymbolTable* symTab) {
	return myExp->nameAnalysis(symTab);
}



}