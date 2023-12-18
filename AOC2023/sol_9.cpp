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
long long hist_next(vi hist){
    bool valid = true;
    for(int i : hist) valid &= !i;
    if(valid) return 0;
    vi next;
    rep(i,1,hist.size()) next.pb(hist[i]-hist[i-1]);
    return hist.back() + hist_next(next);
}
//long long hist_prev(vi hist){
//    bool valid = true;
//    for(int i : hist) valid &= !i;
//    if(valid) return 0;
//    vi next;
//    rep(i,1,hist.size()) next.pb(hist[i]-hist[i-1]);
//    return hist[0] - hist_prev(next);
//}
ll hist_prev(vi hist, int idx = 0){
    if(all_of(hist.begin(), hist.end(), [=](int i){return i==0;})) return 0;
    vi next;
    adjacent_difference(hist.begin(), hist.end(), back_inserter(next));
    next.erase(next.begin());
    return hist[0] - hist_prev(next);
}
int main(){
	ifstream inputFile("./AOC2023/input_9.txt");
	//ifstream inputFile("./AOC2023/ex_9.txt");
    V<vi> hist(1);
    int OASIS;
    for(string cur; getline(inputFile,cur); hist.pb(vi())) 
        for(stringstream ss(cur); ss>>OASIS;)
            hist.back().pb(OASIS); 
    hist.pop_back();

    int pred = 0;
    for(vi v : hist) pred += hist_next(v);
    cout<<"PART 1: "<<pred<<endl;

    //int prev = 0;
    //for(vi v : hist) prev += hist_prev(v);
    //cout<<"PART 2: "<<prev<<endl;
    cout<<"PART 2: "<<accumulate(hist.begin(), hist.end(), 0, [=](int a, vi v){return a + hist_prev(v);})<<endl;
}
