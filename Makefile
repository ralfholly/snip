
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

test/snip_tests.o: snip.h

test/snip_tests: test/snip_tests.o

test: test/snip_tests
	./$<

# PC-lint Plus MISRA checking.
misra: gcc.lnt
	pclp gcc.lnt ${PCLP_HOME}/lnt/au-misra3.lnt -wlib\(1\) -u snip.c

gcc.lnt:
	python ${PCLP_HOME}/config/pclp_config.py \
	    --compiler-database=${PCLP_HOME}/config/compilers.yaml \
	    --compiler=gcc --compiler-bin=/usr/bin/gcc \
	    --config-output-lnt-file=gcc.lnt \
	    --config-output-header-file=gcc.h \
	    --generate-compiler-config

clean:
	( rm gcc.lnt gcc.h; cd test; rm -rf *.o snip_tests )
