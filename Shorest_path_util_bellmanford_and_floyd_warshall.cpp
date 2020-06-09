/// use 2d matrix represent distance between node
/// negative edge work fine too
void Floyd(){
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

struct edge{
    int a, b, cost;
};
int n, m, v;
vector<edge> e;
const int INF = 1000000000;
void solve(){
    vector<int> d (n, INF);
    d[v] = 0;
    for (int i=0; i<n-1; ++i)
    for (int j=0; j<m; ++j)
        if (d[e[j].a] < INF)
            d[e[j].b] = min (d[e[j].b], d[e[j].a] + e[j].cost);
// display d, for example, on the screen
}

int main () {

}
