CUR_DIR = $(shell pwd)
BUILD_DIR = $(CUR_DIR)/out

ifeq ($(OS),Windows_NT)
    RM = cmd /C del /Q /F
    RRM = cmd /C rmdir /Q /S
	OUT_DIR = $(BUILD_DIR)/win
	SOEXT = dll
else
    RM = rm -f
    RRM = rm -f -r
	OUT_DIR = $(BUILD_DIR)/mac
	SOEXT = so
endif

dir_guard=@mkdir -p $(@D)

$(OUT_DIR)/libusertweet.$(SOEXT): cmd/main.go cmd/main_func.c usertweet.go 
	$(dir_guard)
	cd cmd && go build -o $@ -buildmode=c-shared && cd ..

$(OUT_DIR)/usertweet: client/usertweet.c
	$(dir_guard)
	@gcc -I $(OUT_DIR) -o $@ $< -l dl

.PHONY: all clean lib run
lib: $(OUT_DIR)/libusertweet.$(SOEXT) $(OUT_DIR)/usertweet

all: lib

run: $(OUT_DIR)/usertweet
	cd $(OUT_DIR); ./usertweet

clean:
	@$(RM) -rf $(BUILD_DIR)
