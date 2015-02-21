/*
 *Author: Sabato Ceruso
 *Date: 05/02/2015
*/
#include "RamMachine.h"


RamMachine::RamMachine()
{
	registers_.resize(1);
}


RamMachine::~RamMachine()
{
}


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


void RamMachine::read_code(string filename, string inputFilename, string outputFilename){
	
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
					aux.erase(remove_if(aux.begin(), aux.end(), ::isspace), aux.end());
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
	else {
		cerr << "Error en el fichero" << endl;
		throw 1;
	}
	file.close();

	for (int i = 0; i < ins.size(); i++){
		firstspace = ins[i].find_first_of(" \t\f\v\n\r");
		aux = ins[i].substr(0, firstspace);
		dummy.type_ = -1;
		dummy.opcode_ = -1;
		dummy.operando_ = -1;
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
			cerr << "No se reconoce la instruccion: " << ins[i] << "numero "<< i <<endl;
			error = true;
			break;
		}
                //cout << "La instruccion numero " << i <<" es: "<< ins[i] << endl;//***
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
	input_.setFile(inputFilename);
	try {
		input_.readFile();
	}
	catch (int) {
		throw;
	}
	output_.setFile(outputFilename);
}


void RamMachine::halt() {
	output_.writeFile();
	
}

void RamMachine::reset() {
	input_.reset();
	output_.reset(); 
	program_.set_pc(0);
	registers_.clear();
	registers_.push_back(0);
}


