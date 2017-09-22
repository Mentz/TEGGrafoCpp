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
	
	puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");;
	puts("/*------------------------------------*/");
	puts("Menu:");
	puts("  0. Sair deste utilitário.");
	puts("  1. Carregar grafo (arquivo .txt)");
	puts("  2. Apresenta matriz de adjacência");
	puts("  3. Apresenta matriz de incidência");
	puts("  4. Apresenta lista de adjacência");
	puts("  5. Apresentar grau do nó");
	puts("  6. Apresentar grau do grafo");
	puts("  7. Complemento matriz de adjacência");
	puts("  8. Adicionar vértice");
	puts("  9. Listar vértices");
	puts(" 10. Remover vértice");
	puts(" 11. Adicionar aresta");
	puts(" 12. Listar arestas");
	puts(" 13. Remover aresta");
	puts(" 14. Verificar se grafo é conexo");
	puts(" 15. Verificar se grafo é Euleriano");
	cout << "\nEscolha a operação: ";

	scanf("%d", &operacao);
	//system("clear");
	
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
			g->mostraGrauTotal();
			break;
		
		case 7:
			g->mostraMatAdj(true);
			break;
		
		case 8:
			g->addVertice();
			break;
		
		case 9:
			g->listaVertices();
			break;

		case 10:
			g->remVertice();
			break;
		
		case 11:
			g->addAresta();
			break;

		case 12:
			g->listaArestas();
			break;

		case 13:
			g->remAresta();
			break;

		case 14:
			g->verificaConexo();
			break;

		case 15:
			g->rodaFleury();
			break;

		default:
			operacao = -1;
			break;
	}
	
	if (operacao != 0)
	{
		puts("Pressione 'Enter' para continuar.");
		getc(stdin); getc(stdin);
	}

	return operacao;
}

/*--------------------------------------*/
void Grafo::leGrafo()
{
	string caminho;
	puts("Insira o nome do arquivo (deve estar na pasta atual):");
	cin >> caminho;
	ifstream file;
	file.open(caminho);

	int nn, na, tipo;
	
	file >> nn >> na >> tipo;
	this->tipo = tipo;

	for (int i = 0; i < nn; i++)
	{
		string v;
		file >> v;
		addVertice(v);
	}
	
	for (int i = 0; i < na; i++)
	{
		string vAux1, vAux2;
		file >> vAux1 >> vAux2;
		addAresta(vAux1, vAux2);
	}

	file.close();
}

/*--------------------------------------*/
void Grafo::mostraComplMatAdj() {
	// A implementar
}

/*--------------------------------------*/
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

/*--------------------------------------*/
void Grafo::mostraMatInc() {
	puts("Matriz de incidência:");
	int maxASize = 4;
	int conta;
	int colSize[num_vertices];

	cout << setw(maxASize) << "";
	for (uint i = 0; i < num_vertices; i++)
	{
		colSize[i] = vertices[i].nome.size() + 2;
		cout << setw(colSize[i]) << vertices[i].nome; 
	}

	cout << endl;

	for (uint i = 0; i < num_arestas; i++)
	{
		cout << setw(maxASize) << arestas[i].nome;
		for (uint j = 0; j < num_vertices; j++)
		{
			conta = 0;
			if (arestas[i].v1 == vertices[j].id)
				if (arestas[i].v2 == vertices[j].id)
					conta = 2;
				else
					conta = (tipo) ? 1 : -1;
			else if (arestas[i].v2 == vertices[j].id)
				conta = 1;

			if (conta) printf("%*d", colSize[j], conta); else printf("%*s", colSize[j], "");
		}
		cout << "\n";
	}
}

/*--------------------------------------*/
void Grafo::mostraListaAdj() {
	for (uint i = 0; i < num_vertices; i++)
	{
		printf("%s:", vertices[i].nome.data());
		for (uint j = 0; j < vertices[i].arestas.size(); j++)
		{
			printf("%s %s", j?",":"",
					getNomeV(percorreAresta(vertices[i].arestas[j], vertices[i].id)).data());
		}
		puts("");
	}
}

/*--------------------------------------*/
// Apresenta o grau de todos os nós do grafo de forma bonita.
void Grafo::mostraGrau() {
	for(uint i = 0; i < num_vertices; i++) 
	{
		printf("d(%s) = %d\n", vertices[i].nome.data(), vertices[i].grau);
	}
}

/*--------------------------------------*/
void Grafo::mostraGrauTotal()
{
	uint total = 0, mini = 1<<31, maxi = 0;
	for (uint i = 0; i < num_vertices; i++)
	{
		mini = MIN(mini, vertices[i].grau);
		maxi = MAX(maxi, vertices[i].grau);
		total += vertices[i].grau;
	}
	
	printf("Grau mínimo = %d\nGrau máximo = %d\nGrau total  = %d\n", mini, maxi, total);
}

