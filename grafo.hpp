#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <iomanip>
#include <cmath>

#define MAX(a,b) ((a<b)?b:a)
#define MIN(a,b) ((a<b)?a:b)
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
		this->arestas	= vector<uint>();
	}
};

struct GAresta {
	string nome;
	uint id;
	uint v1, v2; // Guarda identificador (v_id) dos vértices nas pontas dessa aresta.
	bool marcado;

	GAresta(uint v1_id, uint v2_id, uint a_id)
	{
		ostringstream oss;
		oss << "u" << ((int) a_id);
		this->nome		= oss.str();
		this->id 		= a_id;
		this->v1 		= v1_id;
		this->v2	 	= v2_id;
		this->marcado	= false;
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
		this->v_id_c = 0;
		this->a_id_c = 0;
		this->tipo = -1; // Não inicializado.
	}

	void leGrafo();
	void mostraMatAdj(bool complemento);
	void mostraMatInc();
	void mostraListaAdj();
	void mostraGrau();
	void mostraGrauTotal();
	
	// Apresenta lista de vértices.
	void listaVertices();

	// Apresenta lista de arestas.
	void listaArestas();

	// Atualiza num_vertices
	void atualizaNumVertices();

	// Atualiza num_arestas
	void atualizaNumArestas();

	/**	void addVertice([string v1|GVertice v1]);
	 *	Pode ter argumentos:
	 *	1. Nada, solicitando nome e peso (opcional) do vértice;
	 *	2. Uma string, gerando um vértice simples (sem peso);
	 */
	void addVertice();
	void addVertice(string v1);

	// Não tem argumentos, pede o nome do vértice a ser removido.
	/** void remVertice([string v1]);
	 *	Pode ter argumentos:
	 *	1. Nenhum. Apresenta lista de vértices e pede o nome do vértice
	 *		a ser removido;
	 *	2. Uma string, removendo o vértice que tem nome igual à string.
	 */
	void remVertice();
	void remVertice(string v);
	void remVertice(uint v_id);

	/** void addAresta();
	 *	Pode ter argumentos:
	 *	1. Nenhum: apresenta os vértices e pede quais serão parte da aresta;
	 *	2. Nome dos dois vértices: gera um nome para a nova aresta.
	 *	3. ID dos dois vértices: gera um nome para a nova aresta.
	 */
	void addAresta();
	void addAresta(string v1, string v2);
	void addAresta(uint v1_id, uint v2_id);

	/** void remAresta(..);
	 *	Variações:
	 *	remAresta(); Lista as arestas e pede para o usuário escolher qual deve remover.
	 * 	remAresta(uint a_id); Faz a remoção da aresta indicada. Não é acionado pelo usuário.
	 */
	void remAresta();
	void remAresta(uint a_id);

	// Retorna o nome do vértice baseado no ID dele.
	string getNomeV(uint v_id);

	// Retorna o nome da aresta baseado no ID dela.
	string getNomeA(uint a_id);

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

	// Calcula grau do vértice fornecido
	void atualizaGrauV(uint v_id);

	// Apresenta os graus de todos os vértices.
	void getGrauVertice();

	// Apresenta o grau do grafo.
	void getGrauGrafo();

	// Percorre a aresta com base no vértice de partida
	uint percorreAresta(uint a_id, uint v_id);

	void verificaConexo();
	void DFS(string u, int grupo, map<string, int> &grupoVertices);

	void mostraComplMatAdj();

	int verificaIsomorfismo(Grafo* g2);

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

	// DEGUB:
	void listaArestasDeVertice(uint v_id);
};

int menu(Grafo* g);
