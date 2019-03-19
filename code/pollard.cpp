// pollard begins

const int max_step = 4e5;

unsigned long long gcd(unsigned long long a, unsigned long long b){
  if (!a) return 1;
  while (a) swap(a, b%=a);
  return b;
}

unsigned long long get(unsigned long long a, unsigned long long b){
  if (a > b)
    return a-b;
  else
    return b-a;
}

unsigned long long pollard(unsigned long long n){
  unsigned long long x = (rand() + 1) % n, y = 1, g;
  int stage = 2, i = 0;
  g = gcd(get(x, y), n);
  while (g == 1) {
    if (i == max_step)
      break;
    if (i == stage) {
      y = x;
      stage <<= 1;
    }
    x = (x * (__int128)x + 1) % n;
    i++;
    g = gcd(get(x, y), n);
  }
  return g;
}

// pollard ends
