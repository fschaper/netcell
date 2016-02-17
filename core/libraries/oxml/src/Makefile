# Makefile for oxml
include ../../../Makefile.inc
SRCDIR := .

SOURCES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SOURCES))

TARGET_DIR := ../lib/$(OS)/$(ARCH)

EXTLIBS := ../../../extlibs


INCLUDES := -I$(EXTLIBS)/xsd2cpp/include -I$(EXTLIBS)/xerces/include -I../include/oxml -I$(EXTLIBS)/boost/include

CXXFLAGS += -fPIC -c $(INCLUDES)

.PHONY: all

all: $(TARGET_DIR)/liboxml.a

$(TARGET_DIR)/liboxml.a: $(OBJS)
	$(AR) rcs $(TARGET_DIR)/liboxml.a *.o

%.cpp: 
	$(CPP) $(INCLUDES) $(CXXFLAGS) $(DEFS) $< -o $@

clean:
	$(RM) *.o
	$(RM) $(TARGET_DIR)/liboxml.a

