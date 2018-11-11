CXXFLAGS = -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -std=c++14
DEBUG = -g -fsanitize=undefined,address

%.o : %.cc
	g++ $(CXXFLAGS) $(DEBUG) $< -o $@

%.exe : %.cc
	g++ $(CXXFLAGS) $< -o $@

clean:
	rm *.o *.exe
