#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iomanip>

#define MAX(a,b) ((a<b)?b:a)
#define NAODIRECIONADO 0
#define DIRECIONADO 1

using namespace std;

class GVertice {
	string nome;
	int cor;
	bool marcado;
}

class GAresta {
	string nome;
	GVertice v1, v2;
	bool marcado;
}

class Grafo {
private:
	int nArestas;
	int nVertices;
	vector<string> vertices;

	map<string, map<string, int > > matrizAdj;
	map<string, vector<string> > listaAdj;
	map<string, vector<int> > matrizInc;

	map<string, int> grauVertice;

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
	void addVertice();

	// Não tem argumentos, pede o nome do vértice a ser incluso.
	void addVertice();

	// Não tem argumentos, pede o nome do vértice a ser removido.
	void remVertice();

	/** addAresta()
	 *	Não possui argumentos, apresenta os vértices e pede quais serão parte da aresta.
	 */
	void addAresta();

	// Lista as arestas e usuário escolhe qual remover.
	void remAresta();

	// Calcula grau de cada vértice
	void calculaGrau();

	// Lista os vértices e usuário escolhe um para ver o grau.
	int getGrauVertice();
	int getGrauGrafo();
	int verificaConexo();
	void DFS(string u, int grupo, map<string, int> &grupoVertices);

	void RemoveVertice(string v1);
	void mostraComplMatAdj();
};

int menu(Grafo* g);
