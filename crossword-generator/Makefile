CMP = gcc
FUNC = crossword_functions
MAIN = crossword
HEAD = crossword.h
EXEC = runcrossword

$(EXEC): $(FUNC).o $(MAIN).o
	$(CMP) $(FUNC).o $(MAIN).o -o $(EXEC)

$(FUNC).o: $(FUNC).c $(HEAD)
	$(CMP) -c $(FUNC).c -o $(FUNC).o

$(MAIN).o: $(MAIN).c $(HEAD)
	$(CMP) -c $(MAIN).c -o $(MAIN).o

clean:
	rm -f *.o $(EXEC)

