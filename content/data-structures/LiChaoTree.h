/**
 * Author: DeMen100ns
 * Date: 2023
 * Description: 
 */

struct LiChaoTree{
    const int N = 3e5 + 5;
    Line seg[4 * N];
    void upd(int id, int l, int r, Line line){
        if (l == r){
            if (line(l) < seg[id](l)) seg[id] = line;
            return;
        }

        int mid = (l + r) >> 1;

        if (line.a < seg[id].a) swap(seg[id], line);

        if (line(mid) < seg[id](mid)){
            swap(seg[id], line);
            upd(id << 1 | 1, mid + 1, r, line);
        } else {
            upd(id << 1, l, mid, line);
        }
    }

    int get(int id, int l, int r, int x){
        if (l == r) return seg[id](x);

        int ans, mid = (l + r) >> 1;
        if (mid >= x){
            ans = get(id << 1, l, mid, x);
        } else {
            ans = get(id << 1 | 1, mid + 1, r, x);
        }

        return min(ans, seg[id](x));
    }

    void updr(int id, int l, int r, int u, int v, Line line){
        if (l > v || r < u || l > r) return;
        if (l >= u && r <= v){
            upd(id, l, r, line);
            return;
        }

        int mid = (l + r) >> 1;
        updr(id << 1, l, mid, u, v, line);
        updr(id << 1 | 1, mid + 1, r, u, v, line);
    }
};
