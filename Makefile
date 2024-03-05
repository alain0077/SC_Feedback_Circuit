PROGNAME := Feedback
SRCDIR := src
OUTDIR := obj
TARGET := bin/$(PROGNAME)
SRCS := $(shell find $(SRCDIR) -name *.cpp) #$(wildcard $(SRCDIR)/*.cpp)
# OBJS := $(addprefix $(OUTDIR)/,$(SRCS:.cpp=.o))
OBJS := $(subst $(SRCDIR),$(OUTDIR),$(SRCS:.cpp=.o))
# $(warning $(OBJS))
DEPENDS := $(OBJS:.o=.d)
#$(warning $(DEPENDS))

CC 			:= g++
CFLAGS 	:= -std=c++17 -Wall -Wno-missing-field-initializers -O2 -pthread -MMD -MP
LIBS 		:=
INCLUDE := -I./inc

.PHONY: all clean re
all: $(TARGET)
	@if [ ! -e $(@D) ]; then mkdir -p $(@D); fi
	@if [ ! -e $(OUTDIR) ]; then mkdir -p $(OUTDIR); fi
	@if [ ! -e rst ]; then mkdir -p rst; fi

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	@if [ ! -e $(@D) ]; then mkdir -p $(@D); fi
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

clean:
	rm -r $(OUTDIR)

re : clean all

-include $(DEPENDS)