/**
 * Description: 2D BIT.
 * Time: O(log(n) * log(m)).
 */

vector<int> node[N], tree[N];
void fakeUpdate(int x, int val)
{
    for (; x <= n; x += x & -x)
        node[x].pb(val);
}

void fakeGet(int x, int val)
{
    for (; x; x -= x & -x)
        node[x].pb(val);
}

void update(int x, int y, int val)
{
    for (; x <= n; x += x & -x)
    {
        int u = lower_bound(node[x].begin(), node[x].end(), y) - node[x].begin() + 1;
        for (; u <= (int)node[x].size(); u += u & -u)
            tree[x][u] += val;
    }
}
int get(int x, int y)
{
    int res = 0;
    for (; x; x -= x & -x)
    {
        int u = lower_bound(node[x].begin(), node[x].end(), y) - node[x].begin() + 1;
        for (; u; u -= u & -u)
            res += tree[x][u];
    }
    return res;
}