#include "RamMachine.h"

int main(void) {
	RamMachine maquinona;

	maquinona.read_code("test3.txt");
	maquinona.run();
	system("PAUSE");
	return 0;
}
