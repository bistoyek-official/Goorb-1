#include "selected.hpp"

signed main(){
	init();
	make_p();
	while(true){
		cls();
		cout << "Goorb hash" << '\n';
		cout << "Created by: 21" << '\n';
		time_t t = time(0);
		cout << "___________________________________\n";
		cout << ctime(&t);
		cout << "Bot's name: " << botsname << '\n';
		cout << "___________________________________\n\n";
		cout << "You have this options:" << '\n';
		cout << "  1. check\n";
		cout << "  2. hash\n";
		cout << "  3. make stronger the bank\n";
		cout << "  4. delete the bank and generate a new one\n";
		string s;
		getline(cin, s);
		if(s == "1"){
			time_t t = time(nullptr);
			if(_check_())
				cout << "ACCEPTED!\n";
			else
				cout << "INVALID\n";
			cout << "task 1:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "2"){
			time_t t = time(nullptr);
			_hash_();
			cout << "task 2:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "3"){
			int times;
			cout << "How many times? ";
			cin >> times;
			times = max(times, 1);
			time_t t = time(nullptr);
			srand(t);
			cls();
			calls = quality = 0;
			cout << "starting time: " << ctime(&t) << "tries: " << times << "\n--------\n";
			g.play(false, times);
			cout << "task 3:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "4"){
			renew();
			time_t t = time(nullptr);
			srand(t);
			cls();
			calls = quality = 0;
			cout << "starting time: " << ctime(&t) << "--------\n";
			g.play();
			cout << "task 4:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
	}
	return 0;
}