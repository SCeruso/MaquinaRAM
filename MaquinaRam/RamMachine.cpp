/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "RamMachine.h"


RamMachine::RamMachine()
{
}


RamMachine::~RamMachine()
{
}

//Cuidado aca
bool RamMachine::add_tag(Tag t, vector<Tag>& tags) {
	for (int i = 0; i < tags.size(); i++) {
		if (tags[i] == t)
			return false;
	}
	tags.push_back(t);
	return true;

}


bool RamMachine::exist_tag(Tag t, vector<Tag>& tags) {
	for (int i = 0; i < tags.size(); i++){
		if (tags[i] == t)
			return true;
	}
	return false;
}

int RamMachine::get_tagLine(Tag t, vector<Tag>& tags) {
	for (int i = 0; i < tags.size(); i++){
		if (tags[i] == t)
			return tags[i].get_line();
	}
}
void RamMachine::read_code(string filename){
	
	vector<string> ins;
	ifstream file;
	string aux;
	char reader[80];
	int comment;
	int tagsymbol;
	int firstspace, firstnotspace;
	Tag* tag;
	vector<Tag> tags;
	vector<instruction> coded;
	instruction dummy;
	bool error = false; 

	file.open(filename.c_str());

	if (file.good()) {
		while (!file.eof()){
			file.getline(reader, 255);
			aux = reader;
			comment = aux.find(";");
		
			if (comment != string::npos) 
				aux = aux.substr(0, comment);
						
			if (aux.length() != 0 && (aux.find_first_not_of(" \t\f\v\n\r") != string::npos)) {
				ins.push_back(aux);
				if ((tagsymbol = ins.back().find(":")) != string::npos) { //Mejorar para que no ponga dos ':'
					aux = ins.back().substr(0, tagsymbol);
					aux.erase(remove_if(aux.begin(), aux.end(), isspace), aux.end());
					tag = new Tag(aux, (ins.size() - 1));
					if (!add_tag(*tag, tags)){
						cerr << "La etiqueta: " << tag->get_tag() << " esta repetida." << endl;
						error = true;
						delete tag;
						break;
					}
					delete tag;
					ins.back() = ins.back().substr(tagsymbol + 1);
				}

				ins.back().erase(0, ins.back().find_first_not_of(" \t\f\v\n\r"));
				ins.back().erase(ins.back().find_last_not_of(" \t\f\v\n\r") + 1);
			}
		}
	}
	else
		throw 1;
	file.close();

	for (int i = 0; i < ins.size(); i++){
		firstspace = ins[i].find_first_of(" \t\f\v\n\r");
		aux = ins[i].substr(0, firstspace);

		if (aux.c_str() == (string)"LOAD") {
			dummy.opcode_ = LOAD;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"STORE") {
			dummy.opcode_ = STORE;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"ADD") {
			dummy.opcode_ = ADD;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"SUB") {
			dummy.opcode_ = SUB;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"MULT") {
			dummy.opcode_ = MULT;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"DIV") {
			dummy.opcode_ = DIV;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"READ") {
			dummy.opcode_ = READ;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"WRITE") {
			dummy.opcode_ = WRITE;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"JUMP") {
			dummy.opcode_ = JUMP;
			dummy.type_ = TAGJUMP;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"JGTZ") {
			dummy.opcode_ = JGTZ;
			dummy.type_ = TAGJUMP;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"JZERO") {
			dummy.opcode_ = JZERO;
			dummy.type_ = TAGJUMP;
			coded.push_back(dummy);
		}
		else if (aux.c_str() == (string)"HALT") {
			dummy.opcode_ = HALT;
			coded.push_back(dummy);
		}
		else {
			cerr << "No se reconoce la instruccion: " << aux << endl;
			error = true;
			break;
		}
		//Estudiar el halt y jump

		if (coded[i].opcode_ == HALT) {
			if (ins[i] != "HALT") {
				error = true;
				cerr << "Error en la instruccion " << i << endl;
				break;
			}
		}
		else if (coded[i].type_ == TAGJUMP) {
			firstnotspace = ins[i].find_first_not_of(" \t\f\v\n\r", firstspace);
			aux = ins[i].substr(firstnotspace);
			tag = new Tag(aux);
			if (!exist_tag(*tag, tags)){
				error = true;
				cerr << "Error en el operando de la instruccion " << i << endl;
				break;
			}
			coded[i].operando_ = get_tagLine(*tag, tags);
			delete tag;
		}
		else {
			firstnotspace = ins[i].find_first_not_of(" \t\f\v\n\r", firstspace);
			aux = ins[i].substr(firstnotspace);

			if (aux[0] >= 48 && aux[0] <= 57){
				if (aux.find_first_not_of("1234567890") != string::npos) {
					error = true;
					cerr << "Error en el operando de la instruccion " << i << endl;
					break;
				}
				coded[i].type_ = DIRECT;
				coded[i].operando_ = atoi(aux.c_str());
			}
			else if (aux[0] == '*'){
				aux = aux.substr(1);
				if (aux.length() == 0 || aux.find_first_not_of("1234567890") != string::npos) {
					error = true;
					cerr << "Error en el operando de la instruccion " << i << endl;
					break;
				}
				coded[i].type_ = POINTER;
				coded[i].operando_ = atoi(aux.c_str());
			}
			else if (aux[0] == '=') {
				aux = aux.substr(1);
				if (aux.length() == 0 || aux.find_first_not_of("1234567890") != string::npos || coded[i].opcode_ == STORE || coded[i].opcode_ == READ) {
					error = true;
					cerr << "Error en el operando de la instruccion " << i << endl;
					break;
				}
				coded[i].type_ = IMMEDIATE;
				coded[i].operando_ = atoi(aux.c_str());
			}
			else {
				error = true;
				cerr << "Error en el operando de la instruccion " << i << endl;
				break;
			}
		}
	}

	program_.set_program(coded, tags);
}