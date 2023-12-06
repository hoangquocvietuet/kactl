/**
 * Description: Centroid decomposition.
 * Time: O(n \times log(n)).
 */

int mark[N], cl[N], sl[N], fa[N], id, facen[N];
vector<int> a[N];

void DFS_size(int u)
{ /// DFS lại đồ thị sau khi bị tách
    cl[u] = id;
    sl[u] = 1;
    for (auto v : a[u])
        if (mark[v] == 0 && cl[v] != id)
        {
            fa[v] = u;
            DFS_size(v);
            sl[u] += sl[v];
        }
}

void centroid(int u, int pa)
{
    id++;
    fa[u] = 0;
    DFS_size(u);
    int sz = sl[u];
    while (1)
    {
        int ma = sz - sl[u], luu;
        for (auto v : a[u])
            if (mark[v] == 0 && fa[v] == u)
            {
                if (ma < sl[v])
                {
                    ma = sl[v];
                    luu = v;
                }
            }
        if (ma <= sz / 2)
            break;
        u = luu;
    }
    facen[u] = pa; /// Tạo cây centroid
    mark[u] = 1;
    for (auto v : a[u])
        if (mark[v] == 0)
            centroid(v, u);
}
