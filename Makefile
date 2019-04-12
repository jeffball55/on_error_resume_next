
all: lib test login

login:
	gcc login.c -o login -fno-stack-protector
test:
	gcc test.c -o test
lib:
	gcc -c -fPIC oern.c -o oern.o    
	gcc -shared -Wl,-soname,liboern.so -o liboern.so oern.o
clean:
	rm -f liboern.so oern.o login test
