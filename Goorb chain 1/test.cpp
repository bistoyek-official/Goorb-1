#include "random.hpp"

int main(){
	long long num, sum = 0, time_b = time(0), cnt[1024] = {}, serial = 112233445566778899LL;
	_srand(time_b, serial);
	for(int i = 0; i < 1600000; ++i){
		num = _rand();
		++cnt[num];
		sum += num;
	}
	long double var = 0;
	for(int i = 0; i < 1024; ++i)
		var += cnt[i] * (i - 511.5) * (i - 511.5); 
	cout << "time:   " << time_b << '\n';
	cout << "serial: " << serial << '\n';
	cout << "E(X):   " << sum / 1600000.0 << '\n';
	cout << "var(X): " << var / 1600000.0 << '\n';
	cout << "------------------------------------------------\n";
	for(int i = 0; i < 1024; ++i){
		cout << i << ": " << cnt[i] << " ]] ";
		if(i % 8 == 7)
			cout << '\n';
	}
	return 0;
}