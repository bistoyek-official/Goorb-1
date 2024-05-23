#include "basic.hpp"

long long random[2], seed, jomle, mod = 4656763;

int binpow(long long int a, long long b){
	int res = 1;
	a %= mod;
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
	random[0] = binpow((random[0] + random[1]) * seed, 21 * (jomle + seed));
	swap(random[0], random[1]);
	random[1] %= 243 * 243;
	random[1] += 1;
	return random[1] % 1024;
}

void _srand(long long tb){
	seed = tb;
	random[0] = 2, random[1] = 21;
	jomle = 2;
	for(int i = 0; i < 100; ++i)
		_rand();
	return;
}