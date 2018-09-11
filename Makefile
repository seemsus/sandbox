GPP=g++
EXTRACT=git log --all
GPPFLAGS=-std=c++11
OBJECTS=log.txt
DRIVER=test2.cpp
EXE=test.exe
START_DATE=Sep 7
END_DATE=Sep 10

%.txt :
	$(EXTRACT) > log.txt

gcc0 : $(OBJECTS)
	$(GPP) -o $(EXE) $(DRIVER) $(GPPFLAGS)
	./$(EXE) 

.PHONY: clean

clean:
	rm -f *.exe *.o *.txt
  