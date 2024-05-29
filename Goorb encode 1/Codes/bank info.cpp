#include "basic.hpp"
using namespace std;

int main(){
	int len = 1;
	while(true){
		cout << "____________________________________________\n";
		cout << "Press a key to see info" << '\n';
		time_t t = time(0);
		while(time(0) - t < 5 * 60)
			if(kbhit()){
				char c = getch();
				break;
			}
		cout << "____________________________________________\n";
		cout << date() << '\n';
		int cnt[1024] = {}, sum = 0;
		for(int i = 0; i < 1024; ++i){
			ifstream f1("./bank/" + to_string(i) + ".txt");
			int cnt1 = 0;
			string s;
			if(!f1.is_open())
				++cnt[0];
			else{
				while(getline(f1, s))
					++cnt1, ++sum;
				++cnt[cnt1];
			}
			len = max(len, cnt1 + 1);
			f1.close();
		}
		cout << "All codes: " << sum << "\n---------\n";
		for(int i = 0; i < len; ++i){
			cout << cnt[i];
			for(int j = 0; j < 5 - to_string(cnt[i]).size(); ++j)
				cout << " ";
			cout << "|";
		}
		cout << '\n';
		for(int i = 0; i < len; ++i){
			cout << i;
			for(int j = 0; j < 5 - to_string(i).size(); ++j)
				cout << " ";
			cout << "|";
		}
		cout << '\n';
	}
}