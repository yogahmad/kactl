/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 */
#pragma once

void dfs(int now) {
	s.push(now); Time++;
	onstack[now] = true;
	index[now] = Time;
	lowlink[now] = Time;
	visited[now] = true;
	
	for(int i = 0; i < G[now].size(); i++) {
		int next = G[now][i];
		if (!visited[next]) {
			dfs(next);
			lowlink[now] = min(lowlink[now], lowlink[next]);
		} else if (onstack[next]) {
			lowlink[now] = min(lowlink[now], index[next]);
		}
	}
	
	if (lowlink[now] == index[now]) {
		int mini = 1e9;
		int cnt = 0;
		int cur;
		do {
			cur = s.top(); s.pop();
			onstack[cur] = false;
			if (cost[cur] < mini) mini = cost[cur], cnt = 0;
			if (cost[cur] == mini) cnt++;
		} while(cur != now);
		
		mincost += mini;
		ways = (ways * (LL)cnt)%MOD;
	}
}

for(int i = 1; i <= n; i++) {
	if (!visited[i]) {
		dfs(i);
	}
}
	