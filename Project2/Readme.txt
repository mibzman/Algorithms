how to use:
create a build folder within the project 2 folder
in the build folder, run:
cmake ..
make

Part 1:

./LZW c filename
compress the given filename and place the result into filename.lzw

./LZW d filename.lzw
decompress the given filename and place the result into filename2

High-level explanation:
decompress:
1. read binary data into one string in 8 bit chunks
2. parse the binary string into 9-bit numbers
3. decompress with standard LZW

compress:
1. read in file as string
2. compress using standard LZW, capping the dictionary at 9 bits
3. convert integer string to binary
4. write to file

Part 2:

./LZWM c filename
compress the given filename and place the result into filename.lzw

./LZWM d filename.lzw
decompress the given filename and place the result into filename2

High-level explanation:
decompress:
1. read binary data into one string in 8 bit chunks
2. starting with 9 bits, parse the binary one number at a time, building the dictionary as we go
3. increase the bit size whenever the dictionary gets larger than can fit in the current bit size

compress:
1. read in file as string
2. compress using standard LZW, capping the dictionary at 16 bits
3. convert integer string to binary
4. write to file

****NOTE: PART 2 HAS A BUG******
For whatever reason the 511th dictionary entry has an issue reading that particurlar bit sequence.  
this results in one word in the dictionary being slightly wrong, and a stright diff will probably return some differences.
The 511th dictionary entry is the only one with an issue, the entire rest of the dictionary is correct


Notable things:
C++ does not allow you to write arbitrary bits to a file, they must be written in 8 bit characters.
This can present a problem when you want to store a series of 9 bit numbers, since there will almost allways be some left over
my solution is to have the first 8 bits be a flag that describes the amount of padding, followed by 0-7 bits of padding.
this results in a total series of bits divisible by 8

These files can be read by reading the first 8 bits, and then remove the number of bits indicated by those first 8 bits