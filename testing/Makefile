CC = /usr/bin/gcc
CXX = /usr/bin/g++ --std=c++14

CPPFLAGS += -isystem $(GTEST_DIR)/include
LDFLAGS := -L/usr/lib -lpthread -lgtest -lgmock

all :
	$(CXX) -o run_tests $(CPPFLAGS) ./main.cpp ./test.cpp ./datastorage.cpp $(LDFLAGS)
