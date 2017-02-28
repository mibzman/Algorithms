#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector> 
#include <sys/stat.h>
#include <cassert>

#include <sstream>

/*sam borick's (sb205) lzw implementation.
This program will compress and decompress files using the LZW algorithm
NOTE:  My implementation will almost certiantly not be able to decompress files compressed by another LZW implementation,
due to issues with bit lengths
*/


std::string readData(std::ifstream& reader){
	std::stringstream buffer;
	buffer << reader.rdbuf();
	return buffer.str();
}

template <typename Iterator>
Iterator compress(std::string file, Iterator result) {
  std::string uncompressed;
  std::ifstream reader(file);
  uncompressed = readData(reader);
  reader.close();

  // Build the dictionary.
  int dictSize = 256;
  std::map<std::string,int> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[std::string(1, i)] = i;
 
  std::string w;
  for (std::string::const_iterator it = uncompressed.begin();
       it != uncompressed.end(); ++it) {
    char c = *it;
    std::string wc = w + c;
    if (dictionary.count(wc))
      w = wc;
    else {
      *result++ = dictionary[w];
      // Add wc to the dictionary.
      if(dictionary.size() < 512){
        dictionary[wc] = dictSize++;
      }
      w = std::string(1, c);
    }
  }
 
  // Output the code for w.
  if (!w.empty())
    *result++ = dictionary[w];
  return result;
}
 
// Decompress a list of output ks to a string.
// "begin" and "end" must form a valid range of ints
template <typename Iterator>
std::string decompress(Iterator begin, Iterator end) {
  // Build the dictionary.
  int dictSize = 256;
  std::map<int,std::string> dictionary;
  for (int i = 0; i < 256; i++)
    dictionary[i] = std::string(1, i);
 
  std::string w(1, *begin++);
  std::string result = w;
  std::string entry;
  for ( ; begin != end; begin++) {
    int k = *begin;
    if (dictionary.count(k))
      entry = dictionary[k];
    else if (k == dictSize)
      entry = w + w[0];
    else
      throw "Bad compressed k";
 
    result += entry;
 
    // Add w+entry[0] to the dictionary.
    
    if (dictSize < 512){
      dictionary[dictSize++] = w + entry[0];
    }    
 
    w = entry;
  }
  return result;
}

std::string int2BinaryString(int c) {
      int val = c;
      int cl = 9;
      if (c >= 512){
        for (cl = 0; val > 0; val >>= 1)
          cl++;
      }
      std::string p = ""; //a binary code string with code length = cl
      while (c>0) {         
		   if (c%2==0)
            p="0"+p;
         else
            p="1"+p;
         c=c>>1;   
      }
      int zeros = cl-p.size();
      if (zeros<0) {
         //std::cout << "\nWarning: Overflow. code is too big to be coded by " << cl <<" bits!\n";
         p = p.substr(p.size()-cl);
      }
      else {
         for (int i=0; i<zeros; i++)  //pad 0s to left of the binary code if needed
            p = "0" + p;
      }
      return p;
}

std::string int2BinaryString(int c, int cl) {
      
      std::string p = ""; //a binary code string with code length = cl
      while (c>0) {
                   if (c%2==0)
            p="0"+p;
         else
            p="1"+p;
         c=c>>1;
      }
      int zeros = cl-p.size();
      if (zeros<0) {
         //std::cout << "\nWarning: Overflow. code is too big to be coded by " << cl <<" bits!\n";
         p = p.substr(p.size()-cl);
      }
      else {
         for (int i=0; i<zeros; i++)  //pad 0s to left of the binary code if needed
            p = "0" + p;
      }
      return p;
}


int binaryString2Int(std::string p) {
   int code = 0;
   if (p.size()>0) {
      if (p.at(0)=='1') 
         code = 1;
      p = p.substr(1);
      while (p.size()>0) { 
         code = code << 1; 
		   if (p.at(0)=='1')
            code++;
         p = p.substr(1);
      }
   }
   return code;
}

void printPlainText(std::string filename, std::string text){
  std::string newFileName = filename.substr(0, filename.length()-4) + "2";
  std::ofstream outputFile(newFileName);
  outputFile << text;
}

std::string convertIntsToBinary(std::vector<int> nums){
  std::string bcode= "";
  std::string p;
   for (std::vector<int>::iterator it = nums.begin() ; it != nums.end(); ++it) {
      p = int2BinaryString(*it);
      bcode+=p;
   }
   return bcode;
}

void writeBinaryToFile(std::string file, std::string binary){
  std::ofstream myfile;
   myfile.open(file.c_str(),  std::ios::binary);
   
   std::string zeros = "00000000";
   int bitsNeeded = 8 - binary.size()%8; //calculate the padding needed
   std::string flag = int2BinaryString(bitsNeeded, 8); //convert the padding needed to binary
   binary = flag + zeros.substr(0, bitsNeeded) + binary; //first pesudobit
   
   int b; 
   for (int i = 0; i < binary.size(); i+=8) { 
      b = 1;
      for (int j = 0; j < 8; j++) {
         b = b<<1;
         if (binary.at(i+j) == '1')
           b+=1;
      }
      char c = (char) (b & 255); //save the string byte by byte
      myfile.write(&c, 1);  
   }
   myfile.close();
}

void printBinary(std::string file, std::vector<int> compressed){
  std::string binary = convertIntsToBinary(compressed);
  writeBinaryToFile(file, binary);
}

