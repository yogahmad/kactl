/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Ntar isinya comps itu vector of vector setiap  
 *	vector jadi satu komponen, kalok dia AP maka dia jadi edge 
 *	yang menghubungkan komponen yang mempunyai AP tersebut
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 * Usage:
 *  comps vector of vector
 */

void dfs(int now,int par){
	sudah[now]=true;
	disc[now]=low[now]=++idx;
	int anak=0;
	stk.pb(now);
	for(int i:g[now]){
		if(i==par)continue;
		if(!sudah[i]){
			dfs(i,now);
			anak++;
			low[now]=min(low[now],low[i]);
			if(low[i]>=disc[now]){
				comps.pb({now});
				while(comps.back().back()!=i){
					comps.back().pb(stk.back());
					stk.pop_back();
				}
			}
			if(now==1 && anak>1)
				ap[now]=true;
			if(now!=1 && low[i]>=disc[now])
				ap[now]=true;
		}
		else low[now]=min(low[now],disc[i]);
	}
}

int main(){
	dfs(1,0);
	idx=0;
	for(auto i:comps){
		idx++;
		for(int j:i){
			if(ap[j]){
				ve[j].pb(idx);
			}
			else{
				di[j]=idx;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(ap[i]){
			di[i]=++idx;
			ya[idx]=true;
			for(int j:ve[i]){
				G[idx].pb(j);
				G[j].pb(idx);
			}
		}
	}
}
