/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "../includes/Tape.h"


Tape::Tape() : tape_(), pos_(0)
{
}


Tape::~Tape()
{
	tape_.clear();
}

string Tape::toString(){
	stringstream aux;
	
	for (int i = 0; i < tape_.size(); i++) {
		aux << tape_[i];
		aux << " ";
	}

	return aux.str();
}


void Tape::setFile(string filename) { filename_ = filename; }


int Tape::get_pos() { return pos_; }
