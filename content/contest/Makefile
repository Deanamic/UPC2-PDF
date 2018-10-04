CXXFLAGS = -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -std=c++14
DEBUG = -g -fsanitize=undefined,address

% : %.cc
	g++ $(CXXFLAGS) $(DEBUG) $< -o $@.o
	g++ $(CXXFLAGS) $< -o $@.exe

clean:
	rm *.o *.exe
