class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 17;
        while ((1 << LOG) <= n) LOG++;

        vector<vector<int>> up(LOG, vector<int>(n));
        vector<int> tin(n), tout(n), dep(n), mask(n);
        int timer = 0;

        vector<int> st = {0}, par(n, -1), it(n, 0);

        while (!st.empty()) {
            int u = st.back();

            if (it[u] == 0) {
                tin[u] = timer++;
                up[0][u] = (par[u] == -1 ? u : par[u]);
                for (int j = 1; j < LOG; j++)
                    up[j][u] = up[j-1][up[j-1][u]];
            }

            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (v == par[u]) continue;
                par[v] = u;
                dep[v] = dep[u] + 1;
                st.push_back(v);
            } else {
                tout[u] = timer;
                st.pop_back();
            }
        }

        vector<int> bit(n + 2, 0);

        auto upd = [&](int i, int x) {
            for (++i; i <= n; i += i & -i) bit[i] ^= x;
        };

        auto get = [&](int i) {
            int x = 0;
            for (; i > 0; i -= i & -i) x ^= bit[i];
            return x;
        };

        for (int i = 0; i < n; i++) {
            mask[i] = 1 << (s[i] - 'a');
            upd(tin[i], mask[i]);
            upd(tout[i], mask[i]);
        }

        auto lca = [&](int u, int v) {
            if (dep[u] < dep[v]) swap(u, v);

            int d = dep[u] - dep[v];
            for (int j = 0; j < LOG; j++)
                if (d & (1 << j)) u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }
            return up[0][u];
        };

        vector<bool> ans;

        for (auto& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;
                int nw = 1 << (c - 'a');
                int d = mask[u] ^ nw;

                upd(tin[u], d);
                upd(tout[u], d);
                mask[u] = nw;
            } else {
                ss >> v;
                int w = lca(u, v);
                int m = get(tin[u] + 1) ^ get(tin[v] + 1) ^ mask[w];
                ans.push_back((m & (m - 1)) == 0);
            }
        }

        return ans;
    }
};