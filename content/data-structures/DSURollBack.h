/**
 * Description: DSU with rollback.
 * Time: O(1) for each operation.
 */

struct DSU
{
    int n, sltm;
    vector<int> root;

    DSU(int _n = 0)
    {
        sltm = _n;
        n = _n;
        Rank.assign(n + 5, 1);
    }

    struct datadsu
    {
        int u, v, ranku, rankv;
    };
    stack<datadsu> save;

    void reset()
    {
        for (int i = 1; i <= n; i++)
            root[i] = -1;
        sltm = n;
    }

    int get(int u)
    {
        if (root[u] < 0)
            return u;
        return (root[u] = get(root[u]));
    }

    void Join(int u, int v, int state)
    {
        int p = get(u), q = get(v);
        if (p == q)
            return;
        sltm--;
        if (state)
            save.push({p, q, root[p], root[q]});
        if (root[p] > root[q])
            swap(p, q);
        root[p] += root[q];
        root[q] = p;
    }

    void Rollback()
    {
#define sa save.top()
        while (!save.empty())
        {
            save.pop();
            sltm++;
            root[sa.u] = sa.ranku;
            root[sa.v] = sa.rankv;
        }
    }
};