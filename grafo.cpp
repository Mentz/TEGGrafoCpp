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
	int grupos = 0;
	cout << endl;
	puts("Menu:");
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
			g->RemoveVertice();
			break;
		
		case 9:
			g->addVertice();
			break;
		
		case 10:
			
			g->addAresta(u, u1);
			break;

		case 11:
			grupos = g->verificaConexo();
			if(grupos <= 1)
				cout << "O grafo é conexo" << endl;
			else
				//cout << "O grafo é desconexo e possui " << grupos << " subgrafos" << endl; 
				puts("O grafo é desconexo");
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

}

void Grafo::mostraMatAdj(bool complemento) {
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
}

void Grafo::mostraMatInc() {
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
}

void Grafo::mostraListaAdj() {
	map<string, vector<string> > :: iterator it = this->listaAdj.begin();

	for(; it != this -> listaAdj.end(); it++){
		cout << it->first << ":";
		for(int i = 0; i < (int) (it->second).size(); i++){
			cout << " " << (it->second)[i];
		}
		cout << endl;
	}
}

void Grafo::mostraGrau() {
	this->calculaGrau();
	cout << grauVertice.size() << endl;
	map<string, int> :: iterator it = grauVertice.begin();
	for(; it != grauVertice.end(); it++) 
		cout << it -> first << ": " << it->second << endl;
}

void Grafo::addVertice(string v)
{
	for (int i = 0; i < (int) vertices.size(); i++) {
		if (vertices[i].nome == v)
		{
			puts("Já existe um vértice com esse nome");
			exit(EXIT_FAILURE);
        }
    }
	
	vertices.push_back(v);
	nVertices = vertices.size();
	
	// Atualizar matriz de adjacência
	for(int i = 0; i < nVertices; i++){
		if(this->matrizAdj[vertices[i]].count(v) == 0){
			this->matrizAdj[v][vertices[i]] = 0;
			this->matrizAdj[vertices[i]][v] = 0;
			
			/*this->matrizAdj[v][vertices[i]] = 0;
			if(this->tipo == 1)
				this->matrizAdj[vertices[i]][v] = 0;	
			*/
		}
	}
	// fim
	
	
	// Atualiza matriz de incidencia
    this->matrizInc[v] = vector<int> (nArestas);
	// Fim

	// Atualiza lista de adjacência
	this->listaAdj[v] = vector<string> (0);
	// fim
}

void Grafo::calculaGrau() {
	// Calcula o grau de cada vértice a partir das linhas das matriz de incidencia
	map<string, vector<int> > :: iterator it = this->matrizInc.begin();
	
	for(; it != this->matrizInc.end(); it++) {
		int cont = 0;
		for(int i = 0; i < (int) it->second.size(); i++) {
			if(it->second[i] >= 1)
				cont += it->second[i];
		}
		this->grauVertice[it->first] = cont;
	}
	// fim
}

void Grafo::addAresta(string v1, string v2)
{
	this -> nArestas++;

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
		while((int) (it->second).size() != nArestas) {
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
	this->listaAdj[v1].push_back(v2);
	if(this -> tipo == 0 && v1 != v2) 
		this->listaAdj[v2].push_back(v1);
	// fim
}

void Grafo::RemoveVertice(string v1) {
	// Atualizando lista de vértices
	for(int i = 0; i < (int) this->vertices.size(); i++) {
		if(this->vertices[i] == v1) {
			this->vertices.erase(this->vertices.begin() + i);
			break;
		}
	}
	this->nVertices = vertices.size();
	// fim

	// Removendo vertice da matriz adjacencia
	this->matrizAdj.erase(v1);
	map<string, map<string, int> > :: iterator itAdj = this->matrizAdj.begin();

	for(; itAdj != this->matrizAdj.end(); itAdj++) {
		itAdj->second.erase(v1);
	}
	// fim

	
	// Removendo vertice da matriz de incidencia
	map<string, vector<int> > :: iterator itInc;
	for(int i = 0; i < (int) this->matrizInc[v1].size(); i++) {
		if(this->matrizInc[v1][i] != 0) {
			cout << i << endl;
			for (itInc = this -> matrizInc.begin(); itInc != this->matrizInc.end(); itInc++) { 
				(itInc->second).erase((itInc->second).begin() + i);
			}
			i--;
		}
	}

	this -> matrizInc.erase(v1);
	// fim
	
	// Removendo vertice da lista de adjacência
	this->listaAdj.erase(v1);
	map<string, vector<string> > :: iterator itLista;
	for(itLista = this->listaAdj.begin(); itLista != this->listaAdj.end(); itLista++) {
		for(int i = 0; i < (int) itLista->second.size(); i++) { 
			if(itLista->second[i] == v1) 
				itLista->second.erase(itLista->second.begin() + i);
		}
	}
	// fim
	
}

void Grafo::DFS(string u, int grupo, map<string, int> &grupoVertices) {
	grupoVertices[u] = grupo;
	for(int i = 0; i < (int) this->listaAdj[u].size(); i++) {
		string atual = this->listaAdj[u][i];
		if(grupoVertices[atual] == -1) {
			DFS(atual, grupo, grupoVertices);
		}
	} 
}   

int Grafo::verificaConexo() {
	map<string, int> grupoVertices;
	map<string, int> :: iterator it;

	for(int i = 0; i < (int) vertices.size(); i++) { 
		grupoVertices[vertices[i]] = -1;
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
	getchar();
	return grupo;
}
