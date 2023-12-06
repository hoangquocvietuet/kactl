/**
 * Description: Heavy Light Decomposition.
 * Time: O(n \times log(n)).
 */

const int N = (int)1e5 + 228;

int n, par[N], timeIn[N], t = 0;
int nChild[N], mxV[N];
int chainIn[N], chainHead[N], nChain = 1;
vector<int> adj[N];

void upd(int u, int v) // upd u->v
{
    while (true)
    {
        if (chainIn[u] == chainIn[v])
        {
            
        }
        else
        {
            
            u = par[chainHead[chainIn[u]]];
        }
    }
}

void dfs(int u)
{
    mxV[u] = -1;
    nChild[u] = 1;
    for (int i = 0; i < (int)adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (v == par[u])
            continue;
        par[v] = u;
        dfs(v);
        nChild[u] += nChild[v];
        if (mxV[u] == -1 || nChild[mxV[u]] < nChild[v])
            mxV[u] = v;
    }
}

void hld(int u)
{
    timeIn[u] = ++t;
    chainIn[u] = nChain;
    if (!chainHead[nChain])
        chainHead[nChain] = u;

    if (mxV[u] != -1)
        hld(mxV[u]);

    for (int i = 0; i < (int)adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (v == par[u] || v == mxV[u])
            continue;
        ++nChain;
        hld(v);
    }
}