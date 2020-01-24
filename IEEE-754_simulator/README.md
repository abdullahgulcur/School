## IEEE-754 Simulator Program
The purpose of this project is to become more familiar with bit-level representations of integers and floating point numbers.

#### This project takes  
- a file containing hexadecimal numbers as bytes in a memory,
- the byte ordering type (Little Endian or Big Endian),
- the data type to be converted, and
- the size of the given data type,
as input and converts the contents of the file according to the predefined format and gives the converted data as output.

The data type can be any of the following
- signed integer
- unsigned integer
- floating point number

The size of the data type can be 1, 2, 3, 4, or 6 bytes

- If the selected data type is signed integer, program will convert the numbers in the input file using 2’s complement representation.
- If the selected data type is unsigned integer, numbers will be converted using unsigned integer representation.
- If the selected data type is floating point number, program will use IEEE-like format.

Example: input.txt
f0 90 01 40 03 00 ff ff 00 00 e0 7f
00 00 e0 ff 00 00 00 00 00 00 00 80
00 00 18 80 00 00 00 00 00 00 00 00

The byte ordering is Little Endian, and the data type is 4 byte floating point.
- First, program will read the next 4 bytes of the file. For our “input.txt” the first four bytes is:
f0 90 01 40
- The byte ordering is Little Endian, so the floating point number is:
40 01 90 f0, in binary: 0100 0000 0000 0001 1001 0000 1111 0000
- In the specification, we are given that our 4 byte IEEE-like floating point numbers have 10 bits of
exponent part, so Bias = 210-1 – 1 = 511:
Sign bit = 0
Exponent = (1000000000)2 = 512
Fraction = 000011001000011110000 à rounded fraction = 0000110010001
mantissa = 1+1/32+1/64+1/512+1/8192 = 1.0489501953125
Decimal value = (-1)0 * 1.0489501953125 * 2512-511 = 2.097900390625
In the output file, the printed value will be: 2.09790
