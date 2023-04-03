#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <string.h>
#include "BigInt.hpp"
#define digits_length 25

using namespace std;


std::tuple<BigInt, int, BigInt> power2(BigInt a) {
	int counter = 0;
	BigInt a_new = a - 1;
	while (a_new % 2 == 0) {
		a_new /= 2;
		counter++;
	}
	cout << "2^counter " << counter << endl;
	cout << "d " << a_new << endl;
	return tuple<BigInt, int, BigInt> (a_new, counter, a);
}




BigInt modpow(BigInt base, BigInt exp, BigInt modulus)
{
	BigInt result = 1;

	for (base %= modulus; exp > 0; base = (base * base) % modulus, exp /= 2)
		if ((exp % 2) != 0)
			result = (result * base) % modulus;

	return result;
}


bool MillerRabinTest(BigInt d,BigInt n, int s) {

	cout << "Modulo " << n << endl;
	// d * 2^s
	//pair<BigInt, int> p = power2(n);
	cout << " stepen " << d << endl;
	BigInt a = big_random(digits_length + 2)%(n-2)+1;
	//BigInt a = 5; 
	cout << "Base " << a << endl;
	BigInt x = modpow(a, d, n);
	cout  << x << endl;
	if (x == 1 || x == n - 1)
		return true;
	for (int i = 0; i <= s - 1; i++) {
		BigInt two = 2; 
		x = modpow(x, two, n); 
		if(x == 1)
			return false; 
		if (x == n-1)
			return true; 
	}
	return false; 
}

bool isPrime(int iterations, BigInt num) {
	// d * 2^s
	tuple<BigInt, int, BigInt> p = power2(num);
	for (int i = 0; i < iterations; i++)
	{
		bool is_true = MillerRabinTest(get<0>(p), get<2>(p), get<1>(p));
		cout << "Iteration " << i << " " << is_true << endl;
		if (!is_true)
			return false;
	}
	return true; 
}

BigInt generate_prime()
{
	bool global_flag = true;
	BigInt a = 0;
	while (global_flag)
	{
		a = big_random(digits_length);
		cout << "______________________________________________________" << endl;
		cout << "start num " << a << endl;
		if (a % 2 == 0) {
			cout << "Regenerate" << endl;
			a = big_random(digits_length);
			cout << "new regenerated num " << a << endl;
		}
		if (isPrime(4, a))
			global_flag = false;
		cout << "______________________________________________________" << endl;
	}
	return a;
}




int main()
{

	BigInt p = generate_prime();
	BigInt q = generate_prime();
	cout << p << endl;
	cout << q << endl;

}