/*-----------------------------------*/
void Grafo::listaVertices()
{
	printf("Vértices = %u\n", num_vertices);
	for (uint i = 0; i < vertices.size(); i++)
		printf("ID: %3u | Nome: %s\n", vertices[i].id, vertices[i].nome.data());
	
	puts("");
}

/*-----------------------------------*/
void Grafo::listaArestas()
{
	printf("Arestas = %u\n", num_arestas);
	for (uint i = 0; i < num_arestas; i++)
		printf("ID: %3u | Nome: %s | Vértices: %s %s-> %s | Marcado: %s\n",
				arestas[i].id, arestas[i].nome.data(), getNomeV(arestas[i].v1).data(),
				(tipo) ? "":"<", getNomeV(arestas[i].v2).data(),
				getMarcadoAresta(arestas[i].id) ? "Sim":"Não");

	puts("");
}

/*--------------------------------------*/
void Grafo::atualizaNumVertices()
{
	num_vertices = vertices.size();
}

/*--------------------------------------*/
void Grafo::atualizaNumArestas()
{
	num_arestas = arestas.size();
}

/*--------------------------------------*/
void Grafo::addVertice()
{
	string nome;
	puts("Informe o nome do novo vértice. Não pode conter espaços.");
	cin >> nome;
	addVertice(nome);	// Chama função com parâmetro nome.
}

/*--------------------------------------*/
// Só esse faz a adição de verdade.
void Grafo::addVertice(string nome)
{
	if (getIndexV(nome) != -1)
	{
		puts("Já existe um vértice com esse nome, vértice não adicionado.");
		return;
	}
	
	GVertice nv(nome, ++v_id_c);	// Criar item GVertice para inclusão.
	vertices.push_back(nv);			// Incluir vértice na lista de vértices.

	atualizaNumVertices();
}

/*--------------------------------------*/
void Grafo::remVertice()
{
	// Lista todos os vértices e solicita qual deve ser removido.
	puts("Lista de vértices:");
	for (uint i = 0; i < num_vertices; i++)
		printf("ID: %2u | Nome: %s\n", vertices[i].id, vertices[i].nome.data());
	puts("\nDigite o ID do vértice que deseja remover ou digite '0' para cancelar.");
	uint v_id;
	scanf("%u", &v_id);
	if (v_id == 0)
		return;
	remVertice(v_id);					// Chama o método que faz a remoção.
}

/*--------------------------------------*/
void Grafo::remVertice(string v)
{
	int index = getIndexV(v);
	if (index == -1)
		return;
	
	remVertice(vertices[index].id);		// Chama o método que faz a remoção.
}

/*--------------------------------------*/
// Só esse faz a remoção de verdade.
void Grafo::remVertice(uint v_id)
{
	int index = getIndexV(v_id);
	int a_davez;
	if (index == -1)
	{
		puts("Não há vértice com esse identificador.");
		return;
	}
	
	for (int i = vertices[index].arestas.size() - 1; i >= 0; i--)
	{
		//printf("entrei na lista de arestas, i = %u, vert[].arestas.size() = %lu\n", i, vertices[index].arestas.size());
		a_davez = vertices[index].arestas[i];
		//cout << "vou remover a aresta ID " << a_davez << "\n";
		remAresta(a_davez);
	}
	//puts("sai da lista de arestas");

	vertices.erase(vertices.begin() + index);

	//puts("deletei do vetor");

	atualizaNumVertices();
}

/*--------------------------------------*/
void Grafo::addAresta()
{
	uint v1_id, v2_id;
	// Lista todos os vértices e solicita qual deve ser removido.
	puts("Lista de vértices. (ID , Nome)");
	for (uint i = 0; i < num_vertices; i++)
		printf("ID: %2u | Nome: %s\n", vertices[i].id, vertices[i].nome.data());
	puts("\nDos vértices acima, digite o ID do vértice origem ou digite '0' para cancelar.");
	scanf("%u", &v1_id);
	if (v1_id == 0)
		return;
	puts("\nDigite o ID do destino ou digite '0' para cancelar.");
	scanf("%u", &v2_id);
	if (v2_id == 0)
		return;
	
	addAresta(v1_id, v2_id);
}

/*--------------------------------------*/
// Usado somente na leitura de um arquivo.
void Grafo::addAresta(string v1, string v2)
{
	int v1_index, v2_index;
	if ((v1_index = getIndexV(v1)) == -1 || (v2_index = getIndexV(v2)) == -1)
	{
		puts("Um dos vértices não existe.");
		return;
	}

	addAresta(vertices[v1_index].id, vertices[v2_index].id);
}

