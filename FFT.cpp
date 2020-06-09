#include<bits/stdc++.h>
using namespace std;

using cd = complex<double> ;


namespace FFT {

    static const int MX = 1 << 19;
    static const double PI = 4.0 * atan(1);
    int rev_bit[MX];

    void pre_rev_bit (int n) {
        int lg = 0;
        while ((1 << (lg + 1)) < n) ++ lg;

        for (int i = 1 ; i < n ; ++ i) {
            rev_bit[i] = (rev_bit[i >> 1] >> 1) | ((i & 1) << lg);
    }
}


    void fft (cd * a, int n, bool invert) {

        pre_rev_bit(n);

        for (int i = 0 ; i < n; ++ i) {
            int to = rev_bit[i];
            if (i < to) {
                swap(a[i], a[to]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (int i = 0 ; i < n ; ++ i)
                a[i] /= n;
        }
    }

    void multiply (cd * a, int n, cd * b, int m, cd * out) {

        int f = 1;

        while (f < n + m) f <<= 1;

        fft(a, f, false);
        fft(b, f, false);

        for (int i = 0 ; i < f ; ++ i)
            out[i] = a[i] * b[i];

        fft(out, f, false);

        for (int i = 0 ; i < f ; ++ i) {
            out[i] = round(out[i].real());
        }
    }

}



int main () {

}
