vector<int> Grafo[MAXN];
int match[MAXN];
int vis[MAXN];

int dfs(int x){
    if(vis[x]) return 0;
    vis[x] = 1;
    for (int i = 0; i < Grafo[x].size(); i++)
    {
        if(match[Grafo[x][i]]==-1 || dfs(match[Grafo[x][i]])){
            match[Grafo[x][i]] = x;
            return 1;
        }
    }
    return 0;//não conseguiu alocar
}
int main()
{
	res=0;
	memset(match, -1, sizeof match);
    for (int i = n; i < n; i++)
    {
        memset(vis, 0, sizeof vis);
        res += dfs(i);
    }
    printf("%d\n", res);

    return 0;
}
