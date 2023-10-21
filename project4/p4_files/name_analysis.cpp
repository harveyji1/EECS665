#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"
#include "errName.hpp"

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
    string varName = myID->getName();
    if(symTab->existsInCurrentScope(varName)){
		string varType = this->getTypeNode()->getType();
		if (varType == "void") {
			NameErr::badVarType(myID->pos());
		} 
		NameErr::multiDecl(myID->pos());
        nameAnalysisOk = false;
		return nameAnalysisOk;
    } else {
        string varType = this->getTypeNode()->getType();
		if (varType == "void") {
			NameErr::badVarType(myID->pos());
			nameAnalysisOk = false;
			return nameAnalysisOk;
		} 
        string varKind = "var";
        SemSymbol * newVarSymbol = new SemSymbol(varName, varKind, varType);
        symTab->insertSymbolIntoCurrentScope(newVarSymbol);
        myID->attachSymbol(newVarSymbol);
		if(myInit){
			nameAnalysisOk = nameAnalysisOk && myInit->nameAnalysis(symTab);
		}
		
    }
	/*bool nameAnalysisOk = true;
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
	}*/

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

    string funcName = myID->getName();

    TypeNode* retTypeNode = this->myRetType;
	if(symTab->searchscopes(retTypeNode->getType())){
		retTypeNode->nameAnalysis(symTab);
	}

	ClassTypeNode* classReturnType = dynamic_cast<ClassTypeNode*>(retTypeNode);
	if (classReturnType && !symTab->searchscopes(classReturnType->getType())) {
		NameErr::badVarType(classReturnType->pos());  
		nameAnalysisOk = false;
	}

    if (symTab->existsInCurrentScope(funcName)) {
        NameErr::multiDecl(myID->pos());
        nameAnalysisOk = false;
    }

    string returnType = "(";
    bool firstFormal = true;
    for(auto formal : *myFormals ){
        if(firstFormal){
            returnType += formal->getTypeNode()->getType();
            firstFormal = false;
        }else{
            returnType += "," + formal->getTypeNode()->getType();
        }
    }
    returnType += ")->" + myRetType->getType();

	
    
    string funcKind = "fn";
    SemSymbol * newFuncSymbol = new SemSymbol(funcName, funcKind, returnType);
    symTab->insertSymbolIntoCurrentScope(newFuncSymbol);
    myID->attachSymbol(newFuncSymbol);
	ScopeTable* newFnScope = new ScopeTable();
    symTab->insert(newFnScope);

    for (FormalDeclNode * formal : *myFormals) {
        string paramName = formal->ID()->getName();
        string paramType = formal->getTypeNode()->getType();

        if (paramType == "void") { 
            NameErr::badVarType(formal->ID()->pos());
            nameAnalysisOk = false;
        }

        if (symTab->existsInCurrentScope(paramName)) {
            NameErr::multiDecl(formal->ID()->pos());
            nameAnalysisOk = false;
        } else {
            string paramKind = "var";  
            SemSymbol * paramSymbol = new SemSymbol(paramName, paramKind, paramType);
            symTab->insertSymbolIntoCurrentScope(paramSymbol);
            formal->ID()->attachSymbol(paramSymbol);
        }
    }

    for (StmtNode * stmt : *myBody) {
        if(!stmt->nameAnalysis(symTab)) {
            nameAnalysisOk = false;
        }
    }

    symTab->remove();

    return nameAnalysisOk;
	/*bool nameAnalysisOk = true;
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
	return nameAnalysisOk;*/
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
		NameErr::badVarType(myID->pos());
		return false;
	}

	myID->attachSymbol(classSymbol);

	return true;

}

bool MemberFieldExpNode::nameAnalysis(SymbolTable* symTab){
	bool nameAnalysisOk = true;

	if(!(myBase->nameAnalysis(symTab))){
		NameErr::undeclID(myBase->pos());
		nameAnalysisOk=false;
	}

	if(!(myField->nameAnalysis(symTab))){
		nameAnalysisOk=false;
		 NameErr::undeclID(myField->pos());
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

    if (IDNode* idCallee = dynamic_cast<IDNode*>(myCallee)) {    
        SemSymbol * fnSymbol = symTab->searchscopes(idCallee->getName());
        if (fnSymbol) {
            idCallee->attachSymbol(fnSymbol);
        } else {

            nameAnalysisOk = false;
        }
    }  else{
			nameAnalysisOk = myCallee->nameAnalysis(symTab);
    }

    for (ExpNode * argExp : *myArgs) {
        if (IDNode* idArg = dynamic_cast<IDNode*>(argExp)) {    
            SemSymbol * argSymbol = symTab->searchscopes(idArg->getName());
            if (argSymbol) {
                idArg->attachSymbol(argSymbol);
            } else {
                nameAnalysisOk = false;
            }
        }else if (MemberFieldExpNode* memberFuncCall = dynamic_cast<MemberFieldExpNode*>(argExp)){
			memberFuncCall->getBase()->nameAnalysis(symTab);
			memberFuncCall->getField()->nameAnalysis(symTab);
			
		}
		 else {
            nameAnalysisOk &= argExp->nameAnalysis(symTab);
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
		NameErr::undeclID(myPos);
		return false;
	}
}

bool AssignStmtNode::nameAnalysis(SymbolTable* symTab) {
	 bool nameAnalysisOk = true;

    if (IDNode* idDst = dynamic_cast<IDNode*>(myDst)) {
        SemSymbol * dstSymbol = symTab->searchscopes(idDst->getName());
        if(dstSymbol){
            idDst->attachSymbol(dstSymbol);
        } else {
            nameAnalysisOk = false;
        }
    } else if (!myDst->nameAnalysis(symTab)) {
        nameAnalysisOk = false;
    }

    if (IDNode* idSrc = dynamic_cast<IDNode*>(mySrc)) {
        SemSymbol * srcSymbol = symTab->searchscopes(idSrc->getName());
        if(srcSymbol){
            idSrc->attachSymbol(srcSymbol);
        } else {
            nameAnalysisOk = false;
        }
    } else if (!mySrc->nameAnalysis(symTab)) {
        nameAnalysisOk = false;
    }

    return nameAnalysisOk;
}

bool ExpNode::nameAnalysis(SymbolTable * symTab){
	return true;
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
	if(myExp){
        return myExp->nameAnalysis(symTab);
    }
    

    return true;
}

bool MagicNode::nameAnalysis(SymbolTable * symTab) {
    return true;
}

bool AndNode::nameAnalysis(SymbolTable * symTab){

    bool leftOk = myExp1->nameAnalysis(symTab);
    bool rightOk = myExp2->nameAnalysis(symTab);


    
    return leftOk && rightOk; 
}

bool OrNode::nameAnalysis(SymbolTable * symTab){

    bool leftOk = myExp1->nameAnalysis(symTab);
    bool rightOk = myExp2->nameAnalysis(symTab);

    
    return leftOk && rightOk; 
}

bool NotNode::nameAnalysis(SymbolTable * symTab){
    
    bool operandOk = myExp->nameAnalysis(symTab);
    return operandOk; 
}

bool PostIncStmtNode::nameAnalysis(SymbolTable * symTab){
    
    return myLoc->nameAnalysis(symTab);
}

bool PostDecStmtNode::nameAnalysis(SymbolTable * symTab){
    
    return myLoc->nameAnalysis(symTab);
}


bool ExitStmtNode::nameAnalysis(SymbolTable * symTab){
    
    return true;
}


bool NegNode::nameAnalysis(SymbolTable * symTab){
    
    return myExp->nameAnalysis(symTab);
}

}
