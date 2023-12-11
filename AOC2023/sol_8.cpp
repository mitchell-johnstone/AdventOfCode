#include <bits/stdc++.h>
using namespace std;

// var types
typedef long long ll;
typedef long double ld;
#define nn '\n'
#define pb push_back
#define mp make_pair

// collection shorthand
#define V vector
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i, a, b) for(int i = a; i < (b); ++i)

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}
ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}
// -------------------MAIN CODE-------------------//
int main(){
	ifstream inputFile("./AOC2023/input_8.txt");
	//ifstream inputFile("./AOC2023/ex_8.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    map<string,pair<string,string>> m;
    map<string,int> ind;
    rep(i,2,lines.size()){
        stringstream ss(lines[i]);
        string from, l, r, equal;
        ss>>from>>equal>>l>>r;
        m[from] = {l.substr(1,3),r.substr(0,3)};
        ind[from] = i-2;
    }

    ll steps = 0;
    for(string cur = "AAA"; cur != "ZZZ"; steps++){
        if(lines[0][steps % lines[0].size()] == 'L') cur = m[cur].first;
        else cur = m[cur].second;
    }
    cout<<"PART 1: "<<steps<<endl;

    V<string> cur;
    for(auto p : m) if(p.first.back() == 'A') cur.pb(p.first);
    //cout<<cur.size()<<endl;
//    steps = 0;
//    auto check = [=](V<string>& s){for(string c : s) if(c.back() != 'Z') return false; return true;};
//    while(!check(cur)){
//        bool left = lines[0][steps % lines[0].size()] == 'L';
//        for(string& s : cur) s = left ? m[s].first : m[s].second;
//        steps++;
//    }
//    cout<<"PART 2: "<<steps<<endl;
    ll mod = lines[0].size();
//    for(string s : cur){
//        map<string, ll> first;
//        steps = 0;
//        cout<<s<<" ";
//        while(s.back() != 'Z'){
//        //while(s.back() != 'Z' || first.find(s) == first.end() || steps % mod != first[s] % mod){
//            if(lines[0][steps % mod] == 'L') s = m[s].first;
//            else s = m[s].second;
//            if(first.find(s) == first.end()) first[s] = steps;
//            steps++;
//        }
//        cout<<steps<<endl;
//    }
    ll seen[mod][lines.size()-2];
    //ll c, M = 0;
    ll res = 0;
    for(string s : cur){
        rep(i,0,mod)
            rep(j,0,lines.size()-2)
                seen[i][j] = 0;
        steps = 0;
        //cout<<s<<" ";
        while(!seen[steps % mod][ind[s]] || s.back() != 'Z'){
            seen[steps%mod][ind[s]] = steps;
            if(lines[0][steps % mod] == 'L') s = m[s].first;
            else s = m[s].second;
            steps++;
        }
        //cout<<s<<": ";
        cout<<seen[steps%mod][ind[s]]<<"-"<<steps<<endl;
        if(res == 0) res = seen[steps%mod][ind[s]];
        else {
            ll next = seen[steps%mod][ind[s]];
            ll g = gcd(res, next);
            res *= next / g;
        }
//        ll a = seen[steps%mod][ind[s]];
//        ll m = steps - a;
//        if(M == 0) c = a, M = m;
//        else {
//            c = crt(a,m,c,M);
//            M *= m;
//        }
//        cout<<c<<" % "<<M<<endl;
    } 
    cout<<res<<endl;
}

