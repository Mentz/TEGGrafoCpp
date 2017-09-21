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

typedef unsigned int uint;

using namespace std;

struct GVertice {
	string nome;
	uint v_id;
	int cor; // Não implementado.
	uint grau;
	bool marcado;
	vector<uint> arestas; // Guarda identificador (a_id) das arestas que tocam esse vértice.
};

struct GAresta {
	string nome;
	uint a_id;
	uint v1_id, v2_id; // Guarda identificador (v_id) dos vértices nas pontas dessa aresta.
	bool marcado;
};

class Grafo {
private:
	vector<GVertice> vertices;
	vector<GAresta> arestas;

	//map<string, int> grauVertice;

	int tipo; // 0 para não-direcionado, 1 para direcionado.

public:
	void leGrafo();
	void mostraMatAdj(bool complemento);
	void mostraMatInc();
	void mostraListaAdj();
	void mostraGrau();
	void mostraGrauGrafo();

	void construirMatAdj();

	/**	void addVertice([string v1|GVertice v1]);
	 *	Pode ter argumentos:
	 *	1. Nada, solicitando nome e peso (opcional) do vértice;
	 *	2. Uma string, gerando um vértice simples (sem peso);
	 *	3. Um GVertice completo.
	 */
	void addVertice();
	void addVertice(string v1);
	void addVertice(GVertice v1);

	// Não tem argumentos, pede o nome do vértice a ser removido.
	/** void remVertice([string v1]);
	 *	Pode ter argumentos:
	 *	1. Nenhum. Apresenta lista de vértices e pede o nome do vértice
	 *		a ser removido;
	 *	2. Uma string, removendo o vértice que tem nome igual à string.
	 */
	void remVertice();
	void remVertice(string v);

	/** void addAresta();
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

	int verificaIsomorfismo(Grafo* g2);

	// Retorna lista de arestas partindo de v.
	vector<GAresta *> getArestaEm(string v);

	// Marca vértice.
	void marcaVertice(string v);

	// Marca aresta.
	void marcaAresta(string a);
};

int menu(Grafo* g);
