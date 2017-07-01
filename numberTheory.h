#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H
#include "ReallyLongInt.h"


template <class X>
X modPower(const X& base, const X& exponent, const X& modulus)
{
  X answer;
  X value;
  if (exponent == 0)
    {
      return 1;
    }
  else
    {
      value = modPower(base, exponent/2, modulus);
    }
  if (exponent%2 == 0)
    {
      answer = value%modulus * value%modulus;
    }
  else
    {
      answer = base%modulus * value%modulus * value%modulus;
    }
  answer = answer % modulus;
  return answer;
}

template <class X>
bool isPrime(const X& num)
/*Takes a number as a parameter and returns True or False if it is a prime number*/
{
  if(num == 0 || num == 1)
    {
      return 0;
    }
  else
    {
      for(int i = 2; i < num/2; i++) 
	{
	  if(num%i == 0)
	    {
	      return 0;
	    }
	}
    }
  return 1;
}

template <class X>
X extendedEuclid(const X& a, const X& b, X& px, X& py)
/*Takes two numbers and two pointers to return the GCD (1 if primes) (a*x)+(b*y) = gcd*/
{
  if(b == 0)
    {
      px = 1;
      py = 0;
      return a;
    }
  else
    {
      X d = extendedEuclid(b, a%b, px, py);
      X holdx = px;
      X holdy = py;
      px = holdy;
      py = holdx - (a/b)*holdy;
      return d;
    }
}

#endif
