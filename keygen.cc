//keygen.cc

/*Uses methods from numberTheory.cc to create text files containing the keys*/

#include <iostream>
#include "numberTheory.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv)
/*Uses four command line parameters 2 prime numbers then 2 filenames to create keys and store them in the files*/
{
  ReallyLongInt p = atoi(argv[1]);
  ReallyLongInt q = atoi(argv[2]);
  ofstream fout (argv[3]);
  ofstream fout2 (argv[4]);
  if(p>100000 || q>100000)
    {
      cout << "Primality is not being verified for arguments larger than 100,000" << endl;
    }
  else
    {
      if(!isPrime(p)||!isPrime(q))
	{
	  if(!isPrime(p))
	    {
	      cout << "First number is not a prime number" << endl;
	      return 1;
	    }
	  else if(!isPrime(q))
	    {
	      cout << "Second number is not a prime number" << endl;
	      return 1;
	    }
	  cout << "Both numbers are not prime numbers" << endl;
	  return 1;
	}
    }

  ReallyLongInt n = p*q;
  ReallyLongInt t = ((p-1)*(q-1));
  ReallyLongInt e = 2;
  ReallyLongInt x = 0;
  ReallyLongInt y = 0;
  while(extendedEuclid(e,t,x,y)!=1)
    {
      e=e+1;
    }
  if(x < 0)
    {
      x = t + x;
    }
  fout << e << " " << n << endl;
  fout2 << x << " " << n << endl;
}








