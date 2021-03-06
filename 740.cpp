// Tabulation/Bottom-Up DP
class Solution {
public:
    const int MAX = 10001;
    int deleteAndEarn(vector<int>& nums) {
        vector<int> v, cnt(MAX, 0);
        for(int i = 0; i < nums.size(); ++i) cnt[nums[i]]++;
        for(int i = 0; i < MAX; ++i) {
            if(cnt[i]) v.push_back(i);
        }
        sort(v.begin(), v.end());
        int prev1 = v[0] * cnt[v[0]], prev2 = 0;
        if(v.size() > 1) {
            prev2 = v[1] * cnt[v[1]];
            if(v[1] - 1 != v[0]) prev2 += prev1;
            else prev2 = max(prev2, prev1);
        }
        for(int i = 2; i < v.size(); ++i) {
            int m = v[i] * cnt[v[i]];
            int c1 = prev2, c2 = m + prev1;
            if(v[i] - 1 != v[i-1]) c1 += m;
            swap(prev1, prev2);
            prev2 = max(c1, c2);
        }
        return max(prev1, prev2);
    }
};

// Memorization/Top-Down DP
class Solution {
public:
    const int MAX = 10001;
    int getMaxPoint(vector<int>& cnt, vector<int>& dp, int idx) {
        if(idx >= MAX) return 0;
        if(dp[idx] == -1) {
            dp[idx] = max(idx * cnt[idx] + getMaxPoint(cnt, dp, idx + 2), getMaxPoint(cnt, dp, idx + 1));
        }
        return dp[idx];
    }
    int deleteAndEarn(vector<int>& nums) {
        vector<int> cnt(MAX, 0), dp(MAX);
        for(int i = 0; i < MAX; ++i) dp[i] = -1;
        for(int i = 0; i < nums.size(); ++i) cnt[nums[i]]++;
        return getMaxPoint(cnt, dp, 1);
    }
};
