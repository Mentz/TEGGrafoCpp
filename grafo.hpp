#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>

#define MAX(a,b) ((a<b)?b:a)
#define NAODIRECIONADO 0
#define DIRECIONADO 1

using namespace std;

class Grafo {
private:
	int nArestas;
	int nVertices;
	vector<string> vertices;

	map<string, map<string, int > > matrizAdj;
	map<string, vector<int> > listaAdj;
	map<string, vector<int> > matrizInc;

	vector<int> grauVertice;

	int tipo; // 0 para não-direcionado, 1 para direcionado.

public:
	void leGrafo();
	void mostraMatAdj();
	void mostraMatInc();
	void mostraListaAdj();
	void mostraGrau();
	void mostraGrauGrafo();


	void construirMatAdj();

	// Aceita um GVertice como argumento, retorna sucesso (0) ou fracasso (1).
	void addVertice(string v);

	// Não tem argumentos, pede o nome do vértice a ser incluso.
	void addVertice();

	// Não tem argumentos, pede o nome do vértice a ser removido.
	void remVertice();
	void addAresta(string v1, string v2);

	// Lista as arestas e usuário escolhe qual remover.
	void remAresta();

	// Calcula grau de cada vértice
	void calculaGrau();

	// Lista os vértices e usuário escolhe um para ver o grau.
	int getGrauVertice();
	int getGrauGrafo();
	int verificaConexo();
	void DFS(int u, int grupo, vector<int> &grupoVertices);

	void RemoveVertice(string v1);
	void mostraComplMatAdj();
};

int menu(Grafo* g);
