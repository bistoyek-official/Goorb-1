#include "basic.hpp"

struct node{
	long long f[10];
};

vector<node> decode[(1 << 10)];

void appit(vector<long long> v, int res){
	node obj;
	for(int i = 0; i < 10; ++i)
		obj.f[i] = v[i];
	decode[res].push_back(obj);
	if(decode[res].size() == 1){
		ofstream f("./bank/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i){
			for(int j = 0; j < 10; ++j)
				f << decode[res][i].f[j] << " ";
			f << '\n';
		}
		f.close();
		decode[res].clear();
	}
}

void saveit(){
	for(int res = 0; res < 1024; ++res){
		ofstream f("./bank/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i){
			for(int j = 0; j < 10; ++j)
				f << decode[res][i].f[j] << " ";
			f << '\n';
		}
		f.close();
		decode[res].clear();
	}
}