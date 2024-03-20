#include<bits/stdc++.h>
using namespace std;
#define task "fair"
#define start ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); if (fopen(task".INP", "r")){ freopen(task".INP", "r", stdin); freopen(task".OUT", "w", stdout); }
int a[105][105];
int d[105][105];
int const N = 1e9;
const int hx[4] = {-1, 0, 0, 1};
const int hy[4] = {0, -1, 1, 0};
pair<int, int > trace[105][105];
int n, m;
struct pii {
    int fi, se, rd;
};

pii ans;

bool aval(int x, int y) {
    if (x < 1 || y < 1 || x > m || y > n) {
        return false;
    }
    return true;
}

struct cmp {
    bool operator () (pii A, pii B){
        return A.fi > B.fi;
    }
};


void dijkstra() {
    priority_queue<pii, vector<pii> ,cmp> pq;
    for (int i = 1; i <= m; i ++) {
        for (int j = 1; j <= n; j ++) {
            d[i][j] = N;
        }
    }
    for (int i = 1; i <= m; i ++) {
        d[i][1] = a[i][1];
        pq.push({d[i][1], i, 1});
    }

    while(!pq.empty()) {
        int c = pq.top().fi;
        int u1 = pq.top().se;
        int u2 = pq.top().rd;
        //cout << u1 << " " << u2 << " " << c << '\n';
        pq.pop();
        if (c > d[u1][u2]) {
            continue;
        }
        for (int i = 0; i < 4; i ++) {
            if (!aval(u1 + hx[i], u2 + hy[i])) {
                continue;
            }
            if (d[u1 + hx[i]][u2 + hy[i]] > d[u1][u2] +  a[u1 + hx[i]][u2 + hy[i]]) {
                d[u1 + hx[i]][u2 + hy[i]] = d[u1][u2] +  a[u1 + hx[i]][u2 + hy[i]];
                trace[u1 + hx[i]][u2 + hy[i]].first = u1;
                trace[u1 + hx[i]][u2 + hy[i]].second = u2;
                pq.push({d[u1 + hx[i]][u2 + hy[i]], u1 + hx[i], u2 + hy[i]});
            }
        }
    }
    for (int i = 1; i <= m; i ++) {
        if (ans.fi > d[i][n]) {
            ans.fi = d[i][n];
            ans.se = i;
            ans.rd = n;
        }
    }
}
void fp(int u1, int u2) {
    vector<pair<int, int > > path;
    while(true) {
        path.push_back({u1, u2});
        if (u2 == 1) {
           break;
        }
        int u11 = u1;
        u1 = trace[u1][u2].first;
        u2 = trace[u11][u2].second;
    }
    for (int i = path.size() - 1; i > 0; i --) {
        cout << path[i].first << " " << path[i].second << '\n';
    }
}
int main() {
    start
    ans.fi = N;
    cin >> m >> n;
    for (int i = 1; i <= m; i ++) {
        for (int j = 1; j <= n; j ++) {
            cin >> a[i][j];
        }
    }
    dijkstra();
    cout << ans.fi << '\n';
    fp(ans.se, ans.rd);
    cout << ans.se << " " << ans.rd;
    return 0;
}
