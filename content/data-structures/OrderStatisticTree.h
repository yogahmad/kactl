/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * Time: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

using namespace __gnu_pbds;
using namespace __gnu_cxx;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
ordered_set S;
// S.find_by_order(x) -> return pointer to the x-th element
// (int)S.order_of_key(x) -> return the position of lower_bound(x)

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
	  tree_order_statistics_node_update>;

void example() {
	Tree<int> t, t2; t.insert(8);
	auto it = t.insert(10).first;
	assert(it == t.lower_bound(9));
	assert(t.order_of_key(10) == 1);
	assert(t.order_of_key(11) == 2);
	assert(*t.find_by_order(0) == 8);
	cout<<*X.find_by_order(1)<<endl;          // array index ke-1
  cout<<(end(X)==X.find_by_order(6))<<endl; // end(X) = pointer
  cout<<X.order_of_key(400)<<endl;          // idx lower_bound 400
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
