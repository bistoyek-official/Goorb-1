#include "./Codes/random.hpp"
using namespace std;

int mp[256];

struct obj{
	public:
	long long f[10];
};

vector<obj> res[1024];

int main(){
	ifstream f2("./mail.txt");
	ofstream fres("./result.txt");
	_srand(time(0) / 2, time(0));
	mp[(int)' '] = 0;
	for(int i = 0; i < 26; ++i)
		mp[(int)'a' + i] = i + 1;
	mp[(int)'.'] = 27;
	mp[(int)'+'] = 28;
	mp[(int)'-'] = 29;
	mp[(int)'?'] = 30;
	mp[(int)'\n'] = 31;
	for(int i = 0; i < 1024; ++i){
		ifstream fbank("./Codes/bank/" + to_string(i) + ".txt");
		bool b = true;
		while(b){
			res[i].push_back({});
			for(int j = 0; j < 10 && b; ++j){
				if(fbank >> res[i].back().f[j])
					int x;
				else{
					res[i].pop_back();
					b = false;
				}
			}
		}
		fbank.close();
	}
	bitset<1024 * 8 * 100> b_set;
	int cnt = 0;
	string s;
	while(getline(f2, s)){
		s += '\n';
		for(int i = 0; i < s.size(); ++i)
			for(int j = 0; j < 5; ++j){
				b_set[(cnt + i) * 5 + j] = (bool)((mp[s[i]] & (1 << (4 - j))) != 0);
			}
		cnt += s.size();
	}
	for(int i = 0; i < s.size(); ++i)
		for(int j = 0; j < 5; ++j)
			b_set[(cnt + i) * 5 + j] = (bool)((mp[s[i]] & (1 << (4 - j))) != 0);
	cnt += s.size();
	int ln = (cnt * 5 + 9) / 10;
	for(int i = 0; i < ln; ++i){
		int num = 0;
		for(int j = i * 10; j < (i + 1) * 10; ++j)
			num = num * 2 + b_set[j];
		long long idx = _rand() + (_rand() << 10) + (_rand() << 20);
		idx %= res[num].size();
		for(int j = 0; j < 10; ++j)
			for(int k = 0; k < 64; k += 8)
				fres << (char)((res[num][idx].f[j] >> k) % 256);
	}
	return 0;
}