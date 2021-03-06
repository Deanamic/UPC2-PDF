/**
 * Author: Dean Zhu
 * Date: 2018-11-15
 * License: CC0
 * Source: KACTL PDF
 * Description: Calculates de maxflow using push relabel, reset ec cur hs and H to reuse.
 * Time: O(V^{2}\sqrt{E})
 * Status: tested on SPOJ (same problem as FASTMAXFLOW)
 */

typedef ll Flow;
struct Edge {
	int dest, back;
	Flow f, c;
};

struct PushRelabel {
	vector<vector<Edge>> g;
	vector<Flow> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

	void addEdge(int s, int t, Flow cap, Flow rcap=0) {
		if (s == t) return;
		Edge a = {t, sz(g[t]), 0, cap};
		Edge b = {s, sz(g[s]), 0, rcap};
		g[s].push_back(a);
		g[t].push_back(b);
	}

	void addFlow(Edge& e, Flow f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
  void reset() {
		int v = sz(g);
		FOR(i, 0, v) FOR(j, 0, sz(g[i])) g[i][j].c += g[i][j].f, g[i][j].f = 0;
		ec = vector<Flow>(v,0);
		H = vi(v,0);
		hs = vector<vi>(2*v);
  }
	Flow maxflow(int s, int t) {
    //reset();
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2*v); co[0] = v-1;
		FOR(i,0,v) cur[i] = g[i].data();
		for(auto& e : g[s]) add_flow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0) {
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for(auto& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						FOR(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					add_flow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
      }
		}
	}
};
