BINDIR = build

all: $(BINDIR)/p_3_11_1 $(BINDIR)/p_3_11_3

$(BINDIR)/p_% : p_%.cpp
	clang++ -std=c++11 -stdlib=libc++ $^ -o $@ 

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*