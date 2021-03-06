#include <bits/stdc++.h>

using namespace std;

void debug_out() { cerr << endl; }
template <typename H, typename... T> void debug_out(H h, T... t) {  cerr << " " << (h);  debug_out(t...); }
void read() {}
template <typename H, typename... T> void read(H &h, T&... t) { cin >> h; read(t...) ;}
template <typename H, typename... T> void read(vector<H> &h, T&... t) { for (auto &i : h) read(i); read(t...) ;}

#ifndef LOCAL
#define endl '\n'
#define debug(...) //
#else
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#endif

typedef long double T;

const T pi = acos(-1);

struct cpx {
    T real, image;
    cpx(T _real, T _image) {
        real = _real;
        image = _image;
    }
    cpx() {}
};

cpx operator + (const cpx &c1, const cpx &c2) {
    return cpx(c1.real + c2.real, c1.image + c2.image);
}

cpx operator - (const cpx &c1, const cpx &c2) {
    return cpx(c1.real - c2.real, c1.image - c2.image);
}

cpx operator * (const cpx &c1, const cpx &c2) {
    return cpx(c1.real * c2.real - c1.image * c2.image , c1.real *c2.image + c1.image * c2.real);
}

int rev(int id, int len) {
    int ret = 0;
    for (int i = 0; (1 << i) < len; i++) {
        ret <<= 1;
        if (id & (1 << i)) ret |= 1;
    }
    return ret;
}

const int MAXLEN = 1 << 20;
cpx A[MAXLEN];

void fft(cpx *a, int len, int dir) {
    for (int i = 0; i < len; i++) {
        A[rev(i, len)] = a[i];
    }

    for (int s = 1; (1 << s) <= len; s++) {
        int m = (1 << s);

        cpx wm = cpx(cos(dir * 2 * pi / m), sin(dir * 2 * pi / m ));
        for (int k = 0; k < len; k += m) {
            cpx w = cpx(1, 0);
            for (int j = 0; j < (m >> 1); j++) {
                cpx t = w * A[k + j + (m >> 1)];
                cpx u = A[k + j];
                A[k + j] = u + t;
                A[k + j + (m >> 1)] = u - t;
                w = w * wm;
            }
        }
    }
    if (dir == -1) for (int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
    for (int i = 0; i < len; i++) a[i] = A[i];
}

cpx a[MAXLEN], b[MAXLEN];

void solve() {
    string line; cin >> line;

    for (int i = 0; i < line.size(); i++) {
        a[i] = cpx(line[i] - '0', 0);
        // b[line.size() - 1 - i] = cpx(line[i] - '0', 0);
        b[i] = cpx(line[i] - '0', 0);
    }

    fft(a, MAXLEN, 1);
    fft(b, MAXLEN, 1);

    for (int i = 0; i < MAXLEN; i++) {
        a[i] = a[i] * b[i];
    }

    fft(a, MAXLEN, -1);

    long long ans = 0;

    for (int i = 0; i < line.size(); i++) {
        debug(i, a[i].real);
        if (line[i] == '1') {
            ans += round(a[i + i].real) - 1;
        }
    }

    cout << (ans / 2) << endl;

}

int main() {
#ifndef LOCAL
  ios_base::sync_with_stdio(false); cin.tie(NULL);
#else
    freopen("b2.in", "r", stdin);
#endif
    solve();
  return 0;
}

