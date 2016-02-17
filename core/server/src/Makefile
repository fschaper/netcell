#
# Linux Makefile
#
# Author:
# Radu Racariu <radu@yalos-solutions.com>
# Florian Schaper <florian.schaper@jedox.com>
# Jedox AG, Freiburg, Germany
#

include ../../Makefile.inc
INCLUDES := -I.
INCLUDES += -I../include
INCLUDES += -I../../extensions/memory/include
INCLUDES += -I../../extlibs/boost/include
INCLUDES += -I../../extensions/memory/include
INCLUDES += -I../../extlibs/atomic/include

INCLUDES += -I../../extlibs/icu/include
INCLUDES += -I../../extlibs/xsd2cpp/include
INCLUDES += -I../../extlibs/xerces/include
INCLUDES += -I../../libraries/oxml/include

LDFLAGS += -lboost_thread-mt
LDFLAGS += -lboost_regex-mt
LDFLAGS += -lboost_system-mt
LDFLAGS += -lboost_date_time-mt
LDFLAGS += -lboost_filesystem-mt
LDFLAGS += -lboost_program_options-mt
LDFLAGS += -lboost_signals-mt
LDFLAGS += -lxerces-c-3.0
LDFLAGS += -licuuc
LDFLAGS += -licudata
LDFLAGS += -ldl
LDFLAGS += -L../../extlibs/boost/$(LIBDIR) -L../../extlibs/xerces/$(LIBDIR) -L../../extlibs/icu/$(LIBDIR)
LDFLAGS += -export-dynamic

TARGET=core.bin

all:	$(TARGET)
ifeq ($(BUILD_MODE), release)
	strip -s $(TARGET)
endif

ifneq "$(filter clean,$(MAKECMDGOALS))" "clean"
    -include $(DEPS)
endif

_MKDIRS := $(shell \
		test -d ./obj || mkdir ./obj; \
		test -d ./dep || mkdir ./dep )

$(TARGET):	precompiled_header.hpp.gch $(OBJS) $(DEPS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

precompiled_header.hpp.gch:
	$(shell ../bin/update_version_number.sh)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -x c++-header -c precompiled_header.hpp -o precompiled_header.hpp.gch

./obj/%.o:	%.cpp precompiled_header.hpp.gch
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

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
	$(RM) $(TARGET)
	$(RM) *.gch
	$(RM) -R ./dep