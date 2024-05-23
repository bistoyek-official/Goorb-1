#include "random.hpp"

int main(){
	int sum = 0;
	_srand(time(0), 123456789987654321LL);
	for(int i = 0; i < 1000; ++i)
		sum += _rand();
	cout << sum / 1000.0 << '\n';
	return 0;
}