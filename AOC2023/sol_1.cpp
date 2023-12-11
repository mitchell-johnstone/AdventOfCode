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
    fstream my_file;
	my_file.open("./AOC2023/input_1.txt", ios::in);
    V<string> lines;
    string cur;
    while(my_file>>cur){
        lines.pb(cur);
    }

    int sum = 0;
    for(string l : lines){
        int first = -1, last;
        for(char c : l){
            if (c >='0' && c<='9'){
                if(first == -1){
                    first = c-'0';
                }
                last = c-'0';
            }
        }
        sum+=first*10+last;
    }
    cout<<"PART1: "<<sum<<endl;

    sum = 0;
    //regex r("one|two|three|four|five|six|seven|eight|nine|[1-9]");
    for(string l : lines){
        int first = -1, last = -1;
        for(int i = 0; i < l.size(); i++){
            int val = -1;
            if(l.substr(i,3) == "one"){
                val = 1;
            } else if(l.substr(i,3) == "two"){
                val = 2;
            } else if(l.substr(i,5) == "three"){
                val = 3;
            } else if(l.substr(i,4) == "four"){
                val = 4;
            } else if(l.substr(i,4) == "five"){
                val = 5;
            } else if(l.substr(i,3) == "six"){
                val = 6;
            } else if(l.substr(i,5) == "seven"){
                val = 7;
            } else if(l.substr(i,5) == "eight"){
                val = 8;
            } else if(l.substr(i,4) == "nine"){
                val = 9;
            } else if(l.substr(i,1) != ""){
                if(l.substr(i,1)[0] >= '0' && l.substr(i,1)[0] <= '9')
                    val = l.substr(i,1)[0]-'0';
            }

            if(val != -1){
                if(first == -1){
                    first = val;
                }
                last = val;
            }
        }
        sum+=first*10+last;
    }
    cout<<"PART2: "<<sum<<endl;
}

