BINDIR = build

all: $(BINDIR)/p_6_7_1

$(BINDIR)/p_% : p_%.cpp people.cpp
	clang++ -std=c++11 -stdlib=libc++ $^ -o $@ 

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*