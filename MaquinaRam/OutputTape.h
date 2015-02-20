/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#pragma once

#include "Tape.h"

class OutputTape :
	public Tape
{
public:
	OutputTape();
	~OutputTape();

	void write(int);
	void reset();
};

