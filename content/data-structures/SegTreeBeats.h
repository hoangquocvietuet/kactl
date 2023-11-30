/**
 * Author: DeMen100ns
 * Date: 2023
 * Description:
 */
#pragma once

const int N = 2e5 + 5;

struct segbeat{
	int mi[4 * N], semi[4 * N];
	int ma[4 * N], sema[4 * N];
	int cntmi[4 * N], cntma[4 * N];
	int sum[4 * N], lazy[4 * N];

	void reset(){
		memset(mi, 0, sizeof mi);
		memset(semi, 0, sizeof semi);
		memset(ma, 0, sizeof ma);
		memset(sema, 0, sizeof sema);
		memset(sum, 0, sizeof sum);
		memset(cntmi, 0, sizeof cntmi);
		memset(cntma, 0, sizeof cntma);
		memset(lazy, 0, sizeof lazy);
	}

	void merge(int id){
		ma[id] = max(ma[id << 1], ma[id << 1 | 1]);
		int mase = max(sema[id << 1], sema[id << 1 | 1]);
		if (ma[id << 1] > ma[id << 1 | 1]){
			sema[id] = max({ma[id << 1 | 1], mase});
			cntma[id] = cntma[id << 1];
		} else {
			if (ma[id << 1] == ma[id << 1 | 1]) {
				sema[id] = mase;
				cntma[id] = cntma[id << 1] + cntma[id << 1 | 1];
			}
			else{
				sema[id] = max({ma[id << 1], mase});
				cntma[id] = cntma[id << 1 | 1];
			}
		}
		mi[id] = min(mi[id << 1], mi[id << 1 | 1]);
		int mise = min(semi[id << 1], semi[id << 1 | 1]);
		if (mi[id << 1] < mi[id << 1 | 1]){
			semi[id] = min({mi[id << 1 | 1], mise});
			cntmi[id] = cntmi[id << 1];
		} else {
			if (mi[id << 1] == mi[id << 1 | 1]){
				semi[id] = mise;
				cntmi[id] = cntmi[id << 1] + cntmi[id << 1 | 1];
			}
			else{
				semi[id] = min({mi[id << 1], mise});
				cntmi[id] = cntmi[id << 1 | 1];
			}
		}
		sum[id] = sum[id << 1] + sum[id << 1 | 1];
	}

	void down(int id, int l, int r){
		int t = lazy[id];

		int mid = (l + r) >> 1;
		
		sum[id << 1] += t * (mid - l + 1);
		sum[id << 1 | 1] += t * (r - mid);
		
		ma[id << 1] += t; ma[id << 1 | 1] += t;
		mi[id << 1] += t; mi[id << 1 | 1] += t;
		
		if (sema[id << 1] != -INF) sema[id << 1] += t; 
		if (sema[id << 1 | 1] != -INF) sema[id << 1 | 1] += t;
		
		if (semi[id << 1] != INF) semi[id << 1] += t; 
		if (semi[id << 1 | 1] != INF) semi[id << 1 | 1] += t;
		
		lazy[id << 1] += t; lazy[id << 1 | 1] += t;
		lazy[id] = 0;

		int val = ma[id];
		if (ma[id << 1] > val){
			sum[id << 1] += cntma[id << 1] * (val - ma[id << 1]);
			ma[id << 1] = val;
			if (l == mid){
				mi[id << 1] = val;
			} else {
				if (val <= mi[id << 1]) mi[id << 1] = val;
				else if (val < semi[id << 1]) semi[id << 1] = val;
			}
		}

		if (ma[id << 1 | 1] > val){
			sum[id << 1 | 1] += cntma[id << 1 | 1] * (val - ma[id << 1 | 1]);
			ma[id << 1 | 1] = val;
			if (mid + 1 == r){
				mi[id << 1 | 1] = val;
			} else {
				if (val <= mi[id << 1 | 1]) mi[id << 1 | 1] = val;
				else if (val < semi[id << 1 | 1]) semi[id << 1 | 1] = val;
			}
		}

		val = mi[id];
		if (mi[id << 1] < val){
			sum[id << 1] += cntmi[id << 1] * (val - mi[id << 1]);
			mi[id << 1] = val;
			if (l == mid){
				ma[id << 1] = val;
			} else {
				if (val >= ma[id << 1]) ma[id << 1] = val;
				else if (val > sema[id << 1]) sema[id << 1] = val;
			}
		}

		if (mi[id << 1 | 1] < val){
			sum[id << 1 | 1] += cntmi[id << 1 | 1] * (val - mi[id << 1 | 1]);
			mi[id << 1 | 1] = val;
			if (mid + 1 == r){
				ma[id << 1 | 1] = val;
			} else {
				if (val >= ma[id << 1 | 1]) ma[id << 1 | 1] = val;
				else if (val > sema[id << 1 | 1]) sema[id << 1 | 1] = val;
			}
		}

	}

