#include<bits/stdc++.h>
using namespace std;
const int nax = 3e5 + 10;
int sz[nax];
int parent[nax];
int head[nax];
int where[nax];
int tot;
vector <int> g[nax];
/**
*   Heavy light decomposition
*   verification : Toki regular open contest 14 problem F
*
*/
void dfs_sz(int node, int par) {
    sz[node] = 1;
    parent[node] = par;
    if (par > 0) g[node].erase(find(g[node].begin(), g[node].end(), par));
    for (int & i : g[node]) {
        dfs_sz(i, node);
        sz[node] += sz[i];
        if (sz[i] > sz[g[node][0]]) swap(i, g[node][0]);
    }
}
void dfs_hld(int node) {
    where[node] = ++ tot;
    for (int i : g[node]) {
        head[i] = i == g[node][0] ? head[node] : i;
        dfs_hld(i);
    }
}
void update(int node) { /// example of update from node to root
    /// if update to arbitary parent simply check position during update
    for (int x = node ; x > 0 ; x = parent[head[x]]) {
        int to = head[x];
    }
}

int main() {

}
