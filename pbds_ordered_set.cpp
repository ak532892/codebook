#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

// 如果元素不重複
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
// 如果元素重複
template<typename T> using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

// 一個是less, 另一個是less_equal

ordered_set<int> oset;
oset.insert(1);

// 找第k小的值 (k是從0開始 也就是說第0小 就是最小值)
*oset.find_by_order(k);
 
// 找第k大的值 (k是從0開始 也就是說第0大 就是最大值)
*oset.find_by_order(oset.size() - 1 - k)

// 回傳有幾個數字小於num, 改成less_equal也沒救
oset.order_of_key(num);

// 如果用 less_equal 要刪除元素的話，要這樣使用
// upper_bound 相當於 lower_bound return the first element >= it
// lower_bound 相當於 upper_bound return the first element > it
// oset.erase(oset.upper_bound(num));
