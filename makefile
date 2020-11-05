# 
# This file was slightly modified from:
# https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
#

CC := g++ -std=c++20

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

TARGET := $(TARGETDIR)/executable
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB := #-lm
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGETDIR)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Tests
tester: $(OBJECTS)
	$(CC) $(filter-out build/main.o, $(^)) $(CFLAGS) test/tester.cpp $(LIB) -o bin/tester

.PHONY: clean

clean:
	@echo " $(OBJECTS)"
	@echo " $(BUILDDIR)/%.o"
	@echo " Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGETDIR)"; $(RM) -r $(BUILDDIR) $(TARGETDIR)
