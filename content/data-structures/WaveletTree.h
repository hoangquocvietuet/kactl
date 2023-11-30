/**
 * Author: DeMen100ns
 * Date: 2023
 * License: CC0
 * Description: 
 */

void build(int id, int l, int r, vector <int> v){
    if (l == r) return;

    int mid = (l + r) >> 1;

    pre[id].push_back(0); //0-based -> 1-based

    vector <int> vl, vr;
    for(int i : v){
        if (a[i] <= mid) vl.push_back(i);
        else vr.push_back(i);

        int tmp = (a[i] <= mid);
        pre[id].push_back(tmp + pre[id].back());
    }

    build(id << 1, l, mid, vl);
    build(id << 1 | 1, mid + 1, r, vr);
}

int get(int id, int l, int r, int u, int v, int k){
    if (l == r){
        return decmp(l);
    }

    int ul = pre[id][u - 1] + 1, vl = pre[id][v];
    int ur = u - ul + 1, vr = v - vl;

    int mid = (l + r) >> 1;

    if (vl - ul + 1 >= k){
        return get(id << 1, l, mid, ul, vl, k);
    } else {
        return get(id << 1 | 1, mid + 1, r, ur, vr, k - (vl - ul + 1));
    }
}
