int c, s;
int pow(int a, int b){
    int x = a; int ans = 1;
    while(b>0){
        if(b&1) ans*=x;
        x*=x;
        b>>=1;
    }
    return ans;

}
int solve(int c, int s){
    int sum = 0;
    for(int i=1; i<=s; i++){
        sum += pow(c,__gcd(s,i));
    }
    if(s&1)
        sum += s*pow(c, (s+1)/2);
    else
        sum += s/2 * (pow(c, s/2) + pow(c, s/2+1));
    sum = sum/(2*s);
    return sum;
}