#include "selected.hpp"

void Encryption(){
	init();
	while(true){
		cls();
		cout << "Goorb encode 2" << '\n';
		cout << "Created by: 21" << '\n';
		time_t t = time(nullptr);
		cout << "___________________________________\n";
		cout << ctime(&t);
		cout << "Key's name: " << keysname << '\n';
		cout << "___________________________________\n\n";
		cout << "You have these options:" << '\n';
		cout << "  1. decode\n";
		cout << "  2. encode\n";
		cout << "  3. make stronger the bank\n";
		cout << "  4. delete the bank and generate a new one\n";
		cout << "  5. delete the bank\n";
		string dir = "./messages/" + keysname + "/", s;
		getline(cin, s);
		if(s == "1"){
			time_t t = time(nullptr);
			_decode_(dir);
			cout << "task 1:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "2"){
			time_t t = time(nullptr);
			_encode_(dir);
			cout << "task 2:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "3"){
			int times;
			cout << "How many times? ";
			cin >> times;
			times = min(max(times, 1), 1021);
			time_t t = time(nullptr);
			cls();
			calls = 0;
			cout << "starting time: " << ctime(&t) << "tries: " << times << "\n--------\n";
			sha256.encrypt(times);
			cout << "task 3:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "4"){
            time_t t = time(nullptr);
			renew();
			cls();
			calls = 0;
			cout << "starting time: " << ctime(&t) << "--------\n";
			rescount = vector<int>(1 << K_, 0);
			sha256.encrypt();
			cout << "task 4:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "5"){
            time_t t = time(nullptr);
            renew();
            rescount = vector<int>(1 << K_, 0);
            calls = 0;
            cout << "task 5:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
	}
	return;
}

int main(){
    Encryption();
    return 0;
}
