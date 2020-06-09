#include<bits/stdc++.h>
using namespace std;
struct Eulertour{
    vector<vector<pair<int,int>>> a;
    vector<int> deg;
  //  vector<bool> vis;
    vector<int> pt;
    vector<pair<int,int>> edge;
    int n;
 /*
    //used when necessary
    void cvis(){
        for(int i=1;i<=n;i++)
            vis[i]=false;
        return;
    }*/
    void add_edge(int u,int v){
        a[u].push_back({v,++id});
        a[v].push_back({u,id});
        deg[u]++;deg[v]++;
    }

    Eulertour(int _n){
        a.resize(_n+5);
       // vis.resize(_n+5,false);
        deg.resize(_n+5,0);
        pt.resize(_n+5,0);
        n=_n;
    }
    pair<bool,int> ok(bool tour){
        int odd=0;
        int mark=1;
        for(int i=1;i<=n;i++){
            if(deg[i]&1){
                odd++;
                mark=i;
            }
        }
        return tour?make_pair(odd==0,mark):make_pair(((odd==2)||(odd==0)),mark);
    }
    vector<int> tour(int nod){
        vector<int> path;
        for(int i=0;i<(int)edge.size();i++){
            a[edge[i].first].push_back({edge[i].second,i});
            a[edge[i].second].push_back({edge[i].first,i});
        }
        vector<int> st;
        vector<bool> rem((int)edge.size()+5,false);
        st.push_back(nod);
        while(!st.empty()){
            int p=st.back();
            int q=-1;
            while(pt[p]<deg[p]&&q==-1){
                if(!rem[a[p][pt[p]].second]){
                    q=a[p][pt[p]].first;
                    rem[a[p][pt[p]].second]=true;
                }
                ++pt[p];
            }
            if(q==-1){
                st.pop_back();path.push_back(p);
            }
            else{
                st.push_back(q);
            }
        }
        return path;
    }
};

int main(){
}

