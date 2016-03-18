CFLAGS = -O
CXXFLAGS = -O

#CLIBS =  -L. -lblas -L. -llinpack -lgfortran -lm
CXXLIBS = -L. -lblas -L. -llinpack -lgfortran 

PROGRAM = iter_main
MAKEFILE = Makefile

#FC = g77
FC = gfortran
#CC = gcc
CXX = g++

#.f.o : $(FSRC)
#	$(FC) $(FFLAGS) -c $<

.c.o : $(CSRC)
	$(CC) $CFFLAGS) -c $<

#.cpp.o : $(CXXSRC)
#	$(CXX) $(CXXFLAGS) -c $<

#all : c cpp

#c : libblas.a
#	$(CC) $(CFLAGS) -o $(PROGRAM)_c $(PROGRAM).c $(CLIBS)
#	@echo "$(PROGRAM) built"

cpp : libblas.a liblinpack.a
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(PROGRAM).cpp $(CXXLIBS)
	@echo "$(PROGRAM) built"

libblas.a :
	./mkblas_libs

liblinpack.a:
	./mklinpack_libs

clean:
#	rm -f $(PROGRAM)_c $(PROGRAM)_cpp
	rm -f $(PROGRAM)

veryclean :
#	rm -f $(PROGRAM)_c $(PROGRAM)_cpp libblas.a
	rm -f $(PROGRAM) libblas.a liblinpack.a
