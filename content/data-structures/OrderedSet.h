/**
 * Author: ???
 * Date: 2017-11-12
 * License: CC0
 * Source: ???
 * Description: Order Statistics tree
 * Usage: Set.find_by_order(k) returns an iterator to the k-th object, Set.order_of_key finds its rank in the set. (its index in the sorted set)
 * Time: O(\log N)
 * Status: tested
 */

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
