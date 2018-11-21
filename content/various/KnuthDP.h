/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $dp[i][j] = \min_{i < k < j}(dp[i][k] + dp[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $dp[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$, That is $p[i][j-1] \leq p[i][j] \leq p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 * We should calculate the values on decreasing i and increasing j.
 * Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * Time: O(N^3) \rightarrow O(N^2)
 */
