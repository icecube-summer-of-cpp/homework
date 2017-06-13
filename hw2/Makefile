BINDIR = build

all: $(BINDIR)/p_2_8_1# $(BINDIR)/p_2_8_2 $(BINDIR)/p_2_8_3

$(BINDIR)/p_% : p_%.cpp
	clang++ -std=c++11 -stdlib=libc++ $< -o $@

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*