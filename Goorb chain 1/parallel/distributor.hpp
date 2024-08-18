#include "p_validation.hpp"//jaye in bayad chizi bezari ke file ro befreste be server haie ke mikhaim
//#include "value.hpp"
//			       59  59 30    30 30 10    10     10    30  30     8
//                  O   O  O        O
long long user_serial, tb, N, maxn, M, same, addr, addr1, bl, blsc, rang, jml;
vector<vector<int>> a;

long long ok(string &s, int lim){
	if(s.size() > lim || s.size() == 0)
		return -1;
	for(int i = 0; i < s.size(); ++i)
		if(s[i] > '9' && '0' < s[i])
			return -1;
	long long ans = 0;
	for(int i = 0; i < s.size(); ++i)
		ans = (ans * 10) + (s[i] - '0');
	return ans;
}

void check(){
	int maxmove = 5000;
	cout << "~ enter file dir: ";
	string s, input;
	getline(cin, s);
	ifstream fin(s);
	if(!fin.is_open()){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	user_serial = ok(input, 18);
	if(user_serial == -1 || user_serial >= (1LL << 59)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	tb = ok(input, 18);
	if(tb == -1 || tb >= (1LL << 59)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	N = ok(input, 10);
	if(N == -1 || N >= (1 << 30)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	maxn = ok(input, 10);
	if(maxn == -1 || maxn >= (1 << 30)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	M = ok(input, 10);
	if(M == -1 || M >= (1 << 30)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	same = ok(input, 4);
	if(same == -1 || same > 1023){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	addr = ok(input, 4);
	if(addr == -1 || addr > 1023){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	addr1 = ok(input, 4);
	if(addr1 == -1 || addr1 > 1023){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	bl = ok(input, 10);
	if(bl == -1 || bl >= (1 << 30)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	blsc = ok(input, 10);
	if(blsc == -1 || blsc >= (1 << 30)){
		cout << "INVALID" << '\n';
		return;
	}
	input = "";
	fin >> input;
	rang = ok(input, 3);
	if(rang == -1 || rang > 255){
		cout << "INVALID" << '\n';
		return;
	}
	/*
	if(!has_value(user_serial, tb, N, maxn, M, same, addr, addr1, bl, blsc, rang)){
		cout << "INVALID" << '\n';
		return;
	}
	*/
	for(int i = 0; i < maxn; ++i){
        a.push_back(vector<int>{});
        for(int j = 0; j < M; ++j)
            a[i].push_back(0);
    }
	long long cnt = 0;
	long long canon, rnd[18];
	bool b;
	while(true){
		++cnt;
		string dir = "moves.txt";
		ofstream fout(dir);
		fout << user_serial << '\n' << tb << '\n' << N << '\n' << maxn << '\n' << M << '\n';
		fout << same << '\n' << addr << '\n' << addr1 << '\n' << bl << '\n' << blsc << '\n' << rang << '\n';
		if(cnt != 1){
			for(int i = 0; i < maxn; ++i)
				for(int j = 0; j < M; ++j)
					fout << a[i][j] << '\n';
			fout << canon << '\n';
			for(int i = 0; i < 18; ++i)
				fout << rnd[i] << '\n';
			fout << jml << '\n';
		}
        int cor[2];
		input = "";
		fin >> input;
		cor[0] = ok(input, 9);
		if(cor[0] == -1){
            cout << "INVALID" << '\n';
            return;
		}
		fout << cor[0] << '\n';
		input = "";
		fin >> input;
		cor[1] = ok(input, 9);
		if(cor[1] == -1){
            cout << "INVALID" << '\n';
            return;
		}
		fout << cor[1] << '\n';
        b = false;
		for(int i = 1; i < maxmove; ++i){
            input = "";
            fin >> input;
            cor[0] = ok(input, 9);
            if(cor[0] == -1){
                if(input.size()){
                    cout << "INVALID" << '\n';
                    return;
                }
                else{
                	fout.close();
                    g.play(dir, (cnt == 1), true);
                    b = true;
                    break;
                }
            }
            fout << cor[0] << '\n';
            input = "";
            fin >> input;
            cor[1] = ok(input, 9);
            if(cor[1] == -1){
                cout << "INVALID" << '\n';
                return;
            }
            fout << cor[1] << '\n';
		}
		if(b)
            break;
		input = "";
		fin >> input;
		a[0][0] = ok(input, 9);
		if(a[0][0] == -1){
            if(input.size()){
                cout << "INVALID" << '\n';
                return;
            }
            else{
                fout.close();
				g.play(dir, (cnt == 1), true);
                break;
            }
		}
		fout << a[0][0] << '\n';
		for(int i = 0; i < maxn; ++i)
			for(int j = (int)(i == 0); j < M; ++j){
				input = "";
				fin >> input;
				a[i][j] = ok(input, 9);
				if(a[i][j] == -1){
                    cout << "INVALID" << '\n';
                    return;
				}
				fout << a[i][j] << '\n';
            }
		input = "";
		fin >> input;
		canon = ok(input, 9);
		if(canon == -1){
            cout << "INVALID" << '\n';
            return;
		}
		fout << canon << '\n';
		for(int i = 0; i < 18; ++i){
            input = "";
            fin >> input;
            rnd[i] = ok(input, 9);
            if(rnd[i] == -1){
                cout << "INVALID" << '\n';
                return;
            }
            fout << rnd[i] << '\n';
		}
		input = "";
        fin >> input;
        jml = ok(input, 18);
        if(jml == -1){
            cout << "INVALID" << '\n';
            return;
        }
        fout << jml << '\n';
		fout.close();
		g.play(dir, (cnt == 1), false);
		//jaye in bayad be ye server befrestish
	}
	return;
}
