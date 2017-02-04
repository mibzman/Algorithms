// You need to complete this program for a part of your first project.

// Standard libraries
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


// `BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"
#include "BigIntegerAlgorithms.hh"
//another student did somehting like this, I thought it was a great idea
#define bAlgos BIGINTEGERALGORITHMS_H

//an Implementation of modular exponentiation
/*
BigInteger FastModulo(BigInteger base, BigInteger expo, BigInteger mod){
  BigInteger x = 1;
  BigInteger y = base;
  while (expo > 0){
    if (expo % 2 == 1)
      x = (x * y) % mod;
    y = (y * y) % mod;
    expo = expo / 2;
  }
  return x % mod;
}

*/
bool Fermat(BigInteger& p, int lim){
	int counter = 1;
	while (counter != lim){
		const BigInteger start = BigInteger(rand()) % (p - 1) + 1;
		BigUnsigned val = bAlgos::modexp(start, p.getMagnitude()-1, p.getMagnitude());
		if(val != 1){
			return false;
		}
		++counter;
	}
	return true;
}

BigInteger MakeBigInt(){
	BigInteger random = BigInteger(1);
	for (int i=1; i<155; ++i){
		int randDig = rand() % 10;
        	random = random * 10 + randDig;
         }
	return random;

}

BigInteger FindPrime(){
	BigInteger prime = MakeBigInt();
	while(!Fermat(prime, 3)){
		prime = MakeBigInt();	
	}
	return prime;
}
/*
void TryBigInt(){
	BigUnsigned intermediate = BigUnsigned(4);
	intermediate.bitShiftLeft(intermediate, 511);
	BigInteger x = BigInteger(intermediate);

	BigInteger result = new BigInteger(x.bitLength(), rand());
	std::cout << result;
}*/

bool relativelyPrime(BigInteger& phi, BigInteger& maybeE){
   return bAlgo::gcd(phi.getMagnitude(), maybeE.getMagnitude()) == 1;
}

BigInteger FindE(BigInteger phi){
	BigInteger maybeE = BigInteger(2 * (rand() + 1));
	while(!relativelyPrime(phi, maybeE)){
		maybeE = BigInteger(2 * (rand() + 1));
	}
	return maybeE;
}



int main() {
	/* The library throws `const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a `try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */

    srand (time(NULL));

	try{
		BigInteger p = generatePrime();
		BigInteger q = generatePrime();
		BigInteger m = p * q;
		BigInteger phi = (p -1) * (q - 1);
		BigInteger e = FindE(phi);
 
      
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}
	std::cout << "calculating prime" << std::endl;
	std::cout << FindPrime() << std::endl;

	return 0;
}
