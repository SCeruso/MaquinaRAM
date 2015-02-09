#include "RamMachine.h"

int main(void) {
	RamMachine maquinona;

	maquinona.read_code("test2.txt");
	maquinona.run();
	system("PAUSE");
	return 0;
}