CXX=g++
CXXFLAGS=-O3 -fopenmp
LDFLAGS=-fopenmp -O3

OBJECTS=main.o

removeRuido: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o removeRuido $(OBJECTS)

all:	removeRuido

run:	all
	./removeRuido imagem1.ppm imagem1_out.ppm 5


clean:
	rm -f *.optrpt *.o removeRuido *~ 
