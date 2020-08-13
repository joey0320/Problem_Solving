// dfs(root, root)
// lca(x, y)
const int maxn = 2e5+5;

int tin[maxn], tout[maxn], par[maxn], up[maxn][logn];
vector<int> graph[maxn];
int root, T;

void dfs ( int u, int p ) {
    tin[u] = ++T;
    par[u] = p;
    up[u][0] = p;
    for ( int i = 0; i < logn - 1; i++ ) {
        int mid = up[u][i];
        up[u][i+1] = up[mid][i];
    }
    for ( auto v : graph[u] ) dfs(v, u);
    tout[u] = ++T;
}

bool is_ancestor ( int x, int y ) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int get_lca ( int x, int y ) {
    if ( is_ancestor(x, y) ) return x;
    for ( int i = logn - 1; i >= 0; i-- ) 
        if ( !is_ancestor(up[x][i], y) ) 
            x = up[x][i];
    return up[x][0];
}