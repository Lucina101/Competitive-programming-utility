#include <vector>
using std::vector;
int const nax = 1 << 17;

bool out[nax];
int centroid_par[nax];
int sz[nax];
vector <int> c[nax];

int dfs_sz (vector <int> * v, int nod, int pa) {
    sz[nod] = 1;

    for (int i : v[nod]) {
        if (!out[i] && i != pa)
            sz[nod] +=  dfs_sz(v, i, nod);
    }

    return sz[nod];
}

int find_centroid (vector <int> * v, int nod, int pa, int tree_sz) {
    for (int i : v[nod]) {
        if (!out[i] && i != pa && sz[i] > tree_sz / 2) {
            return find_centroid(v, i, nod, tree_sz);
        }
    }

    return nod;
}

int find_centroid (vector <int> * v, int root) {
    dfs_sz(v, root, 0);
    return find_centroid(v, root, 0, sz[root]);
}

int build_centroid_tree(vector <int> * v, int root) {
    int centroid = find_centroid(v, root);
    out[centroid] = true;

    for (int i : v[centroid]) {
        if (!out[i]) {
            int ret = build_centroid_tree(v, i);
            c[centroid].push_back(ret);
            c[ret].push_back(centroid);
            centroid_par[ret] = centroid;
        }
    }

    return centroid;
}

int main() {
}
