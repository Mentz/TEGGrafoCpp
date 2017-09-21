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
 *	Os métodos da classe 'Grafo'
 */

int menu(Grafo *g)
{
	int operacao = -1;
	
	cout << endl;
	puts("Menu:\n");
	puts("  0. Sair deste utilitário.");
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
	puts(" 11. Verificar se grafo é conexo");
	cout << "Escolha a operação: ";

	scanf("%d", &operacao);
	//system("clear");
	
	string u, u1;

	switch(operacao)
	{
		case 0:
			break;
		
		case 1:
			g->leGrafo();
			break;
		
		case 2:
			g->mostraMatAdj(false);
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
			g->mostraMatAdj(true);
			break;
		
		case 8:
			g->remVertice();
			break;
		
		case 9:
			g->addVertice();
			break;
		
		case 10:
			g->addAresta();
			break;

		case 11:
			g->verificaConexo();
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
	this -> num_arestas  = 0;
	this -> num_vertices = 0;
	this -> tipo = tipo;

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

void Grafo::mostraComplMatAdj() {
	// A implementar
}

void Grafo::mostraMatAdj(bool complemento) {
	/*
	map<string, map<string, int> > :: iterator it;
	int maxS = -1, compNo[this->matrizAdj.size()], i, j;
	
	for(i = 0, it = this->matrizAdj.begin(); it != this->matrizAdj.end(); i++, it++) {
		compNo[i] = it->first.size();
		maxS = MAX(maxS, compNo[i]);
	}
	
	cout << setw(maxS) << "";

	for(i = 0, it = this->matrizAdj.begin(); it != this->matrizAdj.end(); i++, it++)
		cout << setw(compNo[i] + 2) << it -> first;

	cout << endl;

	for(i = 0, it = this->matrizAdj.begin(); it != this->matrizAdj.end(); i++, it++) {
		cout << setw(maxS) << it -> first;
		map<string, int>:: iterator it2;
		for(j = 0, it2 = this->matrizAdj[it->first].begin();
			it2 != this->matrizAdj[it->first].end(); j++, it2++)
		{
			if(!complemento)
				cout << setw(compNo[j] + 2) << it2 -> second;
			else {
				int print = (it2->second == 0) ? 1 : 0;
				cout << setw(compNo[j] + 2) << print;
			}
		}
		cout << endl;	
	}
	*/
}

void Grafo::mostraMatInc() {
	/*
	map<string, vector<int> > :: iterator it = this->matrizInc.begin();
	int maxS = -1;

	for(; it != this->matrizInc.end(); it++) {
		maxS = MAX(maxS, (int) it->first.size());
	}
	
	for(it = this->matrizInc.begin(); it != this -> matrizInc.end(); it++){
		cout << setw(maxS) << it -> first;
		for(int i = 0; i < (int) it->second.size(); i++){
			cout << setw(3) << (it -> second)[i];
		}
		cout << endl;
	}
	*/
}

void Grafo::mostraListaAdj() {
	/*
	map<string, vector<string> > :: iterator it = this->listaAdj.begin();

	for(; it != this -> listaAdj.end(); it++){
		cout << it->first << ":";
		for(int i = 0; i < (int) (it->second).size(); i++){
			cout << " " << (it->second)[i];
		}
		cout << endl;
	}
	*/
}

// Apresenta o grau de todos os nós do grafo de forma bonita.
void Grafo::mostraGrau() {
	uint maxnome = 0;
	// Calcula a maior largura de nome
	for(uint i = 0; i < num_vertices; i++)
		maxnome = MAX(maxnome, vertices[i].nome.size());
	for(uint i = 0; i < num_vertices; i++) 
		printf("d(%s)%*s= %d\n", vertices[i].nome.data(), maxnome-1, "", vertices[i].grau);
}

void Grafo::addVertice()
{
	string nome;
	puts("Informe o nome do novo vértice. Não pode conter espaços.");
	cin >> nome;
	for (int i = 0; i < (int) vertices.size(); i++) {
		if (vertices[i].nome == nome)
		{
			puts("Já existe um vértice com esse nome");
			return;
        }
    }

}

void Grafo::addVertice(string v)
{
	for (int i = 0; i < (int) vertices.size(); i++) {
		if (vertices[i].nome == v)
		{
			puts("já existe um vértice com esse nome");
			return;
        }
    }
	
	GVertice nv(v, ++v_id_c);
	
	vertices.push_back(nv);
	num_vertices = vertices.size();
}

int Grafo::getIndexV(string v)
{
	for (uint i = 0; i < num_vertices; i++)
	{
		if (vertices[i].nome == v)
			return i;
	}
	puts("Não há um vértice com esse nome.");
	return -1; // Não encontrado.
}

int Grafo::getIndexV(uint v_id)
{
	for (uint i = 0; i < num_vertices; i++)
	{
		if (vertices[i].id == v_id)
			return i;
	}

	puts("Não há um vértice com esse identificador.");
	return -1;
}

int Grafo::getIndexA(string a)
{
	for (uint i = 0; i < num_arestas; i++)
	{
		if (arestas[i].nome == a)
			return i;
	}
	puts("Não há uma aresta com esse nome.");
	return -1; // Não encontrado.
}

int Grafo::getIndexA(uint a_id)
{
	for (uint i = 0; i < num_arestas; i++)
	{
		if (arestas[i].id == a_id)
			return i;
	}

	puts("Não há um vértice com esse identificador.");
	return -1;
}

void Grafo::calculaGrau() {
	/*a
	map<string, vector<int> > :: iterator it = this->matrizInc.begin();
	
	for(; it != this->matrizInc.end(); it++) {
		int cont = 0;
		for(int i = 0; i < (int) it->second.size(); i++) {
			if(it->second[i] >= 1)
				cont += it->second[i];
		}
		this->grauVertice[it->first] = cont;
	}
	*/
}

void Grafo::addAresta(string v1, string v2)
{
	/*
	this -> num_arestas++;

	// Atualiza matriz de adjacência
	if(this->tipo == 0) {
		this->matrizAdj[v1][v2]++;
		this->matrizAdj[v2][v1]++;
	}
	else 
		this->matrizAdj[v1][v2]++;
	// fim


	// Atualizar matriz de incidência
	map<string, vector<int> > :: iterator it;
	for(it = this->matrizInc.begin(); it != this->matrizInc.end(); it++) {
		while((int) (it->second).size() != num_arestas) {
			it->second.push_back(0);
		}
	}

	int last = max(0, num_arestas - 1);
	this->matrizInc[v2][last]++;
	if(this -> tipo == 0)
		this->matrizInc[v1][last]++;
	else
		this->matrizInc[v1][last] = -1;
	// fim


	// Atualizar lista de adjacência
	this->listaAdj[v1].push_back(v2);
	if(this -> tipo == 0 && v1 != v2) 
		this->listaAdj[v2].push_back(v1);
	// fim
	*/
}

void Grafo::remVertice(string v) {
	int index = getIndexV(v), a_davez;
	if (index == -1)
	{
		puts("Não há vértice com esse nome.");
		return;
	}
	for (uint i = vertices[index].arestas.size(); i >= 0; i--)
	{
		a_davez = vertices[index].arestas[i];
		remAresta(a_davez);
	}
	/*
	// Atualizando lista de vértices
	for(int i = 0; i < int(num_vertices); i++) {
		if(this->vertices[i].nome == v) {
			this->vertices.erase(this->vertices.begin() + i);
			break;
		}
	}
	this->num_vertices = vertices.size();
	// fim
	*/
}

void Grafo::DFS(string u, int grupo, map<string, int> &grupoVertices) {
	/*
	grupoVertices[u] = grupo;
	for(int i = 0; i < (int) this->listaAdj[u].size(); i++) {
		string atual = this->listaAdj[u][i];
		if(grupoVertices[atual] == -1) {
			DFS(atual, grupo, grupoVertices);
		}
	}
	*/
}   

void Grafo::verificaConexo() {
	/*
	map<string, int> grupoVertices;
	map<string, int> :: iterator it;

	for(int i = 0; i < (int) vertices.size(); i++) { 
		grupoVertices[vertices[i].nome] = -1;
	}
	
	int grupo = 0;
	for(it = grupoVertices.begin(); it != grupoVertices.end(); it++) {
		string atual = it->first;
		int grupoAtual = it->second;
		
		if(grupoAtual == -1) {
			this->DFS(atual, grupo, grupoVertices);
			grupo++;
		}
	}

	for(it = grupoVertices.begin(); it != grupoVertices.end(); it++) {
		cout << it -> first << " " << it -> second << endl;
	}

	if(grupo <= 1)
		cout << "O grafo é conexo" << endl;
	else
		cout << "O grafo é desconexo e possui " << grupo << " subgrafos" << endl; 
	*/
}

uint Grafo::percorreAresta(uint a_id, uint v_id)
{
	int a_index = getIndexA(a_id);
	if (arestas[a_index].v1 == v_id)
		return arestas[a_index].v2;
	else if (arestas[a_index].v2 == v_id)
		return arestas[a_index].v1;
	else
	{
		puts("Não é possível percorrer essa aresta.");
		return 0;
	}
}

bool Grafo::getMarcadoVertice(uint v_id)
{
	int index = getIndexV(v_id);
	return vertices[index].marcado;
}

void Grafo::marcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == false)
		vertices[index].marcado = true;
}

