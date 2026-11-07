class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> free;

        priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<tuple<long long,int,int>>> busy;

        vector<int> ans(m);

        for(int i = 0; i < n; i++) {
            free.push({servers[i], i});
        }

        long long time = 0;

        for(int i = 0; i < m; i++) {

            time = max(time, (long long)i);

            while(!busy.empty() && get<0>(busy.top()) <= time) {
                auto [endTime, weight, index] = busy.top();
                busy.pop();

                free.push({weight, index});
            }

            if(free.empty()) {
                time = get<0>(busy.top());

                while(!busy.empty() && get<0>(busy.top()) <= time) {
                    auto [endTime, weight, index] = busy.top();
                    busy.pop();

                    free.push({weight, index});
                }
            }

            auto [weight, index] = free.top();
            free.pop();

            ans[i] = index;

            busy.push({time + tasks[i], weight, index});
        }

        return ans;
    }
};