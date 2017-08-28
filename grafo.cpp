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
	int grupos = 0;
	puts("Bem vindo ao utilitário de grafos de Leo e Lucas!");
	puts("Escolha a opção desejada:\n");
	puts("1 - Carregar grafo (arquivo .txt)");
	puts("2 - Apresenta matriz de adjacência");
	puts("3 - Apresenta matriz de incidência");
	puts("4 - Apresenta lista de adjacência");
	puts("5 - Apresentar grau do nó");
	puts("6 - Apresentar grau do grafo");
	puts("7 - Verificar se grafo é conexo");

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
			g->mostraMatInc();
			break;
		case 4:
			g->mostraListaAdj();
			break;
		case 5:
			g->mostraGrau();
			break;
		case 6:
			//g->mostraGrauGrafo();
			break;
		case 7:
			grupos = g->verificaConexo();
			if(grupos == 0)
				cout << "O grafo é conexo" << endl;
			else
				cout << "O grafo é desconexo e possui " << grupos+1 << " subgrafos" << endl; 
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
	this -> nArestas  = na;
	this -> nVertices = nn;

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
		for (int j = 0; j < (int) vertices.size(); j++)
		{
			printf("%4d", matrizAdj[i][j]);
		}
		printf("\n");
	}
}

void Grafo::mostraMatInc() {
	for (int i = 0; i < (int) matrizInc.size(); i++) {
		for (int j = 0; j < (int) matrizInc.size(); j++)
			printf("%4d", matrizInc[i][j]);
		
		printf("\n");
	} 
}

void Grafo::mostraListaAdj() {
	for (int i = 0; i < (int) listaAdj.size(); i++){
		cout << " N" << i + 1 << ":";
		for (int j = 0; j < (int) listaAdj[i].size(); j++) {
			cout << " N" << listaAdj[i][j] + 1;
		}
		cout << endl;
	}
}

void Grafo::mostraGrau() {
	this -> calculaGrau();

	cout << "Grau dos nós: " << endl;
	for(int i = 0; i < (int) grauVertice.size(); i++)
		cout << "N" << i+1 << ": " << grauVertice[i] << endl;
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

	// Atualiza lista de adjacência
	this -> listaAdj.push_back(vector<int>());
}

void Grafo::calculaGrau() {
	grauVertice = vector<int>((int) nVertices, 0);
	// Calcula o grau de cada vértice a partir das colunas da matriz de Incindência
	for(int j = 0; j < this->nVertices; j++){
		for(int i = 0; i < this->nArestas; i++){
			if(matrizInc[i][j] > 0)
				grauVertice[j] += matrizInc[i][j];
		}
	}
	// fim
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

	// Atualizar matriz de incidência
	matrizInc.push_back(vector<int> (nVertices, 0));
	matrizInc[matrizInc.size() - 1][p1] = -1;
	matrizInc[matrizInc.size() - 1][p2] =  1;

	if (tipo == NAODIRECIONADO)
		matrizInc[matrizInc.size() - 1][p1] = 1;
	//fim

	// Atualizar lista de adjacência
	listaAdj[p1].push_back(p2);
	if (tipo == NAODIRECIONADO)
		listaAdj[p2].push_back(p1);
	// fim
}

void Grafo::DFS(int u, int grupo, vector<int> &grupoVertices) {
	grupoVertices[u] = grupo;
	for(int i = 0; i < (int) listaAdj[u].size(); i++){
		int atual = listaAdj[u][i];
		if(grupoVertices[atual] == -1)
			DFS(atual, grupo, grupoVertices);
	}
}   

int Grafo::verificaConexo() {
	vector<int> grupoVertices (this->nVertices, -1);
	
	int grupo = 0;
	for(int i = 0; i < nVertices; i++){
		if(grupoVertices[i] == -1) {
			if(i != 0)
				grupo++;
			DFS(i, grupo, grupoVertices);
		}
	}

	return grupo;
}