#include "random.hpp"
using namespace std;

int mp[256];
bitset<1000000> b_set;

struct obj{
	public:
	long long f[10];
};

vector<obj> res[1024];

int main(){
	ifstream f1("map1.txt");
	for(int i = 0; i < 62; ++i){
		char c;
		f1 >> c;
		mp[c] = i;
	}
	f1.close();
	mp[(int)' '] = 62;
	mp[(int)'\n'] = 63;
	for(int i = 0; i < 1024; ++i){
		ifstream f4("./bank/" + to_string(i) + ".txt");
		bool b = true;
		while(b){
			res[i].push_back({});
			for(int j = 0; j < 10 && b; ++j)
				if(f4 >> res[i].back().f[j])
					int x;
				else
					b = false;
			if(!b)
				res[i].pop_back();
		}
		f4.close();
	}
	_srand(0, 0);
	int cnt = 0;
	ifstream f2("name.txt");
	string s;
	while(getline(f2, s)){
		s += '\n';
		for(int i = 0; i < s.size(); ++i)
			for(int j = 0; j < 6; ++j){
				b_set[(cnt + i) * 6 + j] = (bool)((mp[s[i]] & (1 << (5 - j))) != 0);
			}
		cnt += s.size();
	}
	f2.close();
	s = "||";
	for(int i = 0; i < s.size(); ++i)
		for(int j = 0; j < 6; ++j){
			b_set[(cnt + i) * 6 + j] = (bool)((mp[s[i]] & (1 << (5 - j))) != 0);
		}
	cnt += s.size();
	int ln = (cnt * 6 + 9) / 10;
	for(int i = 0; i < ln; ++i){
		int num = 0;
		for(int j = i * 10; j < i * 10 + 10; ++j)
			num = num * 2 + b_set[j];
		long long idx = _rand() + (_rand() << 10) + (_rand() << 20);
		idx %= res[num].size();
		for(int j = 0; j < 10; ++j)
			cout << res[num][idx].f[j] << " ";
		cout << '\n';
	}
}