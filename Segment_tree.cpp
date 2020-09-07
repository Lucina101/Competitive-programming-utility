struct segtree {
    static const int Mx = 4 * nax;

    int sg[Mx] = {}, tag[Mx] = {};
u

    inline void pull (int v) {
        sg[v] = max(sg[v * 2], sg[v * 2 + 1]);
    }

    inline void push (int v) {
        if (v * 2 + 1 < Mx && tag[v]) {
            sg[v * 2] +=  tag[v];
            sg[v * 2 + 1] += tag[v];
            tag[v * 2] +=  tag[v];
            tag[v * 2 + 1] += tag[v];
        }
        tag[v] = 0;
    }

    inline void update (int v, int x, int y, int l, int r , int val) {
        push(v);
        if (l > r) return ;

        if (l == x && r == y) {
            sg[v] += val; tag[v] += val;
            return push(v);
        }

        int mid = x + y >> 1;
        update(v * 2, x , mid, l, min(r, mid), val);
        update(v * 2 + 1, mid + 1, y, max(l, mid + 1), r, val);
        pull(v);
    }

    inline int query (int v, int x, int y, int l, int r) {
        push(v);
        if (l > r) return INT_MIN;

        if (l == x && r == y) {
            return sg[v];
        }

        int mid = x + y >> 1;

        return max(query(v << 1 , x , mid, l, min(r, mid)), query(v * 2 + 1, mid + 1, y, max(l, mid + 1), r));
    }

    void update (int l, int r, int val) {
        update(1, 1, m, l, r, val);
    }

};
