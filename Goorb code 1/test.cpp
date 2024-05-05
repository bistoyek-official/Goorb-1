#include<bits/stdc++.h>
using namespace std;

int main(){
    ifstream f1("inam shans ma1.txt");
    ifstream f2("inam shans ma2.txt");
    ofstream f3("compare1.txt");
    string l1, l2;
    while(getline(f1, l1)){
        getline(f2, l2);
        if(l1 == l2)
            f3 << l1 + " == " + l2 << '\n';
        else
            f3 << l1 + " != " + l2 << '\n';
    }
	return 0;
}
