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
	uint id;
	int cor; // Não implementado.
	uint grau;
	bool marcado;
	vector<uint> arestas; // Guarda identificador (a_id) das arestas que tocam esse vértice.

	GVertice(string nome, uint v_id)
	{
		this->nome		= nome;
		this->id		= v_id;
		this->cor		= 0;
		this->grau		= 0;
		this->marcado	= false;
		this->arestas	= vector<uint>(0);
	}
};

struct GAresta {
	string nome;
	uint id;
	uint v1, v2; // Guarda identificador (v_id) dos vértices nas pontas dessa aresta.
	bool marcado;

	GAresta(string nome, uint a_id, uint v1_id, uint v2_id)
	{
		this->nome		= nome;
		this->id 		= a_id;
		this->v1 		= v1_id;
		this->v2	 	= v2_id;
		this->marcado	= false;
	}

	GAresta(uint a_id, uint v1_id, uint v2_id)
	{
		// Geração de nome para arestas sem nome.
		GAresta(string("u" + a_id), a_id, v1_id, v2_id);
	}
};

class Grafo {
private:
	uint num_vertices, v_id_c; // v_id_c é o identificador único incremental para cada GVertice.
	uint num_arestas, a_id_c; // a_id_c é o identificador único incremental para cada GAresta.
	vector<GVertice> vertices;
	vector<GAresta> arestas;

	//map<string, int> grauVertice;

	int tipo; // 0 para não-direcionado, 1 para direcionado.

public:
	Grafo()
	{
		this->num_vertices = 0;
		this->num_arestas = 0;
		this->v_id_c = 1;
		this->a_id_c = 1;
		this->tipo = -1; // Não inicializado.
	}

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
	 *	Pode ter argumentos:
	 *	1. Nenhum: apresenta os vértices e pede quais serão parte da aresta;
	 *	2. Nome dos dois vértices: gera um nome para a nova aresta.
	 */
	void addAresta();
	void addAresta(string v1, string v2);

	// Lista as arestas e usuário escolhe qual remover.
	void remAresta();

	/** uint getIndexV(..);
	 *	Variações:
	 *	getIndexV(string v); Busca pelo nome do vértice.
	 *	getIndexV(uint v_id); Busca pelo ID do vértice.
	 */
	int getIndexV(string v);
	int getIndexV(uint v_id);


	/** uint getIndexA(..);
	 *	Variações:
	 *	getIndexA(string a); Busca pelo nome da aresta.
	 *	getIndexA(uint a_id); Busca pelo ID da aresta.
	 */
	int getIndexA(string a);
	int getIndexA(uint a_id);

	// Calcula grau de cada vértice
	void calculaGrau();

	// Lista os vértices e usuário escolhe um para ver o grau.
	void getGrauVertice();
	void getGrauGrafo();
	void verificaConexo();
	void DFS(string u, int grupo, map<string, int> &grupoVertices);

	void mostraComplMatAdj();

	int verificaIsomorfismo(Grafo* g2);

	// Percorre a aresta com base no vértice de partida
	uint percorreAresta(uint a_id, uint v_id);

	// Marcação de vértice.
	bool getMarcadoVertice(uint v_id); // Retorna true se está marcado, false se não.
	void marcaVertice(uint v_id);
	void desmarcaVertice(uint v_id);

	// Marcação de aresta.
	bool getMarcadoAresta(uint a_id); // Retorna true se está marcado, false se não.
	void marcaAresta(uint a_id);
	void desmarcaAresta(uint a_id);

	// Verifica se o grafo é Euleriano
	void rodaFleury();
	bool fleury(uint v_davez_id, uint v_inicial_id);
};

int menu(Grafo* g);
