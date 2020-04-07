const int MX = 5e4 + 5;
int T, N, V, cnt, num[MX], low[MX], iscut[MX];
vector<int> adj[MX];
vector<vector<pii>> bcc;
stack<pii> st;

void dfs(int u, int p){
	num[u] = low[u] = ++cnt;
	int child = 0;
	for(auto v : adj[u]){
		if(num[v] && v == p) continue;
		if(!num[v]){
			child++;
			st.push({u,v});
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(num[u] <= low[v]){//u is articulation point, create new bcc
				if(p!=-1) iscut[u] = true;
				vector<pii>  nbcc;
				while(!st.empty() && st.top() != pii(u, v)){
					nbcc.pb(st.top()); st.pop();
				}
				if(!st.empty()){
					nbcc.pb(st.top()); st.pop();
				}
				bcc.pb(nbcc);

			}
		}
		else if(num[v] < num[u]){
			low[u] = min(low[u], num[v]);
			st.push({u, v}); //backedge
		}
	}
	if( p==-1 && child > 1) iscut[u] = true;
}