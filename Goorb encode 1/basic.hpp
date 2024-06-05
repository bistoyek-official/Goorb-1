#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<algorithm>
#include<bitset>
using namespace std;

string botsname;
int K;

void cls(){
	#ifdef __unix__
		system("clear");
	#elif defined(__MACH__)
		system("clear");
	#else
		system("cls");
	#endif
	return;
}