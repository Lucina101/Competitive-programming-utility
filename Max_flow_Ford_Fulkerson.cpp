#include<bits/stdc++.h>
using namespace std;

template <typename T = int>
struct ford_fulkerson {
    /**
    actually edmond karp
    O(VE^2) when the size of flow is small it's O(EF) where F is maximum flow
    Verification:
        Jakarta regional 2019 problem L: Road construction
        Hiphop vs techno Hackerank
    */

    struct Edge {
        int from, to;
        T cap;

        Edge () {}
        Edge (int from, int to, T cap) : from(from) , to(to), cap(cap) {}
    };

    int n; /// number of nodes
    int m = 0; /// number of edges
    /// lesson UB can always happen don't think UB member in class will automatically initialized
    /// well, I faced this bug more than 1000 times, but never learn
    vector <Edge> flow_edge;
    vector <int> parent;
    vector <vector <int> > g;


    ford_fulkerson (int n) {
        this->n = n;
        g.resize(n + 3, vector<int>());
        parent.resize(n + 3);
    }

    void add_edge (int from, int to, T cap) {
        flow_edge.emplace_back(from, to, cap);
        flow_edge.emplace_back(to, from, 0);
        g[from].push_back(m);
        g[to].push_back(m + 1);
        m += 2;
    }

    T bfs (int source, int sink) {
        /// make_sure source differ from sink
        /// number to be modified
        queue <pair <int, T>> q;
        q.emplace(source, numeric_limits<T>::max() / 4);


        for (; !q.empty() ;) {
            int cur_node = q.front().first;
            int cur_flow = q.front().second;
            q.pop();


            for (int edge_id : g[cur_node]) {

                auto [from, to, cap] = flow_edge[edge_id];

                if (cap > 0 && parent[to] == -1) {
                    int new_flow = min(cur_flow, cap);
                    parent[to] = edge_id;
                    q.emplace(to, new_flow);
                    if (to == sink) {
                        return new_flow;
                    }
                }
            }
        }

        return 0;
    }

    T max_flow (int source, int sink) {
        T flow = 0;

        int new_flow = 0;
        while (true) {
            fill(parent.begin(), parent.end(), -1);
            new_flow = bfs(source, sink);
            if (new_flow == 0) break;
            flow += new_flow;
            int cur = sink;
            while (true) {
                int id_to_parent = parent[cur];

                flow_edge[id_to_parent].cap -= new_flow;
                flow_edge[id_to_parent ^ 1].cap += new_flow;
                cur = flow_edge[id_to_parent].from;
                if (cur == source) break;
            }
        }

        return flow;
    }
};



int main () {

}
