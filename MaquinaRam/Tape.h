/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/

#pragma once
#include <vector>
#include <string>
#include <sstream>
#include<fstream>
using namespace std;

class Tape
{
protected:
	vector<int> tape_;
	int pos_;
	string filename_;
public:
	Tape();
	~Tape();

	string toString();
	int get_pos();
	void setFile(string);
	virtual void reset();
};

