/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "InputTape.h"


InputTape::InputTape()
{
}


InputTape::~InputTape()
{
}


int InputTape::read()
{
	int x;

	cout << "Introduzca la entrada a leer: ";
	cin >> x;

	tape_.push_back(x);
	pos_++;

	return x;
}
