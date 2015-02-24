/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#pragma once
#include <string>

using namespace std;

class Tag
{
private:
	string tag_;
	int line_;
public:
	Tag(string, int);
	Tag(string);
	~Tag();
	string get_tag();
	int get_line();
	bool operator == (Tag&);
};

