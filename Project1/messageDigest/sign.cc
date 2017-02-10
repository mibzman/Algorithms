#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "BigIntegerLibrary.hh"
#include "BigIntegerAlgorithms.hh"
#include "messageDigest/sha256.h"
//another student did somehting like this, I thought it was a great idea
#define bAlgos BIGINTEGERALGORITHMS_H
#define bUtils BIGINTEGERUTILS_H
#define sha SHA256_H

std::string readData(std::ifstream& reader){
	std::stringstream buffer;
	buffer << reader.rdbuf();
	return buffer.str();
}

void Sign(BigInteger* d, BigInteger* n, std::string file){
	std::ifstream reader(file);
	if (reader){
		std::string data = readData(reader);
		fileReader.close();
		std::string hash = sha::sha256(data);
		BigInteger temp(sha_hash.size());
		BigInteger m = bUtils::dataToBigInteger<const char>(hash.c_str(), temp.getLength(), temp.getSign());
		const BigInteger decrypt = bAlgo::modexp(m, d.getMagnitude(), n.getMagnitude());
		file += ".signed";
		std::ofstream signedFile(file);
		signedFile << original_data;
		signedFile << "=====BEGIN SIGNED CONTENT=====";
		signedFile << decrypt;
	}
}

void Verify(std::string file){

}

void GetEAndN(BigInteger* e, BigInteger* n){
	std::ifstream reader();
	if (reader){
		reader.open("e_n.txt");
		if (reader){
			std::string eString, nString;
			reader >> sString, >> nString;
			*e = bUtils::stringToBigInteger(eString);
			*n = bUtils::stringToBigInteger(nString);
		}
	}
	return;
}

void GetDAndN(BigInteger* d, BigInteger* n){
	std::ifstream reader();
	if (reader){
		reader.open("d_n.txt");
		if (reader){
			std::string dString, nString;
			reader >> sString, >> nString;
			*d = bUtils::stringToBigInteger(dString);
			*n = bUtils::stringToBigInteger(nString);
		}
	}
	return;
}

int main(int argn, char *args[]) {
	srand (time(NULL));

	//it's super stupid that the exe is an argument
	assert("Bad arguments.  Flags should be wither v or s" && argn == 3);

	std::string file = ReadString(args[3]);

	try{
		if (*args[1] == 'v'){
		BigInteger e,n;
		GetEAndN(&e,&n);
		Verify(e,n,file);
		} else if (*args[1] == 's'){
			BigInteger d,n;
			GetDAndN(&d,&n);
			Sign(d,n,file);
		} else{
			std::cout << "wrong flags.  Please enter either v or s followed by the file" << std::endl;
			return 1;
		}
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl;
	}

	return 0;
}
