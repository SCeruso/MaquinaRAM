/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/

#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Tape
{
protected:
	vector<int> tape_;
	int pos_;
public:
	Tape();
	~Tape();
	string toString();
	int get_pos();
};

