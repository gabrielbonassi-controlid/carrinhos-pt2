CURR_DIR = $(shell pwd)
INCLUDE_PATH = $(CURR_DIR)/src/include/
SRC_PATH = $(CURR_DIR)/src/source/
OBJS_PATH = $(CURR_DIR)/src/objs/
USER_NAME = $(shell whoami)

# arquivos fontes
SRCS = $(wildcard $(SRC_PATH)*.cpp)
# arquivos headers
HEADERS = $(wildcard $(INCLUDE_PATH)*.hpp)
# arquivos objetos
OBJS = $(SRCS:.cpp=.o)
# usando o comando compila do cekeikon
#CXX = compila

# com as flags personalizadas:
#CXXFLAGS = -c -e="-I$(INCLUDE_PATH)"

CXX = g++ -std=gnu++14
CXXFLAGS = -fmax-errors=2 `pkg-config opencv --libs --cflags` -lcekeikon -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -O3 -s
CXXFLAGS_X86_64 = -fmax-errors=2 -L/home/$(USER_NAME)/cekeikon5/opencv2cpu/lib -I/home/$(USER_NAME)/cekeikon5/opencv2cpu/include `pkg-config /home/$(USER_NAME)/cekeikon5/opencv2cpu/lib/pkgconfig/opencv.pc --libs --cflags` -lcekeikon2 -L/home/$(USER_NAME)/cekeikon5/cekeikon/bin -I/home/$(USER_NAME)/cekeikon5/cekeikon/src -I$(INCLUDE_PATH) -O3 -s
# Get the system architecture
ARCH := $(shell uname -m)

# If the architecture is x86_64, use the x86_64 flags
ifeq ($(ARCH),x86_64)
    CXXFLAGS = $(CXXFLAGS_X86_64)
endif

# 6b:
# client:
OBJS_CLIENT6B = $(SRC_PATH)device.o $(SRC_PATH)client.o $(SRC_PATH)client6b.o
SOURCE_CLIENT6B = device.cpp client.cpp client6b.cpp
HEADERS_CLIENT6B = device.hpp client.hpp
# server:
OBJS_SERVER6B = $(SRC_PATH)device.o $(SRC_PATH)server.o $(SRC_PATH)server6b.o
SOURCE_SERVER6B = device.cpp server.cpp server6b.cpp
HEADERS_SERVER6B = device.hpp server.hpp
# 6c:
# client:
OBJS_CLIENT6C = $(SRC_PATH)device.o $(SRC_PATH)client.o $(SRC_PATH)client6c.o
SOURCE_CLIENT6C = device.cpp client.cpp client6c.cpp
HEADERS_CLIENT6C = device.hpp client.hpp
# server:
OBJS_SERVER6C = $(SRC_PATH)device.o $(SRC_PATH)server.o $(SRC_PATH)server6c.o
SOURCE_SERVER6C = device.cpp server.cpp server6c.cpp
HEADERS_SERVER6C = device.hpp server.hpp
# 8:
# client:
OBJS_CLIENT8 = $(SRC_PATH)device.o $(SRC_PATH)client.o $(SRC_PATH)client8.o
SOURCE_CLIENT8 = device.cpp client.cpp client8.cpp
HEADERS_CLIENT8 = device.hpp client.hpp
# server:
OBJS_SERVER8 = $(SRC_PATH)device.o $(SRC_PATH)server.o $(SRC_PATH)server8.o
SOURCE_SERVER8 = device.cpp server.cpp server8.cpp
HEADERS_SERVER8 = device.hpp server.hpp

all: client6b server6b client6c server6c client8 server8

server: server6b server6c server8
	@echo "Servidores compilados!"

client: client6b client6c client8
	@echo "Clientes compilados!"

client6b: $(OBJS_CLIENT6B)
	$(CXX) $(OBJS_CLIENT6B) -o $@ $(CXXFLAGS)

server6b: $(OBJS_SERVER6B)
	$(CXX) $(OBJS_SERVER6B) -o $@ $(CXXFLAGS)

client6c: $(OBJS_CLIENT6C)
	$(CXX) $(OBJS_CLIENT6C) -o $@ $(CXXFLAGS)

server6c: $(OBJS_SERVER6C)
	$(CXX) $(OBJS_SERVER6C) -o $@ $(CXXFLAGS)

client8: $(OBJS_CLIENT8)
	$(CXX) $(OBJS_CLIENT8) -o $@ $(CXXFLAGS)

server8: $(OBJS_SERVER8)
	$(CXX) $(OBJS_SERVER8) -o $@ $(CXXFLAGS)

client6b.o:
	$(CXX) -c $(SRC_PATH)client6b.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server6b.o:
	$(CXX) -c $(SRC_PATH)server6b.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client6c.o:
	$(CXX) -c $(SRC_PATH)client6c.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server6c.o:
	$(CXX) -c $(SRC_PATH)server6c.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client8.o:
	$(CXX) -c $(SRC_PATH)client8.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server8.o:
	$(CXX) -c $(SRC_PATH)server8.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

device.o: $(INCLUDE_PATH)device.hpp $(SRC_PATH)device.cpp
	$(CXX) -c $(SRC_PATH)device.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

client.o: $(INCLUDE_PATH)client.hpp $(SRC_PATH)client.cpp
	$(CXX) -c $(SRC_PATH)client.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

server.o: $(INCLUDE_PATH)server.hpp $(SRC_PATH)server.cpp
	$(CXX) -c $(SRC_PATH)server.cpp -o $(OBJS_PATH)$@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(SRC_PATH)*.o client6b server6b client6c server6c client8 server8