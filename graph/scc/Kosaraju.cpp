int V, E, cnt;
bool vis[MX];
vector<int> adj[MX];
vector<int> radj[MX];
vector<vector<int>> scc;
stack<int> s;
void dfs(int u){
    vis[u] = true;
    for(auto v : adj[u]) if(!vis[v]) {
        dfs(v);
    }
    s.push(u);
}
void rdfs(int u, int c){
    vis[u] = true;
    scc[c].push_back(u);
    for(auto v : radj[u]) if(!vis[v]) rdfs(v, c);
}