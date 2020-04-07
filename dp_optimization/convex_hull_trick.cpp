//https://www.weeklyps.com/entry/%EC%BB%A8%EB%B2%A1%EC%8A%A4-%ED%97%90-%ED%8A%B8%EB%A6%AD-Convex-Hull-Trick 참고
const int MX = 1e5 + 5;
int n, a[MX], b[MX];
ll dp[MX] = {0};
struct line{
    ll a, b;
    double s;// y = ax + b, x>=s
    line() : a(1), b(0), s(0){}
    line(ll a1, ll b1) : a(a1), b(b1), s(0){}
};
vector<line> cv;
double lineintersect(line l1, line l2){
    return (l2.b - l1.b)/(l1.a - l2.a);
}
void solve(){
    for(int i=2; i<=n; i++){
        line nl(b[i-1], dp[i-1]);
        while(!cv.empty()){
            nl.s = lineintersect(cv.back(), nl);
            if(nl.s < cv.back().s) cv.pop_back(); //if the intersect is before the current line's starting point, pop stack
            else break;
        }
        cv.push_back(nl);
        if(a[i] >= cv.back().s) dp[i] = a[i] * cv.back().a + cv.back().b;
        else{//binary search for the line in which a[i] is emplaced
            int l = 0, r = cv.size() - 1, ans = 0;
            while(l<=r){
                int m = (l + r)/2;
                if(cv[m].s < a[i]){
                     l = m+1;
                     ans = m;
                }
                else r = m-1;
            }
            dp[i] = a[i] * cv[ans].a + cv[ans].b;
        }
        //cout<<dp[i]<<endl;
    }
    printf("%lld\n", dp[n]);
}