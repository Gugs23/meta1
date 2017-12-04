DEPN = Item.o Mapa.o FileControl.o Solucao.o Ponto.o

OPT = -g

Compile: Greedy ExecInstance SimAnn MemCheck

MemCheck: $(DEPN)
	$(CXX) $(OPT) -o MemCheck MemCheck.cpp $(DEPN)

SimAnn: $(DEPN)
	$(CXX) $(OPT) -o SimAnn simAnn.cpp $(DEPN)

Greedy: $(DEPN)
	$(CXX) $(OPT) -o Greedy Greedy.cpp $(DEPN)

ExecInstance: $(DEPN)
	$(CXX) -o ExecInstance Main.cpp $(DEPN)

%.o: %.cpp %.hpp
	$(CXX) $(OPT) -c $<
clear:
	rm *.o ./ExecInstance ./Greedy ./SimAnn ./MemCheck
