#include "grafo.hpp"

using namespace std;

/** Notas:
 *  Matriz de adjacência: Cada célula <x, y> indica o número de arestas ligando aqueles vértices.
 *	Em grafo não-direcionado: usa-se somente a parte triangular superior da matriz.
 *	Em grafo direcionado: usa-se a tabela inteira (não é simétrica).
 *	Grau de um vértice: somatório do valor da linha do vértice.
 *	Grau de entrada: somatório da coluna do vértice.
 *	Grau de saída: somatório da linha do vértice.
 *	Diagonal principal: indica arestas entre o mesmo ponto.
 */


/**	A implementar:
 *	Matriz de incidência
 *	Listas de adjacência
 *	Vetores de adjacência
 *	Os métodos da classe 'Grafo'
 */

int menu(Grafo *g)
{
	int operacao = -1;
	puts("Bem vindo ao utilitário de grafos de Leo e Lucas!");
	puts("Escolha a opção desejada:\n");
	puts("1 - Carregar grafo (arquivo .txt)");
	puts("2 - Apresenta matriz de adjacência");
	puts("3 - Apresenta matriz de incidência");
	puts("4 - Apresentar grau do nó");
	puts("5 - Apresentar grau do grafo");
	puts("6 - Verificar se grafo é conexo");

	scanf("%d", &operacao);
	system("clear");

	switch(operacao)
	{
		case 0:
			break;
		case 1:
			g->leGrafo();
			break;
		case 2:
			g->mostraMatAdj();
			break;
		case 3:
			//g->mostraMatInc();
			break;
		case 4:
			//g->mostraGrauNo();
			break;
		case 5:
			//g->mostraGrauGrafo();
			break;
		default:
			operacao = -1;
			break;
	}

	return operacao;
}


void Grafo::leGrafo ()
{
	string caminho;
	puts("Insira o nome do arquivo (deve estar na pasta atual):");
	cin >> caminho;
	ifstream file;
	file.open(caminho);

	int nn, na, tipo;
	
	file >> nn >> na >> tipo;
	GVertice vAux1, vAux2;

	for (int i = 0; i < nn; i++)
	{
		file >> vAux1.nome;
		this->addVertice(vAux1);
	}

	for (int i = 0; i < nn; i++)
	{
		file >> vAux1.nome >> vAux2.nome;
		this->addAresta(vAux1, vAux2);
	}
	
	file.close();
}

void Grafo::mostraMatAdj()
{
	//int maxLen = 0;
	for (int i = 0; i < (int) vertices.size(); i++)
	{
		/*
		if (i == 0)
		{
			for (int k = 0; k < (int) vertices.size(); k++)
			{
				printf("%*s%s", (int) vertices[k].nome.size(), vertices[k].nome.c_str(),
						  		(k < (int) vertices.size()) ? " | " : "");
				maxLen = MAX(maxLen, (int) vertices[k].nome.size());
			}
			printf("\n");
		}
		*/
			

		for (int j = 0; j < (int) vertices.size(); j++)
		{
			/*
			printf("%*s%*d%s", maxLen, vertices[i].nome.c_str(),
				(int) vertices[j].nome.size(), matrizAdj[i][j],
				(j < (int) vertices.size() - 1) ? " | ":"");
			*/
			printf("%4d", matrizAdj[i][j]);
		}
		printf("\n");
	}
}

void Grafo::addVertice(GVertice v)
{
	for (int i = 0; i < (int) vertices.size(); i++)
		if (vertices[i].nome == v.nome)
		{
			puts("Já existe um vértice com esse nome");
			exit(EXIT_FAILURE);
		}
	
	vertices.push_back(v);
	
	// Atualizar matriz de adjacência
	matrizAdj.push_back(vector<int>((int) vertices.size(), 0));
	for (int i = 0; i < (int) matrizAdj.size() - 1; i++)
		matrizAdj[i].push_back(0);
	// fim

	// Atualizar matriz de incidência

}

void Grafo::addAresta(GVertice v1, GVertice v2)
{
	int p1 = -1, p2 = -1;
	for (int i = 0; i < (int) vertices.size(); i++)
	{
		if (vertices[i].nome == v1.nome)
			p1 = i;
		if (vertices[i].nome == v2.nome)
			p2 = i;
	}

	// error checking
	if (p1 == -1 || p2 == -1)
	{
		puts("Não há um vértice com o nome informado");
		exit(EXIT_FAILURE);
	}

	// Atualizar matriz de adjacência
	matrizAdj[p1][p2]++;
	if (tipo == NAODIRECIONADO)
		matrizAdj[p2][p1]++;
	// fim


}
