vector<int> Grafo[MAXN], Transposto[MAXN];
int n, m, cnt;
int vis[MAXN];
int componente[MAXN];
stack<int> pilha;
map<string, int> mapa;
bool sat;
int ans[MAXN];

void limpa(){
	for (int i = 0; i <= MAXN; i++)
	{
		Grafo[i].clear();
		Transposto[i].clear();
	}	
}
//da pra acessar a negacao de um elemento fazendo o xor. 
//Deve ser indexado como:
//true: x*2
//false: x*2 + 1
//CODIGO SENDO INDEXADO A PARTIR DE 0****************

void addEdge(int u, int v){
	Grafo[u^1].pb(v);// !u -> v
	Grafo[v^1].pb(u);// !v -> u
	//Grafo transposto pra rodar o kosaraju
	Transposto[v].pb(u^1);
	Transposto[u].pb(v^1);
}

void dfs1(int u){
	if (!vis[u])
	{
		vis[u]=1;
		for (int i = 0; i < Grafo[u].size(); i++)
		{
			int v = Grafo[u][i];
			if(!vis[v]) dfs1(v);
		}
		pilha.push(u);
	}	
}

void dfs2(int u){
	if (!vis[u])
	{
		vis[u]=1;
		componente[u] = cnt;
		for (int i = 0; i < Transposto[u].size(); i++)
		{
			int v = Transposto[u][i];
			if(!vis[v]) dfs2(v);
		}
	}	
}
void Kosaraju(){
	memset(vis, 0, sizeof vis);
	while(!pilha.empty()) pilha.pop();
	for (int i = 0; i < 2*n; i++)
		if(!vis[i]) dfs1(i);//visita todos os vertices
	
	memset(vis, 0, sizeof vis);
	memset(componente, 0, sizeof componente);
	cnt=0;
	int u;
	
	while(!pilha.empty()){
		u = pilha.top(); pilha.pop();
		if(!vis[u]){
			dfs2(u);
			cnt++;
		}
		// atribui valores aos elementos
		// se for satisfativel da pra usar esse vetor
		ans[u/2] = 1-u%2;
	}
	
	sat=true;
	for (int i = 0; i < n; i++)
	{
	//se estão na mesma componente a formula nao tem solucao
		if(componente[2*i] == componente[2*i + 1]) 
			sat = false;
	}	
}
