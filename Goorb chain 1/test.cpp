#include "random.hpp"

int main(){
	while(true){
		int n;
		cin >> n; 
		long long num, time_b = time(0), cnt[1024] = {}, cnt2[1024] = {}, serial = 21;
		long double var = 0, var1 = 0, var2 = 0, sum = 0, sum2 = 0;
		_srand(time_b, serial);
		for(int i = 0; i < n; ++i){
			num = _rand();
			++cnt[num];
			sum += num;
		}
		for(int i = 0; i < 1024; ++i)
			var += cnt[i] * (i - 511.5) * (i - 511.5); 
		cout << "time:         " << time_b << '\n';
		cout << "serial:       " << serial << '\n';
		cout << "------------------------------------------------\n";
		cout << setprecision(20) << fixed;
		cout << "E(X):         " << sum / n << '\n';
		cout << "sqrt(var(X)): " << sqrt(var / n) << '\n';
		for(int i = 0; i < 1024; ++i)
			var1 += (i - 511.5) * (i - 511.5);
		cout << "------------------------------------------------\n";
		cout << "E(X): (ideal) " << 511.5 << '\n';
		cout << "sqrt(var(X)): (ideal) " << sqrt(var1 / 1024.0) << '\n';
		cout << "------------------------------------------------\n";
		srand(time_b);
		for(int i = 0; i < n; ++i){
			num = rand() % 1024;
			++cnt2[num];
			sum2 += num;
		}
		for(int i = 0; i < 1024; ++i)
			var2 += cnt2[i] * (i - 511.5) * (i - 511.5);
		cout << "E(X):         " << sum2 / n << '\n';
		cout << "sqrt(var(X)): " << sqrt(var2 / n) << '\n';
		cout << "------------------------------------------------\n";
	}
	return 0;
}