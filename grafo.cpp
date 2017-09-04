#include "grafo.hpp"
#include <bits/stdc++.h>
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
	cout << endl;
	puts("Menu:");
	puts("  1. Carregar grafo (arquivo .txt)");
	puts("  2. Apresenta matriz de adjacência");
	puts("  3. Apresenta matriz de incidência");
	puts("  4. Apresenta lista de adjacência (*)");
	puts("  5. Apresentar grau do nó");
	puts("  6. Apresentar grau do grafo (*)");
	puts("  7. Complemento matriz de adjacência");
	puts("  8. Remover vértices");
	puts("  9. Adicionar vértie");
	puts(" 10. Adicionar aresta");
	puts(" 11. Verificar se grafo é conexo (*)");
	cout << "Escolha a operação: ";

	scanf("%d", &operacao);
	system("clear");

	
	int nvRemocao, qvAdicao, i;
	string u, u1;

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
			cout << "Quantidade de vértices para remoção" << endl;
			cin >> nvRemocao;
			cout << "Digite lista de vértices para remoção" << endl;
			for(i = 0; i < nvRemocao; i++){
				string u;
				cin >> u;
				g->RemoveVertice(u);
			}
			break;

		case 9:
			cout << "Quantidade de vértices para adicão" << endl;
			cin >> qvAdicao;
			cout << "Digite lista de vértices para adição" << endl;
			for(i = 0; i < qvAdicao; i++){
				cin >> u;
				g->addVertice(u);
			}
			break;
		
		case 10:
			cout << "Adição de arestas" << endl;
			cout << "Vértice 1: ";
			cin >> u;
			cout << "Vértice 2: ";
			cin >> u1;
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


void Grafo::leGrafo ()
{
	string caminho;
	puts("Insira o nome do arquivo (deve estar na pasta atual):");
	cin >> caminho;
	ifstream file;
	file.open(caminho);

	int nn, na, tipo;
	
	file >> nn >> na >> tipo;
	this -> nArestas  = 0;
	this -> nVertices = 0;


	for (int i = 0; i < nn; i++)
	{
		string v;
		file >> v;
		this->addVertice(v);
	}

	for (int i = 0; i < na; i++)
	{
		string vAux1, vAux2;
		file >> vAux1 >> vAux2;
		this->addAresta(vAux1, vAux2);
	}
	
	file.close();
}

void construirMatAdj(){

}

void Grafo::mostraComplMatAdj() {

}

void Grafo::mostraMatAdj() {	
	map<string, map<string, int> > :: iterator it;
	cout << "  ";
	for(it = this->matrizAdj.begin(); it != this->matrizAdj.end(); it++) {
		cout << it -> first << "  ";
	}
	cout << endl;
	
	for(it = this->matrizAdj.begin(); it != this->matrizAdj.end(); it++) {
		cout << it -> first;
		map<string, int>:: iterator it2;
		for(it2 = this->matrizAdj[it->first].begin(); it2 != this->matrizAdj[it->first].end(); it2++){
			if(it2 == this->matrizAdj[it->first].begin()){
				cout << " ";
			} else {
				cout << "   ";
			}
			cout << it2 -> second;
		}
		cout << endl;	
	}
}

void Grafo::mostraMatInc() {
	map<string, vector<int> > :: iterator it = this->matrizInc.begin();

	for(; it != this -> matrizInc.end(); it++){
		cout << it -> first << " ";
		for(int i = 0; i < it->second.size(); i++){
			cout << setw(3) << (it -> second)[i];
		}
		cout << endl;
	}
}

void Grafo::mostraListaAdj() {

}

void Grafo::mostraGrau() {

}

void Grafo::addVertice(string v)
{
	for (int i = 0; i < nVertices; i++) {
		if (vertices[i] == v)
		{
			puts("Já existe um vértice com esse nome");
			exit(EXIT_FAILURE);
        }
    }
	
	vertices.push_back(v);
	nVertices++;
	
	// Atualizar matriz de adjacência
	for(int i = 0; i < nVertices; i++){
		if(this->matrizAdj[vertices[i]].count(v) == 0){
			this->matrizAdj[v][vertices[i]] = 0;
			if(this->tipo == 1)
				this->matrizAdj[vertices[i]][v] = 0;	
		}
	}
	// fim
	
	
	// Atualiza matriz de incidencia
    this->matrizInc[v] = vector<int> (nArestas);
	// Fim

	// Atualiza lista de adjacência

	// fim
}

void Grafo::calculaGrau() {
	// Calcula o grau de cada vértice a partir das colunas da matriz de Incindência

	// fim
}

void Grafo::addAresta(string v1, string v2)
{
	this -> nArestas++;
	string n1 = v1;
	string n2 = v2;

	// Atualizar matriz de adjacência
	if(this->tipo == 0) {
		if(this->matrizAdj[n1].count(n2) != 0){
			this->matrizAdj[n1][n2]++;
		}else
			this->matrizAdj[n2][n1]++;
	} else 
		this->matrizAdj[n1][n2]++;
	// fim

	// Atualizar matriz de incidência
	map<string, vector<int> > :: iterator it;
	for(it = this->matrizInc.begin(); it != this->matrizInc.end(); it++) {
		while((it->second).size() != nArestas){
			it->second.push_back(0);
		}
	}

	int last = max(0, nArestas - 1);
	this->matrizInc[v2][last]++;
	if(this -> tipo == 0)
		this->matrizInc[v1][last]++;
	else
		this->matrizInc[v1][last] = -1;
	// fim

	// Atualizar lista de adjacência

	// fim
}

void Grafo::RemoveVertice(string v1) {

	// Removendo vertice da matriz adjacencia

	// fim

	
	// Removendo vertice da matriz de incidencia

	// fim
	
	// Removendo vertice da lista de adjacência

	// fim
	
}

void Grafo::DFS(int u, int grupo, vector<int> &grupoVertices) {

}   

int Grafo::verificaConexo() {

}