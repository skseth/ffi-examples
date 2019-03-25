


BUILD_DIR = $(realpath rust)/target
TEMP_DIR = $(BUILD_DIR)/temp
LIB_DIR = $(BUILD_DIR)/lib
CLASS_DIR = rust
	
dir_guard=@mkdir -p $(@D)

$(CLASS_DIR)/helloWorld.class: java/helloWorld.java
	@javac java/helloWorld.java -d $(@D)

$(TEMP_DIR)/hello_world.o: cpp/hello_world.cpp
	$(dir_guard)
	@g++ -std=c++11   \
	-I /usr/lib/jvm/java-8-openjdk-amd64/include/ \
	-I /usr/lib/jvm/java-8-openjdk-amd64/include/linux/ \
	-L /usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/ \
	-c cpp/hello_world.cpp -o $@ \
	-ljvm 

$(LIB_DIR)/libhellocpp.a: $(TEMP_DIR)/hello_world.o
	$(dir_guard)
	@ar rc $@ $(TEMP_DIR)/hello_world.o

$(LIB_DIR)/libhellogo.so: golang/hello_world.go
	$(dir_guard)
	@go build -o $@ -buildmode=c-shared golang/hello_world.go

build: $(LIB_DIR)/libhellocpp.a $(CLASS_DIR)/helloWorld.class $(LIB_DIR)/libhellogo.so

run: build
	@cd rust && \
	LD_LIBRARY_PATH=/usr/lib/jvm/java-8-openjdk-amd64/jre/lib/amd64/server/:$(LIB_DIR) \
	cargo run 

clean:
	@rm -rf $(BUILD_DIR)
	@rm $(CLASS_DIR)/helloWorld.class || true
