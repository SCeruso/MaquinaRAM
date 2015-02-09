#include "RamMachine.h"

int main(int argc, char* argv[]) {
	RamMachine maquinona;

	maquinona.read_code(argv[1]);
	maquinona.run();

//	system("PAUSE");
	return 0;
}
