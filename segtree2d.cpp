/**
    Problem: Given set of points in 2d plane
    Process two type of queries
    0 x y w add new point (x, y, w) to the plane
    1 l d r u answer sum of all point weight such that l <= x < r and d <= y < u

    status: https://judge.yosupo.jp/problem/point_add_rectangle_sum
*/

#include<bits/stdc++.h>
using namespace std;

using ll = long long ;
struct segtree {

    int n;
    vector <ll> t;
    vector <int> all;

    void build () {
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        n = (int)all.size();
        t.resize(2 * n + 2, 0);
    }

    void reserve (int x) {
        all.push_back(x);
    }

    void add (int pos, int val) {
        int p = lower_bound(all.begin(), all.end(), pos) - all.begin();
        for ( p += n ; p > 0 ; p >>= 1) {
            t[p] += val;
        }
    }

    long long query (int l, int r) {
        /// This is query on [l, r)
        long long res = 0;
        l = lower_bound(all.begin(), all.end(), l) - all.begin();
        r = lower_bound(all.begin(), all.end(), r) - all.begin();
        for (l += n, r += n ; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l ++];
            if (r & 1) res += t[-- r];
        }
        return res;
    }
};

struct segtree2D {
    int n;
    vector <segtree> trees;

    segtree2D (int n) {
        this->n = n;
        trees.resize(2 * n + 5);
    }

    void reserve (int i, int j) {
        for (i += n ; i > 0; i >>= 1) {
            trees[i].reserve(j);
        }
    }

    void build () {
        for (segtree &tree : trees) {
            tree.build();
        }
    }

    void add (int i, int j, int val) {
       /// fprintf(stderr, "add %d %d %d\n", i, j, val);
        for (i += n ; i > 0 ; i >>= 1) {
            trees[i].add(j, val);
        }
    }

    ll  query (int l0, int r0, int l1, int r1) {
        ll res = 0;
        for (l0 += n, r0 += n ; l0 < r0 ; l0 >>= 1, r0 >>= 1) {
            if (l0 & 1) res += trees[l0 ++].query(l1, r1);
            if (r0 & 1) res += trees[-- r0].query(l1, r1);
        }

        return res;
    }
};

int const nax = 3e5 + 10;

struct point {
    int x, y, w;
    void read () {
        scanf("%d %d %d", &x, &y, &w);
    }
};
point p[nax];
int n, nq;

struct query {
    int type;
    point pts;
    int l, d, r, u;

    void read () {
        scanf("%d", &type);
        if (type == 0) {
            pts.read();
        } else if (type == 1) {
            scanf("%d %d %d %d", &l, &d, &r, &u);
        } else throw;
    }
};


query q[nax];

int main () {
    scanf("%d %d", &n, &nq);


    vector <int> com_x;
    for (int i = 1 ; i <= n ; ++ i) {
        p[i].read();
        com_x.push_back(p[i].x);
    }

    for (int i = 1 ; i <= nq ; ++ i) {
        q[i].read();
        if (q[i].type == 0) com_x.push_back(q[i].pts.x);
    }

    sort(com_x.begin(), com_x.end());
    com_x.erase(unique(com_x.begin(), com_x.end()), com_x.end());


    segtree2D seg((int)com_x.size());

    for (int i = 1 ; i <= n ; ++ i) {
        int x = lower_bound(com_x.begin(), com_x.end(), p[i].x) - com_x.begin();
        seg.reserve(x, p[i].y);
    }


    fprintf(stderr, "ALIVE\n");

    for (int i = 1 ; i <= nq ; ++ i) {
        if (q[i].type == 0) {
            int x = lower_bound(com_x.begin(), com_x.end(), q[i].pts.x) - com_x.begin();
            seg.reserve(x, q[i].pts.y);
        }
    }

    seg.build();

    for (int i = 1 ; i <= n ; ++ i) {
        auto [x, y, w] = p[i];
        x = lower_bound(com_x.begin(), com_x.end(), x) - com_x.begin();
        seg.add(x, y, w);
    }

    for (int i = 1 ; i <= nq ; ++ i) {
        int type = q[i].type;
        if (type == 0) {
            point pt = q[i].pts;
            int x = lower_bound(com_x.begin(), com_x.end(), pt.x) - com_x.begin();
            seg.add(x, pt.y, pt.w);
        } else if (type == 1) {
            int l = lower_bound(com_x.begin(), com_x.end(), q[i].l) - com_x.begin();
            int r = lower_bound(com_x.begin(), com_x.end(), q[i].r) - com_x.begin();
            printf("%lld\n", seg.query(l, r, q[i].d, q[i].u));
        } else throw;

    }
}
