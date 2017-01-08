#!bin/bash

ifndef PREFIX
  PREFIX=/usr
endif
CXX := g++
CXXFLAGS := -c -std=c++11  -Wall -Wextra -pedantic
LD := g++
LDFLAGS := -std=gnu++11

NAME := i3gs
SRCDIR := Sources
OBJDIR := Object


OBJ := $(OBJDIR)/Block.o $(OBJDIR)/Manager.o $(OBJDIR)/main.o
EXE := $(NAME)

.PHONY: all clean

all: $(EXE)

clean:
	rm -rf $(OBJDIR)
	rm -f $(EXE) main.o
	

install:
	install -m 755 -D $(EXE) $(DESTDIR)$(PREFIX)/bin/$(EXE)
	install -m 755 -D i3gs.conf $(DESTDIR)$(PREFIX)/share/$(NAME)/i3gs.conf


$(EXE): $(OBJDIR) $(OBJ)
	$(LD) $(OBJ) $(LDFLAGS) -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
