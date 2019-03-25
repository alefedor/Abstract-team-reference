// kto begins
//return pair(nmod,nr)
//nr%mod1=r1, nr%mod2=r2
//nmod=mod1*mod2/gcd(mod1,mod2)
//if input incosistent return mp(-1,-1)
pll kto (ll mod1, ll r1, ll mod2, ll r2)
{
  ll d=__gcd(mod1,mod2);
  if (r1%d!=r2%d)
    return mp(-1,-1);
  ll rd=r1%d;
  mod1/=d, mod2/=d, r1/=d, r2/=d;
 
  if (mod1<mod2)
    swap(mod1,mod2), swap(r1,r2);
 
  ll k=(r2-r1)%mod2;
  if (k<0)
    k+=mod2;
 
  ll x, y;
  gcdex(mod1,mod2,x,y);
  x%=mod2;
  if (x<0)
    x+=mod2;
  k*=x, k%=mod2;
  return mp(mod1*mod2*d,(k*mod1+r1)*d+rd);
}
// kto ends
