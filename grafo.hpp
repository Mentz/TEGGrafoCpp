#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdlib>

#define MAX(a,b) ((a<b)?b:a)
#define NAODIRECIONADO 0
#define DIRECIONADO 1

using namespace std;

class GVertice {
public:
	string nome;
};

class GAresta {
public:
	int peso;
	string nome;
};

class Grafo {
private:
	vector<GAresta> arestas;
	vector<GVertice> vertices;
	vector<vector<int> > matrizAdj;
	vector<vector<int> > matrizInc;
	vector<vector<int> > listaAdj;
	vector<int> grauVertice;
	int nArestas;
	int nVertices;

	int tipo; // 0 para não-direcionado, 1 para direcionado.

public:
	void leGrafo();
	void mostraMatAdj();
	void mostraMatInc();
	void mostraListaAdj();
	void mostraGrau();
	void mostraGrauGrafo();

	// Aceita um GVertice como argumento, retorna sucesso (0) ou fracasso (1).
	void addVertice(GVertice v);

	// Não tem argumentos, pede o nome do vértice a ser incluso.
	void addVertice();

	// Não tem argumentos, pede o nome do vértice a ser removido.
	void remVertice();
	void addAresta(GVertice v1, GVertice v2);

	// Lista as arestas e usuário escolhe qual remover.
	void remAresta();

	// Calcula grau de cada vértice
	void calculaGrau();

	// Lista os vértices e usuário escolhe um para ver o grau.
	int getGrauVertice();
	int getGrauGrafo();
	int verificaConexo();
	void DFS(int u, int grupo, vector<int> &grupoVertices);
};

int menu(Grafo* g);
