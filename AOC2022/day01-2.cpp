#include <bits/stdc++.h>

// var types
#define ll long long
#define ld long double
#define nn '\n'
#define pb push_back
#define mp make_pair

// collection shorthand
#define V vector
#define vi V<int>
#define vii V<vi>
#define vll V<ll> 
#define vd V<double>
#define pii pair<int, int>
#define pll pair<ll,ll>
#define vpii V<pii>
#define vpll V<pll>

// funcs 
#define inRange(x,y,l,w) (x >= 0 && x < l && y >= 0 && y < w)
#define minimum(a) *min_element(a.begin(), a.end())
#define maximum(a) *max_element(a.begin(), a.end())
#define in_map(m,e) (m.find(e) != m.end())
#define findchar(s,c) ((s.find(c)==string::npos)?(-1):(s.find(c)))
#define repi(a) for(int i = 0; i < a; i++)
#define repj(a) for(int j = 0; j < a; j++)
#define repk(a) for(int k = 0; k < a; k++)
#define peri(a) for(int i = a; i >= 0; i--)
#define perj(a) for(int j = a; j >= 0; j--)
#define perk(a) for(int k = a; k >= 0; k--)

using namespace std;

// fast io
void fast_io(){ios_base::sync_with_stdio(false);cin.tie(NULL);}

// constants
const double PI = 3.1415926585323;
const int MOD = 1e9 + 7;

// -------------------MAIN CODE-------------------//
int main(){
    ifstream file("day01-1-input.txt");
    string line;
    int res[3] = {0,0,0};
    int cur = 0;
    while(getline(file,line)){
        if(line == ""){
            cout<<cur<<" "<<res[0]<<" "<<res[1]<<" "<<res[2]<<nn;
            if(cur > res[2]){
                res[2] = cur;
            }
            if(res[2] > res[1]){
                res[2] ^= res[1];
                res[1] ^= res[2];
                res[2] ^= res[1];
            }
            if(res[1] > res[0]){
                res[1] ^= res[0];
                res[0] ^= res[1];
                res[1] ^= res[0];
            }
            cur = 0;
        } else {
            stringstream s;
            s<<line;
            int tmp;
            s>>tmp;
            cur += tmp;
        }
    }
    if(cur > res[2]){
        res[2] = cur;
    }
    if(res[2] > res[1]){
        res[2] ^= res[1];
        res[1] ^= res[2];
        res[2] ^= res[1];
    }
    if(res[1] > res[0]){
        res[1] ^= res[0];
        res[0] ^= res[1];
        res[1] ^= res[0];
    }
    cout<<res[0]+res[1]+res[2]<<nn;
    return 0;
    return 0;
}

