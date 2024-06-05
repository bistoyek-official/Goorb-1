#include "random.hpp"

int constexpr buff = 1, KB = 100, per = 100;

struct node{
	long long f[11];
};

struct note{
	void note_it(ofstream &f, node &obj);
} nt;

vector<vector<node>> decode;
vector<int> rescount;

long long calls = 0, quality = 0;

void flush_it();
void bank_info();

bool add_it(vector<long long> v, int res){
	++rescount[res];
	node obj;
	for(int i = 0; i < 10; ++i)
		obj.f[i] = v[i];
	decode[res].push_back(obj);
	if(sizeof(decode) >= 1024.0 * KB)
		flush_it();
	else if(decode[res].size() == buff){
		ofstream f("./bank/" + botsname + "/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i)
			nt.note_it(f, decode[res][i]);
		f.close();
		decode[res].clear();
	}
	if(!((++calls) % per))
		bank_info();
	return *min_element(rescount.begin(), rescount.end());
}

void flush_it(){
	for(int res = 0; res < decode.size(); ++res){
		ofstream f("./bank/" + botsname + "/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i)
			nt.note_it(f, decode[res][i]);
		f.close();
		rescount[res] += decode[res].size();
		decode[res].clear();
	}
	bank_info();
	return;
}

void bank_info(){
	cout << "____________________________________________\n";
	botsname[0] = 'B';
	cout << "~ " << botsname + "'s bank log:" << '\n';
	botsname[0] = 'b';
	time_t t = time(nullptr);
	cout << ctime(&t) << '\n';
	int cnt[1024] = {}, sum = 0, len = 1;
	for(int i = 0; i < decode.size(); ++i){
		ifstream f1("./bank/" + botsname + "/" + to_string(i) + ".txt");
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
	cout << "Game's quality: " << quality / (calls * 1.0) << "\n---------\n";
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