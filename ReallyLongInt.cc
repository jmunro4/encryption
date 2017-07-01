#include <cmath>
#include <string>
#include <iostream>
#include <climits>
#include <sstream>

#include "ReallyLongInt.h"

using namespace std;

ReallyLongInt::ReallyLongInt()
{
  isNeg = false;
  numDigits = 1;
  digits = new unsigned char[numDigits];
  this->digits[0] = 0;
}

ReallyLongInt::ReallyLongInt(const string& numStr)
{
  numDigits = numStr.size();
  isNeg = false;
  digits = new unsigned char[numDigits];
  for(unsigned i = 0; i < numDigits; i++)
    {
      if(numStr[i] == '-')
	{
	  isNeg = true;
	  digits[i] = 0;
	}
      else
	{
	  digits[i] = numStr[i] - 48;
	}
    }
  ReallyLongInt::removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(long long num) //Check these ranges
{
  this->isNeg = false;
  if(num < 0)
    {
      this->isNeg = true;
      num = num * -1;
    }

  if(num == 0)
    {
      numDigits = 1;
    }
  else
    {
      numDigits = (log10(num)) + 1;
    }
  this->digits = new unsigned char[numDigits];
  long long storenum = 0;
  for(unsigned i = 0; i < numDigits; i++)
    {
      unsigned long long power = 1;
      for(unsigned j = 1; j < (numDigits-i); j++)
	{
	  power = power * 10;
	}
      storenum = num % power;
      this->digits[i] = num/power;
      num = storenum;
    }
  this->digits[numDigits] = num;
  ReallyLongInt::removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(bool isNeg, unsigned char* digits, unsigned numDigits)
{
  this->isNeg = isNeg;
  this->digits = digits;
  this->numDigits = numDigits;
  ReallyLongInt::removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
  this->numDigits = other.numDigits;
  this->isNeg = other.isNeg;
  digits = new unsigned char[numDigits];
  for(unsigned i = 0; i < numDigits; i++)
    {
      digits[i] = other.digits[i];
    }
  ReallyLongInt::removeLeadingZeros();
}

ReallyLongInt::~ReallyLongInt()
{
  delete[] digits;
}

void ReallyLongInt::removeLeadingZeros()
{
  while(int(digits[0]) == 0 && numDigits != 1)
    {
      for(unsigned i = 0; i < numDigits - 1; i++)
	{
	  digits[i] = digits[i+1];
	}
      digits[numDigits] = '\0';
      numDigits--;
    }
}

ostream& ReallyLongInt::print(ostream& out) const
{
  if(isNeg && int(digits[0]) != 0)
    {
      out << '-';
    }
  for(unsigned i = 0; i < numDigits; i++)
    { 
      out << int(digits[i]);
    }
  return out;
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{
  if(this->isNeg != other.isNeg && (this->digits[0] != 0 || other.digits[0] != 0))
    {
      return false;
    }
  else if(this->numDigits == other.numDigits)
    {
      for(unsigned i = 0; i < this->numDigits; i++)
	{
	  if(int(this->digits[i]) != int(other.digits[i]))
	    {
	      return false;
	    }
	}
      return true;
    }
  return false;
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
  if(this->numDigits > other.numDigits)
    {
      return true;
    }
  else if(this->numDigits == other.numDigits)
    {
      for(unsigned i = 0; i < this->numDigits; i++)
	{
	  if(int(this->digits[i]) > int(other.digits[i]))
	    {
	      return true;
	    }
	  else if(int(this->digits[i]) < int(other.digits[i]))
	    {
	      return false;
	    }
	}
      return false;
    }
  return false;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
  x.print(out);
  return out;
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
  ReallyLongInt temp = ReallyLongInt(other);
  ReallyLongInt temp2;
  this->isNeg = temp.isNeg;
  this->numDigits = temp.numDigits;
  for(unsigned i = 0; i < numDigits; i++)
    {
      digits[i] = temp.digits[i];
    }
  return *this;
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
  if(this->digits[0] == 0 && other.digits[0] == 0)
    {
      return false;
    }
  else if(this->isNeg && other.isNeg)
    {
      return not this->absGreater(other);
    }
  else if(not this->isNeg && not other.isNeg)
    {
      return this->absGreater(other);
    }
  else if(this->isNeg && not other.isNeg)
    {
      return false;
    }
  else
    {
      return true;
    }
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.equal(y);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return not x.equal(y);
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return not x.greater(y);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.greater(y) or x.equal(y);
}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return not x.greater(y) or x.equal(y);
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
  const unsigned char* lArray;
  const unsigned char* sArray;
  int diff = 0;
  int resultSize = 0;

  if(this->absGreater(other))
    {
      lArray = this->digits;
      sArray = other.digits;
      diff = this->numDigits - other.numDigits;
      resultSize = this->numDigits + 1;
    }
  else
    {
      lArray = other.digits;
      sArray = this->digits;
      diff = other.numDigits - this->numDigits;
      resultSize = other.numDigits + 1;
    }
  unsigned char* myArray = new unsigned char[resultSize];
  int sum = 0;
  for(int i = 0; i < resultSize; i++)
    {
      myArray[i] = 0;
    }
  for(int j = resultSize-1; j > 0; j--)
    {
      int k = j-1;
      if((k-diff)+1 > 0)
	{
	  sum = int(myArray[k+1]) + int(lArray[k]) + int(sArray[k-diff]);
	}
      else
	{
	  sum = int(myArray[k+1]) + int(lArray[k]);
	}
      
      if(sum > 9)
	{
	  myArray[k] = 1;
	  sum = sum % 10;
	}
      myArray[k+1] = sum;
    }
  return ReallyLongInt(false, myArray, resultSize);
}


ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
  const unsigned char* lArray;
  const unsigned char* sArray;
  int diff = 0;
  int resultSize = 0;
  bool neg;
  if(this->absGreater(other))
    {
      neg = false;
      lArray = this->digits;
      sArray = other.digits;
      diff = this->numDigits - other.numDigits;
      resultSize = this->numDigits;
    }
  else
    {
      neg = true;
      lArray = other.digits;
      sArray = this->digits;
      diff = other.numDigits - this->numDigits;
      resultSize = other.numDigits;
    }
  unsigned char* myArray = new unsigned char[resultSize];
  int difference = 0;
  for(int i = 0; i < resultSize; i++)
    {
      myArray[i] = 0;
    }
  for(int j = resultSize-1; j >= 0; j--)
    {
      if(j-diff >= 0)
	{
	  if(int(sArray[j-diff]) > (int(lArray[j])-int(myArray[j])))
	    {
	      difference = ((int(lArray[j])+10)-int(sArray[j-diff])) - int(myArray[j]);
	      myArray[j-1] = 1;
	    }
	  else
	    {
	      difference = (int(lArray[j]) - int(sArray[j-diff])) - int(myArray[j]);
	    }
	}
      else
	{
	  difference = int(lArray[j]) - int(myArray[j]);
	}
      myArray[j] = difference;
    }
  return ReallyLongInt(neg, myArray, resultSize);
}

void ReallyLongInt::flipSign()
{
  this->isNeg = not this->isNeg;
}

ReallyLongInt ReallyLongInt::operator-() const
{
  return ReallyLongInt(not this->isNeg, this->digits, this->numDigits);
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
  if(this->isNeg)
    {
      if(other.isNeg)
	{
	  ReallyLongInt temp = this->absAdd(other);
	  temp.flipSign();
	  return temp;
	}
      else
	{
	  ReallyLongInt temp = *this;
	  temp.flipSign();
	  return other.absSub(temp);
	}
    }
  else if(other.isNeg)
    {
      return this->absSub(other);
    }
  else
    {
      return this->absAdd(other);
    }
  return 1;
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
  if(this->isNeg)
    {
      if(other.isNeg)
	{
	  ReallyLongInt temp = *this;
	  temp.flipSign();
	  return other.absSub(temp);
	}
      else if(not other.isNeg)
	{
	  ReallyLongInt temp = this->absAdd(other);
	  temp.flipSign();
	  return temp;
	}
    }
  else if(other.isNeg)
    {
      return this->absAdd(other);
    }
  else
    {
      return this->absSub(other);
    }
  return 1;
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.add(y);
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.sub(y);
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  *this = this->add(other);
  return *this;
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  *this = this->sub(other);
  return *this;
}

ReallyLongInt& ReallyLongInt::operator++()
{
  ReallyLongInt x(1);
  *this = this->add(x);
  return *this;
}

ReallyLongInt& ReallyLongInt::operator--()
{
  ReallyLongInt x(1);
  *this = this->sub(x);
  return *this;
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
  ReallyLongInt x(1);
  ReallyLongInt copy = *this;
  *this = this->add(x);
  return copy;
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
  ReallyLongInt x(1);
  ReallyLongInt copy = *this;
  *this = this->sub(x);
  return copy;
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{
  int resultSize = this->numDigits + other.numDigits;
  unsigned char* myArray = new unsigned char[resultSize];
  for(int i = 0; i < resultSize; i++)
    {
      myArray[i] = 0;
    }
  for(int j = this->numDigits - 1; j >= 0; j--)
    {
      for(int k = other.numDigits - 1; k >= 0; k--)
	{
	  int sum = int(this->digits[j])*int(other.digits[k]);
	  myArray[j+k+1] = int(myArray[j+k+1]) + sum%10;
	  myArray[j+k] = int(myArray[j+k]) + sum/10;
	  
	  if(int(myArray[j+k+1]) > 9)
	    {
	      myArray[j+k] = int(myArray[j+k])+int(myArray[j+k+1])/10;
	      myArray[j+k+1] = int(myArray[j+k+1])%10;
	    }
	}
    }
  return ReallyLongInt(false, myArray, resultSize);
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{
  if(this->isNeg && other.isNeg)
    {
      return this->absMult(other);
    }
  else if(not this->isNeg && not other.isNeg)
    {
      return this->absMult(other);
    }
  else
    {
      ReallyLongInt temp = this->absMult(other);
      temp.flipSign();
      return temp;
    }
  return 1;
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return x.mult(y);
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{
  *this = this->mult(other);
  return *this;
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  remainder = 0;
  int size = this->numDigits;
  unsigned char* myArray = new unsigned char[size];
  for(int j = 0; j < size; j++)
    {
      myArray[j] = 0;
    }
  for(int i = 0; i < size; i++)
    {
      
      remainder = remainder * 10;
      remainder = remainder + int(this->digits[i]);

      int div = 0;
      while(remainder >= other)
	{
	  remainder = remainder - other;
	  div = div + 1;
	}
      myArray[i] = div;
    }
  quotient = ReallyLongInt(false, myArray, size);
}

void ReallyLongInt::div(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  if(this->isNeg && other.isNeg)
    {
      ReallyLongInt temp1 = *this;
      temp1.flipSign();
      ReallyLongInt temp2 = other;
      temp2.flipSign();
      temp1.absDiv(temp2, quotient, remainder);
    }
  else if(not this->isNeg && not other.isNeg)
    {
      this->absDiv(other, quotient, remainder);
    }
  else if(this->isNeg && not other.isNeg)
    {		
      ReallyLongInt temp1 = *this;
      temp1.flipSign();
      temp1.absDiv(other, quotient, remainder);
      quotient.flipSign();
    }
  else if(not this->isNeg && other.isNeg)
    {
      ReallyLongInt temp1 = other;
      temp1.flipSign();
      this->absDiv(temp1,quotient,remainder);
      quotient.flipSign();
    }

}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt remainder;
  ReallyLongInt quotient;
  x.div(y, quotient, remainder);
  return quotient;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt remainder;
  ReallyLongInt quotient;
  x.div(y, quotient, remainder);
  return remainder;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
  ReallyLongInt remainder;
  ReallyLongInt quotient;
  this->div(other, quotient, remainder);
  *this = quotient;
  return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
  ReallyLongInt remainder;
  ReallyLongInt quotient;
  this->div(other, quotient, remainder);
  *this = remainder;
  return *this;
}

long long ReallyLongInt::toLongLong() const
{
  ReallyLongInt max = LLONG_MAX;
  max = max + 1;
  ReallyLongInt answer = *this % max;
  long long fin = 0;
  int k = 0;
  for(int i = answer.numDigits - 1; i >= 0; i--)
    {
      long long power = 1;
      for(int j = 0; j < k; j++)
	{
	  power = power * 10;
	}
      fin = fin + (int(answer.digits[i]) * power);
      k++;
    }
  return fin;
}
