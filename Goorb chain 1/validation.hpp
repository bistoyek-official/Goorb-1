#include "random.hpp"

struct game{

	int maxn, N, M, same, addr, addr1, bl, blsc, rang;

	ifstream file;

	vector<vector<int>> a, lst, ok;
	vector<vector<bool>> exs, blast;
	long long tbr, tb;
	bool enought = false;

	int pts = 0, tries = 0, sum, moves, canon, ini;

	int dx[6] = {0, 0, 1, 1, -1, -1}, dy[6] = {2, -2, -1, 1, -1, 1};

	int rnd(){
		int res = 0, k;
		if(_rand() % 8 == 0)
			res = (_rand() % rang + 1) * (rang + 2);
		k = _rand() % rang + 1;
		int cnt = 4;
		while(k == res / (rang + 2) && cnt--){
			k = _rand() % rang + 1;
			if(!cnt)
				k = 0;
		}
		res += k;
		if(res / (rang + 2) > res % (rang + 2))
			return (res % (rang + 2)) * (rang + 2) + res / (rang + 2);
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
			for(int k = 0; k < 3; ++k){
				if(!k && i != ini && _rand() % same == 0)
					a[0][i] = a[0][i - 2];
				else
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
				if(tmp1 - tmp > blsc && k == 2){
					a[0][i] = rang + 1;
					break;
				}
				upd_rnd();
			}
			exs[0][i] = true;
		}
		return;
	}

	void gen(){
		cout << "\n~ enter file dir: ";
		string s;
		getline(cin, s);
		sum = 0;
		ini = pts = 0;
		tbr = time(nullptr);
		++tries;
		long long user_serial = 0;
		if(tries > 1)
			file.close();
		file.open(s);
		if(!file.is_open()){
			enought = true;
			return;
		}
		file >> user_serial >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc >> rang;
		_srand(tb, user_serial);
		a.clear(), exs.clear(), blast.clear(), lst.clear();
		for(int i = 0; i < maxn; ++i){
			a.push_back({}), exs.push_back({}), blast.push_back({});
			for(int j = 0; j < M; ++j)
				a[i].push_back(0), exs[i].push_back(0), blast[i].push_back(0);
		}
		for(int i = 0; i < N; ++i)
			add_row();
		canon = rnd();
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
			string s = "";
			file >> s;
			if(!s.empty()){
				cout << "INVALID" << '\n';
				return true;
			}
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
		if(a[p[0]][p[1]] % (rang + 2) == a[c[0]][c[1]] % (rang + 2))
			return true;
		if(a[p[0]][p[1]] / (rang + 2) == a[c[0]][c[1]] % (rang + 2))
			return true;
		if(a[p[0]][p[1]] % (rang + 2)  == a[c[0]][c[1]] / (rang + 2))
			return true;
		if(a[p[0]][p[1]] / (rang + 2) == a[c[0]][c[1]] / (rang + 2) && a[c[0]][c[1]] > (rang + 2))
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
		sum += lst.size();
		return;
	}

	void upd_rnd(){
		int num = 0, bs = 71, mod = 1000000021;
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < M; ++j)
				num = ((num * bs) % mod + a[i][j]) % mod;
		num %= 21;
		while(num-- >= 0)
			if(_rand() & 1)
				_rand();
		return;
	}
	
	int search_it(vector<int> c){
		int l = 0, r = lst.size();
		while(r - l > 1){
			int mid = (l + r) / 2;
			if(lst[mid][0] > c[0] || (lst[mid][0] == c[0] && lst[mid][1] > c[1]))
				r = mid;
			else
				l = mid;
		}
		if(lst[l][0] != c[0] || lst[l][1] != c[1])
			return 0;
		return l + 1;
	}

	void gameplay(){
		gen();
		if(enought)
			return;
		moves = 0;
		int mvs = 0, mvs1 = 0;
		while(true){
			if(check_end())
				return;
			if(moves % 5000 == 0 && moves){
				int x;
				for(int i = 0; i < maxn; ++i)
					for(int j = 0; j < M; ++j){
						file >> x;
						if(a[i][j] != x){
							cout << "INVALID" << '\n';
							return;
						}
					}
				file >> x;
				if(x != canon){
					cout << "INVALID" << '\n';
					return;
				}
				for(int i = 0; i < 18; ++i){
					file >> x;
					if(x != random[i]){
						cout << "INVALID!" << '\n';
						return;
					}
				}
				file >> x;
				if(x != jomle){
					cout << "INVALID!" << '\n';
					return;	
				}
			}
			updlst();
			++moves;
			int x, y;
			file >> x >> y;
			int s_it = search_it({x, y});
			if(s_it)
				while(s_it--)
					_rand();
			else{
				cout << "INVALID" << '\n';
				return;
			}
			a[x][y] = canon, exs[x][y] = true;
			if(!check_good({x, y})){
				++mvs1;
				upd_sit(rnd());
				if(_rand() <= addr1)
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
			if(_rand() <= addr)
				add_row();
			canon = rnd();
		}
		return;
	}

	void play(){
		int times = 1021;
		while(--times && !enought)
			gameplay();
	}

	void update(){
		cout << "ACCEPTED!\n";
		cout << "strength: " << min(sum % moves, 99999) << '\n';
		return;
	}
} g;