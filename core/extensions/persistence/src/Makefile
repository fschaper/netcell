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
INCLUDES += -I../../../extlibs/uuid/include
INCLUDES += -I../../../extlibs/xio/include
INCLUDES += -I../../../libraries/oxml/include
INCLUDES += -I../../../extlibs/xsd2cpp/include
INCLUDES += -I../../../extlibs/xerces/include
INCLUDES += -I../../../extlibs/zlib/include
LDFLAGS += -L../../../extlibs/boost/$(LIBDIR)
LDFLAGS += -L../../../libraries/oxml/$(LIBDIR)
LDFLAGS += -L../../../extlibs/zlib/$(LIBDIR)
LDFLAGS += -m32 -fvisibility=hidden -Wl,-Bstatic -loxml -lboost_iostreams-mt -lz -lminizip -Wl,-Bdynamic

TARGET=persistence.so

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

$(TARGET):	precompiled_header.hpp.gch $(OBJS) $(DEPS)  ../../../libraries/oxml/$(LIBDIR)/liboxml.a
	$(CXX) $(OBJS) -shared $(LDFLAGS) -Wl,-soname=$(TARGET) -o $(TARGET)

precompiled_header.hpp.gch: precompiled_header.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -x c++-header -c precompiled_header.hpp -o precompiled_header.hpp.gch

../../../libraries/oxml/$(LIBDIR)/liboxml.a:
	$(MAKE) -C ../../../libraries/oxml/src

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
