#include "../../alg.hpp"

int mp[256];
char map_list[32];
vector<node> res[1024];

void init(){
	K = 1024;
	botsname = "bot-1";
	decode = vector<vector<node>>(K);
	rescount = vector<int>(K);
	return;
}

void renew(){
	#ifdef __unix__
		system("rm -fr ./bank/bot-1/*");
	#elif defined(__MACH__)
		system("rm -fr ./bank/bot-1/*");
	#else
		system("del /s /q .\\bank\\bot-1\\* > nul");
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
	file >> user_serial >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc;
	return;
}

void game::fill_factors(){
	factors.clear();
	maxn = rand() % 50 + 25;
	N = rand() % 20 + (maxn - 25);
	M = rand() % 24 + 16;
	same = rand() % 1024;
	addr1 = rand() % 2 + 1;
	addr = rand() % 2 + 1;
	bl = M / 5 + rand() % (M / 2);
	blsc = rand() % (M / 10) + bl;
	tb = (1LL << 60) + ((1LL * (rand() % 1024)) << 50) + ((1LL * (rand() % 1024)) << 40);
	tb += ((1LL * (rand() % 1024)) << 30) + ((1LL * (rand() % 1024)) << 20) + ((1LL * (rand() % 1024)) << 10) + (1LL * (rand() % 1024));
	user_serial = (1LL << 60) + ((1LL * (rand() % 1024)) << 50) + ((1LL * (rand() % 1024)) << 40);
	user_serial += ((1LL * (rand() % 1024)) << 30) + ((1LL * (rand() % 1024)) << 20) + ((1LL * (rand() % 1024)) << 10) + (1LL * (rand() % 1024));
	factors.push_back(user_serial);
	factors.push_back(tb);
	factors.push_back(N);
	factors.push_back(maxn);
	factors.push_back(M);
	factors.push_back(same);
	factors.push_back(addr);
	factors.push_back(addr1);
	factors.push_back(bl);
	factors.push_back(blsc);
	return;
}

int game::cmp(int i, int sen){
	auto a1 = a;
	auto exs1 = exs;
	auto blast1 = blast;
	int x = lst[i][0], y = lst[i][1];
	a[x][y] = canon, blast[x][y] = false, exs[x][y] = true;
	if(!check_good({x, y})){
		if(sen == 1){
			a = a1, exs = exs1, blast = blast1;
			return 1000000020;
		}
	}
	else{
		int tmp = pts;
		dfs_blast({x, y});
		pts = tmp;
		fall();
	}
	if(sen == 1){
		int cnt = 0;
		for(int i = 0; i < maxn; ++i)
			for(int j = (ini + i) % 2; j < M; j += 2)
				cnt += (int)exs[i][j];
		a = a1, exs = exs1, blast = blast1;
		return cnt;
	}
	else if(sen == 2){
		int ans = -1;
		for(int i = maxn - 1; ~i; --i)
			if(not_null(i)){
				ans = i;
				break;
			}
		a = a1, exs = exs1, blast = blast1;
		return (ans == maxn - 1 ? 1000000020 : ans);
	}
	return -1;
}

vector<int> game::bot(){
	if(810 <= code.size())
		return {};
	int mn1 = 1000000021, mn2 = 1000000021;
	int x = lst[0][0], y = lst[0][1];
	for(int i = 0; i < lst.size(); ++i){
		int balls = cmp(i, 1);
		int rws = cmp(i, 2);
		if(rws == 1000000020 && mn1 == 1000000020)
			continue;
		if(mn1 > balls)
			mn1 = balls, mn2 = rws, x = lst[i][0], y = lst[i][1];
		else if(mn1 == balls && mn2 > rws)
			mn1 = rws, x = lst[i][0], y = lst[i][1];
		else if(mn1 == balls && mn2 == rws)
			mn1 = rws, x = lst[i][0], y = lst[i][1];
	}
	return {x, y};
}

void game::upd_res(int pos){
	if(pos != 1)
		return;
	for(int i = 0; i < maxn; ++i)
		for(int j = 0; j < M; ++j)
			res += a[i][j];
	res %= 1024;
	return;
}

string game::map_it(){
	string mapped = "00";
	mapped[0] = map_list[res / 32];
	mapped[1] = map_list[res % 32];
	return mapped;
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
	int ln = (cnt * 5 + 9) / 10;
	for(int i = 0; i < ln; ++i){
		int num = 0;
		for(int j = i * 10; j < (i + 1) * 10; ++j)
			num = num * 2 + b_set[j];
		long long idx = _rand() + (_rand() << 10) + (_rand() << 20);
		idx %= res[num].size();
		for(int j = 0; j < 10; ++j)
			fres << res[num][idx].f[j] << " ";
		fres << '\n';
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
	game g;
	g.play("./messages/" + botsname + "/", cnt);
	return;
}