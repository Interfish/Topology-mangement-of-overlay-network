objects = EasyBMP.o Topology.o TMAN.o

TMAN : $(objects)
	g++ -o TMAN $(objects)
EasyBMP.o : ./EasyBMP_1.06/EasyBMP.cpp
	g++ -c ./EasyBMP_1.06/EasyBMP.cpp
Topology.o : Topology.cpp
	g++ -c Topology.cpp
TMAN.o : TMAN.cpp
	g++ -c TMAN.cpp
clean : 
	rm $(objects) TMAN
