// linear sieve begins

const int N = 1000000;

int pr[N + 1], sz = 0;
/* minimal prime, mobius function, euler function */
int lp[N + 1], mu[N + 1], phi[N + 1];
 
lp[1] = mu[1] = phi[1] = 1;
for (int i = 2; i <= N; ++i) {
  if (lp[i] == 0)
    lp[i] = pr[sz++] = i;
  for (int j = 0; j < sz && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
    lp[i * pr[j]] = pr[j];

  mu[i] = lp[i] == lp[i / lp[i]] ? 0 : -1 * mu[i / lp[i]];
  phi[i] = phi[i / lp[i]] * (lp[i] == lp[i / lp[i]] ? lp[i] : lp[i] - 1);
}

// linear sieve ends
