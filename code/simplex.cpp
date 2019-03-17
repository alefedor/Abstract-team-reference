// simplex begins

const double EPS = 1e-9;

typedef vector<double> vdbl;

// n variables, m inequalities
// Ax <= b, c*x -> max, x >= 0
double simplex( int n, int m, const vector<vdbl> &a0, const vdbl &b, const vdbl &c, vdbl &x ) {
	// Ax + Ez = b, A[m]*x -> max
	// x = 0, z = b, x >= 0, z >= 0
	vector<vdbl> a(m + 2, vdbl(n + m + 2));
	vector<int> p(m);
	forn(i, n)
		a[m + 1][i] = c[i];
	forn(i, m) {
		forn(j, n)
			a[i][j] = a0[i][j];
		a[i][n + i] = 1;
		a[i][m + n] = -1;
		a[i][m + n + 1] = b[i];
		p[i] = n + i;
	}

	// basis: enter "j", leave "ind+n"
	auto pivot = [&]( int j, int ind ) {
		double coef = a[ind][j];
		assert(fabs(coef) > EPS);
		forn(col, n + m + 2)
			a[ind][col] /= coef;
		forn(row, m + 2)
			if (row != ind && fabs(a[row][j]) > EPS) {
				coef = a[row][j];
				forn(col, n + m + 2)
					a[row][col] -= a[ind][col] * coef;
				a[row][j] = 0; // reduce precision error
			}
		p[ind] = j;
	};

	// the Simplex itself
	auto iterate = [&]( int nn ) {
		for (int run = 1; run; ) {
			run = 0;
			forn(j, nn) {
				if (a[m][j] > EPS) { // strictly positive
					run = 1;
					double mi = INFINITY, t;
					int ind = -1;
					forn(i, m)
						if (a[i][j] > EPS && (t = a[i][n + m + 1] / a[i][j]) < mi - EPS)
							mi = t, ind = i;
					if (ind == -1) 
						return false;
					pivot(j, ind);
				}
			}
		}
		return true;
	};

	int mi = min_element(b.begin(), b.end()) - b.begin();
	if (b[mi] < -EPS) {
		a[m][n + m] = -1;
		pivot(n + m, mi);
		assert(iterate(n + m + 1));
		if (a[m][m + n + 1] > EPS) // optimal value is positive
			return NAN;
		forn(i, m)
			if (p[i] == m + n) {
				int j = 0;
				while (find(p.begin(), p.end(), j) != p.end() || fabs(a[i][j]) < EPS)
					j++, assert(j < m + n);
				pivot(j, i);
			}
	} 
	swap(a[m], a[m + 1]);
	if (!iterate(n + m))
		return INFINITY;
	x = vdbl(n, 0);
	forn(i, m)
		if (p[i] < n) 
			x[p[i]] = a[i][n + m + 1];
	return -a[m][n + m + 1];
}

// simplex usage: 
vdbl x(n);
double result = simplex(n, m, a, b, c, x);
if (isinf(result)) 
	puts("Unbounded");
else if (isnan(result))
	puts("No solution");
else {
	printf("%.9f :", result);
	forn(i, n)
		printf(" %.9f", x[i]);
	puts("");
}

// simplex ends

