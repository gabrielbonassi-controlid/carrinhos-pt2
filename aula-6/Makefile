CURR_DIR = $(shell pwd)
INCLUDE_PATH = $(CURR_DIR)/src/include/
SRC_PATH = $(CURR_DIR)/src/source/
OBJS_PATH = $(CURR_DIR)/src/objs/
USER_NAME = $(shell whoami)

CXX = g++ -std=gnu++14
CXXFLAGS = -fmax-errors=2 `pkg-config opencv --libs --cflags` -lcekeikon -lwiringPi -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -fopenmp -pthread -O3 -s
CXXFLAGS_X86_64 = -fmax-errors=2 -L/home/$(USER_NAME)/cekeikon5/opencv2cpu/lib -I/home/$(USER_NAME)/cekeikon5/opencv2cpu/include `pkg-config /home/$(USER_NAME)/cekeikon5/opencv2cpu/lib/pkgconfig/opencv.pc --libs --cflags` -lcekeikon2 -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -pthread -fopenmp -O3 -s
# Get the system architecture
ARCH := $(shell uname -m)

# If the architecture is x86_64, use the x86_64 flags
ifeq ($(ARCH),x86_64)
    CXXFLAGS = $(CXXFLAGS_X86_64)
endif

OBJS_SERVER6 = $(OBJS_PATH)device.o $(OBJS_PATH)server.o $(OBJS_PATH)carrinho.o $(OBJS_PATH)server6.o
OBJS_CLIENT6 = $(OBJS_PATH)device.o $(OBJS_PATH)client.o $(OBJS_PATH)gui.o $(OBJS_PATH)client6.o

all: server client

server: server6
	@echo "Servidores compilados!"

client: client6
	@echo "Clientes compilados!"

server6: device.o server.o carrinho.o server6.o
	$(CXX) $(OBJS_SERVER6) -o $(CURR_DIR)/$@ $(CXXFLAGS)

client6: device.o client.o gui.o client6.o
	$(CXX) $(OBJS_CLIENT6) -o $(CURR_DIR)/$@ $(CXXFLAGS)

server6.o:
	$(CXX) -c $(SRC_PATH)server6.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client6.o:
	$(CXX) -c $(SRC_PATH)client6.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

device.o: $(INCLUDE_PATH)device.hpp $(SRC_PATH)device.cpp
	$(CXX) -c $(SRC_PATH)device.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client.o: $(INCLUDE_PATH)client.hpp $(SRC_PATH)client.cpp
	$(CXX) -c $(SRC_PATH)client.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server.o: $(INCLUDE_PATH)server.hpp $(SRC_PATH)server.cpp
	$(CXX) -c $(SRC_PATH)server.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

carrinho.o: $(INCLUDE_PATH)carrinho.hpp $(SRC_PATH)carrinho.cpp
	$(CXX) -c $(SRC_PATH)carrinho.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

gui.o : $(INCLUDE_PATH)gui.hpp $(SRC_PATH)gui.cpp
	$(CXX) -c $(SRC_PATH)gui.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS_PATH)*.o server6 client6