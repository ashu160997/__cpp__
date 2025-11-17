#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef vector<int> vi;

int fib(int n)
{
    vector<int> vec(n + 1);

    vec[0] = 0;
    vec[1] = 1;

    for (int i = 2; i < n + 1; i++)
    {
        vec[i] = vec[i - 1] + vec[i - 2];
    }

    return vec[n];
}

int minmatrixmul(vector<int> &arr, int i, int j)
{
    if (i + 1 == j)
        return 0;

    int res = INT_MAX;

    for (int k = i + 1; k < j; k++)
    {
        int coun = minmatrixmul(arr, i, k) + minmatrixmul(arr, k, j) + arr[i] * arr[k] * arr[j];

        res = min(res, coun);
    }
    return res;
}

int minmatrixmul_dp(vector<int> &arr)
{
    int n = arr.size();

    vector<vector<int>> arr_dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++)
    {
        for (int i = 0; i < n - len; i++)
        {
            int j = i + len;
            arr_dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++)
            {
                int res = arr_dp[i][k] + arr_dp[k][j] + arr[i] * arr[k] * arr[j];
                arr_dp[i][j] = min(arr_dp[i][j], res);
            }
        }
    }
    return arr_dp[0][n - 1];
}

int minSquare_rec(int n)
{
    if (n == 0 || n == 1 || n == 2 | n == 3)
    {
        return n;
    }

    int ans = INT_MAX;

    for (int i = 1; i * i <= n; i++)
    {
        ans = min(ans, 1 + minSquare_rec(n - i * i));
    }
    return ans;
}

// minimum square problem
int minSquare(int n)
{
    if (n == 0 || n == 1 || n == 2 | n == 3)
    {
        return n;
    }
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;

    for (int i = 1; i * i <= n; i++)
    {
        for (int j = 0; i * i + j <= n; j++)
        {
            dp[i * i + j] = min(dp[i * i + j], 1 + dp[j]);
        }
    }
    return dp[n];
}
// coin change problem
int minCoinChangeRec(vector<int> &arr, int n, int sum)
{
    if (sum == 0)
        return 1;

    if (sum < 0 || n == 0)
    {
        return 0;
    }

    return minCoinChangeRec(arr, n - 1, sum) + minCoinChangeRec(arr, n, sum - arr[n - 1]);
}
int minCoinChange(vector<int> &arr, int n, int sum)
{
    if (sum == 0)
        return 1;

    if (sum < 0 || n == 0)
        return 0;

    vi dp(sum + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = arr[i]; j <= sum; j++)
        {
            dp[j] += dp[j - arr[i]];
        }
    }
    return dp[sum];
}

// 0 1 kanpsack problem
int knapsack(vector<int> &val, vector<int> &wt, int w, int n, vector<vector<int>> &dp_knapsack)
{
    if (w == 0 || n == 0)
        return 0;

    if (dp_knapsack[n][w] != -1)
        return dp_knapsack[n][w];

    int count = 0;

    if (wt[n - 1] <= w)
    {
        count = val[n - 1] + knapsack(val, wt, w - wt[n - 1], n - 1, dp_knapsack);
    }
    int nt = knapsack(val, wt, w, n - 1, dp_knapsack);

    return dp_knapsack[n][w] = max(count, nt);
}

// longest increasing subsequence
int longest_inc_subsequence(vector<int> &arr)
{
    int n = arr.size();
    vector<int> lis(n, 1);
    int max_lis = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1)
            {
                lis[i] = lis[j] + 1;
                max_lis = max(max_lis, lis[i]);
            }
        }
    }
    return max_lis;
}

///////////minimum jump to reach the end//////////////
int min_jump_end(vector<int> &arr)
{
    int n = arr.size();
    vector<int> jumps(n, INT_MAX);
    jumps[0] = 0;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if ((arr[j] + j) >= i)
            {
                jumps[i] = min(jumps[i], jumps[j] + 1);
            }
        }
    }
    return jumps[n - 1];
}

