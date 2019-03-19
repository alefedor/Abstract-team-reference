// AND-FFT begins

void fast_fourier(vector<int>& a) { // AND-FFT.
    for (int k = 1; k < SZ(a); k *= 2)
	for (int start = 0; start < (1 << K); start += 2 * k) {
	    for (int off = 0; off < k; ++off) {
		int a_val = a[start + off];
		int b_val = a[start + k + off];
		
		a[start + off] = b_val;
		a[start + k + off] = add(a_val, b_val);
	    }
	}
}

void inverse_fast_fourier(vector<int>& a) {
    for (int k = 1; k < SZ(a); k *= 2)
	for (int start = 0; start < (1 << K); start += 2 * k) {
	    for (int off = 0; off < k; ++off) {
		int a_val = a[start + off];
		int b_val = a[start + k + off];
		
		a[start + off] = sub(b_val, a_val);
		a[start + k + off] = a_val;
	    }
	}
}

// AND-FFT ends
