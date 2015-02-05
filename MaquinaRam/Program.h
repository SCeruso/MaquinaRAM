/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#pragma once
#include "Tag.h"
#include <vector>

using namespace std;

enum { IMMEDIATE, DIRECT, POINTER, TAGJUMP };
enum { LOAD, STORE, ADD, SUB, MULT, DIV, READ, WRITE, JUMP, JGTZ, JZERO, HALT };

typedef struct {
	int opcode_;
	int type_;
	int operando_;
}instruction;

class Program
{
private: 
	vector<instruction> program_;
	int pc_;
	vector<Tag> tags_;
public:
	Program();
	~Program();
	void set_program(vector<instruction>, vector<Tag>);
	instruction run();
};

