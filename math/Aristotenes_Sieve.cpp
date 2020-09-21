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

vector<int> factor ( int x ) {
	vector<int> f;
	int y = x;
	for ( int i = 2; i <= sqrt(y); i++ ) {
		while ( x % i == 0 ) {
			f.pb(i);
			x /= i;
		}
		if ( x < i ) break;
	}
	if ( x > 1 ) f.pb(x);
	return f;
}

int euler_pi_function  ( int x ) {
	vector<int> f = factor(x);
	auto ff = f;
	ff.erase(unique(ff.begin(), ff.end()), ff.end());
	int ans = 1;
	for ( auto fi : ff ) {
		int ui = upper_bound(f.begin(), f.end(), fi) - f.begin();
		int li = lower_bound(f.begin(), f.end(), fi) - f.begin();
		ans *= pow(fi, li - ui - 1) * (fi - 1);
	}
	return ans;
}
