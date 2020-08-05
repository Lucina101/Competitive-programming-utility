#include<bits/stdc++.h>
using namespace std;
const int nax = 2e5 + 10;
constexpr pair <int, int> mod = make_pair(998244353, int(1e9) + 7);
int p[2][nax];

/**
    check if two non-rooted tree is isomorphic or not.
    Complexity O(nlog(n))
    verification: cses.fi tree Isomorphism II test case seems not to be very strong though.
    SPOJ tree isomorphism
    Codeforces : Jakarta regional 2019 regular forestation
*/

void dfs (vector < vector <int>> & tree, vector <int> &sz, vector <int> &par, int node, int parent) {
    par[node] = parent;
    sz[node] = 1;

    for (int i : tree[node]) {
        if (i == parent) continue;
        dfs(tree, sz, par, i, node);
        sz[node] += sz[i];
    }
}

vector <int> get_centroid (int tree_sz, vector <vector <int> > &tree, vector <int> &parent, vector <int> &sz) {
    vector <int> res;
    for (int i = 1 ; i <= tree_sz ; ++ i) {
        bool is_centroid = true;
        for (int j : tree[i]) {
            if (j == parent[i]) {
                is_centroid &= ((tree_sz - sz[i]) * 2 <= tree_sz);
            } else is_centroid &= (2 * sz[j] <= tree_sz);
        }
        if (is_centroid) res.push_back(i);
    }
    return res;
}

int resolve_hash (vector <pair <int, int>> & vec_hash, const int MOD, int * pre_power) {
    int cur = 1;

    for (auto &[val, sz] : vec_hash) {
        cur = 1LL * cur * pre_power[sz] % MOD;
        cur += val ;
        cur %= MOD;
    }

    return cur * 2 % MOD;
}

pair <int, int> dfs_hash_code(vector <vector <int> > &tree, vector <int> &sz, int node, int parent) {
    vector < pair <int, int>> hash1, hash2;
    for (int to : tree[node]) {
        if (to == parent) continue;
        pair <int, int> get = dfs_hash_code(tree, sz, to, node);
        hash1.emplace_back(get.first, sz[to] * 2 - 1);
        hash2.emplace_back(get.second, sz[to] * 2 - 1);
    }
    sort(hash1.begin(), hash1.end());
    sort(hash2.begin(), hash2.end());

    return make_pair(resolve_hash(hash1, mod.first, p[0]), resolve_hash(hash2, mod.second, p[1]));
}

pair <int ,int> get_hash_code (vector <vector <int>> & tree, int root, vector <int> &parent, vector <int> &sz) {
    dfs(tree, sz, parent, root, 0);
    return dfs_hash_code(tree, sz, root, 0);
}

bool solve() {
    int n;
    scanf("%d", &n);
    vector < vector <int>> a(n + 1), b(n + 1);
    vector <int> sz_a(n + 1, 0), sz_b(n + 1, 0);
    vector <int> parent_a(n + 1, 0), parent_b(n + 1, 0);

    for (int i = 1 ; i < n ; ++ i) {
        int u, v;
        scanf("%d %d", &u, &v);
        a[u].push_back(v);
        a[v].push_back(u);
    }

    for (int i = 1 ; i < n ; ++ i) {
        int u, v;
        scanf("%d %d", &u, &v);
        b[u].push_back(v);
        b[v].push_back(u);
    }


    dfs(a, sz_a, parent_a, 1, 0);
    dfs(b, sz_b, parent_b, 1, 0);

    vector <int> centroid_a = get_centroid(n, a, parent_a, sz_a);
    vector <int> centroid_b = get_centroid(n, b, parent_b, sz_b);

    if (centroid_a.size() != centroid_b.size()) return false;

    for (int i : centroid_a)
    for (int j : centroid_b) {
        if (get_hash_code(a, i, parent_a, sz_a) == get_hash_code(b, j, parent_b, sz_b)) return true;
    }

    return false;
}

int main () {
    int T;

   p[0][0] = 1;
   p[1][0] = 1;

    for (int i = 1 ; i < nax ; ++ i) {
        p[0][i] = p[0][i - 1] * 2 % mod.first;
        p[1][i] = p[1][i - 1] * 2 % mod.second;
    }

    for (scanf("%d", &T) ; T -- ;) {
        puts(solve() ? "YES" : "NO");
    }
}
