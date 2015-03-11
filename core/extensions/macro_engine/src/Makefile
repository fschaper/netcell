#
# Linux Makefile
#
# Author:
# Radu Racariu <radu@yalos-solutions.com>
# Florian Schaper <florian.schaper@jedox.com>
# Jedox AG, Freiburg, Germany
#

include ../../../Makefile.inc
INCLUDES := -I.
INCLUDES += -I../include
INCLUDES += -I../../../server/include
INCLUDES += -I../../../extlibs/boost/include
INCLUDES += -I../../../extlibs/atomic/include
INCLUDES += -I../../../extlibs/jlib/include
INCLUDES += -I../../../extlibs/xsd2cpp/include
INCLUDES += -I../../../extlibs/xerces/include
INCLUDES += -I../../../extlibs/icu/include
INCLUDES += -I../../../extlibs/php5.2.13/include/Linux/
INCLUDES += -I../../../extlibs/php5.2.13/include/Linux/Zend
INCLUDES += -I../../../extlibs/php5.2.13/include/Linux/main
INCLUDES += -I../../../extlibs/php5.2.13/include/Linux/TSRM

LDFLAGS += -fvisibility=hidden -L../../../extlibs/php5.2.13/$(LIBDIR) -L../../../extlibs/icu/$(LIBDIR)
LDFLAGS += -lphp5 -licuuc -licui18n
CXXFLAGS += -Wno-write-strings
TARGET=macro_engine.so

ifneq "$(filter clean,$(MAKECMDGOALS))" "clean"
    -include $(DEPS)
endif

_MKDIRS := $(shell \
		test -d ./obj || mkdir ./obj; \
		test -d ./dep || mkdir ./dep )

all:	$(TARGET)
ifeq ($(BUILD_MODE), release)
	strip -s $(TARGET)
endif

$(TARGET):	precompiled_header.hpp.gch $(OBJS) $(DEPS)
	$(CXX) $(OBJS) -shared $(LDFLAGS) -Wl,-soname=$(TARGET) -o $(TARGET)

precompiled_header.hpp.gch: precompiled_header.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -x c++-header -c precompiled_header.hpp -o precompiled_header.hpp.gch

./obj/%.o:	%.cpp precompiled_header.hpp.gch
	$(CXX) -c -fPIC $(CXXFLAGS) $(INCLUDES) $< -o $@

./dep/%.d:	%.cpp
	$(CXX) -MM $(CXXFLAGS) $(INCLUDES) $*.cpp > ./dep/$*.d
	@mv -f ./dep/$*.d ./dep/$*.d.tmp
	@sed -e 's|.*:|./obj/$*.o:|' < ./dep/$*.d.tmp > ./dep/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < ./dep/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> ./dep/$*.d
	@rm -f ./dep/$*.d.tmp

clean:
	$(RM) -R ./obj
	$(RM) *.o
	$(RM) *.so
	$(RM) *.gch
	$(RM) -R ./dep
