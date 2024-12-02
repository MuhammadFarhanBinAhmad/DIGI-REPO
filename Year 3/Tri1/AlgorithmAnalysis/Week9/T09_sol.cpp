// Q1
// Q1.2: O(n)
class Solution {
public:
    int rob(vector<int>& nums) {
        // Q1.1 recursive
        int n = nums.size();
        vector<int> memo(n, -1);
        return dfs(n - 1, memo, nums);

        // Q1.3 iterative
        // int n = nums.size();
        // if(n<=1) return nums[0];
        // vector<int> dp (n+1, 0);
        // dp[0] = nums[0];
        // dp[1] = max(nums[0], nums[1]);
        // for(int i = 1; i<n; i++) {
        //     dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        // }

        // return dp[n-1];

        // Q1.3 using only two vars
        // int dp0 = 0, dp1 = 0;
        // for (int x : nums) {
        //     int new_dp = max(dp1, dp0 + x);
        //     dp0 = dp1;
        //     dp1 = new_dp;
        // }
        // return dp1;
    }

    int dfs(int i, vector<int> &memo, vector<int>& nums) {
        if (i < 0) return 0;
        if (memo[i] != -1) return memo[i]; // computed
        return memo[i] = max(dfs(i-1, memo, nums), dfs(i-2, memo, nums) + nums[i]); // not computed
    }
};


// Q2
// Q2.2 O(nm)
// Q2.3
//   0ace
// 0 0000
// a 0111
// b 0111
// c 0122
// d 0122
// e 0123
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {

    // Q2.1 iterative solution
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    for (int i = 1; i <= m; i++) {
        char c1 = text1.at(i - 1);
        for (int j = 1; j <= n; j++) {
            char c2 = text2.at(j - 1);
            if (c1 == c2) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
            //cout<<dp[i][j];
        }
        //cout<<endl;
    }

    // return dp[m][n];

    // Q2.4 using only a 1D array
    // int m = text1.length(), n = text2.length();
    // vector<int>dp(n + 1);

    // for (int i = 1; i <= m; i++) {
    //     char c1 = text1.at(i - 1);
    //     for (int j = 1, pre = 0; j <= n; j++) { // dp[j] needs dp[j-1], so increasing j
    //         char c2 = text2.at(j - 1);
    //         int temp = dp[j]; //record the dp[j]
    //         if (c1 == c2) {
    //             dp[j] = pre + 1;
    //         } else {
    //             dp[j] = max(dp[j], dp[j - 1]);
    //         }
    //         pre = temp; // pre is the previouse dp[j]: dp[i-1][j-1]
    //     }
    // }
    // return dp[n];

    }
};

// Q3
// Q3.2 O(nm)
// Q3.3
//   0execution
// 0 0123456789
// i 1123456678
// n 2223456777
// t 3333455678
// e 4343456678
// n 5444456777
// t 6555555678
// i 7666666567
// 0 8777777656
// n 9888888765
class Solution {
 public:
  int minDistance(string word1, string word2) {
    
    // Q3.1 iterative solution
    int m = word1.length(), n = word2.length();
    // dp[i][j] := min # of operations to convert word1[0..i] to word2[0..j]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) {
      dp[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
      dp[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
      char c1 = word1.at(i - 1);
      for (int j = 1; j <= n; j++) {
        char c2 = word2.at(j - 1);
        if (c1 == c2) {// same characters
          dp[i][j] = dp[i - 1][j - 1];// no operation
        } else {
          dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                             //replace       //delete        //insert
        }
        cout<<dp[i][j];
      }
      cout<<endl;
    }
    return dp[m][n];


    // Q3.4 using only a 1D array
    // int m = word1.length(), n = word2.length();
    // vector<int>dp(n + 1);
    // for (int j = 0; j <= n; ++j) {
    //   dp[j] = j;
    // }

    // for (int i = 1; i <= m; i++) {
    //     char c1 = word1.at(i - 1);
    //     int pre = dp[0];
    //     dp[0]++;
    //     for (int j = 1; j <= n; j++) { // dp[j] needs dp[j-1], so increasing j
    //         char c2 = word2.at(j - 1);
    //         int temp = dp[j]; //record the dp[j]
    //         if (c1 == c2) {
    //             dp[j] = pre; // no operation
    //         } else {
    //             dp[j] = min(min(pre, dp[j]), dp[j - 1]) + 1;
    //         }
    //         pre = temp; // pre is the previouse dp[j]: dp[i-1][j-1]
    //         cout<<dp[j];
    //     }
    //     cout<<endl;
    // }
    // return dp[n];

  }
};