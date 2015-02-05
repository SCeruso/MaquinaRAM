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

instruction Program::run() {

	pc_++;
	while (true){
		if (program_[pc_].type_ == JUMP) {
			//GESTIONAR SALTO
		}
		else
			return program_[pc_]; 
	}
}