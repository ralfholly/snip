
ifneq ("$(MAKECMDGOALS)", "clean")
ifeq ("$(GOOGLE_TEST_HOME)", "")
$(error "Please define GOOGLE_TEST_HOME, ie. `make GOOGLE_TEST_HOME=~/googletest-release-1.8.0'")
endif
endif

GMOCK_INCLUDE_PATH = $(GOOGLE_TEST_HOME)/googlemock
GTEST_INCLUDE_PATH = $(GOOGLE_TEST_HOME)/googletest

GMOCK_LIBRARY_PATH = $(GOOGLE_TEST_HOME)/googlemock
GTEST_LIBRARY_PATH = $(GOOGLE_TEST_HOME)/googlemock/gtest

# 'override' allows you to pass in extra flags when invoking `make', ie.
# make CPPFLAGS=-std=c++14
override CPPFLAGS += -W -Wconversion -Wall -g -pthread -I . -I $(GTEST_INCLUDE_PATH)/include -I $(GMOCK_INCLUDE_PATH)/include
override LDFLAGS += -L$(GTEST_LIBRARY_PATH) -L$(GMOCK_LIBRARY_PATH)
override LDLIBS += -lgtest_main -lgtest -lgmock -lpthread -lstdc++

.PHONY : all clean

all: test

test/snip.o: snip.h

test/snip: test/snip.o

test: test/snip
	./$<

clean:
	( cd test; rm -rf *.o snip )
