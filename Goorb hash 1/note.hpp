#include "random.hpp"

int constexpr buff = 10, KB = 2, per = 100;

vector<int> rescount;

struct node{
	long long f[11];
};

struct note{
	void note_it(ofstream &f, node &obj);
} nt;

vector<vector<node>> bank;

long long calls = 0, quality = 0;

void flush_it();
void bank_info();

bool add_it(node &obj, int res, int sd){
	++rescount[sd * 32 + res];
	bank[sd * 32 + res].push_back(obj);
	if(sizeof(bank) >= 1024.0 * KB)
		flush_it();
	else if(bank[sd * 32 + res].size() == buff){
		ofstream f("./bank/" + botsname + "/" + to_string(sd * 32 + res) + ".txt", ios::app);
		for(int i = 0; i < bank[sd * 32 + res].size(); ++i)
			nt.note_it(f, bank[sd * 32 + res][i]);
		f.close();
		bank[sd * 32 + res].clear();
	}
	if(!((++calls) % per))
		flush_it();
	return *min_element(rescount.begin(), rescount.end());
}

void flush_it(){
	for(int res = 0; res < bank.size(); ++res)
		if(bank[res].size()){
			ofstream f("./bank/" + botsname + "/" + to_string(res) + ".txt", ios::app);
			for(int i = 0; i < bank[res].size(); ++i)
				nt.note_it(f, bank[res][i]);
			f.close();
			rescount[res] += bank[res].size();
			bank[res].clear();
		}
	bank_info();
	return;
}

void bank_info(){
	cout << "____________________________________________\n";
	cout << "~ " << botsname + "'s bank log:" << '\n';
	time_t t = time(nullptr);
	cout << ctime(&t) << '\n';
	int cnt[1024] = {}, sum = 0, len = 1;
	for(int i = 0; i < bank.size(); ++i){
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