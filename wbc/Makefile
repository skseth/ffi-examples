CFLAGS = -Og -ggdb -Wall
CXXFLAGS = $(CFLAGS) -std=c++11
AES256_KEY = 603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4

.PHONY: clean all

all: aes_whitebox_compiler aes_test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

aes_whitebox_compiler: aes_whitebox_compiler.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lntl

aes_whitebox_tables.cc: aes_whitebox_compiler
	./aes_whitebox_compiler aes256 $(AES256_KEY)

aes_whitebox.o: aes_whitebox.cc aes_whitebox_tables.cc
	$(CXX) $(CXXFLAGS) -c aes_whitebox.cc -o $@

aes_test: aes_test.o aes_whitebox.o
	$(CC) $(LDFLAGS) aes_whitebox.o aes_test.o -o $@

clean:
	rm -f *.o *.a aes_whitebox_tables.cc aes_whitebox_compiler aes_test
