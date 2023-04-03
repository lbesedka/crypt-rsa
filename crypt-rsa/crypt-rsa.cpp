#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <string.h>
#include "BigInt.hpp"
#define digits_length 25

using namespace std;

//generation big prime numbers
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
//encrypt key
BigInt key(BigInt p, BigInt q) {
	BigInt e = big_random(digits_length);
	BigInt pq_1 = (p - 1)*(q - 1);
	while (gcd(e, pq_1) != 1) {
		e = big_random(digits_length);
	}
	cout << e << endl; 
	return e; 
}
// for decrypt key
tuple<BigInt, BigInt, BigInt> extended_gcd(BigInt a, BigInt p, BigInt q){
	BigInt b = (p - 1) * (q - 1); 
	BigInt x = 0, y = 1, u = 1, v = 0;
	while (a != 0) {
		BigInt q = b / a;
		BigInt r = b % a;
		BigInt m = x - u * q;
		BigInt n = y - v * q;
		b = a;
		a = r;
		x = u;
		y = v;
		u = m;
		v = n;
	}
	return make_tuple(b, x, y);
}

BigInt mod_inverse(BigInt a, BigInt p, BigInt q)
{
	BigInt g, x, y;
	BigInt m = (p - 1) * (q - 1);
	tie(g, x, y) = extended_gcd(a, p, q);
	if (g != 1) {
		return -1;   // inverse doesn't exist
	}
	return (x % m + m) % m;   
}



int main()
{

	//BigInt p = generate_prime();
	//BigInt q = generate_prime();
	BigInt p ("8279170237136523271263427");
	BigInt q ("9223448226441434779857647");
	BigInt e("9527360111833535202863801");
	cout << p << endl;
	cout << q << endl;
	cout << e << endl;
	//BigInt d = extended_gcd(e, p, q);
	BigInt d = mod_inverse(e, p, q);
	cout << d << endl; 
	//cout << d << endl; 
	//key(p, q); 
}