std::string readBinaryFromFile(std::string file) {

  //get whatever is in the file
  std::ifstream myfile2;
  myfile2.open (file.c_str(),  std::ios::binary);
  struct stat filestatus;
  stat(file.c_str(), &filestatus );
  long fsize = filestatus.st_size; //get the size of the file in bytes
  std::string zeros = "00000000";
  char c2[fsize];
  myfile2.read(c2, fsize);

  std::string s = "";
  long count = 0;
  while(count<fsize) {
    unsigned char uc =  (unsigned char) c2[count];
    std::string p = ""; //a binary string
    for (int j=0; j<8 && uc>0; j++) {         
     if (uc%2==0)
          p="0"+p;
       else
          p="1"+p;
       uc=uc>>1;   
    }
    p = zeros.substr(0, 8-p.size()) + p; //pad 0s to left if needed
    s+= p; 
    count++;
  } 
  myfile2.close();

  //if we wrote this file than the first 8 bits are the flag that tell us how much padding there is
  int flag = binaryString2Int(s.substr(0,8));
  //remove flag and padding
  s = s.substr(8+flag);
  return s;
}

std::vector<int> convertBinaryToInts(std::string binary){
   std::vector<int> output;
  int counter = 0;
  while (counter <= binary.length()){
    output.push_back(binaryString2Int(binary.substr(counter, 9)));
    counter += 9;
  }

  //scrub trailing newlines
  counter = output.size() -1;
  while (output[counter] == 0){
    output.pop_back();
    counter--;
  }
  return output;
}

std::vector<int> readBinary(std::string file) {
  std::string binary = readBinaryFromFile(file);
  return convertBinaryToInts(binary);
}

bool binaryIOTest(std::string file, std::vector<int> data){
  printBinary(file + "test", data);

  std::vector<int> result = readBinary(file + "test");
  int overageCounter = 0;
  for (int counter = 0; counter < data.size(); counter++){
    if (data[counter] != result[counter]){
      std::cout << "Difference found at: " << std::endl;
      std::cout << counter << "/" << data.size() << "/" << result.size() << std::endl;
      for (int counter2 = counter -5; counter2 < counter + 5; counter2++){
        if (counter2 > 0) {
        std::cout << "does " << data[counter2] << " == " << result[counter2] << std::endl;
        }
      }
      break;
     //overageCounter++;
    }
    if (data[counter] > 512){
       overageCounter++;
    }
  }
  //result.pop_back();
  if (data.size() != result.size()){
    std::cout << "length different: "  << data.size() << " , " << result.size()<< std::endl;
    std::cout << "last output val: " << result[result.size() - 2] << std::endl;
  }
  std::cout << "over 512: " << overageCounter << std::endl;
  if (result == data){
    std::cout << "100% match" << std::endl;
    std::cout << "lengths: "  << data.size() << " , " << result.size()<< std::endl;
  }
}

bool binaryConversionTest(){
  std::string threeHundred = int2BinaryString(300);
  int result = binaryString2Int(threeHundred);
  return 300 == result;
}

bool integerListConversionTest(){
  const int arr[] = {16,2,77,29,0,300,500};
  std::vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );

  //std::cout << convertIntsToBinary(vec) << std::endl;
  //std::cout << convertBinaryToInts(convertIntsToBinary(vec)) << std::endl;

  return vec == convertBinaryToInts(convertIntsToBinary(vec));
}

bool readWriteIrregularBinaryTest(){
  std::string data = "1111111111111"; //a non-8bit binary string

  writeBinaryToFile("wowWhatAGoodFilename2", data);
  //std::cout << readBinaryFromFile("wowWhatAGoodFilename2") << std::endl;
  return data == readBinaryFromFile("wowWhatAGoodFilename2");
}

bool readWriteBinaryTest(){
  std::string data = "1111111111111111"; 

  writeBinaryToFile("wowWhatAGoodFilename", data);
  //std::cout << readBinaryFromFile("wowWhatAGoodFilename") << std::endl;
  return data == readBinaryFromFile("wowWhatAGoodFilename");
}
 
int main(int argn, char *args[]) {
  assert("Bad arguments.  Flags should be wither v or s" && argn == 3);

  std::string file(args[2]);

  //std::cout << binaryTest

  std::vector<int> compressed;

  if (*args[1] == 'c'){
    compress(file, std::back_inserter(compressed));
//    std::cout << binaryIOTest(file, compressed) << std::endl;
    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    printBinary(file + ".lzw", compressed);
  } else if (*args[1] == 'd'){
    compressed = readBinary(file);
    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::string decompressed = decompress(compressed.begin(), compressed.end());
    printPlainText(file, decompressed);
  }else if (*args[1] == 't'){
    std::cout << "Testing" << std::endl;
    compress(file, std::back_inserter(compressed));
    std::cout << "binaryConversion: " << binaryConversionTest()  << std::endl;
    std::cout << "intlist: " << integerListConversionTest()  << std::endl;
    std::cout << "irregular: " << readWriteIrregularBinaryTest()  << std::endl;
    std::cout << "regular: " << readWriteBinaryTest()  << std::endl;
    binaryIOTest(file, compressed);
  }else{
    std::cout << "wrong flags.  Please enter either c or d followed by the file" << std::endl;
    return 1;
  }

  
  
  return 0;
}
