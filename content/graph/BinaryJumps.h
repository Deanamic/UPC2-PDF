/**
 * Author: Dean
 * License: CC0
 * Description: Computes lca with binaryjumps, root is 0
 * Time: O(nlogn)
 * Status: Tested?
 */

struct BinaryLifting {
    vector<vector<int> > BL;
    vector<vector<int> > adj;
    vector<int> P;
    vector<int> D;
    int V,E;
    int MAXLOG = 0;

    void dfs(int u, int p){
        D[u] = D[p] + 1;
        for (int v : adj[u]) {
            if (v != p) {
                BL[v][0] = u;
                dfs(v, u);
            }
        }
    }

    void build(int n){
        V = n;
        E = n-1;
        P.resize(V+1);
        D.resize(n);
        while ((1 << MAXLOG) <= V) ++MAXLOG;
        BL = vector<vector<int> > (V, vector<int> (MAXLOG));
        adj.resize(V);
        for (int i = 0; i < E; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        D[0] = -1;
        dfs(0,0);
        int LOG = 0;

        for (int i = 1; i < V + 1; ++i) {
            if(1 << (LOG+1) <= i) P[i] = ++LOG;
            else P[i] = LOG;
        }

        for (int j = 1; j < MAXLOG; ++j) {
            for (int i = 0; i < V; ++i) {
                BL[i][j] = BL[BL[i][j-1]][j-1];
            }
        }
    }

    int maxjump(int depth, int node){
        return BL[node][P[depth]];
    }

    int lift(int node, int h) {
        int cnt = 0;
        while(h) {
            if(h&1) node = BL[node][cnt];
            cnt++;
            h >>= 1;
        }
        return node;
    }

    int LCA(int a, int b) {
        if(D[a] > D[b]) a = lift(a, D[a] - D[b]);
        else b = lift(b, D[b] - D[a]);
        if(a == b) return a;
        int jump = MAXLOG-2;
        while(jump && a != b) {
            if(BL[a][jump] != BL[b][jump] && BL[a][jump+1] != BL[b][jump+1]) {
                a = lift(a, jump);
                b = lift(b, jump);
            }
            --jump;
        }
        return BL[a][0];
    }
};
