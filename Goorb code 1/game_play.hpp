#include "random.hpp"

struct game{

	int maxn, N, M, same, addr, addr1, tries = 0, bot;
	bool silent;

	ifstream file;

	vector<vector<int>> a, lst, ok;
	vector<vector<bool>> exs, blast;
	string modes[3] = {"timer", "infinite", "normal"}, mode;
	long long tbr, tb, user_serial;
	bool checking = false, checkmanual = false, enough = false;
	vector<string> code;

	int pts = 0, canon, ini, tl = 120, rows, X, Y, bl, blsc;
	bool frombot;

	int dx[6] = {0, 0, 1, 1, -1, -1}, dy[6] = {2, -2, -1, 1, -1, 1};

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
			if(toupper(mode[0]) != 'M'){
				if(ini != i && _rand() % same == 1)
					a[0][i] = a[0][i - 2];
				else
					a[0][i] = rnd();
			}
			else{
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
			}
			exs[0][i] = true;
			blast[0][i] = false;
		}
		return;
	}

	void sit(){
		head();
		for(int i = 0; i < maxn; ++i, cout << '\n')
			for(int j = 0; j < M; ++j)
				cout << exs[i][j] << " ";
		cout << endl;
		getch();
		prt_scr(canon);
		return;
	}

	void gen(){
		ini = pts = 0;
		tb = time(nullptr) + tries;
		tbr = time(nullptr);
		++tries;
		if(checkmanual){
			cout << "enter time: ";
			cin >> tb;
		}
		if(!checking){
			if(!frombot)
				silent = false;
			N = 5, maxn = 31, M = 16, same = 512;
			addr = 4, addr1 = 4;
			bl = 10, blsc = 14;
			_srand(tb, user_serial);
		}
		else{
			cout << "\n~ enter file dir: ";
			string s;
			getline(cin, s);
			if(tries > 1)
				file.close();
			file.open(s);
			if(!file.is_open()){
				enough = true;
				return;
			}
			file >> user_serial >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc;
			_srand(tb, user_serial);
		}
		rows = 10;
		a.clear(), exs.clear(), blast.clear(), lst.clear(), code.clear();
		code.push_back(to_string(user_serial)), code.push_back(to_string(tb));
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
		prt_scr(rnd());
		return;
	}

	void prt_scr(int color){
		if(!silent){
			head();
			if(frombot)
				cout << "Tries: " << tries << ", Bot: " << bot <<'\n';
			cout << "------------------------\n";
			mode[0] = toupper(mode[0]);
			cout << "Mode: " << mode << '\n';
			mode[0] += 32;
			c_col(6);
			cout << "Score: " << pts << "\n\n";
			c_col(9);
			cout << "Timer: " << time(nullptr) - tbr << "s " << (mode == "timer" ? "of 120s" : "")  << (checkmanual ? ", tb: " + to_string(tb) : "") << '\n';
			c_col(15);
			cout << "------------------------\n\n  ";
			for(int i = 0; i < M; ++i)
				cout << (char)('A' + i);
			cout << "\n ";
			for(int i = 0; i < M + 2; ++i)
				cout << "_";
			cout << '\n';
		}
		for(int i = 0; i < maxn; ++i){
			if(!silent)
				cout << (char)('A' + i) << "|";
			for(int j = (i + ini) % 2; j < M; j += 2){
				if((i + ini) % 2){
					if(!silent)
						cout << " ";
				}
				if(exs[i][j]){
					if(!silent){
						c_col(a[i][j]);
						cout << (char)('A' + j);
						c_col(15);
					}
				}
				else{
					if(blast[i][j]){
						if(!silent)
							cout << (i == X && j == Y ? "*" : "X");
					}
					else if(a[i][j]){
						if(!silent)
							cout << "-";
					}
					else{
						if(!silent){
							if(maxn % 2)
								cout << ((ini && i == maxn - 1) ? "~" : " ");
							else
								cout << ((!ini && i == maxn - 1) ? "~" : " ");
						}
					}
					blast[i][j] = a[i][j] = 0;
				}
				if(!((i + ini) % 2) && j != M - 1){
					if(!silent){
						if(maxn % 2)
							cout << ((!ini && i == maxn - 1) ? "~" : " ");
						else
							cout << ((ini && i == maxn - 1) ? "~" : " ");
					}
				}
			}
			if((i + ini) % 2){
				if(!silent)
					cout << " ";
			}
			if(!silent){
				if((i + ini) % 2 && M % 2 == 0)
					cout << "\b \b";
				cout << "|\n";
			}
		}
		if(!silent){
			cout << " |";
			for(int i = 0; i < (M - 3) / 2; ++i)
				cout << " ";
			if(M % 2 == 0)
				cout << " ";
			cout << "(";
		}
		canon = color;
		if(!silent){
			c_col(canon);
			cout << '0';
			c_col(15);
			cout << ")";
			for(int i = 0; i < (M - 3) / 2; ++i)
				cout << " ";
			cout << "|\n";
			if(!frombot && toupper(mode[0]) != 'M'){
				cout << "\n---------------------------------\n";
				cout << "to choose a cell you have to write it's cordinate e.g. AA or FB and it should be valid\n";
				cout << "---------------------------------\n";
			}
		}
		return;
	}

	bool not_null(int i){
		return *max_element(a[i].begin(), a[i].end());
	}

	bool check_end(){
		time_t te = time(nullptr) - tbr;
		if(not_null(maxn - 1)){
			if(checking){
				cout << "INVALID" << '\n';
				return true;
			}
			cout << (mode[0] != 'i' ? "\n====================YOU LOSE!==================|\n" : "\n====================GAME OVER==================|\n");
			string report = "Tries: " + to_string(tries) + ", Timer: " + to_string(te) + ", Score: " + to_string(pts) + ", moves: " + to_string(code.size());
			while(report.size() < 47)
				report += " ";
			report += "|";
			cout << report << ":: " << jomle << '\n';
			return true;
		}
		if(mode == "timer" && time(0) - tbr > tl){
			cout << "\n====================GAME OVER==================|\n";
			string report = "Tries: " + to_string(tries) + ", Timer: " + to_string(te) + ", Score: " + to_string(pts) + ", moves: " + to_string(code.size());
			while(report.size() < 47)
				report += " ";
			report += "|";
			cout << report << ":: " << jomle << '\n';
			return true;
		}
		if(!not_null(0)){
			if(mode[0] == 'i'){
				add_row();
				prt_scr(canon);
				return false;
			}
			if(!checking){
				c_col(10);
				cout << "\n====================YOU WIN!===================|\n";
				string report = "Tries: " + to_string(tries) + ", Timer: " + to_string(te) + ", Score: " + to_string(pts) + ", moves: " + to_string(code.size());
				while(report.size() < 47)
					report += " ";
				report += "|";
				cout << report << ":: " << jomle << '\n';
				c_col(15);
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

	int willfall(int i){
		auto a1 = a;
		auto exs1 = exs;
		auto blast1 = blast;
		int x = lst[i][0], y = lst[i][1];
		a[x][y] = canon, blast[x][y] = false, exs[x][y] = true;
		if(!check_good({x, y})){
			if(bot == 1){
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
		if(bot == 1){
			int cnt = 0;
			for(int i = 0; i < maxn; ++i)
				for(int j = (ini + i) % 2; j < M; j += 2)
					cnt += (int)exs[i][j];
			a = a1, exs = exs1, blast = blast1;
			return cnt;
		}
		else if(bot == 2){
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
		if(enough)
			return;
		int mvs = 0, mvs1 = 0;
		while(true){
			if(check_end())
				break;
			updlst();
			int x, y;
			if(frombot){
				int mn1 = 1000000021, mn2 = 1000000021;
				x = lst[0][0], y = lst[0][1];
				for(int i = 0; i < lst.size(); ++i){
					int balls = willfall(i);
					bot = 3 - bot;
					int rws = willfall(i);
					bot = 3 - bot;
					if(rws == 1000000020 && mn1 == 1000000020)
						continue;
					if(mn1 > balls)
						mn1 = balls, mn2 = rws, x = lst[i][0], y = lst[i][1];
					else if(mn1 == balls && mn2 > rws)
						mn1 = rws, x = lst[i][0], y = lst[i][1];
					else if(mn1 == balls && mn2 == rws)
						mn1 = rws, x = lst[i][0], y = lst[i][1];
				}
				int s_it = search_it({x, y});
				while(s_it--)
					_rand();
			}
			else{
				while(true){
					string s;
					if(!checking){
						if(toupper(mode[0]) != 'M')
							cin >> s;
						else
							cin >> x >> y;
					}
					else
						file >> s;
					if(toupper(mode[0]) != 'M'){
						if(s == "q"){
							cout << "\n======GAME OVER=====\n";
							return;
						}
						if(s == "s"){
							sit();
							continue;
						}
						x = s[0] - 'A', y = s[1] - 'A';
					}
					int s_it = search_it({x, y});
					if(s_it){
						while(s_it--)
							_rand();
						break;
					}
					if(checking){
						cout << "INVALID" << '\n';
						return;
					}
					else
						cout << "invlaid input, try again" << '\n';
				}
			}
			string str = to_string(x) + " " + to_string(y);
			code.push_back(str);
			X = x, Y = y;
			a[x][y] = canon, blast[x][y] = false, exs[x][y] = true;
			if(!check_good({x, y})){
				++mvs1;
				if(mode == "normal" && rows-- >= 0)
					add_row();
				else if(mode != "normal" && toupper(mode[0]) != 'M' && rows-- >= 0)
					add_row();
				prt_scr(rnd());
				if(mode != "normal" && mvs1 % addr1 == 0)
					add_row();
				prt_scr(canon);
				if(check_end())
					return;
				continue;
			}
			++mvs;
			dfs_blast({x, y}), --pts;
			fall();
			prt_scr(canon);
			upd_rnd();
			if(!frombot && !checking)
				Beep(414, 300);
			if(mode == "normal" && mvs % 2 == 0 && rows-- >= 0)
				add_row();
			else if(mode != "normal" && mvs % addr == 0)
				add_row();
			prt_scr(rnd());
		}
		return;
	}

	void play(){
		while(true){
			frombot = false;
			tries = 0;
			head();
			cout << "Game Modes:" << '\n';
			cout << "  1. Timer Mode" << '\n';
			cout << "  2. Infinite Mode" << '\n';
			cout << "  3. Normal Mode" << '\n';
			cout << "  4. Back to the menu" << '\n';
			cout << "\n----------------------------\n";
			cout << "to choose an option write it's section number" << '\n';
			cout << "----------------------------\n";
			char index = 'm';
			if(!checking)
				index = getch();
			if(index == '!'){
				checking = false, checkmanual = true;
				continue;
			}
			if(index == '@'){
				checking = true, checkmanual = false;
				continue;
			}
			if(index == '#'){
				checking = checkmanual = false;
				continue;
			}
			if(index == '4')
				return;
			if(index != 'm'){
				if('0' >= index || index >= '4')
					continue;
				mode = modes[index - '1'];
				user_serial = 0;
				gameplay();
				update();
			}
			else{
                char c = 'y';
				head();
				if(!checking){
					cout << "Do you want to use bot? (y/n)" << '\n';
					frombot = ('y' == getch());
				}
				else{
					frombot = false;
					cout << "Do you want to watch the game? (y/n)" << '\n';
					c = getch();
				}
				mode = (frombot ? "Miner-Bot" : "Miner-Manual");
				if(frombot){
					cout << "Witch Miner-Bot?" << '\n';
					cin >> bot;
					cout << "Do you want to watch the game? (y/n)" << '\n';
					c = getch();
				}
				cout << "enter your serial code: ";
				cin >> user_serial;
				int times = 1021;
				if((frombot && c == 'n') || checking){
					cout << "How many tries do you want to do? (enter the number)" << '\n';
					cin >> times;
					if(times < 0)
						times = 1021;
				}
				do{
					silent = (c == 'n');
					gameplay();
				} while(--times && c == 'n' && !enough);
				enough = false;
				tries = 0;
			}
			if(checking){
				cout << "press any key to continue ";
				getch();
				return;
			}
			cout << "press any key to back into the game modes ";
			getch();
		}
		return;
	}

	void update(){
		if(checking){
			cout << "ACCEPTED!\n";
			return;
		}
		string tmp = mode;
		if(toupper(mode[0]) == 'M')
			mode = "infinite";
		int timer = time(nullptr) - tbr, r_changes = pts;
		string s = ctime(&tbr), ln;
		ifstream hs("./accounts/games/" + user + ".txt");
		vector<string> vec;
		while(getline(hs, ln))
			vec.push_back(ln);
		hs.close();
		ofstream histo("./accounts/games/" + user + ".txt");
		histo << s;
		histo << mode << '\n';
		histo << timer << '\n';
		if(r_changes > 0)
			histo << '+';
		histo << r_changes << '\n';
		for(string &e: vec)
			histo << e << '\n';
		histo.close();
		vec.clear();
		ifstream rnk("./accounts/ranking.txt");
		while(getline(rnk, ln))
			vec.push_back(ln);
		for(int i = 0; i < vec.size(); i += 2)
			if(user1 == vec[i]){
				vec[i + 1] = to_string(stoi(vec[i + 1]) + r_changes);
				break;
			}
		ofstream rank("./accounts/ranking.txt");
		for(int i = 0; i < vec.size(); ++i)
			rank << vec[i] << '\n';
		rank.close();
		vec.clear();
		ifstream rnk1("./accounts/ranking" + mode + ".txt");
		while(getline(rnk1, ln))
			vec.push_back(ln);
		for(int i = 0; i < vec.size(); i += 2)
			if(user1 == vec[i]){
				vec[i + 1] = to_string(stoi(vec[i + 1]) + r_changes);
				break;
			}
		ofstream rank1("./accounts/ranking" + mode + ".txt");
		for(int i = 0; i < vec.size(); ++i)
			rank1 << vec[i] << '\n';
		rank1.close();
		mode = tmp;
		if(toupper(mode[0]) == 'M'){
			ofstream coin("./accounts/games/" + to_string(tb) + ", " + user + ".txt");
			for(auto &e: code)
				coin << e << '\n';
		}
		return;
	}
};