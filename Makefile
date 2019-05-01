SRC_DIRS := src
C_SRCS := $(foreach srcdir,$(SRC_DIRS),$(wildcard $(srcdir)/*.c))
CXX_SRCS := $(foreach srcdir,$(SRC_DIRS),$(wildcard $(srcdir)/*.cpp))
C_OBJS := ${C_SRCS:.c=.o}
CXX_OBJS := ${CXX_SRCS:.cpp=.o}
OBJS := $(C_OBJS) $(CXX_OBJS)
INCLUDE_DIRS := include
LIBRARY_DIRS :=
LIBRARIES :=

prog_NAME := experiment
prog_DIR := bin
prog_FULL := $(prog_DIR)/$(prog_NAME)
prog_SRC_DIRS := experiment
prog_C_SRCS := $(foreach srcdir,$(prog_SRC_DIRS),$(wildcard $(srcdir)/*.c))
prog_CXX_SRCS := $(foreach srcdir,$(prog_SRC_DIRS),$(wildcard $(srcdir)/*.cpp))
prog_C_OBJS := ${prog_C_SRCS:.c=.o}
prog_CXX_OBJS := ${prog_CXX_SRCS:.cpp=.o}
prog_OBJS := $(prog_C_OBJS) $(prog_CXX_OBJS)
prog_INCLUDE_DIRS :=
prog_LIBRARY_DIRS :=
prog_LIBRARIES :=

test_NAME := test
test_DIR := bin
test_FULL := $(test_DIR)/$(test_NAME)
test_SRC_DIRS := test
test_C_SRCS := $(foreach srcdir,$(test_SRC_DIRS),$(wildcard $(srcdir)/*.c))
test_CXX_SRCS := $(foreach srcdir,$(test_SRC_DIRS),$(wildcard $(srcdir)/*.cpp))
test_C_OBJS := ${test_C_SRCS:.c=.o}
test_CXX_OBJS := ${test_CXX_SRCS:.cpp=.o}
test_OBJS := $(test_C_OBJS) $(test_CXX_OBJS)
test_INCLUDE_DIRS := catch
test_LIBRARY_DIRS :=
test_LIBRARIES :=

all_OBJS := $(OBJS) $(prog_OBJS) $(test_OBJS)
DEP := $(all_OBJS:%.o=%.d)

CXXFLAGS += -std=c++11 -Wall
CXXFLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(LIBRARIES),-l$(library))

.PHONY: test experiment clean

test: CXXFLAGS += $(foreach includedir,$(test_INCLUDE_DIRS),-I$(includedir))
test: LDFLAGS += $(foreach librarydir,$(test_LIBRARY_DIRS),-L$(librarydir))
test: LDFLAGS += $(foreach library,$(test_LIBRARIES),-l$(library))

experiment: CXXFLAGS += $(foreach includedir,$(prog_INCLUDE_DIRS),-I$(includedir))
experiment: LDFLAGS += $(foreach librarydir,$(prog_LIBRARY_DIRS),-L$(librarydir))
experiment: LDFLAGS += $(foreach library,$(prog_LIBRARIES),-l$(library))

test: $(test_FULL)
	./$(test_FULL)

experiment: $(prog_FULL)
	./$(prog_FULL)

lint:
	cpplint --filter=+readability/*,+whitespace/*,-legal/copyright,-build/header_guard,-runtime/int src/*.cpp experiment/*.cpp include/*.h

$(test_FULL): $(test_OBJS) $(OBJS)
	$(LINK.cc) $^ -o $@

$(prog_FULL): $(prog_OBJS) $(OBJS)
	$(LINK.cc) $^ -o $@

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	@- $(RM) $(prog_FULL)
	@- $(RM) $(prog_OBJS)
	@- $(RM) $(test_FULL)
	@- $(RM) $(test_OBJS)
	@- $(RM) $(OBJS)
	@- $(RM) $(DEP)
	rm -rf html/
	rm -rf latex/


doc:
	doxygen doxConfig
