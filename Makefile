FLAGS = -O2
SOURCES = stack_implementation.cpp lirs_algorithm.cpp lirs_file_read.cpp
DEPS =

main: comparator.cpp $(SOURCES)
	g++ $(FLAGS) -o ./compare comparator.cpp $(SOURCES) $(DEPS)