/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#pragma once

#include "Tape.h"
#include <iostream>

class InputTape :
	public Tape
{
public:
	InputTape();
	~InputTape();
	int read();
};

