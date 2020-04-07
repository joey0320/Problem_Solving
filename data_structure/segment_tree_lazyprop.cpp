void propagate(int n, int nodeL, int nodeR){
    if(lazy[n]==0) return;

    tree[n] += (nodeR - nodeL + 1)*lazy[n];

    if(nodeL != nodeR){
        lazy[L(n)] += lazy[n];
        lazy[R(n)] += lazy[n];
    }
    lazy[n] = 0;
}
void updaterange(int n, int nodeL, int nodeR, int left, int right, int val){
    propagate(n, nodeL, nodeR);
    if(nodeL > right || nodeR < left) return;
    if(left <= nodeL && nodeR <= right){
        tree[n] += (nodeR - nodeL + 1) * val;
        if(nodeL!=nodeR){
            lazy[L(n)] += val;
            lazy[R(n)] += val;
        }
        return;
    }
    int m = (nodeL + nodeR) >>1;
    updaterange(L(n), nodeL, m, left, right, val);
    updaterange(R(n), m + 1, nodeR, left, right, val);
    tree[n] = tree[L(n)] + tree[R(n)];
}
int squery(int n, int nodeL, int nodeR, int left, int right){
    propagate(n, nodeL, nodeR);
    if(nodeL > right || nodeR < left) return 0;
    if(left <= nodeL && nodeR <= right) return tree[n];
    int m = (nodeL + nodeR) >>1;
    return squery(L(n), nodeL, m, left, right) + squery(R(n), m+1, nodeR, left, right);
}