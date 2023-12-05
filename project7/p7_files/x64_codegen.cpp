#include <ostream>
#include "3ac.hpp"

namespace drewno_mars{

void IRProgram::allocGlobals(){
	//Choose a label for each global
	for (auto itr : globals) {
		SemSymbol* semSymbol = itr.first;
		SymOpd* symOpd = itr.second;
		std::string lbl = "gbl_" + semSymbol->getName();
		symOpd->setMemoryLoc(lbl);
	}
}

void IRProgram::datagenX64(std::ostream& out){
	out << ".data\n";
	for (auto itr : globals) {
		if (itr.first->getName() == "console") { continue; }
		SymOpd* symOpd = itr.second;
		out << symOpd->getMemoryLoc() << ": .quad 0\n";
	}

	for (auto itr : strings) {
		LitOpd* strLbl = itr.first;
		std::string myContent = itr.second;
		out << strLbl->valString() + ": .asciz "
			<< myContent << "\n";
	}
	//Put this directive after you write out strings
	// so that everything is aligned to a quadword value
	// again
	out << ".align 8\n";

}

void IRProgram::toX64(std::ostream& out){
	allocGlobals();
	datagenX64(out);
	// Iterate over each procedure and codegen it
	out << ".globl main\n";
	out << ".text\n";
	for (auto p : *procs) {
		p->toX64(out);
	}
}

void Procedure::allocLocals(){
	//Allocate space for locals
	// Iterate over each procedure and codegen it
	int count = -24;
	for (auto itr : locals) {
		SymOpd* symOpd = itr.second;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		symOpd->setMemoryLoc(memLoc);
		count -= int(symOpd->getWidth());
	}
	for (auto temp : temps) {
		AuxOpd* auxOpd = temp;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		auxOpd->setMemoryLoc(memLoc);
		count -= int(auxOpd->getWidth());
	}
	for (auto formal : formals) {
		SymOpd* symOpd = formal;
		std::string memLoc = std::to_string(count) + "(%rbp)";
		symOpd->setMemoryLoc(memLoc);
		count -= int(symOpd->getWidth());
	}
}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	enter->codegenLabels(out);
	enter->codegenX64(out);
	out << "#Fn body " << myName << "\n";
	for (auto quad : *bodyQuads){
		quad->codegenLabels(out);
		out << "#" << quad->toString() << "\n";
		quad->codegenX64(out);
	}
	out << "#Fn epilogue " << myName << "\n";
	leave->codegenLabels(out);
	leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream& out){
	if (labels.empty()){ return; }

	size_t numLabels = labels.size();
	size_t labelIdx = 0;
	for ( Label * label : labels){
		out << label->getName() << ": ";
		if (labelIdx != numLabels - 1){ out << "\n"; }
		labelIdx++;
	}
}

