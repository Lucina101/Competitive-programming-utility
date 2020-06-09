/*
Binary lifting + LCA
Credit:https://cp-algorithms.com/graph/lca_binary_lifting.html#toc-tgt-1
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10,LOG=20;
int up[maxn][LOG],n,tin[maxn],tout[maxn],timer,x,y;
vector<int> a[maxn];
void dfs(int nod,int pa){
    ++timer;
    tin[nod]=timer;
    up[nod][0]=pa;
    for(int i=1;i<=LOG;i++){
        up[nod][i]=up[up[nod][i-1]][i-1];
    }
    for(int i:a[nod]){
        if(i!=pa){
            dfs(i,nod);
        }
    }
    tout[nod]=++timer;
    return;
}
bool ancestor(int u,int v){
    return tin[u]<=tin[v]&&tout[u]>=tout[v];
}
int lca(int u,int v){
    if(ancestor(u,v))
        return u;
    if(ancestor(v,u))
        return v;
    for(int i=LOG;i>=0;i--){
        if(!ancestor(up[u][i],v))
            u=up[u][i];
    }
    return up[u][0];
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        scanf("%d%d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(1,0);
    cout<<"LuCinA"<<endl;
    return 0;
}
