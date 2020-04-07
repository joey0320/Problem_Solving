//https://github.com/KwanghyunOn/Competitive-Programming/blob/master/Graph/Articulation%20Point%20%26%20Bridge.cpp
//온광현 github 참고

void dfs(int p, int v){
    int child =0;
    num[v] = low[v] = ++cur;
    for(auto c: adj[v]) if(c!=p){
        if(num[c]) low[v] = min(low[v], num[c]);
        else{
            child++;
            dfs(v,c);
            low[v] = min(low[v], low[c]);
            if(p!=-1 && low[c]>=num[v]) iscut[v] = true;
            if(low[c]> num[v]) bridge.emplace_back(min(v,c), max(v,c));
        }
    }
    if(p==-1 && child>1) iscut[v] = true;
}

void color(int x, int c){
	if(c > 0) bcc[x].push_back(c);
	vis[x] = 1;
	for(int i=0; i<graph[x].size(); i++){
		int w = graph[x][i];
		if(vis[w]) continue;
		if(dfn[x] <= low[w]){
			bcc[x].push_back(++cpiv);
			color(w, cpiv);
		}
		else{
			color(w, c);
		}
	}
}