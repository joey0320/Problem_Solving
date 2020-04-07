int c[1005]; //점화식의 계수
int a[1005]; //점화식의 초항들
int d[1005]; //우리가 구하고 싶은 계수들 a(n) 을 a(1) .. a(m)로 나타냈을때의 계수들
int t[2020]; //임시저장

void kit(int m, ll n) { //n 번째 계수, 항 m개짜리 점화식
	int a, b;
	if (n == 1) {
		repp(i, m) d[i] = 0;
		d[1] = 1;
		return;
	}
	if (n & 1) {//a(n+1)을 a(1)...a(m)으로 나타냈을 때의 계수를 구한다
		kit(m, n -1);
		a = d[m];
		for (int i = m; i >= 1; i--) {
			d[i] = d[i - 1] + a * c[m - i + 1];
			d[i] %= q;
		}
		return;
	}
	else {//n이 2의 배수이면 n/2의 계수들을 통해서 a(n)을 a(1)...a(m)으로 나타냈을 때의 계수를 구한다
		kit(m, n >> 1);
		repp(i, 2*m) t[i] = 0;
		repp(i, m) {
			repp(j, m) {
				t[i + j] += d[i] * d[j];
				t[i + j] %= q;
			}
		}
		for (int i = 2 * m; i > m; i--) {
			for (int j = 1; j <= m; j++) {
				t[i - j] += t[i] * c[j];
				t[i - j] %= q;
			}
		}
		repp(i, m)
			d[i] = t[i];
	}
}
// https://junis3.tistory.com/27