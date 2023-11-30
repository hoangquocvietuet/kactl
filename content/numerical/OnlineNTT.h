/**
 * Author: ShahjalalShohag
 * Date: 2023-11-30
 * Description:
 */

// 1s for n = 2e5
struct OnlineConvolution {
  vector<int> a, b, c;
  int k;
  OnlineConvolution(int n): a(n), b(n), c(n), k(0) {}
  // poly c = poly a * poly b
  // add a[i] = x and b[i] = y and it will return c[i]
  // online!
  int extend(int i, int x, int y) {
  	assert(i == k);
    a[k] = x;
    b[k] = y;
    int s = k + 2;
    for (int w = 1; s % w == 0 && w < s; w <<= 1) {
      for (int ri = 0; ri < 2; ri++) {
        if (ri == 0 || w * 2 != s) {
          vector<int> f(w), g(w);
          for (int i = 0; i < w; i++) f[i] = a[w - 1 + i], g[i] = b[k - w + 1 + i];
          f = multiply(f, g);
          for (int i = 0, j = k; i < f.size() && j < c.size(); i++, j++) {
            c[j] += f[i];
            if (c[j] >= mod) c[j] -= mod;
          }
        }
        swap(a, b);
      }
    }
    return c[k++];
  }
};
