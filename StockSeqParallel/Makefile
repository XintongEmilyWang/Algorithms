CXX=icpc
#BITS=-m64
INCLUDES=-I.
CXXFLAGS=-O2 $(INCLUDES) $(BITS)

# If you are using a version of binutils prior to 2.17, 
# uncomment following line to work around a known issue. 
# please reference the Release Notes for more information. 
LIBS = -lcilkrts
#LIBS= -lcilkrts /opt/cilk/lib64/libcilkrts.so

PROGS=Stocks

all:: $(PROGS)

Stocks: Stocks.o StocksResult.o StocksSupport.o Timer.o
	$(CXX) $(BITS) -o $@ Stocks.o $(LIBS)

clean::
	-rm -f $(PROGS) *.o
