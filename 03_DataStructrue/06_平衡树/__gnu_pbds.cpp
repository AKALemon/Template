#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class KT, class VT = null_type>
using RBTree = tree<KT, VT, less<KT>, rb_tree_tag, tree_order_statistics_node_update>;

insert(x)：向树中插入一个元素 x，返回 std::pair<point_iterator, bool>。
erase(x)：从树中删除一个元素/迭代器 x，返回一个 bool 表明是否删除成功。
order_of_key(x)：返回 x 以 Cmp_Fn 比较的排名。
find_by_order(x)：返回 Cmp_Fn 比较的排名所对应元素的迭代器。
lower_bound(x)：以 Cmp_Fn 比较做 lower_bound，返回迭代器。
upper_bound(x)：以 Cmp_Fn 比较做 upper_bound，返回迭代器。
join(x)：将 x 树并入当前树，前提是两棵树的类型一样，x 树被删除。
split(x,b)：以 Cmp_Fn 比较，小于等于 x 的属于当前树，其余的属于 b 树。
empty()：返回是否为空。
size()：返回大小。


哈希表 似乎比unordered_map快
gp_hash_table<int, int>
