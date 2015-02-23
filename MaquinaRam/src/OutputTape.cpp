/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "../includes/OutputTape.h"


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



void OutputTape::writeFile() {
	ofstream file;

	file.open(filename_.c_str());

	if (file.good()) {
		for (int i = 0; i < tape_.size(); i++) 
			file << tape_[i];		
		file.close();
	}
	else {
		cerr << "Error en el fichero de escritura de cinta de salida" << endl;
		throw 10;
	}
}
void OutputTape::reset() { 
	pos_ = 0; 
	tape_.clear();
}
