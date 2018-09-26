GPP=g++
EXTRACT=git log --all
GPPFLAGS=-std=c++11
OBJECTS=log.txt
DRIVER=test3.cpp
EXE=test.exe
START_DATE=2018 Jan 10
END_DATE=2018 Jan 15

%.txt :
	$(EXTRACT) > log.txt

gcc0 : $(OBJECTS)
	$(GPP) -o $(EXE) $(DRIVER) $(GPPFLAGS)
	./$(EXE) $(START_DATE) $(END_DATE)

.PHONY: clean

clean:
	rm -f *.exe *.o *.txt
  