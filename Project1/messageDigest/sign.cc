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

BigInteger GenerateSigniture(std::string data, BigInteger val, BigInteger n){
	std::string hash = sha::sha256(data);
	BigInteger temp(hash.size());
	BigInteger m = bUtils::dataToBigInteger<const char>(hash.c_str(), temp.getLength(), temp.getSign());
	return  bAlgo::modexp(m, val.getMagnitude(), n.getMagnitude());
}

void Sign(BigInteger* d, BigInteger* n, std::string& file){
	std::ifstream reader(file);
	if (reader){
		std::string data = readData(reader);
		fileReader.close();

		BigInteger signiture = GenerateSigniture(data, d, n);

		file += ".signed";
		std::ofstream signedFile(file);
		signedFile << original_data;
		signedFile << "=====BEGIN SIGNED CONTENT=====";
		signedFile << signiture;
	}
}

void Verify(BigInteger* e, BigInteger* n, std::string& file){
	std::ifstream reader(file);
	if (reader){
		std::string data = readData(reader);
		fileReader.close();
		auto pos = data.find_last_of("=");
		if(pos == -1){
			std::cout << "unable to read file.  file is likly unsigned by this program" << std::endl;
			return;
		}
		//we've gotten the encrypted hash
		BigInteger hash = bUtils::stringToBigInteger(data.substr(pos+1));
		//so if the file hasn't been edited this decrypted hash should match what happens when when sha256 the message we got
		const BigInteger decryptedHash = bAlgo::modexp(dhash, e.getMagnitude(), n.getMagnitude());

		BigInteger thisSigniture =  GenerateSigniture(data.substr(0,pos-29), e, n);

		if (decryptedHash == thisSigniture){
			std::cout << "OHNO!  your file has been tampered with.  Beware Deception!"
			return;
		}

		std::cout << "your file is intact"
		return;

	}
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
