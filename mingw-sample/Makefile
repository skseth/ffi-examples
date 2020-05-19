ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q /F
    RRM = cmd /C rmdir /Q /S
else
    RM = rm -f
    RRM = rm -f -r
endif

%.o: %.c
	gcc -c -o $@ $<

add.o: add.c
	gcc -c -o $@ $< -D ADD_EXPORTS

# -s : strip symbols --subsystem - needed for windows dlls
add.dll: add.o
	gcc -o $@ -s -shared $< -Wl,--subsystem,windows 

# -s : strip symbols --subsystem - needed for windows dlls
addtest.exe: addtest.o
	gcc -o $@ -s $< -L. -ladd

.PHONY: all
all: add.dll addtest.exe

.PHONY: clean
clean:
	$(RM) *.dll
	$(RM) *.o
	$(RM) *.exe