void Grafo::desmarcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == true)
		vertices[index].marcado = false;
}

bool Grafo::getMarcadoAresta(uint a_id)
{
	int index = getIndexA(a_id);
	return arestas[index].marcado;
}

void Grafo::marcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == false)
		arestas[index].marcado = true;
}

void Grafo::desmarcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == true)
		arestas[index].marcado = false;
}

void Grafo::rodaFleury()
{
	if (vertices.size() < 1)
	{
		puts("Grafo não Euleriano.");
		return;
	}
	if (fleury(0, vertices[0].id) == 1)
	{
		puts("Grafo é Euleriano.");
		return;
	}
}

bool Grafo::fleury(uint v_id_davez, uint v_id_inicial)
{
	uint v_id_prox = 0, v_index_davez, a_davez = 0;
	if (v_id_davez == v_id_inicial)
	{
		// Encontrado um ciclo partindo do vértice inicial.
		int ruim = false;

		// Verificar se todas as arestas foram visitadas.
		for (uint i = 0; i < num_arestas; i++)
		{
			if (!arestas[i].marcado)
			{
				ruim = true;
				break;
			}
		}

		if (!ruim)
		{
			puts("Ciclo:");
			printf("%s", vertices[getIndexV(v_id_davez)].nome.data());
			return true; // Todas as arestas foram percorridas, é ciclo Euleriano.
		}
		else
			return false; // Nem todas as arestas foram percorridas, continue.
	} 
	else if (v_id_davez == 0)
	{
		v_id_davez = v_id_inicial;
	}

	v_index_davez = getIndexV(v_id_davez);

	for (uint i = 0; i < vertices[v_index_davez].arestas.size(); i++)
	{
		a_davez = vertices[v_index_davez].arestas[i];
		if (getMarcadoAresta(a_davez) == true)
			continue;
		else
		{
			marcaAresta(a_davez);
			v_id_prox = percorreAresta(a_davez, v_id_davez);
			if (fleury(v_id_prox, v_id_inicial) == true) // Deu certo, imprima o caminho.
			{
				printf("-%s-%s", arestas[getIndexA(a_davez)].nome.data(),
								 vertices[getIndexV(v_id_davez)].nome.data()); 
				return 1;
			}
			desmarcaAresta(a_davez);
		}
	}

	return 0;
}
