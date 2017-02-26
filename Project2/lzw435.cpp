#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector> 
#include <sys/stat.h>
#include <cassert>

#include <sstream>


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
      dictionary[wc] = dictSize++;
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
    dictionary[dictSize++] = w + entry[0];
 
    w = entry;
  }
  return result;
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

bool binaryTest(std::vector<int> compressed) {
   int c = 69;
   //int bits = 9;
   std::string p = int2BinaryString(c, 9);
   
   std::string bcode= "";
   for (std::vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) {
      //if (*it<256)
        // bits = 8;
      //else
        // bits = 9;
      p = int2BinaryString(*it, 9);
      bcode+=p;
   }
   
   //writing to file
   std::string fileName = "example435.lzw";
   std::ofstream myfile;
   myfile.open(fileName.c_str(),  std::ios::binary);
   
   std::string zeros = "00000000";
   if (bcode.size()%8!=0) //make sure the length of the binary string is a multiple of 8
      bcode += zeros.substr(0, 8-bcode.size()%8);
   
   int b; 
   for (int i = 0; i < bcode.size(); i+=8) { 
      b = 1;
      for (int j = 0; j < 8; j++) {
         b = b<<1;
         if (bcode.at(i+j) == '1')
           b+=1;
      }
      char c = (char) (b & 255); //save the string byte by byte
      myfile.write(&c, 1);  
   }
   myfile.close();
   
   //reading from a file
   std::ifstream myfile2;
   myfile2.open (fileName.c_str(),  std::ios::binary);
   
   struct stat filestatus;
   stat(fileName.c_str(), &filestatus );
   long fsize = filestatus.st_size; //get the size of the file in bytes
   
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

  std::vector<int> output;
  int counter = 0;
  while (counter <= s.length()){
    output.push_back(binaryString2Int(s.substr(counter, 9)));
    counter += 9;
  }
  std::cout << "compressed: "; 
  copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl << "----output: ";
  copy(output.begin(), output.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;


  for (int counter2 = 0; counter2 < compressed.size(); counter2++){
    std::cout << "does " << compressed[counter2] << " == " << output[counter2] << std::endl;
  }
  output.pop_back();
  return compressed == output;
}


std::vector<int> readBinary(std::string file) {   
  //reading from a file
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

  //iterate through all the bits 8 at a time
  std::vector<int> output;
  int counter = 0;
  while (counter <= s.length()){
    output.push_back(binaryString2Int(s.substr(counter, 9)));
    counter += 9;
  }
   output.pop_back();
   return output;
}

void printBinary(std::string file, std::vector<int> compressed){
    int c = 69;
   int bits = 9;
   std::string p = int2BinaryString(c, bits);
   
   std::string bcode= "";
   for (std::vector<int>::iterator it = compressed.begin() ; it != compressed.end(); ++it) {
      p = int2BinaryString(*it, bits);
      bcode+=p;
   }
   
   //writing to file
   std::ofstream myfile;
   myfile.open(file.c_str(),  std::ios::binary);
   
   std::string zeros = "00000000";
   if (bcode.size()%8!=0) //make sure the length of the binary string is a multiple of 8
      bcode += zeros.substr(0, 8-bcode.size()%8);
   
   int b; 
   for (int i = 0; i < bcode.size(); i+=8) { 
      b = 1;
      for (int j = 0; j < 8; j++) {
         b = b<<1;
         if (bcode.at(i+j) == '1')
           b+=1;
      }
      char c = (char) (b & 255); //save the string byte by byte
      myfile.write(&c, 1);  
   }
   myfile.close();
}

void printPlainText(std::string filename, std::string text){
  std::string newFileName = filename.substr(0, filename.length()-4) + "2";
  std::ofstream outputFile(newFileName);
  outputFile << text;
}


bool binaryIOTest(std::string file, std::vector<int> data){
  printBinary(file, data);

  std::vector<int> result = readBinary(file);

  for (int counter = 0; counter < compressed.size(); counter++){
    if (data[counter] != result[counter]){
      std::cout << "Difference Ditected at: " << std::endl;
      std::cout << counter << "/" << compressed.size << std::endl;
    }
  }

  return result == data;
}


 
int main(int argn, char *args[]) {
  assert("Bad arguments.  Flags should be wither v or s" && argn == 3);

  std::string file(args[2]);

  //std::cout << binaryTest

  std::vector<int> compressed;

  if (*args[1] == 'c'){
    compress(file, std::back_inserter(compressed));
    std::cout << binaryIOTest(file, compressed) << std::endl;
    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    printBinary(file + ".lzw", compressed);
  } else if (*args[1] == 'd'){
    compressed = readBinary(file);
    //copy(compressed.begin(), compressed.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::string decompressed = decompress(compressed.begin(), compressed.end());
    printPlainText(file, decompressed);
  } else{
    std::cout << "wrong flags.  Please enter either c or d followed by the file" << std::endl;
    return 1;
  }

  
  
  return 0;
}
