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
	my_file.open("./AOC2023/input_2.txt", ios::in);
    V<string> lines;
    string cur;
    while(getline(my_file,cur)){
        lines.pb(cur);
    }

    int sum = 0, sum2 = 0;
    for(string line : lines){
        stringstream ss(line);

        string cur, tmp;
        int id;
        ss>>cur>>id>>tmp;

        int blue, red, green;
        blue = red = green = 0;
        int blue2, red2, green2;
        blue2 = red2 = green2 = 0;
        bool valid = true;
        string a, b;
        while(ss>>a>>b){
            if(b.back() == ','){
                if(b[0]=='b'){
                    blue = stoi(a);
                } else if(b[0] == 'r'){
                    red = stoi(a);
                } else {
                    green = stoi(a);
                }
            } else {
                if(b[0]=='b'){
                    blue = stoi(a);
                } else if(b[0] == 'r'){
                    red = stoi(a);
                } else {
                    green = stoi(a);
                }
                if(red > 12 || green > 13 || blue > 14) valid = false;
                green2 = max(green2, green);
                blue2 = max(blue2, blue);
                red2 = max(red2, red);
                blue = red = green = 0;
            }
        }
        if(valid) sum+=id;
        sum2 += green2 * blue2 * red2;
    }
    cout<<"PART 1: "<<sum<<endl;
    cout<<"PART 2: "<<sum2<<endl;
}

