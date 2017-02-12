#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <cstring>
#include <sstream>
#include <fstream>

#include "BigIntegerLibrary.hh"
#include "BigIntegerAlgorithms.hh"
#include "sha256.h"
//another student did somehting like this, I thought it was a great idea
#define bAlgos BIGINTEGERALGORITHMS_H
#define bUtils BIGINTEGERUTILS_H
#define sha SHA256_H

std::string readData(std::ifstream& reader){
	std::stringstream buffer;
	buffer << reader.rdbuf();
	return buffer.str();
}

std::string ReadString(char arr[]){
	std::string output = "";
	int size = strlen(arr), i = 0;
	while(i < size)
		output += *(arr + i++);
	return output;
}

BigInteger GenerateSigniture(std::string data, BigInteger val, BigInteger n){
	std::string hash = sha::sha256(data);
//	std::cout << hash.size() << std::endl;
	BigInteger temp(hash.size());
//	std::cout << temp.getLength() << std::endl;
	BigInteger m = bUtils::dataToBigInteger<const char>(hash.c_str(), temp.getLength(), temp.getSign());
	std::cout << m << std::endl;
	return  bAlgos::modexp(m, val.getMagnitude(), n.getMagnitude());
}

void Sign(BigInteger d, BigInteger n, std::string& file){
	std::ifstream reader(file);
	if (reader){
		std::string data = readData(reader);
		reader.close();

		BigInteger signiture = GenerateSigniture(data, d, n);
		//std::cout << signiture << std::endl;
		file += ".signed";
		std::ofstream signedFile(file);
		signedFile << data;
		signedFile << "=====BEGIN SIGNED CONTENT=====";
		signedFile << signiture;
	}
}

void Verify(BigInteger e, BigInteger n, std::string& file){
	std::ifstream reader(file);
	if (reader){
		std::string data = readData(reader);
		reader.close();
		auto pos = data.find_last_of("=");
		if(pos == -1){
			std::cout << "unable to read file.  file is likly unsigned by this program" << std::endl;
			std::cout << "file reads: " << std::endl << data << std::endl;
			return;
		}
		//we've gotten the encrypted hash
		//std::cout << data.substr(pos+1) << std::endl;
		BigInteger hash = bUtils::stringToBigInteger(data.substr(pos+1));
		//so if the file hasn't been edited this decrypted hash should match what happens when when sha256 the message we got
		const BigInteger decryptedHash = bAlgos::modexp(hash, e.getMagnitude(), n.getMagnitude());
		//std::cout << data.substr(0,pos-30);
		std::string tempSigniture =  sha::sha256(data.substr(0,pos-29));
        	BigInteger temp(tempSigniture.size());
        	BigInteger thisSigniture = bUtils::dataToBigInteger<const char>(tempSigniture.c_str(), temp.getLength(), temp.getSign());

		if (decryptedHash != thisSigniture){
			std::cout << "OHNO!  your file has been tampered with.  Beware Deception!" << std::endl;
			std::cout << "Decrypted hash: " << std::endl << decryptedHash  << std::endl << "this signiture: "  << std::endl << thisSigniture << std::endl;
			return;
		}

		std::cout << "your file is intact" << std::endl;
		return;

	}
}

void GetEAndN(BigInteger* e, BigInteger* n){
	std::ifstream reader("e_n.txt");
	if (reader){
		if (reader){
			std::string eString, nString;
			reader >> eString >> nString;
			*e = bUtils::stringToBigInteger(eString);
			*n = bUtils::stringToBigInteger(nString);
		}
	}
	return;
}

void GetDAndN(BigInteger* d, BigInteger* n){
	std::ifstream reader("d_n.txt");
	if (reader){
		std::string dString, nString;
		reader >> dString >> nString;
		*d = bUtils::stringToBigInteger(dString);
		*n = bUtils::stringToBigInteger(nString);
	}else{
		throw std::invalid_argument( "the d_n.txt file is not present" );
	}	
	return;
}



int main(int argn, char *args[]) {
	srand (time(NULL));

	//it's super stupid that the exe is an argument
	assert("Bad arguments.  Flags should be wither v or s" && argn == 3);

	std::string file(args[2]);

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
