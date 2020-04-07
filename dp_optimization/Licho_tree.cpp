//http://www.secmem.org/blog/2019/01/03/lichao-tree/   김진표군 블로그 
const ll inf = 2e18;
ll f(pll l, ll x){
    return l.first * x + l.second;
}
struct Lichao_tree{
    struct node{
        int left, right;
        ll xl, xr;
        pll line;
    };
    vector<node> nodes;
    void init(ll xmin, ll xmax){
        nodes.push_back({-1, -1, xmin, xmax, {0, -inf}}); 
    }
    void insert(int n, pll nl){
        pll low = nodes[n].line;
        pll high = nl;
        ll xl = nodes[n].xl;
        ll xr = nodes[n].xr;
        ll xm = (xl + xr) >> 1;
        if(f(low, xl) > f(high, xl)) swap(low, high);

        if(f(low, xr) <= f(high, xr)) {
            nodes[n].line = high;
            return;
        }
        else if(f(low, xm) < f(high, xm)){
            nodes[n].line = high;
            if(nodes[n].right == -1){
                nodes[n].right = nodes.size();
                nodes.push_back({-1, -1, xm+1, xr, {0,-inf}});
            }
            insert(nodes[n].right, low);
        }
        else{
            nodes[n].line = low;
            if(nodes[n].left ==-1){
                nodes[n].left = nodes.size();
                nodes.push_back({-1, -1, xl, xm, {0, -inf}});
            }
            insert(nodes[n].left, high);
        }
    }
    ll get(int n, ll xq){
        if(n==-1) return -inf;
        ll xl = nodes[n].xl;
        ll xr = nodes[n].xr;
        ll xm = (xl + xr)>>1;
        auto line = nodes[n].line;
        if(xq<=xm) return max(f(line, xq), get(nodes[n].left, xq));
        else return max(f(line, xq), get(nodes[n].right, xq));
    }
};