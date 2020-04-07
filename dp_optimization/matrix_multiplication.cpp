  
const int q = 1000000;
struct mat {
	ll arr[2][2];
	mat operator * (const mat& rhs) {
		mat res;
		rep(i, 2) {
			rep(j, 2) {
				res.arr[i][j] = 0;
				rep(k, 2) {
					res.arr[i][j] += arr[i][k] * rhs.arr[k][j];
					res.arr[i][j] %= q;
				}
			}
		}
		return res;
	}
	void printmat() {
		cout << arr[0][0] << " " << arr[0][1] << endl << arr[1][0] << " " << arr[1][1] << endl;
	}
};
mat fmul(mat A, ll p) {
	mat X = A;
	mat I; I.arr[0][0] = I.arr[1][1] = 1; I.arr[1][0] = I.arr[0][1] = 0;
	while (p > 0) {
		if ((p & 1)) I = I * X;
		X = X * X;
		p /= 2;
	}
	return I;
}
//김진표 코드 참고