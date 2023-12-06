/**
 * Description: Dinic's algorithm for maximum flow.
 * Time: O(V^2E)
 */
const int N = 2020;
const int INF = (int)1e9 + 9072004;
struct edge
{
    int v, cap, flow;
    edge(int _v = 0, int _cap = 0, int _flow = 0)
    {
        v = _v, cap = _cap, flow = _flow;
    }
};

vector<edge> E;
int n, m, c[N], cur[N];
vector<int> adj[N];
int src, snk, dist[N];
queue<int> q;

void addEdge(int u, int v, int cap)
{
    adj[u].push_back(E.size());
    E.push_back(edge(v, cap, 0));
    adj[v].push_back(E.size());
    E.push_back(edge(u, 0, 0));
}

void bfs()
{
    dist[src] = 0;
    q.push(src);
    // for(int i=0 ; i<(int)E.size() ; ++i) cout << E[i].v << " " << E[i].cap << " " << E[i].flow << '\n';
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < (int)adj[u].size(); ++i)
        {
            int id = adj[u][i];
            int v = E[id].v;
            if (E[id].cap > E[id].flow && dist[v] > dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

bool findPath()
{
    for (int i = src; i <= snk; ++i)
        dist[i] = INF;
    bfs();
    return (dist[snk] != INF);
}

int incFlow(int u, int flowIn)
{
    if (u == snk)
        return flowIn;
    int flowOut = 0;
    for (; cur[u] < (int)adj[u].size(); cur[u]++)
    {
        int id = adj[u][cur[u]], v = E[id].v;
        if (E[id].cap == E[id].flow || dist[v] != dist[u] + 1)
            continue;
        int tmp = incFlow(v, min(flowIn, E[id].cap - E[id].flow));
        E[id].flow += tmp, E[id ^ 1].flow -= tmp;
        flowOut += tmp, flowIn -= tmp;
        if (flowIn == 0)
            break;
    }
    return flowOut;
}

void solve()
{
    while (findPath())
    {
        for (int i = src; i <= snk; ++i)
            cur[i] = 0;
        maxFlow += incFlow(src, INF);
    }
}
