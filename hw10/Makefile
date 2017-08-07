BINDIR = build

all: $(BINDIR)/p_4_8_1 #$(BINDIR)/p_4_8_2

$(BINDIR)/p_% : p_%.cpp
	clang++ -std=c++14 -stdlib=libc++ $^ -o $@

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*