	void build(int id, int l, int r){
		if (l == r){
			ma[id] = mi[id] = sum[id] = a[l];
			sema[id] = -INF;
			semi[id] = INF;
			cntmi[id] = cntma[id] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(id << 1, l, mid);
		build(id << 1 | 1, mid + 1, r);
		merge(id);
	}

	void upd_chmax(int id, int l, int r, int u, int v, int val){
		//a[i] = max(a[i], val)
		if (l > v || r < u || mi[id] >= val) return;
		if (l >= u && r <= v && semi[id] > val){
			sum[id] += cntmi[id] * (val - mi[id]);
			mi[id] = val;
			if (l == r){
				ma[id] = val;
			} else {
				if (val >= ma[id]) ma[id] = val;
				else if (val > sema[id]) sema[id] = val;
			}
			return;
		}
		down(id, l, r);
		int mid = (l + r) >> 1;
		upd_chmax(id << 1, l, mid, u, v, val);
		upd_chmax(id << 1 | 1, mid + 1, r, u, v, val);
		merge(id);
	}

	void upd_chmin(int id, int l, int r, int u, int v, int val){
		//a[i] = min(a[i], val)
		if (l > v || r < u || ma[id] <= val) return;
		if (l >= u && r <= v && sema[id] < val){
			sum[id] += cntma[id] * (val - ma[id]);
			ma[id] = val;
			if (l == r){
				mi[id] = val;
			} else {
				if (val <= mi[id]) mi[id] = val;
				else if (val < semi[id]) semi[id] = val;
			}
			return;
		}
		down(id, l, r);
		int mid = (l + r) >> 1;
		upd_chmin(id << 1, l, mid, u, v, val);
		upd_chmin(id << 1 | 1, mid + 1, r, u, v, val);
		merge(id);
	}

	void upd_sum(int id, int l, int r, int u, int v, int val){
		//a[i] = max(a[i], val)
		if (l > v || r < u) return;
		if (l >= u && r <= v){
			sum[id] += val * (r - l + 1);
			ma[id] += val;
			mi[id] += val;
			if (semi[id] != INF) semi[id] += val;
			if (sema[id] != -INF) sema[id] += val;
			lazy[id] += val;
			return;
		}
		down(id, l, r);
		int mid = (l + r) >> 1;
		upd_sum(id << 1, l, mid, u, v, val);
		upd_sum(id << 1 | 1, mid + 1, r, u, v, val);
		merge(id);
	}

	int get(int id, int l, int r, int u, int v){
		if (l > v || r < u) return 0;
		if (l >= u && r <= v){
			return sum[id];
		}
		down(id, l, r);
		int mid = (l + r) >> 1;
		int v1 = get(id << 1, l, mid, u, v);
		int v2 = get(id << 1 | 1, mid + 1, r, u, v);
		return v1 + v2;
	}

	void debug(int n){
		for(int i = 1; i <= n; ++i){
			cout << get(1, 1, n, i, i) << " ";
		} cout << endl;
	}

} seg;
