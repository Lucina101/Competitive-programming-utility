#include<cstdio>

int max (int a, int b);

const int L = 17, nax = 1e5 + 10, inf = 1e9;

int lg[nax];
int b[nax], a[100][100];
int n, m;

struct sparse_table {
    int sp[L][nax];

    sparse_table () {
        for (int i = 2 ; i < nax ; ++ i)
            lg[i] = lg[i >> 1] + 1;
    }

    void build () {
        for (int i = 1 ; i <= n ; ++ i)
            sp[0][i] = ::b[i];

        for (int i = 1 ; i < L ; ++ i)
        for (int j = 1 ; j + (1 << i) <= n + 1; ++ j)
            sp[i][j] = max(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
    }

    int get_max (int l, int r) {
        int d = lg[r - l + 1];
        return max(sp[d][l], sp[d][r - (1 << d) + 1]);

    }
};



struct sparse_table_2d {
    int sp[L][L][nax][nax];

    sparse_table_2d () {
        for (int i = 2 ; i < nax ; ++ i)
            lg[i] = lg[i >> 1] + 1;
    }

    void build () {

        for (int i = 1 ; i <= n ; ++ i)
        for (int j = 1 ; j <= m ; ++ j) {
            sp[0][0][i][j] = ::a[i][j];
        }

        for (int x = 1 ; x < L ; ++ x) {
            for (int i = 1 ; i + (1 << x) <= n + 1 ; ++ i)
            for (int j = 1 ; j <= m ; ++ j) {
                sp[x][0][i][j] = max(sp[x - 1][0][i][j], sp[x - 1][0][i + (1 << (x - 1))][j]);
            }
        }

        for (int x = 0 ; x < L ; ++ x)
        for (int y = 1 ; y < L ; ++ y) {
            for (int i = 1 ; i + (1 << x) <= n + 1; ++ i)
            for (int j = 1 ; j + (1 << y) <= m + 1; ++ j) {
                sp[x][y][i][j] = max(sp[x][y - 1][i][j], sp[x][y - 1][i][j + (1 << (y - 1))]);
            }
        }

    }

    int get_max (int x1, int y1, int x2, int y2) {
        if (x1 > x2 || y1 > y2) return -inf;
       // if (!in_x_range(x1) || !in_x_range(x2)) return - inf;
       // if (!in_y_range(y1) || !in_y_range(y2)) return - inf;

        int a = lg[x2 - x1 + 1];
        int b = lg[y2 - y1 + 1];

        int m1 = max(sp[a][b][x1][y1], sp[a][b][x1][y2 - (1 << b) + 1]);
        int m2 = max(sp[a][b][x2 - (1 << a) + 1][y1], sp[a][b][x2 - (1 << a) + 1][y2 - (1 << b) + 1]);

        return max(m1, m2);

    }
};

int main () {

}
