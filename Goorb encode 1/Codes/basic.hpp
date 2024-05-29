#include <bits/stdc++.h>
#include <chrono>
#include <conio.h>
#include <windows.h>
using namespace std;
using namespace chrono;

HANDLE col =  GetStdHandle(STD_OUTPUT_HANDLE);

string user, user1;

void c_col(int c){
    SetConsoleTextAttribute(col, c);
    return;
}

void cls(){
    system("cls");
    return;
}

char* date(){
	time_t t = time(0);
	char* dt = ctime(&t);
	return dt;
}

void head(){
    cls();
	c_col(10);
	cout << "Goorb code\n";
	cout << "Created by: " << "21" << '\n';
	c_col(15);
	cout << "_______________________________________________\n";
	if(user.size()){
		c_col(1);
		cout << "~ " << user1 << "\n";
		c_col(15);
		cout << "_______________________________________________\n";
	}
	c_col(14);
	cout << "Local time: " << date() << "\n";
	c_col(15);
	return;
}