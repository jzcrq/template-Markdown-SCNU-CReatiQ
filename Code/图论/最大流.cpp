bool bfs(ll s,ll t){
	queue<ll>q;
	for(int i=1;i<=n;i++) dis[i]=-1;dis[s]=0;
	for(int i=1;i<=n;i++) cur[i]=frm[i];
	q.push(s);
	while(!q.empty()){
		ll x=q.front();q.pop();
		for(int i=frm[x];i;i=e[i].net){
			ll v=e[i].to;
			if(dis[v]==-1&&e[i].val) dis[v]=dis[x]+1,q.push(v);
		}
	}
	return dis[t]!=-1;
}

ll dfs(ll s,ll flow){
	if(s==t||!flow) return flow;
	if(dis[s]>=dis[t]) return 0;
	ll now=0,res=0;
	for(int i=cur[s];i;i=e[i].net){
		ll x=e[i].to;
		if(dis[x]==dis[s]+1&&e[i].val){
			res=dfs(x,min(flow-now,e[i].val));
			if(!res) continue;
			e[i].val-=res;e[i^1].val+=res;now+=res;flow-=res;
			cur[s]=i;
			if(!flow) break;
		} 
	}
	if(!now) return (dis[s]=0);
	return now;
}

void dinic(ll s,ll t){
	while(bfs(s,t)){
		ll last=dfs(s,1e18);
		while(last) ans+=last,last=dfs(s,1e18);
	}
}
