BUILD_DIR = out

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

$(OUT_DIR)/libhellogo.$(SOEXT): hello_world.go
	$(dir_guard)
	@go build -o $@ -buildmode=c-shared $<

.PHONY: all clean lib
lib: $(OUT_DIR)/libhellogo.$(SOEXT)

all: lib

clean:
	@$(RM) -rf $(BUILD_DIR)
