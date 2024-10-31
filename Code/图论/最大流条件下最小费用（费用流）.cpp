bool bfs(ll s,ll t){
	queue<ll>q;
	memset(dis,127,sizeof dis);memset(vis,0,sizeof vis);memset(pre,-1,sizeof pre);
	ll inf=dis[0];dis[s]=0;vis[s]=1;
	dis[s]=pre[s]=0;flow[s]=inf;q.push(s);
	while(!q.empty()){
		ll x=q.front();q.pop();vis[x]=0;
		for(int i=frm[x];i;i=e[i].net){
			ll v=e[i].to;
			if(dis[v]>dis[x]+e[i].cost&&e[i].val){
				dis[v]=dis[x]+e[i].cost;
				xb[v]=i;pre[v]=x;flow[v]=min(flow[x],e[i].val);
				if(!vis[v]) q.push(v),vis[v]=1;
			}
		}
	}
	if(dis[t]==inf) return 0;
	return 1;
}

void EK(ll s,ll t){
	while(bfs(s,t)){
		ll k=t;
		while(s!=k){
			e[xb[k]].val-=flow[t];e[xb[k]^1].val+=flow[t];
			k=pre[k];
		}
		maxflow+=flow[t];mincost+=flow[t]*dis[t];
	}
}
//add(x,y,v,c);add(x,y,0,-c);
