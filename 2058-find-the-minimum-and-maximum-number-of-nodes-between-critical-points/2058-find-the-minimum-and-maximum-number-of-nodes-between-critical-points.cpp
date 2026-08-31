class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        vector<int> ans = {-1, -1};

        // At least 3 nodes are required for a critical point
        if (head == nullptr || head->next == nullptr || 
            head->next->next == nullptr) {
            return ans;
        }

        ListNode* prev = head;
        ListNode* curr = head->next;

        int pos = 1;          // position of curr
        int first = -1;       // first critical point
        int last = -1;        // previous critical point
        int minDist = INT_MAX;

        while (curr->next != nullptr) {

            int nextVal = curr->next->val;

            // Check local maxima or local minima
            if ((curr->val > prev->val && curr->val > nextVal) ||
                (curr->val < prev->val && curr->val < nextVal)) {

                // First critical point
                if (first == -1) {
                    first = pos;
                }

                // If this isn't the first critical point
                if (last != -1) {
                    minDist = min(minDist, pos - last);
                }

                last = pos;
            }

            prev = curr;
            curr = curr->next;
            pos++;
        }

        // Fewer than two critical points
        if (first == -1 || first == last) {
            return ans;
        }

        int maxDist = last - first;

        return {minDist, maxDist};
    }
};