GPP=g++
EXTRACT=git log
GPPFLAGS=-std=c++11
OBJECTS=log.txt
DRIVER=test.cpp
EXE=test.exe

%.txt :
	$(EXTRACT) > log.txt

gcc0 : $(OBJECTS)
	$(GPP) -o $(EXE) $(DRIVER) $(GPPFLAGS)
	./$(EXE)

.PHONY: clean

clean:
	rm -f *.exe *.o *.txt
  