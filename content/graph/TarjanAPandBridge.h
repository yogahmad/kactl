/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds Articulation point and bridge
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */

void tarjanAPB(int u){ 
	dlow[u] = dnum[u] = nxt++; 
	for ( int i = 0; i < adlis[u].size(); i++ ){ 
	    int v = adlis[u][i]; 
	    if ( dnum[v] == -1 ) { 
		dpar[v] = u; 
		if ( u == dfs_root ) child_root++; 
		tarjanAPB(v); 
		if ( dlow[v] >= dnum[u] ) { 
			isAP[u] = true; 
		} 
		if ( dlow[v] > dnum[u] ) { 
			is_bridge[u][v] = true; 
		} 
		dlow[u] = min(dlow[u], dlow[v]); 
	    } 
	    else if ( v != dpar[u] ) { 
		dlow[u] = min(dlow[u], dnum[v]); 
	    } 
	} 
}... 
nxt=0; 
RESET(dnum,-1); 
RESET(dlow,-1); 
RESET(dpar,-1); 
RESET(isAP,0); 
RESET(is_bridge,0); 
for ( int i=0; i < nvert; i++ ){ 
	if ( dnum[i] == -1 ){ 
	    dfs_root = i; 
	    child_root = 0; 
	    tarjanAPB(i); 
	    is_AP[dfs_root] = (child_root > 1); 
	} 
}
