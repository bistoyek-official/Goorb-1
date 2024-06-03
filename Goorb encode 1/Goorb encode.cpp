#include "selected.hpp"

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

signed main(){
	init();
	while(true){
		system("cls");
		cout << "Goorb encode" << '\n';
		cout << "Created by 21" << '\n';
		time_t t = time(0);
		cout << "___________________________________\n";
		cout << ctime(&t);
		cout << "Bot's name: " << botsname << '\n';
		cout << "___________________________________\n\n";
		cout << "You have this options:" << '\n';
		cout << "  1. decode\n";
		cout << "  2. encode\n";
		cout << "  3. make stronger the bank\n";
		cout << "  4. delete the bank and generate a new one\n";
		string s;
		getline(cin, s);
		if(s == "1"){
			_decode_();
			cout << "task 1:\ndone!\npress any key to continue\n";
			getch();
		}
		if(s == "2"){
			_encode_();
			cout << "task 2:\ndone!\npress any key to continue\n";
			getch();
		}
		if(s == "3"){
			game g;
			int times;
			cout << "How many times? ";
			cin >> times;
			time_t t = time(nullptr);
			srand(t);
			system("cls");
			cout << "starting time: " << ctime(&t) << "--------\n";
			g.play("", times);
			cout << "task 3:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "4"){
			game g;
			renew();
			time_t t = time(nullptr);
			srand(t);
			system("cls");
			cout << "starting time: " << ctime(&t) << "--------\n";
			g.play();
			cout << "task 4:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
	}
	return 0;
}