#include "grafo.hpp"

using namespace std;

int main(void)
{
	//system("clear");
	puts("Bem vindo ao utilitário de grafos de Leo e Lucas!");
	int res = 0;

	Grafo g;

	// Loop do menu
	do { res = menu(&g); } while (res != 0);

	return 0;
}
