CFLAGS = -O
CXXFLAGS = -O

CLIBS =  -L . -llibs -lgfortran -lm
CXXLIBS = -L . -llibs -lgfortran

PROGRAM = iter_precond
MAKEFILE = Makefile

FC = g77
CC = gcc
CXX = g++

.f.o : $(FSRC)
	$(FC) $(FFLAGS) -c $<

.c.o : $(CSRC)
	$(CC) $CFFLAGS) -c $<

.cpp.o : $(CXXSRC)
	$(CXX) $(CXXFLAGS) -c $<

all : cpp

cpp : liblibs.a
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(PROGRAM).cpp $(CXXLIBS)
	@echo "$(PROGRAM) built"

liblibs.a :
	./mklibs

clean:
	rm -f $(PROGRAM)

veryclean :
	rm -f $(PROGRAM) liblibs.a
