class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        function<void(int)> dfs = [&](int node) {
            int c = s[node] - 'a';
            int prev = last[c];

            if (prev != -1) {
                newParent[node] = prev;
            }

            last[c] = node;

            for (int child : adj[node]) {
                dfs(child);
            }

            last[c] = prev;
        };

        dfs(0);

        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 1);

        function<void(int)> calculate = [&](int node) {
            for (int child : newAdj[node]) {
                calculate(child);
                ans[node] += ans[child];
            }
        };

        calculate(0);

        return ans;
    }
};