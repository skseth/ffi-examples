ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q /F
    RRM = cmd /C rmdir /Q /S
	CC = gcc
	CXX = g++
	EXT = .exe
	OUT = out/win
else
    RM = rm -f
    RRM = rm -f -r
	EXT = 
	OUT = out/mac
endif


CFLAGS = -Og -ggdb -Wall
CXXFLAGS = $(CFLAGS) -std=c++11
AES256_KEY = 603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4

.PHONY: clean all

all: $(OUT)/aes_test$(EXT)

$(OUT)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT)/aes_whitebox.o: aes_whitebox.cc aes_whitebox_tables.cc
	$(CXX) $(CXXFLAGS) -c aes_whitebox.cc -o $@

$(OUT)/aes_test$(EXT): $(OUT)/aes_test.o $(OUT)/aes_whitebox.o
	$(CC) $(LDFLAGS) $(OUT)/aes_whitebox.o $(OUT)/aes_test.o -o $@

clean:
	$(RM) $(OUT)/*
