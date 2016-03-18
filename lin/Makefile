FSRC =
FOBJ = 

CSRC = 
COBJ = 

CXXSRC = 
CXXOBJ =

FFLAGS = -O
CFLAGS = -O
CXXFLAGS = -O

CLIBS =  -L . -llibs -lgfortran -lm
CXXLIBS = -L . -llibs -lgfortran

PROGRAM = linpack_demo
MAKEFILE = Makefile

#FC = g77
FC = gfortran
CC = gcc
CXX = g++

.f.o : $(FSRC)
	$(FC) $(FFLAGS) -c $<

.c.o : $(CSRC)
	$(CC) $CFFLAGS) -c $<

.cpp.o : $(CXXSRC)
	$(CXX) $(CXXFLAGS) -c $<

all : c cpp

c : liblibs.a
	$(CC) $(CFLAGS) -o $(PROGRAM)_c $(PROGRAM).c $(CLIBS)
	@echo "$(PROGRAM)_c built"
	@echo

cpp : liblibs.a
	$(CXX) $(CXXFLAGS) -g -o $(PROGRAM)_cpp $(PROGRAM).cpp $(CXXLIBS)
	@echo "$(PROGRAM)_cpp built"
	@echo

liblibs.a :
	./mklibs

clean :
	rm -f liblibs.a

veryclean :
	rm -f $(PROGRAM)_c $(PROGRAM)_cpp liblibs.a
