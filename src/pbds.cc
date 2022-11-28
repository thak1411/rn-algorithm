#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
typedef int tree_type;
typedef tree < tree_type, null_type, std::less < tree_type >, rb_tree_tag, tree_order_statistics_node_update > ordered_set;

int main() {
    ordered_set st;
    st.insert(1); st.insert(2); st.insert(4); st.insert(5);

    printf("%d\n", *st.find_by_order(1)); // 2
    printf("%d\n", *st.find_by_order(2)); // 4
    printf("%d\n", *st.find_by_order(3)); // 5
    printf("%d\n", (end(st)==st.find_by_order(10))); // true
    printf("%d\n", st.order_of_key(-1)); // 0
    printf("%d\n", st.order_of_key(1)); // 0
    printf("%d\n", st.order_of_key(3)); // 2
    printf("%d\n", st.order_of_key(4)); // 2
    printf("%d\n", st.order_of_key(10)); // 4
    return 0;
}