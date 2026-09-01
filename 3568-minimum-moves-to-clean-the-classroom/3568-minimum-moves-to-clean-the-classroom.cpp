class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        vector<pair<int, int>> litter;

        // Find S and L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        // Assign bit to every litter
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            best[r][c][mask] = maximum energy
            with which we have reached (r,c)
            after collecting 'mask'.
        */
        int states = 1 << k;

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(
                n,
                vector<int>(states, -1)
            )
        );

        // {row, col, remainingEnergy, mask}
        queue<array<int, 4>> q;

        q.push({sr, sc, energy, 0});
        best[sr][sc][0] = energy;

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if (mask == fullMask)
                    return moves;

                // No energy -> cannot make another move
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    /*
                        If we have already reached this exact
                        (cell, mask) with >= energy, this state
                        can never give a better result.
                    */
                    if (best[nr][nc][nmask] >= ne)
                        continue;

                    best[nr][nc][nmask] = ne;
                    q.push({nr, nc, ne, nmask});
                }
            }

            moves++;
        }

        return -1;
    }
};