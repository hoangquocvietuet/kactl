/**
 * Description: Fast Fourier Transform.
 * Time: O(nlogn).
 * Usage: fft(a, n, false), fft(b, n, false), fft(c, n, true)
 */

const double PI = acos(-1);

#define rep(i, a, b) for (int i = a; i < b; i++)

struct Complex
{
    double r, i;
    Complex() : r(0), i(0) {}
    Complex(double t) : r(cos(t)), i(sin(t)) {}
    Complex(double r, double i) : r(r), i(i) {}
    void operator/=(double d)
    {
        this->r /= d;
        this->i /= d;
    }
};
Complex operator+(Complex a, Complex b)
{
    a.r += b.r;
    a.i += b.i;
    return a;
}
Complex operator-(Complex a, Complex b)
{
    a.r -= b.r;
    a.i -= b.i;
    return a;
}
Complex operator*(Complex a, Complex b)
{
    return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

int reverse(int n, int S)
{
    int r = 0;
    rep(i, 0, S) r |= ((n & (1 << i)) >> i) << (S - i - 1);
    return r;
}

Complex *fft(Complex *a, int n, bool inv = false)
{
    Complex *b = new Complex[n];
    int S = log2(n);
    rep(i, 0, n) b[i] = a[reverse(i, S)];
    rep(s, 0, S)
    {
        int len = 1 << s;
        Complex w((inv ? 1 : -1) * PI / len);
        int i = 0, j = 0;
        for (int count = n >> (s + 1); count--;)
        {
            i = j;
            j = i + len;
            Complex t(1.0, 0);
            for (int l = len; l--;)
            {
                a[i] = b[i] + t * b[j];
                a[j] = b[i] - t * b[j];
                t = t * w;
                i++, j++;
            }
        }
        swap(a, b);
    }
    delete[] a;
    if (inv)
        rep(i, 0, n) b[i] /= n;
    return b;
}