#include "game_play.hpp"

void history();
void leaderboard();
void menu();

void history(){
    string s1;
	ifstream games("./accounts/games/" + user + ".txt");
	head();
	vector<string> act;
	while(getline(games, s1))
		act.push_back(s1);
	cout << "Your history:" << '\n';
	cout << "________________________________________________________________" << '\n';
	cout << "|";
	c_col(9);
	cout << "Time";
	c_col(15);
	cout << "                    |";
	c_col(9);
	cout << "Game's Mode";
	c_col(15);
	cout << "|";
	c_col(9);
	cout << "Taken Time";
	c_col(15);
	cout << "|";
	c_col(9);
	cout << "Rating Changes";
	c_col(15);
	cout << "|" << '\n';
	for(int i = 0; true; ++i){                      
		cout << "|________________________|___________|__________|______________|" << '\n';
		if(i == act.size())
			break;
		cout << "|";
		c_col(10);
		cout << act[i];
		c_col(15);
		cout << "|";
		c_col(10);
		++i;
		cout << (char)toupper(act[i][0]);
		for(int j = 1; j < 11; ++j){
			if(j < act[i].size())
				cout << act[i][j];
			else
				cout << " ";
		}
		c_col(15);
		cout << "|";
		c_col(10);
		++i;
		for(int j = 0; j < 10; ++j){
			if(j < act[i].size())
				cout << act[i][j];
			else if(j == act[i].size())
				cout << "s";
			else
				cout << " ";
		}
		c_col(15);
		cout << "|";
		c_col(10);
		++i;
		cout << act[i];
		for(int j = 0; j < 14 - (int)act[i].size(); ++j)
			cout << " ";
		c_col(15);
		cout << "|" << '\n';
	}
	cout << "\nTo back into the menu press any key" << endl;
	getch();
	return;
}

void leaderboard(string mode){
	ifstream ranking("./accounts/ranking" + mode + ".txt");
	string s1, s2;
	vector<pair<string, int>> standing;
	while(getline(ranking, s1)){
		int num;
		ranking >> num;
		standing.push_back({s1, num});
		getline(ranking, s1);
	}
	sort(standing.begin(), standing.end(), [&](pair<string, int> e1, pair<string, int> e2){return e1.second > e2.second;});
	head();
	cout << "_______________________________________" << '\n';
	cout << "|";
	c_col(9);
	cout << "Ranking";
	c_col(15);
	cout << "|";
	c_col(9);
	cout << "Handle                ";
	c_col(15);
	cout << "|";
	c_col(9);
	cout << "Rating";
	c_col(15);
	cout << "|" << '\n';
	for(int i = 0; true; ++i){
		cout << "|_______|______________________|______|" << '\n';
		if(i == standing.size())
			break;
		int l;
		cout << "|";
		c_col(10);
		cout << "#" << i + 1;
		l = ceil(log10(i + 2));
		for(int j = 0; j < 6 - l; ++j)
			cout << " ";
		c_col(15);
		cout << "|";
		c_col(10);
		for(int j = 0; j < 22; ++j)
			if(j < standing[i].first.size())
				cout << standing[i].first[j];
			else
				cout << " ";
		c_col(15);
		cout << "|";
		c_col(10);
		cout << standing[i].second;
		l = max(1, (int)ceil(log10(abs(standing[i].second) + 1)) + (int)(standing[i].second < 0));
		for(int j = 0; j < 6 - l; ++j)
			cout << " ";
		c_col(15);
		cout << "|" << '\n';
	}
	cout << "\n----------------------------------------\n";
	cout << "To back see a leaderboards you press:" << '\n';
	cout << "  1. total leader board" << '\n';
	cout << "  2. leader board in timer mode" << '\n';
	cout << "  3. leader board in infinite mode" << '\n';
	cout << "  4. leader board in normal mode" << '\n';
	cout << "\nTo back into the menu press any other key" << endl;
	char c = getch();
	if(c == '1')
		leaderboard("");
	else if(c == '2')
		leaderboard("timer");		
	else if(c == '3')
		leaderboard("infinite");
	else if(c == '4')
		leaderboard("normal");
	return;
}

void menu(){
	while(true){
		head();
		cout << "Main Menu:" << '\n';
		cout << "  1. Play" << '\n';
		cout << "  2. Leaderboard" << '\n';
		cout << "  3. History" << '\n';
		cout << "  4. Sign out" << '\n';
		cout << "\n----------------------------\n";
		cout << "to choose an option write it's section number" << '\n';
		cout << "----------------------------\n";
		char c = getch();
		if(c == '4'){
			head();
			cout << "are you sure you want to sign out? (n: no / any other key: yes) ";
			if(getch() == 'n')
				continue;
			ofstream slo("./accounts/saved_login.txt");
			slo << "" << '\n' << -1 << '\n';
			slo.close();
			user1 = user = "";
			return;
		}
		if(c == '1'){
			game p;
			p.play();
		}
		if(c == '2')
			leaderboard("");
		if(c == '3')
			history();
	}
	return;
}