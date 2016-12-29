#!bin/bash

CXX := g++
CXXFLAGS := -c -std=c++11  -Wall -Wextra -pedantic
LD := g++
LDFLAGS := -std=gnu++11

NAME := i3gs
SRCDIR := Sources
OBJDIR := Object
DESTDIR = /usr/bin

OBJ := $(OBJDIR)/Block.o $(OBJDIR)/Manager.o $(OBJDIR)/main.o
EXE := $(NAME)

.PHONY: all clean

all: $(EXE)

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXE) main.o
install: all
	cp -f $(EXE) $(DESTDIR)
	@echo "Application has been installed!"

$(EXE): $(OBJDIR) $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
