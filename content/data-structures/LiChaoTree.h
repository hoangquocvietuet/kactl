/**
 * Description: Lichao Tree for maximum convex hull trick.
 * Time: O(logn) per operation.
 */
const int N = (int)2e5 + 228;
const long long INF = (long long)1e18;

struct line
{
    long long a, b;
    line(long long _a = INF, long long _b = INF)
    {
        a = _a, b = _b;
    }
    long long operator*(long long x)
    {
        if (a == 0)
            return b;
        if (abs((INF - b) / a) < abs(x))
            return INF;
        return a * x + b;
    }
};

struct LichaoTree
{
    vector<line> tree;
    int n;

    LichaoTree(int _n = 0)
    {
        n = _n;
        tree.assign(n * 4 + 7, line(INF, INF));
    }

    // update line for all x from l to r
    void add(int id, int l, int r, line &x)
    {
        int len = (r - l + 1), m = l + (len + 1) / 2 - 1;
        bool lef = (tree[id] * l > x * l);
        bool mid = (tree[id] * m > x * m);
        if (mid)
        {
            swap(tree[id], x);
        }
        if (len == 1)
            return;
        if (lef != mid)
            add(id * 2, l, m, x);
        else
            add(id * 2 + 1, m + 1, r, x);
    }
    void add(line x)
    {
        add(1, 1, n, x);
    }

    // find line with optimal value at x
    long long calc(int id, int l, int r, int k, long long x)
    {
        long long res = tree[id] * x;
        int len = (r - l + 1), m = l + (len + 1) / 2 - 1;
        if (len == 1)
            return res;
        if (k <= m)
            return min(res, calc(id * 2, l, m, k, x));
        return min(res, calc(id * 2 + 1, m + 1, r, k, x));
    }
    long long calc(int k, long long x)
    {
        return calc(1, 1, n, k, x);
    }
} it;