void  RamMachine::load(int type, int operando) {
	try {
		if (type == IMMEDIATE) {
			registers_[ACCUM] = operando;
		}
		else if (type == DIRECT) {
			registers_[ACCUM] = registers_[operando];
		}
		else if (type == POINTER) {
			registers_[ACCUM] = registers_[registers_[operando]];
		}
	}
	catch (...) {
		cerr << "Se esta intentando cargar un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::store(int type, int operando) {
	try {
		if (type == DIRECT) {
			if (operando >= registers_.size()) {
				registers_.resize(operando + 1, -65555);
			}
			registers_[operando] = registers_[ACCUM];
		}
		else if (type == POINTER) {
			if (operando >= registers_.size()) {
				cerr << "Intento de acceso a registros no inicializados." << endl;
				throw 0;
			}
			if (registers_[operando] >= registers_.size()) {
				registers_.resize(registers_[operando] + 1);
			}
			registers_[registers_[operando]] = registers_[ACCUM];
		}
	}
	catch (...) {
		throw;
	}
}


void RamMachine::add(int type, int operando) {
	try {
		if (type == IMMEDIATE) {
			registers_[ACCUM] += operando;
		}
		else if (type == DIRECT) {
			registers_[ACCUM] += registers_[operando];
		}
		else if (type == POINTER) {
			registers_[ACCUM] += registers_[registers_[operando]];
		}
	}
	catch (...) {
		cerr << "Se esta intentando operar con un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::sub(int type, int operando) {
	try {
		if (type == IMMEDIATE) {
			registers_[ACCUM] -= operando;
		}
		else if (type == DIRECT) {
			registers_[ACCUM] -= registers_[operando];
		}
		else if (type == POINTER) {
			registers_[ACCUM] -= registers_[registers_[operando]];
		}
	}
	catch (...) {
		cerr << "Se esta intentando operar con un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::mult(int type, int operando) {
	try {
		if (type == IMMEDIATE) {
			registers_[ACCUM] *= operando;
		}
		else if (type == DIRECT) {
			registers_[ACCUM] *= registers_[operando];
		}
		else if (type == POINTER) {
			registers_[ACCUM] *= registers_[registers_[operando]];
		}
	}
	catch (...) {
		cerr << "Se esta intentando operar con un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::div(int type, int operando) {
	
	try {
		if (type == IMMEDIATE) {
			if (operando == 0)
				throw 7;
			registers_[ACCUM] /= operando;
		}
		else if (type == DIRECT) {
			if (registers_[operando] == 0)
				throw 7;
			registers_[ACCUM] /= registers_[operando];
		}
		else if (type == POINTER) {
			if (registers_[registers_[operando]] == 0)
				throw 7;
			registers_[ACCUM] /= registers_[registers_[operando]];
		}
	}
	catch (int) {
		cerr << "Se esta intentando dividir por 0" << endl;
		throw;
	}
	catch (...) {
		cerr << "Se esta intentando operar con un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::read(int type, int operando) {

		if (type == DIRECT) {
			if (operando >= registers_.size()) {
				registers_.resize(operando + 1, -65555);
			}
			registers_[operando] = input_.read();
		}
		else if (type == POINTER) {
			if (operando >= registers_.size()) {
				cerr << "Intento de acceso a registros no inicializados." << endl;
				throw 0;
			}
			if (registers_[operando] >= registers_.size()) {
				registers_.resize(registers_[operando] + 1);
			}
			registers_[registers_[operando]] = input_.read();
		}
}


void RamMachine::write(int type, int operando) {

	try {
		if (type == IMMEDIATE) {
			output_.write(operando);
		}
		else if (type == DIRECT) {
			output_.write(registers_[operando]);
		}
		else if (type == POINTER) {
			output_.write(registers_[registers_[operando]]);
		}
	}
	catch (...) {
		cerr << "Se esta intentando operar con un registro no inicializado" << endl;
		throw;
	}
}


void RamMachine::jgtz(int operando) {
	if (registers_[ACCUM] > 0)
		program_.set_pc((operando));
}


void RamMachine::jzero(int operando) {
	if (registers_[ACCUM] == 0)
		program_.set_pc((operando));
}


void RamMachine::run(bool traza) {
	instruction ins;

	ins.opcode_ = -1;
	reset();
	while (ins.opcode_ != HALT) {
		
		ins = program_.run();
		
		try {
			switch (ins.opcode_) {
			case LOAD: load(ins.type_, ins.operando_); break;
			case STORE: store(ins.type_, ins.operando_); break;
			case ADD:  add(ins.type_, ins.operando_); break;
			case SUB: sub(ins.type_, ins.operando_); break;
			case MULT: mult(ins.type_, ins.operando_); break;
			case DIV: div(ins.type_, ins.operando_); break;
			case READ: read(ins.type_, ins.operando_); break;
			case WRITE: write(ins.type_, ins.operando_); break;
			case JUMP: program_.set_pc((ins.operando_)); break;
			case JGTZ: jgtz(ins.operando_); break;
			case JZERO: jzero(ins.operando_); break;
			case HALT: halt(); break;
			default:
				break;
			}
		}
		catch (...) {
			cerr << "Se ha producido un error durante la ejecucion" << endl;
			break;
		}

		imprimirInstruccion(ins);
		cout << endl;
		if (traza) {
			imprimirRegistros();
			getchar();
		}
	}

	cout <<"Se escribio: " << output_.toString() << endl;
}


void RamMachine::imprimirInstruccion(instruction ins) {
	//system("clear");

	//cout << "Instruccion: ";
	switch (ins.opcode_) {
	case LOAD: cout << "LOAD "; break;
	case STORE: cout << "STORE "; break;
	case ADD: cout << "ADD "; break;
	case SUB: cout << "SUB "; break;
	case MULT: cout << "MULT "; break;
	case DIV: cout << "DIV "; break;
	case READ: cout << "READ "; break;
	case WRITE: cout << "WRITE "; break;
	case JUMP: cout << "JUMP "; break;
	case JGTZ: cout << "JGTZ "; break;
	case JZERO: cout << "JZERO "; break;
	case HALT: cout << "HALT "; break;
	}

	if (ins.type_ == IMMEDIATE) 
		cout << "=" << ins.operando_;
	else if (ins.type_== DIRECT)
		cout << ins.operando_;
	else if (ins.type_ == POINTER)
		cout << "*" << ins.operando_;
	else if (ins.type_ == TAGJUMP) {
		cout << program_.get_tagName(ins.operando_);
	}
}


void RamMachine::imprimirRegistros() {
	cout << "Registros: " << endl;

	for (int i = 0; i < registers_.size(); i++) {
		cout << "R[" << i << "]: " << registers_[i] << endl;
	}
}


void RamMachine::imprimirPrograma() {
	string tag;
	
	for (int i = 0; i < program_.get_program().size(); i++) {
		cout << i << ":\t";
		imprimirInstruccion(program_.get_program()[i]);
		cout << endl;
	}

	cout << "Tags: " << endl;
	for (int i = 0; i < program_.get_program().size(); i++) {
		try {
			tag = program_.get_tagName(i);
			cout << tag << "-> line " << i << endl;
		}
		catch (int) {
			continue;
		}
	}
}


void RamMachine::imprimirInput() { cout << input_.toString() << endl; }


void RamMachine::imprimirOutput() { cout << output_.toString() << endl; }