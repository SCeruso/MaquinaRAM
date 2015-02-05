/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "Tape.h"


Tape::Tape() : tape_(), pos_(0)
{
}


Tape::~Tape()
{
	tape_.clear();
}

string Tape::toString(){
	stringstream aux;
	
	for (int i = 0; tape_.size(); i++)
		aux << tape_[i];

	return aux.str();
}

int Tape::get_pos() {return pos_;}