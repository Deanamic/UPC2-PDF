/**
 * Author: Dean Zhu
 * License: CC0
 * Source:https://codeforces.com/gym/101981 Problem B, ioi 2016 aliens dp
 * Description: Given a problem to minimize dp[n][k] choosing k cuts/groups and dp[n][j] is convex, we can relax the second condition and perform a binary search on some integer penalization, we find the min dp[n][x] + C*x, and find the maximum C such that x <= k, then we can simply substract C*k from this answer
 * Time: O(N^2K) $\rightarrow$ O(NlogN)\\
 */
