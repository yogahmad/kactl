/**
 * Author: Yoga Pratama
 * Date: 2009-10-28
 * Description: Build Centroid Structure
 */
void dfs0(int now,int pa,int lev){
	P[now][0]=pa;
	level[now]=lev;
	for(set<int>::iterator it=ad[now].begin();it!=ad[now].end();it++){
		if(pa!=*it){
			dfs0(*it,now,lev+1);
		}
	}
}
 
int dist(int aa,int bb){
	return level[aa]+level[bb]-2*level[findLCA(aa,bb)];
}
 
/////////////////////
int nn=0;
 
void dfs1(int now,int pa){
	sz[now]=1;
	nn++;
	for(set<int>::iterator it=ad[now].begin();it!=ad[now].end();it++){
		if(pa!=*it){
			dfs1(*it,now);
			sz[now]+=sz[*it];
		}
	}
}
 
int dfs2(int now,int pa){
	for(set<int>::iterator it=ad[now].begin();it!=ad[now].end();it++){
		if(pa!=*it && sz[*it]>nn/2){
			return dfs2(*it,now);
		}
	}
	return now;
}
 
void centroid(int now,int pa){
	nn=0;
	dfs1(now,now);
	int center=dfs2(now,now);
	if(pa==-1)pa=center;
	par[center]=pa;
	for(set<int>::iterator it=ad[center].begin();it!=ad[center].end();it++){
		ad[*it].erase(center);
		centroid(*it,center);
	}
	ad[center].clear();
}
 
void update(int now){
	int x=now;
	while(1){
		while(!pq[x].empty() && !white[pq[x].top().s])pq[x].pop();
		pq[x].push(mp(dist(now,x),now));
		ans[x]=pq[x].top().f;
		if(x==par[x])break;
		x=par[x];
	}
}
 
void update1(int now){
	int x=now;
	while(1){
		while(!pq[x].empty() && !white[pq[x].top().s])pq[x].pop();
		ans[x]=pq[x].top().f;
		if(x==par[x])break;
		x=par[x];
	}
}
 
int query(int now){
	int x=now,ret=INF;
	while(1){
		ret=min(ret,dist(now,x)+ans[x]);
		if(x==par[x])break;
		x=par[x];
	}
	return ret;
}