CXX=icpc
#BITS=-m64
INCLUDES=-I.
CXXFLAGS=-O2 $(INCLUDES) $(BITS)

# If you are using a version of binutils prior to 2.17, 
# uncomment following line to work around a known issue. 
# please reference the Release Notes for more information. 
LIBS = -lcilkrts

PROGS=ClosestPair

all:: $(PROGS)


ClosestPair: clean ClosestPair.o PairResult.o PointArray.o Point.o Timer.o 
	$(CXX) $(BITS) -o $@ ClosestPair.o $(LIBS)

clean::
	-rm -f $(PROGS) *.o