/*--------------------------------------*/
// Só esse faz a adição de verdade.
void Grafo::addAresta(uint v1_id, uint v2_id)
{
	//printf("Aresta nova:  %u - %u\n", v1_id, v2_id);
	int v1_index = getIndexV(v1_id), v2_index = getIndexV(v2_id);
	//printf("Indices nova: %d - %d\n", v1_index, v2_index);
	
	if (v1_index == -1 || v2_index == -1)
	{
		puts("Um dos vértices não existe.");
		return;
	}
	
	GAresta na(vertices[v1_index].id, vertices[v2_index].id, ++a_id_c);

	//printf("na.nome = %s\tna.id = %u\n", na.nome.data(), na.id);

	vertices[v1_index].arestas.push_back(na.id);
	if (v1_id != v2_id)
		vertices[v2_index].arestas.push_back(na.id);

	arestas.push_back(na);
	atualizaNumArestas();
	
	atualizaGrauV(v1_id);
	atualizaGrauV(v2_id);
}

/*--------------------------------------*/
void Grafo::remAresta()
{
	uint a_id = 0;
	puts("Lista de arestas:");
	for (uint i = 0; i < num_arestas; i++)
		printf("id: %3u | nome: %s | vértices: %s %s-> %s\n",
				arestas[i].id, arestas[i].nome.data(), getNomeV(arestas[i].v1).data(),
				(tipo) ? "":"<", getNomeV(arestas[i].v2).data());
	
	puts("");
	puts("Digite o ID da aresta a remover ou digite '0' para cancelar.");
	scanf("%u", &a_id);
	if (getIndexA(a_id) == -1)
		return;
	remAresta(a_id);
}

/*--------------------------------------*/
// Só esse faz a remoção de verdade.
void Grafo::remAresta(uint a_id)
{
	//printf("remAresta(%u)\n", a_id);
	int a_index = getIndexA(a_id);
	int v1_id = arestas[a_index].v1;
	int v2_id = arestas[a_index].v2;
	//printf("v1_id = %u, v2_id = %u\n", v1_id, v2_id);
	int v1_index = getIndexV(v1_id);
	int v2_index = getIndexV(v2_id);
	//printf("v1_index = %u, v2_index = %u\n", v1_index, v2_index);

	// Atualizar a lista de arestas em cada vértice da aresta.
	//printf("v1.arestas.size() = %lu\n", vertices[v1_index].arestas.size());
	for (int i = vertices[v1_index].arestas.size() - 1; i >= 0; i--)
		if (vertices[v1_index].arestas[i] == a_id)
		{
			//puts("achei o v1 da aresta");
			vertices[v1_index].arestas.erase(vertices[v1_index].arestas.begin() + i);
			//puts("deleti a referencia v1");
			break;
		}

	//printf("v1.arestas.size() = %lu\n", vertices[v1_index].arestas.size());

	//printf("v2.arestas.size() = %lu\n", vertices[v2_index].arestas.size());
	for (int i = vertices[v2_index].arestas.size() - 1; i >= 0; i--)
		if (vertices[v2_index].arestas[i] == a_id)
		{
			//puts("achei o v2 da aresta");
			vertices[v2_index].arestas.erase(vertices[v2_index].arestas.begin() + i);
			//puts("deleti a referencia v2");
			break;
		}
	//printf("v2.arestas.size() = %lu\n", vertices[v2_index].arestas.size());

	// Atualiza o grau dos vértices.
	atualizaGrauV(v1_id);
	atualizaGrauV(v2_id);

	//printf("REMOVENDO ARESTA ID %u\n", a_id);
	//printf("arestas.size() = %lu\n", arestas.size());
	// Remove da lista de arestas.
	arestas.erase(arestas.begin() + a_index);
	//printf("arestas.size() = %lu\n", arestas.size());
	
	//puts("atualizaNumArestas()");
	//printf("num_arestas = %u\n", num_arestas);
	atualizaNumArestas();
	//printf("num_arestas = %u\n", num_arestas);
	//puts("SAINDO DO remAresta");
}

/*--------------------------------------*/
string Grafo::getNomeV(uint v_id)
{
	int index = getIndexV(v_id);
	return vertices[index].nome;
}

/*--------------------------------------*/
string Grafo::getNomeA(uint a_id)
{
	int index = getIndexA(a_id);
	return arestas[index].nome;
}

/*--------------------------------------*/
int Grafo::getIndexV(string v)
{
	for (uint i = 0; i < num_vertices; i++)
	{
		if (vertices[i].nome == v)
			return i;
	}
	//puts("Não há um vértice com esse nome.");
	return -1; // Não encontrado.
}

