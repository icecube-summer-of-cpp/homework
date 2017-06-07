CXX= g++
#CXXFLAGS= -O3 -DNDEBUG -std=c++0x # Release
CXXFLAGS= -O0 -g -std=c++0x # Debug 

all: excercise_1_10_1 excercise_1_10_2 excercise_1_10_3

.PHONY: clean

clean:
	rm -rf excercise_1_10_1.o excercise_1_10_2.o excercise_1_10_3.o excercise_1_10_1 excercise_1_10_2 excercise_1_10_3 age.txt

excercise_1_10_1: excercise_1_10_1.o
	${CXX} ${CXXFLAGS} $^ -o $@

excercise_1_10_2: excercise_1_10_2.o
	${CXX} ${CXXFLAGS} $^ -o $@
	
excercise_1_10_3: excercise_1_10_3.o
	${CXX} ${CXXFLAGS} $^ -o $@
	
%.o: %.cpp
	${CXX} ${CXXFLAGS} $^ -c -o $@
