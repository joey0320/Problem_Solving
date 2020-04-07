bool vis[MX];
int bi[MX];
vector<vector<int>> graph;

bool dfs(int here){
	if(vis[here]) return false;
	vis[here] = true;
	for(int i = 0; i < size(graph[here]); i++){
		int there = graph[here][i];
		if(!bi[there] || dfs(bi[there])){
			bi[there] = here;
			shirt[here] = there;
			return true;
		}
	}
	return false;
}

int bipartite(){
	int ret = 0;
	repp(i, 1, N){
		memset(vis, false, sizeof(vis));
		if(dfs(i)) ret++;
	}
	return ret;
}