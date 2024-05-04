#include "menu.hpp"

using ll = long long;

void sign_in(vector<pair<string, string>> &users);
void sign_up(vector<pair<string, string>> &users);

string hs(string &s){
	ll bs[5] = {259, 258, 257, 256, 263};
	ll md[5] = {1000000021, 1000000009, 1000000007, 998244353, 2000000011};
	ll sum = 0;
	string res = "", st;
	for(int k = 0; k < 5; ++k, res += st, sum = 0)
		for(int i = 0; i < s.size(); ++i){
			sum = (sum * bs[k]) % md[k];
			sum += s[i];
			sum %= md[k];
			st = to_string((int)sum);
			for(int j = 0; j < 11 - st.size(); ++j)
				res.push_back('0');
		}
	return res;
}

int get_ind(vector<pair<string, string>> &users, string &s){
	string s1 = hs(s);
	for(int i = 0; i < users.size(); ++i)
		if(users[i].first == s1)
			return i;
	return -1;
}

void psw(string &s){
	s = "";
	for(bool b = false; true; b = true){
		char c = getch();
		if(c == 13)
			return;
		else if(c == '\b'){
			if(s.size()){
				s.pop_back();
				cout << "\b \b";
			}
		}
		else{
			cout << c;
			for(int i = 0; i < 300000000; ++i);
			cout << "\b*";
			s.push_back(c);
		}
	}
	return;
}

void sign_up(vector<pair<string, string>> &users){
	string s1, s2, s3;
	for(bool b = false; true; b = true){
		head();
		cout << "If you have an account and want to sing in write \"sign in\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b && s1 != "")
			cout << "username is taken" << '\n';
		if(b && s1 == "")
			cout << "username can't be null" << '\n';
		cout << "username: ";
		getline(cin, s1);
		if(s1 == "sign in"){
			sign_in(users);
			return;
		}
		int ind = get_ind(users, s1);
		if(ind == -1 && s1 != "")
			break;
	}
	for(bool b = false; true; b = true){
		head();
		cout << "If you have an account and want to sing in write \"sing in\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b){
			cout << "password isn't match" << '\n';
			cout << "-------------------\n";
		}
		cout << "username: " << s1 << '\n';
		cout << "password: ";
		psw(s2);
		if(s2 == "sign in"){
			sign_in(users);
			return;
		}
		cout << '\n';
		cout << "confirm passwaord: ";
		psw(s3);
		if(s3 == "sign in"){
			sign_in(users);
			return;
		}
		if(s2 == s3)
			break;
	}
	ofstream us("./accounts/users.txt");
	ofstream ps("./accounts/pass.txt");
	for(auto &e: users){
		us << e.first << '\n';
		ps << e.second << '\n';
	}
	user = hs(s1);
	user1 = s1;
	us << user << '\n';
	ps << hs(s2) << '\n';
	us.close();
	ps.close();
	ofstream games("./accounts/games/" + user + ".txt");
	games.close();
	string modes[4] = {"", "infinite", "timer", "normal"};
	for(int i = 0; i < 4; ++i){
		ifstream rank("./accounts/ranking" + modes[i] + ".txt");
		vector<string> rnk;
		while(getline(rank, s3))
			rnk.push_back(s3);
		rank.close();
		ofstream rank1("./accounts/ranking" + modes[i] + ".txt");
		rnk.push_back(s1);
		rnk.push_back("0");
		for(auto &e: rnk)
			rank1 << e << '\n';
		rank1.close();
	}
	return;
}

void sign_in(vector<pair<string, string>> &users){
	string s1, s2;
	for(bool b = false; true; b = true){
		head();
		cout << "If want to create account write \"sign up\" and press enter" << '\n';
		cout << "-------------------\n";
		if(b)
			cout << "username or password is in correct" << '\n';
		cout << "username: ";
		getline(cin, s1);
		if(s1 == "sign up"){
			sign_up(users);
			return;
		}
		cout << "password: ";
		psw(s2);
		if(s2 == "sign up"){
			sign_up(users);
			return;
		}
		int ind = get_ind(users, s1);
		if(ind != -1 && users[ind].first == hs(s1) && users[ind].second == hs(s2)){
			user = hs(s1);
			user1 = s1;
			return;
		}
	}
	return;
}

void enter(){
	while(true){
		ifstream sli("./accounts/saved_login.txt");
		string l1;
		int l2;
		getline(sli, l1);
		sli >> l2;
		if(l1.size() && time(0) - l2 <= 7 * 60 * 24 * 60){
			user1 = l1, user = hs(user1);
			menu();
			continue;
		}
		sli.close();
		ifstream us("./accounts/users.txt");
		ifstream ps("./accounts/pass.txt");
		vector<pair<string, string>> users;
		string s;
		while(getline(us, s)){
			users.push_back({});
			users.back().first = s;
			getline(ps, s);
			users.back().second = s;
		}
		us.close();
		ps.close();
		for(bool b = false; true; b = true){
			head();
			cout << "Have an account? (y/n)" << '\n';
			if(b)
				cout << "invalid input, try again" << endl;
			getline(cin, s);
			if(s == "y" || s == "n")
				break;
		}
		if(s[0] == 'y')
			sign_in(users);
		else
			sign_up(users);
    	cout << "\nDo you want to save your login for a week? (1:yes, any other keys:no)";
    	char c = getch();
	    if(c == '1'){
    		ofstream slo("./accounts/saved_login.txt");
	    	slo << user1 << '\n';
    		slo << time(0) << '\n';
		}
		menu();
	}
	return;
}