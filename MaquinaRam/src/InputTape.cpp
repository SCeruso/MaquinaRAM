/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "../includes/InputTape.h"


InputTape::InputTape()
{
}


InputTape::~InputTape()
{
}


int InputTape::read()
{
	/*int x;

	cout << "Introduzca la entrada a leer: ";
	cin >> x;

	tape_.push_back(x);
	pos_++;
	
	return x;*/
	return tape_[pos_++];
}



void InputTape::readFile() {
	ifstream file;
	int aux;

	file.open(filename_.c_str());

	if (file.good()) {
		while (!file.eof()) {
			file >> aux;
			tape_.push_back(aux);
		}
		file.close();
	}

	else {
		cerr << "Error en el fichero con la cinta de entrada" << endl;
		throw 7;
	}
}
void InputTape::reset() {
	pos_ = 0;
}