/*--------------------------------------*/
int Grafo::getIndexV(uint v_id)
{
	//printf("v_id = %u\tnum_vertices = %d\n", v_id, num_vertices);
	for (uint i = 0; i < num_vertices; i++)
	{
		//printf("%d %u&&%u\\ ", i, vertices[i].id, v_id);
		if (vertices[i].id == v_id)
		{
			//puts("achei");
			return i;
		}
	}

	//puts("Não há um vértice com esse identificador.");
	return -1;
}

/*--------------------------------------*/
int Grafo::getIndexA(string a)
{
	for (uint i = 0; i < num_arestas; i++)
	{
		if (arestas[i].nome == a)
			return i;
	}
	//puts("Não há uma aresta com esse nome.");
	return -1; // Não encontrado.
}

/*--------------------------------------*/
int Grafo::getIndexA(uint a_id)
{
	//printf("getIndexA(%u)\n", a_id);
	for (uint i = 0; i < num_arestas; i++)
	{
		//printf("arestas[%u].id = %u\n", i, arestas[i].id);
		if (arestas[i].id == a_id)
		{
			//puts("achei");
			return i;
		}
	}

	//puts("Não há uma aresta com esse identificador.");
	return -1;
}

/*--------------------------------------*/
void Grafo::atualizaGrauV(uint v_id)
{
	//printf("atualizaGrauV(%u)\n", v_id);
	int v_index = getIndexV(v_id), a_index = -1;
	uint cont = vertices[v_index].arestas.size();
	//listaArestasDeVertice(v_id);
	for (uint i = 0; i < vertices[v_index].arestas.size(); i++)
	{
		a_index = getIndexA(vertices[v_index].arestas[i]);
		if (v_id == arestas[a_index].v1 &&					// Se for um loop então soma 2 ao
				arestas[a_index].v1 == arestas[a_index].v2)	// invés de 1 no grau do vértice.
			cont++;
	}

	vertices[v_index].grau = cont;
	//printf("grau(%u)=%u\tSaindo.\n", v_id, cont);
}

/*--------------------------------------*/
uint Grafo::percorreAresta(uint a_id, uint v_id)
{
	int a_index = getIndexA(a_id);
	if (arestas[a_index].v1 == v_id)	// Se a origem for o vértice atual, percorre.
		return arestas[a_index].v2;
	else if (arestas[a_index].v2 == v_id && tipo == 0) 	// Se o destino for o vértice atual e o
		return arestas[a_index].v1; 					// grafo for não-direcionado, percorre.
	else
	{
		//puts("Não é possível percorrer essa aresta.");
		return 0;
	}
}

/*--------------------------------------*/
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

/*--------------------------------------*/
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

/*--------------------------------------*/
bool Grafo::getMarcadoVertice(uint v_id)
{
	int index = getIndexV(v_id);
	return vertices[index].marcado;
}

/*--------------------------------------*/
void Grafo::marcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == false)
		vertices[index].marcado = true;
}

/*--------------------------------------*/
void Grafo::desmarcaVertice(uint v_id)
{
	int index = getIndexV(v_id);
	if (vertices[index].marcado == true)
		vertices[index].marcado = false;
}

/*--------------------------------------*/
bool Grafo::getMarcadoAresta(uint a_id)
{
	int index = getIndexA(a_id);
	return arestas[index].marcado;
}

/*--------------------------------------*/
void Grafo::marcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == false)
		arestas[index].marcado = true;
}

/*--------------------------------------*/
void Grafo::desmarcaAresta(uint a_id)
{
	int index = getIndexA(a_id);
	if (arestas[index].marcado == true)
		arestas[index].marcado = false;
}

/*--------------------------------------*/
void Grafo::rodaFleury()
{
	if (num_vertices <= 1)					// Essa condição é para impedir que grafos
	{										// sem vértices causem erros de segmentação
		puts("Grafo não é Euleriano.");		// ao tentar acessar vertices[0].
	}
	else if (fleury(0, vertices[0].id) == 1)
		puts("\nGrafo é Euleriano.");			// Se é euleriano, informe ao usuário.
	else
		puts("Grafo não é Euleriano.");			// Se não, informe também.

	// Reiniciar estado de marcações.
	for (uint i = 0; i < num_arestas; i++)
		desmarcaAresta(arestas[i].id);
}

/*--------------------------------------*/
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

		// Nem todas as arestas foram percorridas, continue.
		// pois pode haver uma aresta laço no nó atual, e
		// ainda será Euleriano.
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

/*-----------------------------------*/
void Grafo::listaArestasDeVertice(uint v_id)
{
	for (uint i = 0; i < vertices[getIndexV(v_id)].arestas.size(); i++)
	{
		printf(" | %u", vertices[getIndexV(v_id)].arestas[i]);
	}
	puts("");
}
