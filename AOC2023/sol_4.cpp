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
int num_matches(string line){
    stringstream ss(line);
    string cur;
    ss>>cur>>cur>>cur;
    unordered_set<int> s;
    while(cur != "|") s.insert(stoi(cur)), ss>>cur;
    int matches = 0;
    while(ss>>cur) matches += s.find(stoi(cur)) != s.end(); // true = 1
    return matches;
}
int main(){
	ifstream inputFile("AOC2023/input_4.txt");
	//ifstream inputFile("AOC2023/ex_4.txt");
    vi matches;
    for(string cur; getline(inputFile,cur);) matches.pb(num_matches(cur));

    int sum1 = 0;
    for(int score : matches) sum1 += 1<<score>>1;
    cout<<"PART 1: "<<sum1<<endl;

    int sum2 = 0;
    vi cps(matches.size(), 1);
    rep(i,0,matches.size()){
        sum2 += cps[i];
        rep(j,i,i+matches[i]) cps[j+1] += cps[i];
    }
    cout<<"PART 2: "<<sum2<<endl;
}

