int T, V, E;
const int MX = 1e5+5;
vector<int> adj[MX];
int sc[MX], num[MX];
int cnt, scnt;
stack<int> s;
int inedge[MX];

int dfs(int p){
    int ret = num[p] = ++cnt;
    s.push(p);
    for(auto c: adj[p]){
        if(num[c] == -1 ) 
            ret = min(ret, dfs(c));
        else if(sc[c] == -1 )
            ret = min(ret, num[c]);
    }
    if(ret == num[p]){
        while(true){
            int v = s.top(); s.pop();
            sc[v] = scnt;
            if(v==p) break;
        }
        scnt++;
    }
    return ret;
}