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
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i, a, b) for(int i = a; i < (b); ++i)

// fast io
void fast_io(){cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
int hsh(string s, int idx = 0, int h = 0){
    return idx == s.size() ? h : hsh(s,idx+1,((h+s[idx])*17)%256);
}
int main(){
	ifstream inputFile("./AOC2023/input_15.txt");
	//ifstream inputFile("./AOC2023/ex_15.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur,',');) lines.pb(cur);
    lines.back().pop_back();

    int res = 0;
    for(string cur : lines) res += hsh(cur);
    cout<<"PART 1: "<<res<<endl;

    res = 0;
    V<string> labels;
    map<string,int> m;
    for(string cur : lines) {
        if(cur.back() == '-'){
            cur.pop_back();
            if(auto f = find(all(labels),cur); f != labels.end())
                labels.erase(f);
        } else {
            int lens = cur.back()-'0';
            cur.pop_back();
            cur.pop_back();
            m[cur] = lens;
            if(find(all(labels),cur) == labels.end())
                labels.pb(cur);
        }
    }
    vi cnt(256);
    for(string l : labels){
        int box = hsh(l) + 1;
        int lens = m[l];
        int layer = ++cnt[box];
        res += box * lens * layer;
    }
    cout<<"PART 2: "<<res<<endl;
}

