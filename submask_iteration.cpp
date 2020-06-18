#include<bits/stdc++.h>
using namespace std;

void iterate (int n) {
    for (int i = 0 ; i < (1 << n) ; ++ i) {
        for (int j = i ; j > 0 ; j = (j - 1) & i) {
            /// overall O(3^n)
        }
    }
}

int main () {

}
