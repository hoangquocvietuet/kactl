/**
 * Description: DSU on tree.
 * Time: O(nlogn).
 */

vector<int> vec[N], adj[N];

void dfs(int u, int fa, bool keep)
{
    int bigchild = -1;
    for (auto v : adj[u])
        if (v != fa)
        {
            if (bigchild == -1 || sz[bigchild] < sz[v])
                bigchild = v;
        }
    for (auto v : adj[u])
        if (v != fa && v != bidchild)
            dfs(v, u, 0);
    if (bigchild != -1)
    {
        dfs(bigchild, u, 1);
        swap(vec[u], vec[bigchild]);
    }
    // add u
    vec[u].push_back(u);
    for (auto v : adj[u])
        if (v != fa && v != bigchild)
        {
            for (auto x : vec[v])
            {
                // add x
                vec[u].push_back(x);
            }
        }
    // Find the answer with subtree u
    if (keep == 0)
    {
        for (auto v : vec[u])
        {
            // remove v
        }
    }
}
