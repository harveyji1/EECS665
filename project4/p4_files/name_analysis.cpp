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
	return nameAnalysisOk;
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	std::string fnType("");
	std::string comma = "";
	for (auto formal : *myFormals) {
		fnType.append(comma + formal->getTypeNode()->getType());
		comma = ",";
	}
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

}
