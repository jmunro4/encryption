//decrypt.cc

/*Uses modPower to decrypt a text file using keys from another text file*/

#include <iostream>
#include <fstream>
#include "numberTheory.h"


using namespace std;


int main(int argc, char** argv)
/*Reads in the decryption keys from 'private.txt', then reads in number values from 'encrypted.txt', then uses modPower to find the ASCII values and writes into 'decrypted.txt'*/
{
  ifstream fin (argv[1]);
  long long d;
  long long n;
  fin >> d;
  fin >> n;
  
  ifstream fin2 (argv[2]);
  ofstream fout (argv[3]);
  
  ReallyLongInt y = d;
  ReallyLongInt z = n;

  unsigned long long num;
  fin2 >> num;
  while (!fin2.eof())
    {
      ReallyLongInt num2 = num;
      ReallyLongInt c = modPower(num2, y, z);
      long long llnum = c.toLongLong();
      char ch = llnum;
      fout << ch;
      fin2 >> num;
    }
}




