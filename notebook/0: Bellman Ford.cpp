vii Grafo[MAXN];
int dist[MAXN];
int parent[MAXN];
vi pathToDest;
int n;
bool hasNegativeCycle;

int BellmanFord(int source, int dest){
	int custo, v;
	hasNegativeCycle = false;
	for (int i = 0; i < n; i++){
		dist[i] = 1e8;
		parent[i] = -1;
	}
	dist[source]=0;
	parent[source]=source;
	
	for (int j = 0; j < n-1; j++)//roda n-1 vezes
	{
		for (int u = 0; u < n; u++)
		{
			for (int i = 0; i < Grafo[u].size(); i++)
			{
				v = Grafo[u][i].first;
				custo = Grafo[u][i].second;
				if(dist[v] > dist[u] + custo){
					dist[v] = dist[u]+custo;
					parent[v] = u;
				}
			}			
		}		
	}
	
	// se quiser saber quais vertices estao no ciclo é só 
	// adicionar outr for de 0 até 5, por exemplo, e ver 
	// qual distancia diminuiu. Se rodar só uma vez 
	// dependendo da configuração das aresta pode ser que 
	// não ache todos do ciclo, por isso é melhor rodar 
	// uma quantidade X de vezes, o ideal seria X = n
	for (int u = 0; !hasNegativeCycle && u < n; u++)
	{
		for (int i = 0; !hasNegativeCycle 
				&& i < Grafo[u].size(); i++)
		{
			v = Grafo[u][i].first;
			custo = Grafo[u][i].second;
			// se depois de n-1 iterações ainda 
			// existe um caminho menor, 
			// existe um ciclo negativo
			if(dist[v] > dist[u] + custo)
				hasNegativeCycle = true;
		}		
	}
	
	
	if(!hasNegativeCycle){
		pathToDest.clear();
		v = dest;
		while(v!=source){
			pathToDest.push_back(v);
			v = parent[v];
		}
		pathToDest.push_back(source);
	}
	return dist[dest];
}

// limpa();
// BellmanFord(origem, destino) retorna o menor caminho. 
// Se tiver ciclo negativo a variável vai ser true.