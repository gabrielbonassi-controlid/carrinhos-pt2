CURR_DIR = $(shell pwd)
INCLUDE_PATH = $(CURR_DIR)/src/include/
SRC_PATH = $(CURR_DIR)/src/source/
OBJS_PATH = $(CURR_DIR)/src/objs/
USER_NAME = $(shell whoami)

CXX = g++ -std=gnu++14
CXXFLAGS = -fmax-errors=2 `pkg-config opencv --libs --cflags` -lcekeikon -lwiringPi -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -O3 -s
CXXFLAGS_X86_64 = -fmax-errors=2 -L/home/$(USER_NAME)/cekeikon5/opencv2cpu/lib -I/home/$(USER_NAME)/cekeikon5/opencv2cpu/include `pkg-config /home/$(USER_NAME)/cekeikon5/opencv2cpu/lib/pkgconfig/opencv.pc --libs --cflags` -lcekeikon2 -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -O3 -s
# Get the system architecture
ARCH := $(shell uname -m)

# If the architecture is x86_64, use the x86_64 flags
ifeq ($(ARCH),x86_64)
    CXXFLAGS = $(CXXFLAGS_X86_64)
endif

OBJS_CAMCLIENT1 = $(OBJS_PATH)device.o $(OBJS_PATH)client.o $(OBJS_PATH)camclient1.o
OBJS_CAMSERVER1 = $(OBJS_PATH)device.o $(OBJS_PATH)server.o $(OBJS_PATH)camserver1.o
OBJS_CAMCLIENT2 = $(OBJS_PATH)device.o $(OBJS_PATH)client.o $(OBJS_PATH)camclient2.o
OBJS_CAMSERVER2 = $(OBJS_PATH)device.o $(OBJS_PATH)server.o $(OBJS_PATH)camserver2.o
OBJS_SERVER1 = $(OBJS_PATH)device.o $(OBJS_PATH)server.o $(OBJS_PATH)server1.o
OBJS_CLIENT1 = $(OBJS_PATH)device.o $(OBJS_PATH)client.o $(OBJS_PATH)client1.o
OBJS_SERVER2 = $(OBJS_PATH)device.o $(OBJS_PATH)server.o $(OBJS_PATH)carrinho.o $(OBJS_PATH)server2.o
OBJS_CLIENT2 = $(OBJS_PATH)device.o $(OBJS_PATH)client.o $(OBJS_PATH)client2.o

all: server client

server: camserver1 camserver2 server1 server2
	@echo "Servidores compilados!"

client: camclient1 camclient2 client1 client2
	@echo "Clientes compilados!"

camclient1: device.o client.o camclient1.o
	$(CXX) $(OBJS_CAMCLIENT1) -o $(CURR_DIR)/$@ $(CXXFLAGS)

camserver1: device.o server.o camserver1.o
	$(CXX) $(OBJS_CAMSERVER1) -o $(CURR_DIR)/$@ $(CXXFLAGS)

camclient2: device.o server.o camclient2.o
	$(CXX) $(OBJS_CAMCLIENT2) -o $(CURR_DIR)/$@ $(CXXFLAGS)

camserver2: device.o server.o camserver2.o
	$(CXX) $(OBJS_CAMSERVER2) -o $(CURR_DIR)/$@ $(CXXFLAGS)

server1: device.o server.o server1.o
	$(CXX) $(OBJS_SERVER1) -o $(CURR_DIR)/$@ $(CXXFLAGS)

client1: device.o client.o client1.o
	$(CXX) $(OBJS_CLIENT1) -o $(CURR_DIR)/$@ $(CXXFLAGS)

server2: device.o server.o carrinho.o server2.o
	$(CXX) $(OBJS_SERVER2) -o $(CURR_DIR)/$@ $(CXXFLAGS)

client2: device.o client.o client2.o
	$(CXX) $(OBJS_CLIENT2) -o $(CURR_DIR)/$@ $(CXXFLAGS)

camclient1.o:
	$(CXX) -c $(SRC_PATH)camclient1.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

camserver1.o:
	$(CXX) -c $(SRC_PATH)camserver1.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

camclient2.o:
	$(CXX) -c $(SRC_PATH)camclient2.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

camserver2.o:
	$(CXX) -c $(SRC_PATH)camserver2.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server1.o:
	$(CXX) -c $(SRC_PATH)server1.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client1.o:
	$(CXX) -c $(SRC_PATH)client1.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server2.o:
	$(CXX) -c $(SRC_PATH)server2.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client2.o:
	$(CXX) -c $(SRC_PATH)client2.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

device.o: $(INCLUDE_PATH)device.hpp $(SRC_PATH)device.cpp
	$(CXX) -c $(SRC_PATH)device.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client.o: $(INCLUDE_PATH)client.hpp $(SRC_PATH)client.cpp
	$(CXX) -c $(SRC_PATH)client.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server.o: $(INCLUDE_PATH)server.hpp $(SRC_PATH)server.cpp
	$(CXX) -c $(SRC_PATH)server.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

carrinho.o: $(INCLUDE_PATH)carrinho.hpp $(SRC_PATH)carrinho.cpp
	$(CXX) -c $(SRC_PATH)carrinho.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS_PATH)*.o camclient1 camclient2 camserver1 camserver2 server1 server2 client1 client2