// optimal game strategy
int optimalGameStrategy_rec(int i, int j, vector<int> &arr, vector<vector<int>> &dp)
{
    if (i == j)
    {
        return arr[i];
    }
    if (i > j)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    int l = arr[i] + min(optimalGameStrategy_rec(i + 2, j, arr, dp), optimalGameStrategy_rec(i + 1, j - 1, arr, dp));
    int r = arr[j] + min(optimalGameStrategy_rec(i + 1, j - 1, arr, dp), optimalGameStrategy_rec(i, j - 2, arr, dp));

    return dp[i][j] = max(l, r);
}

int optimalGameStrategy(vector<int> &arr)
{
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));

    int res = optimalGameStrategy_rec(0, n - 1, arr, dp);

    return res;
}

// number of string without consecutive binary 1

int binarywoConsOne(int n)
{
    vector<int> vec(n + 2, 0);
    vec[0] = 1;
    vec[1] = 1;
    for (int i = 2; i <= n + 1; i++)
    {
        vec[i] = vec[i - 1] + vec[i - 2];
    }
    return vec[n + 1];
}
// 0 N knapsack problem
/*
int zeroNknapsack()
{
}*/

// kadane algorithm

int maxsumarray(vector<int> &arr)
{
    int n = arr.size();
    int count = 0;
    int maxtillnow = 0;

    for (int i = 0; i < n; i++)
    {
        count = count + arr[i];
        maxtillnow = max(maxtillnow, count);

        if (count < 0)
        {
            count = 0;
        }
    }
    return maxtillnow;
}

int maxbitonicseq(vector<int> &arr)
{
    int n = arr.size();
    vector<int> inc(n, 1);
    vector<int> dec(n, 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j])
            {
                inc[i] = max(inc[i], inc[j] + 1);
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (arr[i] > arr[j])
            {
                dec[i] = max(dec[j], dec[j] + 1);
            }
        }
    }
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        mx = max(mx, inc[i] + dec[i] - 1);
    }
    return mx;
}

int main()
{
    cout << "..........fibonacci numbers..........." << endl;
    int k = fib(10);

    cout << k << endl;

    cout << "..........min matrix multiplication..........." << endl;
    vector<int> arr = {2, 1, 3, 4};
    cout << minmatrixmul_dp(arr) << endl;

    cout << "..........min square problem..........." << endl;
    cout << minSquare(14) << endl;

    cout << "..........min change problem..........." << endl;
    vi arr1 = {1, 2, 3};
    cout << minCoinChange(arr1, arr1.size(), 6) << endl;

    cout << "..........0-1 kanpsack problem........." << endl;
    vector<int> wt = {4, 5, 1};
    vector<int> val = {1, 2, 3};
    int w = 4;
    int n_k = val.size();
    vector<vector<int>> dp_knapsack(n_k + 1, vector<int>(w, -1));
    cout << knapsack(val, wt, w, 3, dp_knapsack) << endl;

    cout << "...........longest increasing subsequence........." << endl;
    vector<int> lis = {3, 10, 2, 1, 20};
    cout << longest_inc_subsequence(lis) << endl;

    cout << "...........minimum jump to reach the end........." << endl;
    vector<int> mj = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    cout << min_jump_end(mj) << endl;

    cout << "...........optimal game strategy........." << endl;
    vector<int> ogm = {1, 2, 3, 4};
    cout << optimalGameStrategy(ogm) << endl;

    cout << "...........number of string without consecutive binary 1........." << endl;
    cout << binarywoConsOne(3) << endl;

    cout << "...........kadane algorithm........." << endl;
    vector<int> kd = {-5, -1, 5, -3, -1, 2, 3, -6};
    cout << maxsumarray(kd) << endl;

    cout << "...........maximum length bitonic sequence........." << endl;
    vector<int> kd1 = {1, 11, 2, 10, 4, 5, 2, 1};
    cout << maxbitonicseq(kd1) << endl;

    return 0;
}