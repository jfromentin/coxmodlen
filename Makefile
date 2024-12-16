ALONE	= bin/coxmodlen_alone
MULTI 	= bin/coxmodlen_multi

CPP	 = g++
CFLAGS	 = -Wno-stringop-overflow -DNDEBUG -O3

EXE 	= $(ALONE) $(MULTI)

all: $(EXE)

obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(ALONE): src/main_alone.cpp
	$(CPP) $(CFLAGS) $^ -pthread -o $@

$(MULTI): src/main_multi.cpp
	$(CPP) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(EXE) obj/*.o
