#include "../../alg.hpp"

int mp[256];
char map_list[32];
vector<node> res[1024];

void init(){
	botsname = "bot-0";
	decode = vector<vector<node>>(1024);
	rescount = vector<int>(1024);
	return;
}

void renew(){
	#ifdef __unix__
		system("rm -fr ./bank/bot-0/*");
	#elifdef __mach__
		system("rm -fr ./bank/bot-0/*");
	#else
		system("del /s /q .\\bank\\bot-0\\* > nul");
	#endif
	return;
}

void gen_map_list(){
	map_list[0] = ' ';
	for(int i = 0; i < 26; ++i)
		map_list[i + 1] = 'a' + i;
	map_list[27] = '.', map_list[28] = '+', map_list[29] = '-';
	map_list[30] = '?', map_list[31] = '\n';
	return;
}

void game::set_factors(){
	file >> user_serial >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc >> rang;
	return;
}

void game::fill_factors(){
	maxn = 31;
	N = 5;
	M = 17;
	same = 512;
	addr1 = 1023;
	addr = 512;
	bl = 10;
	blsc = 14;
	tb = time(nullptr) + tries;
	user_serial = 21;
	rang = 5;
	factors.f[0] = user_serial;
	factors.f[1] = tb;
	factors.f[2] = N;
	factors.f[3] = maxn;
	factors.f[4] = M;
	factors.f[5] = same;
	factors.f[6] = addr;
	factors.f[7] = addr1;
	factors.f[8] = bl;
	factors.f[9] = blsc;
	factors.f[10] = rang;
	return;
}

vector<int> game::cmp(int i){
	return {};
}

vector<int> game::bot(){
	if(200 == mvs + mvs1)
		return {};
	return lst[0];
}

void game::upd_res(int pos){
	if(pos != 1)
		return;
	for(int i = 0; i < maxn; ++i)
		for(int j = 0; j < M; ++j)
			res += a[i][j], res %= 1024;
	return;
}

string game::map_it(){
	string mapped = "00";
	mapped[0] = map_list[res / 32];
	mapped[1] = map_list[res % 32];
	return mapped;
}

void note::note_it(ofstream &f, node &obj){
	for(int i = 0; i < 11; ++i)
		f << obj.f[i] << " ";
	f << '\n';
	return;
}

void _encode_(){
	ifstream f2("./messages/" + botsname + "/decoded.txt");
	ofstream fres("./messages/" + botsname + "/encoded.txt");
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
		ifstream fbank("./bank/" + botsname + "/" + to_string(i) + ".txt");
		bool b = true;
		while(b){
			res[i].push_back({});
			for(int j = 0; j < 11 && b; ++j){
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
	int ln = (cnt * 5 + 9) / 10;
	for(int i = 0; i < ln; ++i){
		int num = 0;
		for(int j = i * 10; j < (i + 1) * 10; ++j)
			num = num * 2 + b_set[j];
		long long idx = _rand() + (_rand() << 10) + (_rand() << 20);
		idx %= res[num].size();
		nt.note_it(fres, res[num][idx]);
	}
	return;
}

void _decode_(){
	int cnt = 0;
	ifstream f("./messages/" + botsname + "/encoded.txt");
	string s;
	while(getline(f, s))
		++cnt;
	f.close();
	gen_map_list();
	g.play("./messages/" + botsname + "/", cnt);
	return;
}
