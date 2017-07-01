//encrypt.cc

/*Uses modPower to encrypt a text file with keys from another text file*/

#include <iostream>
#include <fstream>
#include "numberTheory.h"
#include <stdlib.h>


using namespace std;



int main(int argc, char** argv)
/*Reads in the encryption keys from 'public.txt', then reads in text to be encrypted from 'plaintext.txt', encrypts ASCII values with modPower and writes into 'encrypted.txt'*/
{
  ifstream fin (argv[1]);
  long long e;
  long long n;
  fin >> e;
  fin >> n;
  
  ifstream fin2 (argv[2]);
  ofstream fout (argv[3]);
  
  ReallyLongInt y = e;
  ReallyLongInt z = n;

  char c;
  while(fin2.get(c))
    {
      ReallyLongInt x = c;
      fout << modPower(x, y, z) << endl;
    }
}
