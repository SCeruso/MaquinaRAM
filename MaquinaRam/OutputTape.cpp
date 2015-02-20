/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "OutputTape.h"


OutputTape::OutputTape()
{
}

OutputTape::~OutputTape()
{
}

void OutputTape::write(int n) {
	tape_.push_back(n);
	pos_++;
}


void OutputTape::reset() { 
	pos_ = 0; 
	tape_.clear();
}