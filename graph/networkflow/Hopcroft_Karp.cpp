struct Hopcroft_Karp{
	int n, m;
	vector<int> A, B, level;
	vector<bool> matched;
	vector<vector<int>> graph;

	Hopcroft_Karp(int n, int m) : n(n), m(m) {
		A.assign(n + 1, -1);
		B.assign(m + 1, -1);
		level.assign(n  + 1, -1);
		matched.assign(n + 1, false);
		graph.resize(n + 1);
	}

	void addedge(int u, int v){
		graph[u].pb(v);
	}

	void assign_level(){

		queue<int> q;

		for(int i = 1; i <= n; i++){
			if(!matched[i]){
				level[i] = 0;
				q.push(i);
			}
			else level[i] = INF;
		}

		while(!q.empty()){
			int here = q.front();
			q.pop();

			for(auto there : graph[here]){
				if(B[there] != -1 && level[B[there]] == INF){
					//이미 match 되어있고 level이 assign 되지 않음
					level[B[there]] = level[here] + 1;
					q.push(B[there]);
				}
			}
		}
	}

	bool find_path(int here){
		for(auto there : graph[here]){
			if( B[there] == -1 || (level[B[there]] == level[here] + 1) && find_path( B[there] ) ){
				//there이 matching이 아직 안되었거나
				//level 차이가 1인 B[there]에서 새로운 matching을 찾을 수 있으면
				matched[here] = true;
				A[here] = there;
				B[there] = here;
				return true;
			}
		}
		return false;
	}

	int bipartite_match(){
		int ret = 0;
		while(true){
			assign_level();

			int aug = 0;
			for(int i = 1; i <= n; i++) if( !matched[i] && find_path(i)) aug++;

			if(!aug) break;

			ret += aug;
		}
		return ret;
	}
};