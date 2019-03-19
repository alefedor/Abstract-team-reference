// discrete log in sqrt(p) begins

int k = sqrt((double)p) + 2;

for (int i = k; i >= 1; i--)
  mp[bin(b, (i * 1ll * k) % (p-1), p)] = i;

bool answered = false;
int ans = INT32_MAX;
for (int i = 0; i <= k; i++){
  int sum = (n * 1ll * bin(b, i, p)) % p;
  if (mp.count(sum) != 0){
    int an = mp[sum] * 1ll * k - i;
    if (an < p)
      ans = min(an, ans);
  }
}

// discrete log in sqrt(p) ends
