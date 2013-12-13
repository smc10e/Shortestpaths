SHELL = /bin/sh
SRCDIR =$(shell pwd)
INCL = -I $(SRCDIR)
CCO = g++ -o

all: shortestpaths

shortestpaths: $(SRCDIR)/shortestpaths.o
		$(CCO) shortestpaths $(SRCDIR)/shortestpaths.o

shortestpaths.o: $(SRCDIR)/shortestpaths.cpp
	$(CCC) $(INCL) shortestpaths.cpp

clean: 
	rm shortestpaths *.o
