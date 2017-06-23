build/uniqueid: uniqueid.cpp uniqueid.hpp
	clang++ -std=c++11 -stdlib=libc++ $< -o $@

build/testids: testids.cpp uniqueid.cpp
	clang++ -std=c++11 -stdlib=libc++ $^ -o $@

clean:
	rm build/*