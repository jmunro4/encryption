OPTS = -Wall

all: encrypt.cc decrypt.cc keygen.cc ReallyLongInt.o numberTheory.h
	 g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o
	 g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o
	 g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

encrypt: encrypt.cc ReallyLongInt.o numberTheory.h 
	 g++ ${OPTS} -o encrypt encrypt.cc ReallyLongInt.o

decrypt: decrypt.cc ReallyLongInt.o numberTheory.h
	 g++ ${OPTS} -o decrypt decrypt.cc ReallyLongInt.o

keygen: keygen.cc ReallyLongInt.o numberTheory.h
	g++ ${OPTS} -o keygen keygen.cc ReallyLongInt.o

ReallyLongInt.o: ReallyLongInt.cc ReallyLongInt.h
	g++ ${OPTS} -c ReallyLongInt.cc

clean:
	rm *.o
	rm encrypt
	rm decrypt
	rm keygen	

cleanemacs:
	rm *~

