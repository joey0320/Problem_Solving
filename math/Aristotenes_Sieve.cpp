const int maxn = 1e7 + 1;
int dmin[maxn];

void get_min_divisor () {
    for ( int i = 2; i < maxn; i++ ) dmin[i] = i; 
    for ( int i = 2; i <= (int) sqrt(maxn); i++ ) {
        if ( dmin[i] == i ) {
            for ( int j = i*i; j < maxn; j += i ) {
                dmin[j] = i;
            }
        }
    }
}

vector<int> factor ( int x ) {
    vector<int> ret;
    while ( x > 1 ) {
        ret.push_back(dmin[x]);
        x /= dmin[x];
    }
    return ret;
}