void BinOpQuad::codegenX64(std::ostream& out){
	BinOp op = this->getOp();
	if(op == ADD64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "addq " << "%rbx, " << "%rax\n" ;
		dst->genStoreVal(out, A);

	}
	
	else if(op == SUB64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "subq " << "%rbx, " << "%rax\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == DIV64)
	{
		src1->genLoadVal(out, D);
		src2->genLoadVal(out, A);
		out << "movq $0, %rdx\nidivq %rbx\nmovq %rax, %rbx\n";
		dst->genStoreVal(out, B);
	}
	else if(op == MULT64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "imulq %rbx, %rax\n";
		dst->genStoreVal(out, A);

	} 
	else if(op == EQ64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "sete " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == NEQ64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "setne " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == LT64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "setl " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == GT64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "setg " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == LTE64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "setle " << "%al\n" ;
		dst->genStoreVal(out, A);

	}

	else if(op == GTE64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%rbx, " << "%rax\n";
		out << "setge " << "%al\n";
		dst->genStoreVal(out, A);

	}

	else if(op == AND64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "andq " << "%rbx, " << "%rax\n" ;
		dst->genStoreVal(out, A);

	}
	
	else if(op == OR64)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "orq " << "%rax, " << "%rax\n" ;
		dst->genStoreVal(out, A);

	}

	if(op == ADD8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "addb " << "%bl, " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	
	else if(op == SUB8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "subb " << "%bl, " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == DIV8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "idivb " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == MULT8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "imulb " << "%al\n" ;
		dst->genStoreVal(out, A);

	} 
	else if(op == EQ8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "sete " << "%al\n";
		dst->genStoreVal(out, A);

	}
	else if(op == NEQ8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "setne " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == LT8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "setl " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == GT8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "setg " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	else if(op == LTE8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "setle " << "%al\n" ;
		dst->genStoreVal(out, A);

	}

	else if(op == GTE8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "cmpq " << "%bl, " << "%al\n";
		out << "setge " << "%al\n" ;
		dst->genStoreVal(out, A);

	}

	else if(op == AND8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "andb " << "%bl, " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
	
	else if(op == OR8)
	{
		src1->genLoadVal(out, A);
		src2->genLoadVal(out, B);
		out << "orb " << "%bl, " << "%al\n" ;
		dst->genStoreVal(out, A);

	}
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	if(op == NOT64) {
		out << "cmpq $0, %rax\n"
			<< "setz %al\n";
	} else if (op == NEG64) {
		out << "negq %rax\n";
	}
	else if (op == NOT8) {
		out << "cmpq $0, %al\n"
			<< "setz %al\n";
	}
	else if (op == NEG8) {
		out << "negb %al\n";
	}
	dst->genStoreVal(out, A);
}

void AssignQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	dst->genStoreVal(out, A);
}

void ReadQuad::codegenX64(std::ostream& out){
	if (myDst->locString() != "console") {
		myDst->genLoadVal(out, DI);
	} else {
		out << "movq $1, %rdi\n";
	}
	if (myDstType->isInt()) {
		out << "callq getInt\n";
	} else if (myDstType->isBool()) {
		out << "callq getBool\n";
	}
	myDst->genStoreVal(out, A);
}

void MagicQuad::codegenX64(std::ostream& out){
	out << "callq magic\n";
}

void ExitQuad::codegenX64(std::ostream& out){
	out << "call exit\n";
}

void WriteQuad::codegenX64(std::ostream& out){
	if (mySrc->locString() != "console") {

		mySrc->genLoadVal(out, SI);
	} else {
		out << "movq $0, %rsi\n";
	}
	mySrc->genLoadVal(out, DI);
	if (mySrcType->isInt()) {
		out << "callq printInt\n";
	} else if (mySrcType->isString()) {
		out << "callq printString\n";
	} else if (mySrcType->isBool()) {
		out << "callq printBool\n";
	}
}

void GotoQuad::codegenX64(std::ostream& out){
	out << "jmp " << tgt->getName() << "\n";
}

void IfzQuad::codegenX64(std::ostream& out){
	cnd->genLoadVal(out, DI);
    out << "cmpq $0, %rdi\n";
    out << "je " << tgt->toString();
}

void NopQuad::codegenX64(std::ostream& out){
	out << "nop" << "\n";
}

void CallQuad::codegenX64(std::ostream& out){
	out << "call " << sym->toString() << "\n";

	// get callee's number of args
	int numArgs = sym->getDataType()->asFn()->getFormalTypes()->size();

	if (numArgs >= 7 && numArgs % 2 != 0) {
		out << "pushq $0 \n";
	}
	out << "callq fun_" << sym->getName() << "\n";
	size_t cleanup;
	if (numArgs >= 7) {
		cleanup = 8*(numArgs-6);
		if (cleanup % 16 != 0) cleanup = cleanup + 8;
		out << "addq $" << cleanup << ", %rsp\n";
	}
}

void EnterQuad::codegenX64(std::ostream& out){
	out << "pushq %rbp\n";
	out << "movq %rsp, %rbp\n";
	out << "addq $16, %rbp\n";
	out << "subq $" << myProc->arSize() << ", %rsp\n";
}

void LeaveQuad::codegenX64(std::ostream& out){
	out << "addq $" << myProc->arSize() << ", %rsp\n";
	out << "popq %rbp\n";
	out << "retq\n";
}

void SetArgQuad::codegenX64(std::ostream& out){
	switch (index) { 
		case 1:
			opd->genLoadVal(out,DI);
			break;
		case 2:
			opd->genLoadVal(out,SI);
			break;
		case 3:
			opd->genLoadVal(out,B);	
			break;
		case 4:
			opd->genLoadVal(out,C);
			break;
		case 5:
			opd->genLoadVal(out, D);
			break;	
		default:
			opd->genLoadVal(out, A);
			out << "pushq %rax\n";
	}
}

void GetArgQuad::codegenX64(std::ostream& out){
	//do nothing
}

void SetRetQuad::codegenX64(std::ostream& out){
	opd->genLoadVal(out, A);
}

void GetRetQuad::codegenX64(std::ostream& out){
	opd->genStoreVal(out, A);
}

void LocQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
	//not needed
}

void SymOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void SymOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}

void SymOpd::genLoadAddr(std::ostream& out, Register reg) {
	TODO(Implement me if necessary)
}

void AuxOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void AuxOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " " << getReg(reg) << ", " << getMemoryLoc() << "\n";
}
void AuxOpd::genLoadAddr(std::ostream& out, Register reg){
	TODO(Implement me not needed)
}


void AddrOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genStoreAddr(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genLoadAddr(std::ostream & out, Register reg){
	TODO(Implement me)
}

void LitOpd::genLoadVal(std::ostream & out, Register reg){
	out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
}

}
