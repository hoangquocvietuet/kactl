/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

//p = first at least n + 1 points: a, a+d, ..., a+n*d of the n degree polynomial, returns f(x)
mint Lagrange(const vector<mint> &p, mint x, mint a = 0, mint d = 1) {
  int n = p.size() - 1;
  if (a == 0 and d == 1 and x.value <= n) return p[x.value];
 
  vector<mint> pref(n + 1, 1), suf(n + 1, 1);
  for (int i = 0; i < n; i++) pref[i + 1] = pref[i] * (x - (a + d * i));
  for (int i = n; i > 0; i--) suf[i - 1] = suf[i] * (x - (a + d * i));
 
  vector<mint> fact(n + 1, 1),finv(n + 1, 1);
  for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * d * i;
  finv[n] /= fact[n];
  for (int i = n; i >= 1; i--) finv[i - 1] = finv[i] * d * i;
 
  mint ans = 0;
  for (int i = 0; i <= n; i++) {
    mint tmp = p[i] * pref[i] * suf[i] * finv[i] * finv[n-i];
    if ((n - i) & 1) ans -= tmp;
    else ans += tmp;
  }
 
  return ans;
}
