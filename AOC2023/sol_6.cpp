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

// -------------------MAIN CODE-------------------//
int main(){
	ifstream inputFile("./AOC2023/input_6.txt");
	//ifstream inputFile("./AOC2023/ex_6.txt");
    V<string> lines;
    for(string cur; getline(inputFile,cur);) lines.pb(cur);

    vi times, dist;
    stringstream ss(lines[0]);
    string cur;
    ss>>cur;
    while(ss>>cur) times.pb(stoi(cur));
    ss = stringstream(lines[1]);
    ss>>cur;
    while(ss>>cur) dist.pb(stoi(cur));
    
    int res1 = 1;
    rep(i,0,times.size()){
        int cnt = 0;
        rep(j,0,times[i]+1){
            if(j*(times[i]-j) > dist[i]) cnt++;
        }
        res1*= cnt;
    }
    cout<<"PART 1: "<<res1<<endl;

    string time, dis;
    ss = stringstream(lines[0]);
    ss>>cur;
    while(ss>>cur) time += cur;
    ss = stringstream(lines[1]);
    ss>>cur;
    while(ss>>cur) dis+=cur;

    ll t = stoll(time), d = stoll(dis);
    
    int res2 = 0;
    rep(j,0,t+1){
        if(j*(t-j) > d) res2++;
    }
    cout<<"PART 2: "<<res2<<endl;
}

