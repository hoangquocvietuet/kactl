/**
 * Description: 2-SAT.
 * Time: O(n + m)
 */
const int N = (int)4e5 + 228;
const int INF = (int)1e9 + 7;
int n;
vector<vector<int>> adj;
int color[N];
bool valid = true;
int low[N], num[N], t = 0;
stack<int> nodes;
void setColor(int u, int c) {
    if (color[u] != -1) {
        if (color[u] != c)
            valid = false;
        return;
    }
    color[u] = c;
    setColor((u + n) % (2 * n), (1 ^ c));

void addEdge(int u, int v){
    adj[(u + n) % (2 * n)].push_back(v);
    adj[(v + n) % (2 * n)].push_back(u);
}
void dfs(int u){
    low[u] = num[u] = ++t;
    nodes.push(u);
    for (int v : adj[u]){
        if (num[v]){
            low[u] = min(low[u], num[v]);
        }
        else{
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        if (color[v] == 0){
            setColor(u, 0);
        }
    }

    if (low[u] == num[u]){
        int v;
        stack<int> candidates;
        int c = -1;
        do{
            v = nodes.top();
            nodes.pop();
            low[v] = num[v] = INF;
            candidates.push(v);
            if (color[v] != -1){
                c = color[v];
            }
        } while (v != u);

        if (c == -1){
            c = 1;
        }
        while (!candidates.empty()){
            v = candidates.top();
            candidates.pop();
            setColor(v, c);
        }
    }
}
void two_sat(){
    valid = true;
    // (u | v) = (!u -> v) & (!v -> u)
    for (int i = 0; i < 2 * n; ++i){
        if (!num[i]){
            dfs(i);
        }
    }
    if (!valid){
        cout << "NO\n";
        return;
    }
}