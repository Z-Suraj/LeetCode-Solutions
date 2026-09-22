class LUPrefix {
public:
    vector<bool> uploaded;
    int curr;

    LUPrefix(int n) {
        uploaded.resize(n + 1, false);
        curr = 0;
    }

    void upload(int video) {
        uploaded[video] = true;

        while (curr + 1 < uploaded.size() &&
               uploaded[curr + 1]) {
            curr++;
        }
    }

    int longest() {
        return curr;
    }
};