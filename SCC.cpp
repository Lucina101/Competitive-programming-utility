#include  <bits/stdc++.h>
using namespace std;

vector <int>  a[1 << 17];
bool vis[1 << 17];
vector <int> ord;
int comp[1 << 17];
int n, m;
int col[1 << 17];

void dfs_ord (int nod) {
    vis[nod] = true;
    for (int i : a[nod]) {
        if (!vis[nod])
            dfs(i);
    }
    ord.push_back(nod);
}

void dfs_col (int nod) {
    vis[nod] = true;
    col[nod] = m;

    for (int i : a[nod])
        if (!vis[i])
            dfs(i);
}

void build_scc () {

    for (int i = 1 ; i <= n ; ++ i) {
        if (!vis[i]) dfs_ord(i);
    }

    reverse(order.begin(), order.end());
    memset(vis, false, sizeof(vis));

    for (int i : order) {
        if (!vis[i]) {
            ++ m;
            dfs_col(i);
        }
    }
}

int main () {

}
