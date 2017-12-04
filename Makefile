Compile : THOPG THOP THOPSA COMP sub-make

THOPG: THOPG.cpp sub-make
	g++ -o THOPG THOPG.cpp
	
THOP: THOPFILE.cpp sub-make
	g++ -o THOP THOPFILE.cpp

THOPSA: THOPSA.cpp sub-make
	g++ -o THOPSA THOPSA.cpp

COMP: COMP.cpp sub-make
	g++ -o COMP COMP.cpp

sub-make:
	$(MAKE) -C Class/
	
clear:
	rm Class/*.o Class/ExecInstance ./THOP ./THOPG ./THOPSA ./COMP
