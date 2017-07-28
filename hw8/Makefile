BINDIR = build

all: $(BINDIR)/p_3_11_4 $(BINDIR)/p_3_11_7 #$(BINDIR)/p_3_11_9

$(BINDIR)/p_% : p_%.cpp
	clang++ -std=c++14 -stdlib=libc++ $^ -o $@

$(BINDIR)/p_3_11_7 : p_3_11_7.cpp stack.cpp
	clang++ -std=c++14 -stdlib=libc++ $^ -o $@

# may need to add -Weverything flag or similar at some point

clean:
	rm $(BINDIR)/*