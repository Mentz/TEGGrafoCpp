#include "grafo.hpp"
#include <iomanip>
#include <iostream>
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
 *	Listas de adjacência
 *	Vetores de adjacência
 *	Os métodos da classe 'Grafo'
 */

int menu(Grafo *g)
{
	int operacao = -1;
	int grupos = 0;
	puts("\n####################################################\n");
	puts("Menu:");
	puts("  0. Sair");
	puts("  1. Carregar grafo (arquivo .txt)");
	puts("  2. Apresenta matriz de adjacência");
	puts("  3. Apresenta matriz de incidência");
	puts("  4. Apresenta lista de adjacência");
	puts("  5. Apresentar grau do nó");
	puts("  6. Apresentar grau do grafo (*)");
	puts("  7. Complemento matriz de adjacência");
	puts("  8. Adicionar vértice");
	puts("  9. Remover vértices");
	puts(" 10. Adicionar aresta");
	puts(" 11. Verificar se grafo é conexo (*)");
	puts("\t(*): Não implementado");
	cout << "Escolha a operação: ";

	scanf("%d", &operacao);
	//system("clear");

	puts("----------\n");

	GVertice u, u1;
	string uaux;

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
			g->mostraComplMatAdj();
			break;
		case 8:
			if (g->getTipo() == -1)
				g->setTipo();
			
			cout << "Insira o nome do novo vértice: ";
			cin >> u.nome;
			g->addVertice(u);
			break;
		case 9:
			cin >> u.nome;
			g->removeVertice(u);
			break;
		case 10:
			if (g->getTipo() == -1)
				g->setTipo();
			cout << "Adição de arestas" << endl;
			cout << "Vértice de partida: ";
			cin >> u.nome;
			cout << "Vértice de destino: ";
			cin >> u1.nome;
			g->addAresta(u, u1);
			break;

		case 11:
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

Grafo::Grafo()
{
	this->tipo = -1;
	this->nArestas = 0;
	this->nVertices = 0;
}

int Grafo::getTipo()
{
	return this->tipo;
}

void Grafo::setTipo()
{
	puts("Informe o tipo do grafo:");
	puts(" 0 - não-direcionado");
	puts(" 1 - direcionado");
	puts("\nDigite \'0\' ou \'1\'.");
	cin >> this->tipo;
}

void Grafo::leGrafo ()
{
	string caminho;
	puts("Insira o nome do arquivo (deve estar na pasta atual):");
	cin >> caminho;
	ifstream file;
	file.open(caminho);

	int nn, na;
	
	file >> nn >> na >> this -> tipo;

	GVertice vAux1, vAux2;
	this -> nArestas  = na;
	this -> nVertices = nn;

	for (int i = 0; i < nn; i++)
	{
		file >> vAux1.nome;
		this->addVertice(vAux1);
	}

	for (int i = 0; i < na; i++)
	{
		file >> vAux1.nome >> vAux2.nome;
		this->addAresta(vAux1, vAux2);
	}
	
	file.close();

	puts("\nArquivo lido com sucesso!");
}

void Grafo::mostraComplMatAdj() {
	int maxLen = 0;
	for (int i = 0; i < nVertices; i++)
		maxLen = MAX(maxLen, (int) getVerticeIndex(i).size());
	cout << setw(maxLen) << "";
	for(int i = 0; i < nVertices; i++)
		cout << setw((int) getVerticeIndex(i).size() + 2) << getVerticeIndex(i);
	cout << endl;
	for (int i = 0; i < nVertices; i++){
		for (int j = 0; j < nVertices; j++){	
			if(j == 0)
				cout << setw(maxLen) << getVerticeIndex(i);
			cout << setw((int) getVerticeIndex(j).size() + 2) << !matrizAdj[i][j];
		}
		cout << endl;
	}
}

void Grafo::mostraMatAdj()
{
	int maxLen = 0;
	for (int i = 0; i < nVertices; i++)
		maxLen = MAX(maxLen, (int) getVerticeIndex(i).size());
	cout << setw(maxLen) << "";
	for(int i = 0; i < nVertices; i++)
		cout << setw((int) getVerticeIndex(i).size() + 2) << getVerticeIndex(i);
	cout << endl;
	for (int i = 0; i < nVertices; i++){
		for (int j = 0; j < nVertices; j++){
			if(j == 0)
				cout << setw(maxLen) << getVerticeIndex(i);
			cout << setw((int) getVerticeIndex(j).size() + 2) << matrizAdj[i][j];
		}
		cout << endl;
	}
}

void Grafo::mostraMatInc() {
	int maxLen = 2;
	//for (int i = 0; i < nArestas; i++)
	//	maxLen = MAX(maxLen, (int) getArestaIndex(i).size());
	cout << setw(maxLen) << "";
	for (int i = 0; i < (int) this -> vertices.size(); i++)
		cout << setw((int) getVerticeIndex(i).size() + 2) << getVerticeIndex(i);
	cout << endl;

	for (int i = 0; i < (int) this->matrizInc.size(); i++) {
		cout << "u" << i;
		for (int j = 0; j < nVertices; j++)
			cout << setw((int) getVerticeIndex(j).size() + 2) << matrizInc[i][j];
		
		puts("");
	} 
}

void Grafo::mostraListaAdj() {
	for (int i = 0; i < (int) listaAdj.size(); i++){
		cout << getVerticeIndex(i) << ":";
		for (int j = 0; j < (int) listaAdj[i].size(); j++) {
			cout << " " << getVerticeIndex(listaAdj[i][j]);
		}
		cout << endl;
	}
}

void Grafo::mostraGrau() {
	this -> calculaGrau();

	cout << "Grau dos nós: " << endl;
	for(int i = 0; i < (int) grauVertice.size(); i++)
		cout << getVerticeIndex(i) << ": " << grauVertice[i] << endl;
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
	
	
	// Atualiza matriz de incidencia
	for(int i = 0; i < (int) matrizInc.size(); i++){
		matrizInc[i].push_back(0);
	}
	// Fim

	// Atualiza lista de adjacência
	this -> listaAdj.push_back(vector<int>());
	// fim
	
	nVertices = this -> vertices.size();
}

void Grafo::calculaGrau() {
	grauVertice = vector<int>((int) nVertices, 0);
	// Calcula o grau de cada vértice a partir das colunas da matriz de Incindência
	for(int j = 0; j < (int) this -> matrizInc[0].size(); j++){
		for(int i = 0; i < (int) this -> matrizInc.size(); i++){
			if(matrizInc[i][j] > 0)
				grauVertice[j] += ABS(matrizInc[i][j]);
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
		return;
	}

	// Atualizar matriz de adjacência
	matrizAdj[p1][p2]++;
	if (tipo == NAODIRECIONADO && p1 != p2)
		matrizAdj[p2][p1]++;
	// fim

	// Atualizar matriz de incidência
	matrizInc.push_back(vector<int> (nVertices, 0));
	if (tipo == DIRECIONADO)
		matrizInc[matrizInc.size() - 1][p1]--;
	else
		matrizInc[matrizInc.size() - 1][p1]++;
	matrizInc[matrizInc.size() - 1][p2]++;
	// fim

	// Atualizar lista de adjacência
	listaAdj[p1].push_back(p2);
	if (tipo == NAODIRECIONADO && p1 != p2)
		listaAdj[p2].push_back(p1);
	// fim

	this->nArestas = this->arestas.size();
}

void Grafo::removeVertice(GVertice v1) {
	int index = -1;
	for(int i = 0; i < (int) this -> vertices.size(); i++)
		if(this -> vertices[i].nome == v1.nome)
			index = i;

	if(index == -1){
		puts("Não há um vertice com o nome informado");
		return;
	}

	this -> vertices.erase(this->vertices.begin() + index);
	nVertices = this->vertices.size();

	// Removendo vertice da matriz adjacencia
	for(int i = 0; i < (int) this->matrizAdj.size(); i++)
		this->matrizAdj[i].erase(this->matrizAdj[i].begin() + index);
	this->matrizAdj.erase(this->matrizAdj.begin() + index);
	// fim

	
	// Removendo vertice da matriz de incidencia
	for (int i = 0; i < (int) this->matrizInc.size(); i++) {
		if(this -> matrizInc[i][index] != 0){
			this -> matrizInc.erase(this -> matrizInc.begin() + i);
			--i;
		}
	}

	for (int i = 0; i < (int) this->matrizInc.size(); i++){
		this->matrizInc[i].erase(this->matrizInc[i].begin() + index);
	}
	// fim
	
	// Removendo vertice da lista de adjacência
	//this->listaAdj.erase(this->listaAdj.begin() + index);
	// fim

	this->nVertices = this->vertices.size();
	
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

string Grafo::getVerticeIndex(int i) {
	return this -> vertices[i].nome;
}

string Grafo::getArestaIndex(int i) {
	return this -> arestas[i].nome;
}

int Grafo::verificaIsomorfismo(Grafo* g2)
{
	// Calcula um hash para cada vértice.
	// Usa o grau de entrada, grau de saída, hash 
	return 1;
}
