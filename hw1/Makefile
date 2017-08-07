BINDIR = build

all: $(BINDIR)/p_1_10_1 $(BINDIR)/p_1_10_2 $(BINDIR)/p_1_10_3

$(BINDIR)/p_% : p_%.cpp
	clang++ -std=c++11 -stdlib=libc++ $< -o $@

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*