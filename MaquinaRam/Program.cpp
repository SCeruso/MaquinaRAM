/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "Program.h"


Program::Program() : pc_(-1)
{
}


Program::~Program()
{
}


void Program::set_program(vector<instruction> instrucciones, vector<Tag> etiquetas) {
	program_ = instrucciones;
	tags_ = etiquetas;
}


void Program::set_pc(int p) { pc_ = p; }


instruction Program::run() {

	pc_++;
	return program_[pc_]; 
}