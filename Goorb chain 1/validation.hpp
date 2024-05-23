#include "basic.hpp"

struct game{

	int maxn, N, M, same, addr, addr1, bl, blsc;

	ifstream file;

	vector<vector<int>> a, lst, ok;
	vector<vector<bool>> exs, blast;
	time_t tb;
	long long tbr;
	bool enought = false;
	vector<string> code;

	int pts = 0, tries = 0, canon, ini;

	int dx[6] = {0, 0, 1, 1, -1, -1}, dy[6] = {2, -2, -1, 1, -1, 1};

	int _rand(){
		return abs(rand()) % 720;
	}

	int rnd(){
		int res = 0, k;
		if(_rand() % 8 == 0)
			res = (_rand() % 5 + 1) * 16;
		k = _rand() % 5 + 1;
		int cnt = 21;
		while(k == res / 16 && cnt--){
			k = _rand() % 5 + 1;
			if(!cnt)
				k = 0;
		}
		res += k;
		if(res / 16 > res % 16)
			return (res % 16) * 16 + res / 16;
		return res;
	}

	void add_row(){
		ini = (1 - ini);
		for(int i = maxn - 1; i; --i)
			for(int j = 0; j < M; ++j){
				swap(a[i][j], a[i - 1][j]);
				swap(exs[i][j], exs[i - 1][j]);
				swap(blast[i][j], blast[i - 1][j]);
			}
		for(int i = ini; i < M; i += 2){
			for(int k = 0; k < 21; ++k){
				a[0][i] = rnd();
				int tmp = pts, tmp1;
				dfs_blast({0, i});
				for(int ii = 0; ii < maxn; ++ii)
					for(int jj = (ii + ini) % 2; jj < M; jj += 2)
						if(blast[ii][jj])
							blast[ii][jj] = false, exs[ii][jj] = true;
				tmp1 = pts, pts = tmp;
				if(tmp1 - tmp <= bl)
					break;
				if(tmp1 - tmp > blsc && k == 20){
					a[0][i] = 8;
					break;
				}
				upd_rnd();
			}
			exs[0][i] = true;
			blast[0][i] = false;
		}
		return;
	}

	void gen(){
		cout << "\n~ enter file dir: ";
		string s;
		getline(cin, s);
		ini = pts = 0;
		tbr = time(nullptr);
		++tries;
		if(tries > 1)
			file.close();
		file.open(s);
		if(!file.is_open()){
			enought = true;
			return;
		}
		file >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc;
		srand(tb);
		a.clear(), exs.clear(), blast.clear(), lst.clear(), code.clear();
		code.push_back(to_string(tb));
		code.push_back(to_string(N)), code.push_back(to_string(maxn)), code.push_back(to_string(M));
		code.push_back(to_string(same)), code.push_back(to_string(addr)), code.push_back(to_string(addr1));
		code.push_back(to_string(bl)), code.push_back(to_string(blsc));
		for(int i = 0; i < maxn; ++i){
			a.push_back({}), exs.push_back({}), blast.push_back({});
			for(int j = 0; j < M; ++j)
				a[i].push_back(0), exs[i].push_back(0), blast[i].push_back(0);
		}
		for(int i = 0; i < N; ++i)
			add_row();
		for(int i = (N + ini) % 2; i < M; i += 2)
			lst.push_back({N, i});
		upd_sit(rnd());
		return;
	}

	void upd_sit(int color){
		for(int i = 0; i < maxn; ++i)
			for(int j = (i + ini) % 2; j < M; j += 2)
				if(!exs[i][j])
					blast[i][j] = a[i][j] = 0;
		canon = color;
		return;
	}

	bool not_null(int i){
		return *max_element(a[i].begin(), a[i].end());
	}

	bool check_end(){
		if(not_null(maxn - 1)){
			cout << "INVALID" << '\n';
			return true;
		}
		if(!not_null(0)){
			update();
			return true;
		}
		return false;
	}

	bool adj_blast(vector<int> c, vector<int> p){
		if(!(-1 < c[0] && c[0] < maxn) || !(-1 < c[1] && c[1] < M))
			return false;
		if(!exs[c[0]][c[1]])
			return false;
		if(a[p[0]][p[1]] % 16 == a[c[0]][c[1]] % 16)
			return true;
		if(a[p[0]][p[1]] / 16 == a[c[0]][c[1]] % 16)
			return true;
		if(a[p[0]][p[1]] % 16 == a[c[0]][c[1]] / 16)
			return true;
		if(a[p[0]][p[1]] / 16 == a[c[0]][c[1]] / 16 && a[c[0]][c[1]] > 16)
			return true;
		return false;
	}

	void dfs_blast(vector<int> c){
		++pts;
		blast[c[0]][c[1]] = true;
		exs[c[0]][c[1]] = false;
		for(int i = 0; i < 6; ++i)
			if(adj_blast({c[0] + dx[i], c[1] + dy[i]}, c) && exs[c[0] + dx[i]][c[1] + dy[i]])
				dfs_blast({c[0] + dx[i], c[1] + dy[i]});
		return;
	}

