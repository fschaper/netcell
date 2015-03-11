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
INCLUDES += -I../../../libraries/oxml/include
INCLUDES += -I../../../extlibs/xsd2cpp/include
INCLUDES += -I../../../extlibs/xerces/include
LDFLAGS += -fvisibility=hidden

TARGET=cell_format.so

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

$(TARGET):	$(OBJS) $(DEPS)
	$(CXX) $(OBJS) -shared $(LDFLAGS) -Wl,-soname=$(TARGET) -o $(TARGET)


./obj/%.o:	%.cpp
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
