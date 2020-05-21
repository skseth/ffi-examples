

CFLAGS = -Og -ggdb -Wall
CXXFLAGS = $(CFLAGS) -std=c++11

AES256_KEY = 603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4

.PHONY: clean all genkey

all: aes_whitebox_compiler key/aes_whitebox_tables.cc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

aes_whitebox_compiler: aes_whitebox_compiler.o
	$(CXX) $(LDFLAGS) $^ -o $@ -lntl

key/aes_whitebox_tables.cc: aes_whitebox_compiler
	./aes_whitebox_compiler aes256 $(AES256_KEY)

genkey: key/aes_whitebox_tables.cc

clean:
	$(RM) key/aes_whitebox_tables.cc *.o *.a aes_whitebox_compiler
