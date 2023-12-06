/**
 * Description: Aho Corasick.
 * Time: O(26 * n).
 * fail: like kmp
 * next[c]: node will jump to if add char c after current position
 */

struct node
{
    node *fail, *nxt[M], *children[M], *par;
    int value, parChar, index;
    node(node *_par = NULL, int _parChar = 0, int _index = 0)
    {
        par = _par, parChar = _parChar, index = _index;
        for (int i = 0; i < M; ++i)
            children[i] = nxt[i] = NULL;
        fail = NULL, value = 0;
    }
};

node nodes[N];
int numNode = 0;

node *createNode(node *par, int parChar)
{
    nodes[numNode] = node(par, parChar, numNode);
    ++numNode;
    return &nodes[numNode - 1];
}
queue<node *> q;
int n, m, k;
struct AhoCorasick
{
    node *root;
    AhoCorasick()
    {
        root = createNode(NULL, -1);
    }

    void addString(const vector<int> &digits, int value)
    {
        node *tmp = root;
        for (int i = 0; i < (int)digits.size(); ++i)
        {
            int c = digits[i];
            if (tmp->children[c] == NULL)
                tmp->children[c] = createNode(tmp, c);
            tmp = tmp->children[c];
        }
        tmp->value += value;
    }

    void bfs()
    {
        // queue<*node > q;
        root->fail = root;
        for (int i = 0; i < m; ++i)
            root->nxt[i] = root->children[i] != NULL ? root->children[i] : root;
        root->value = 0;

        for (int i = 0; i < m; ++i)
            if (root->children[i] != NULL)
                q.push(root->children[i]);
        while (q.size())
        {
            node *u = q.front();
            q.pop();
            u->fail = u->par == root ? root : u->par->fail->nxt[u->parChar];
            u->value += u->fail->value;
            for (int i = 0; i < m; ++i)
            {
                u->nxt[i] = (u->children[i] != NULL ? u->children[i] : u->fail->nxt[i]);
            }
            for (int i = 0; i < m; ++i)
            {
                if (u->children[i] != NULL)
                    q.push(u->children[i]);
            }
        }
    }
} AC;
