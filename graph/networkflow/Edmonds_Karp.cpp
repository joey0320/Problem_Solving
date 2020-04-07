struct networkflow{
	struct edge{
		int to, cap;
		edge* reverse;
		edge(int to, int cap):to(to), cap(cap) {}
	};

	vector<vector<edge*>> graph;
	int V, source, sink;
	
	networkflow(int V, int source, int sink) : V(V), source(source), sink(sink) {
		graph.resize(V+5);
	}

	void push_edge(int u, int v, int cap){
		edge *forward = new edge(v, cap);
		edge *reverse = new edge(u, 0);
		forward->reverse = reverse;
		reverse->reverse = forward;
		graph[u].pb(forward);
		graph[v].pb(reverse);
	}
	
	int bfs(int s){
		vector<bool> vis;
		vector<pii> before;
		vis.assign(V + 5, false);
		before.assign(V + 5, {-1, -1});

		queue<int> q;
		vis[s] = true;
		q.push(s);

		while(!q.empty()){
			auto v = q.front();
			q.pop();
			for(int i = 0; i < size(graph[v]); i++){
				auto e = graph[v][i];
				if(e->cap > 0 && !vis[e->to]) {
					vis[e->to] = true;
					q.push(e->to);
					before[e->to] = {v, i};
				}
			}
		}

		if(!vis[sink]) return 0;

		int x = sink;
		int c = graph[before[x].ff][before[x].ss]->cap;
		while(before[x].ff != -1){
			c = min(c, graph[before[x].ff][before[x].ss]->cap);
			x = before[x].ff;
		}
    
		x = sink;
		while(before[x].ff != -1){
			auto e = graph[before[x].ff][before[x].ss];
			e->cap -= c;
			e->reverse->cap += c;
			x = before[x].ff;
		}
		return c;
	}
	int maxflow(){
		int ans = 0;
		while(true){
			int ret = bfs(source);
			if(!ret) break;
			ans += ret;
		}
		return ans;
	}
};