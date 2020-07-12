int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}
void merge(int x, int y) {
	parent[find(x)] = find(y);
}
