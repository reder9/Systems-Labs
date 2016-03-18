CFLAGS = -O
CXXFLAGS = -O

CLIBS =  -L . -lblas -lgfortran -lm
CXXLIBS = -L . -lblas -lgfortran

PROGRAM = blas_main
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

c : libblas.a
	$(CC) $(CFLAGS) -o $(PROGRAM)_c $(PROGRAM).c $(CLIBS)
	@echo "$(PROGRAM)_c built"

cpp : libblas.a
	$(CXX) $(CXXFLAGS) -o $(PROGRAM)_cpp $(PROGRAM).cpp $(CXXLIBS)
	@echo "$(PROGRAM)_cpp built"

libblas.a :
	./mkblas_libs

clean:
	rm -f $(PROGRAM)_c $(PROGRAM)_cpp

veryclean :
	rm -f $(PROGRAM)_c $(PROGRAM)_cpp libblas.a
