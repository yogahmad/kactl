/**
 * Author: Chen Xing
 * Date: 2009-04-14
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Usage: For eulerian path, should pass cur with odd degree to eulerian().
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */
#pragma once

void eulerian(int cur){
	stack<int> st;
	vector<int> ans;
	st.push(cur);
	//V is multiset
	while(!st.empty()){
		int cur = st.top();
		if(V[cur].size()){
			auto it = V[cur].begin();
			st.push(*it);
			V[cur].erase(it);	
			//use this for bidirectional graph
			//if(V[*it].count(cur)){
			//	V[*it].erase(V[*it].find(cur));
			//}
		}else{
			ans.pb(cur);
			st.pop();
		}
	}
}