	bool adj_conct(vector<int> c){
		if(!(-1 < c[0] && c[0] < maxn) || !(-1 < c[1] && c[1] < M))
			return false;
		return !exs[c[0]][c[1]] && !blast[c[0]][c[1]] && a[c[0]][c[1]];
	}

	int dfs_conct(vector<int> c){
		int res = 1;
		exs[c[0]][c[1]] = true;
		for(int i = 0; i < 6; ++i)
			if(adj_conct({c[0] + dx[i], c[1] + dy[i]}))
				res += dfs_conct({c[0] + dx[i], c[1] + dy[i]});
		return res;
	}

	int check_good(vector<int> c, bool sen = true){
		int cnt = 0, mx = 0;
		for(int i = 0; i < 6; ++i)
			if(adj_blast({c[0] + dx[i], c[1] + dy[i]}, c)){
				if(sen)
					mx = max(mx, check_good({c[0] + dx[i], c[1] + dy[i]}, false));
				++cnt;
			}
		return (sen ? (int)(max(mx, cnt) > 1) : cnt);
	}

	void fall(){
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < M; ++j)
				exs[i][j] = false;
		for(int i = ini; i < M; i += 2)
			if(!blast[0][i] && a[0][i])
				dfs_conct({0, i});
		return;
	}

	void dfs_ok(vector<int> c){
		ok[c[0]][c[1]] = 1;
		int adj_cell = 0;
		for(int i = 0; i < 6; ++i){
			int x = c[0] + dx[i], y = c[1] + dy[i];
			if(0 <= x && 0 <= y && x < maxn && y < M && ok[x][y] != -1)
				++adj_cell;
		}
		if(c[0] == maxn - 1)
			adj_cell += 2;
		if(adj_cell <= 2)
			return;
		for(int i = 0; i < 6; ++i){
			int x = c[0] + dx[i], y = c[1] + dy[i];
			if(0 <= x && 0 <= y && x < maxn && y < M && !ok[x][y])
				dfs_ok(vector<int>{x, y});
		}
		return;
	}

	void updlst(){
		lst.clear();
		ok.clear();
		for(int i = 0; i < maxn; ++i){
			ok.push_back({});
			for(int j = 0; j < M; ++j)
				ok[i].push_back(exs[i][j] ? -1 : 0);
		}
		dfs_ok({maxn - 1, (maxn + ini - 1) % 2});
		for(int i = 0; i < maxn; ++i)
			for(int j = (ini + i) % 2; j < M; j += 2)
				if(!exs[i][j] && ok[i][j] == 1)
					for(int k = 0; k < 6; ++k)
						if(i + dx[k] < maxn && -1 < i + dx[k])
							if(j + dy[k] < M && -1 < j + dy[k])
								if(exs[i + dx[k]][j + dy[k]]){
									lst.push_back({i, j});
									break;
								}
		ok.clear();
		return;
	}

	void upd_rnd(){
		int num = 0, bs = 71, mod = 1000000021;
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < M; ++j)
				num = ((num * bs) % mod + a[i][j]) % mod;
		num %= 100;
		while(num-- >= 0)
			if(_rand() & 1)
				_rand();
		return;
	}

	bool search_it(vector<int> cor){
		for(auto &e: lst)
			if(cor[0] == e[0] && cor[1] == e[1])
				return true;
		return false;
	}

	void gameplay(){
		gen();
		if(enought)
			return;
		int mvs = 0, mvs1 = 0;
		while(true){
			if(check_end())
				break;
			updlst();
			int x, y;
			while(true){
				string s;
				file >> s;
				if(s.size() != 2){
					cout << "INVALID" << '\n';
					return;
				}
				x = s[0] - 'A', y = s[1] - 'A';
				if(search_it(vector<int>{x, y}))
					break;
				cout << "INVALID" << '\n';
				return;
			}
			string str = "00";
			str[0] = (char)(x + 'A');
			str[1] = (char)(y + 'A');
			code.push_back(str);
			a[x][y] = canon, blast[x][y] = false, exs[x][y] = true;
			if(!check_good({x, y})){
				++mvs1;
				upd_sit(rnd());
				if(check_end())
					return;
				if(mvs1 % addr1 == 0)
					add_row();
				if(check_end())
					return;
				continue;
			}
			++mvs;
			dfs_blast({x, y}), --pts;
			fall();
			upd_sit(canon);
			upd_rnd();
			if(mvs % addr == 0)
				add_row();
			canon = rnd();
		}
		return;
	}

	void play(){
		int times = 1021;
		while(--times && !enought)
			gameplay();
		return;
	}

	void update(){
		cout << "ACCEPTED!\n";
		return;
	}
};
