#include "random.hpp"

int main(){
	int sum = 0, sum1 = 0;
	_srand(0, 21LL);
	while(true){
		_rand();
		if(jomle % 1000000 == 0)
			cout << "#";
	}
	return 0;
}