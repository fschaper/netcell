#
# Linux Makefile
#
# Author:
# Radu Racariu <radu@yalos-solutions.com>
# Florian Schaper <florian.schaper@jedox.com>
# Jedox AG, Freiburg, Germany
#

CXX := g++44
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O2 -g -DNDEBUG -Wno-unused-variable
CXXFLAGS := -m32 -Wall -DLINUX -D__UNIX__ -D__unix__ -D_REENTRANT -DBOOST_FILESYSTEM_VERSION=2 -fno-strict-aliasing

ifeq ($(BUILD_TYPE), release)
    CXXFLAGS+=$(RELEASE_FLAGS)
    BUILD_MODE := release
else
    CXXFLAGS+=$(DEBUG_FLAGS)
    BUILD_MODE := debug
    DEPS=$(patsubst %.cpp,./dep/%.d, $(SRCS) )
endif

all:

release:                                                                                                                                                    
	make $(MAKEFILE) BUILD_TYPE="release" all

LDFLAGS := -m32 -lpthread
OS := $(shell uname -s)
#ARCH := $(shell _MAKE_ARCH=`uname -m`; if echo $$_MAKE_ARCH | egrep '^i[356]86$$' > /dev/null; then echo i386; else echo $$_MAKE_ARCH; fi)
ARCH := i386
LIBDIR := lib/$(OS)/$(ARCH)
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,./obj/%.o, $(SRCS) )

CPUS := $(shell cat /proc/cpuinfo | grep processor | wc -l)
MAKE+= -j $(CPUS)
.PHONY : clean