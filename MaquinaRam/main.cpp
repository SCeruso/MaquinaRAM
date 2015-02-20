#include "RamMachine.h"

void help() {
	cout << "r: ver los registros" << endl;
	cout << "t : traza" << endl;
	cout << "g : go" << endl;
	cout << "s : desensamblador" << endl;
	cout << "i : ver cinta entrada" << endl;
	cout << "o : ver cinta salida" << endl;
	cout << "h : ayuda" << endl;
	cout << "x : salir" << endl;
}

int main(void) {
	RamMachine maquinona;
	char op = '0';
	maquinona.read_code("test3.txt");
	maquinona.run();




	while (op != 'x') {
		system("clear");
		cout << ">";
		switch (op)
		{
		case 'r': maquinona.imprimirRegistros(); break;
		case 't': maquinona.run(true); break;
		case 'g': maquinona.run(false); break;
		case 'i': maquinona.imprimirInput(); break;
		case 'o': maquinona.imprimirOutput(); break;
		case 's': maquinona.imprimirPrograma(); break;
		case 'h': help(); break;
		default:
			break;
		}
	}

	system("PAUSE");
	return 0;
}
