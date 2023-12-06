/**
 * Description: Persistent Segment Tree.
 * Time: O(logn) per operation.
 */

const int logn = 17;

struct Node
{
    int left, right; // ID of left child & right child
    long long value; // Max value of node
    Node() {}
    Node(long long value, int left, int right) : value(value), left(left), right(right) {}
};

struct PersistenSegmentTree // max it
{
    vector<int> root;
    vector<Node> tree;
    int nNode = 0, nVer = 0;
    int n;

    PersistenSegmentTree(int _n = 0, int _q = 0)
    {
        n = _n;
        root.assign(_q + 7, 0);
        tree.assign(n * 4 + 7 + _q * logn, Node(0, 0, 0));
    }

    void merge(int cur)
    {
        tree[cur].value = max(tree[tree[cur].left].value, tree[tree[cur].right].value);
    }

    int init(int l, int r)
    {
        if (l == r)
        {
            ++nNode;
            tree[nNode] = Node(0, 0, 0);
            return nNode;
        }

        int mid = (l + r) / 2;
        int cur = ++nNode;

        tree[cur].left = init(l, mid);
        tree[cur].right = init(mid + 1, r);
        merge(cur);
        return cur;
    }
    void init()
    {
        root[nVer] = init(1, n);
    }

    int upd(int l, int r, int k, int newValue, int oldId) // upd value node k -> newValue
    {
        if (l == r)
        {
            ++nNode;
            tree[nNode] = Node(newValue, 0, 0);
            return nNode;
        }

        int mid = (l + r) / 2;
        int cur = ++nNode;

        if (k <= mid)
        {
            tree[cur].left = upd(l, mid, k, newValue, tree[oldId].left);
            tree[cur].right = tree[oldId].right;
            merge(cur);
        }
        else
        {
            tree[cur].left = tree[oldId].left;
            tree[cur].right = upd(mid + 1, r, k, newValue, tree[oldId].right);
            merge(cur);
        }
        return cur;
    }

    void upd(int k, int newValue)
    {
        ++nVer;
        root[nVer] = upd(1, n, k, newValue, root[nVer - 1]);
    }

    int getMax(int l, int r, int u, int v, int oldId)
    {
        if (l > v || r < u)
            return 0;
        if (u <= l && r <= v)
            return tree[oldId].value;

        int mid = (l + r) / 2;
        int L = getMax(l, mid, u, v, tree[oldId].left);
        int R = getMax(mid + 1, r, u, v, tree[oldId].right);

        return max(L, R);
    }

    int getMax(int l, int r, int id)
    {
        return getMax(1, n, l, r, root[id]);
    }
} it;