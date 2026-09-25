class Solution {
public:

    set<string> solve(string &s, int &i) {

        set<string> ans;
        set<string> cur;
        cur.insert("");

        while (i < s.size() && s[i] != '}') {

            // Comma = OR / Choice
            if (s[i] == ',') {

                for (string x : cur)
                    ans.insert(x);

                cur.clear();
                cur.insert("");

                i++;
            }

            // Opening brace
            else if (s[i] == '{') {

                i++;

                set<string> inside = solve(s, i);

                i++; // skip '}'

                set<string> temp;

                // Combine cur + inside
                for (string a : cur) {
                    for (string b : inside) {
                        temp.insert(a + b);
                    }
                }

                cur = temp;
            }

            // Normal character
            else {

                string ch(1, s[i]);

                set<string> temp;

                for (string x : cur) {
                    temp.insert(x + ch);
                }

                cur = temp;

                i++;
            }
        }

        // Add last choice
        for (string x : cur)
            ans.insert(x);

        return ans;
    }

    vector<string> braceExpansionII(string expression) {

        int i = 0;

        set<string> result = solve(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};