#include "basic.hpp"

long long jomle, mod = 1000000021;

long long random[18], seed[18], us[18];

long long r[18] = {192, 526, 305, 980, 52, 237, 297, 366, 289, 564, 362, 937, 947, 1008, 27, 803, 229, 707};

long long binpow(long long a, long long b){
	long long res = 1;
	b %= mod - 1;
	while(b){
		if(b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

int _rand(){
	++jomle;
	long long sum = 0;
	for(int i = 0; i < 18; ++i)
		sum = (sum + us[i] * binpow(random[i], seed[i])) % mod;
	random[0] = binpow(sum, jomle);
	for(int i = 0; i < 17; ++i)
		swap(random[i], random[i + 1]);
	random[17] %= 1000000009, random[17] %= 1024;
	return random[17];
}

void _srand(long long tb, long long u_s){
	for(int i = 0; i < 18; ++i){
		us[i] = u_s % 10 + 1;
		seed[i] = tb % 10 + 1;
		u_s /= 10;
		tb /= 10;
		random[i] = r[i];
	}
	jomle = 18;
	for(int i = 0; i < 100; ++i)
		_rand();
	return;
}