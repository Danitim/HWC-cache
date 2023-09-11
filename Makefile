FLAGS = -O2
SOURCES = LIRS_Cache/stack_implementation.cpp LIRS_Cache/lirs_algorithm.cpp LIRS_Cache/lirs_file_read.cpp Ideal_Cache/ideal_cache.cpp
DEPS =

comparator: comparator.cpp $(SOURCES)
	g++ $(FLAGS) -o ./compare comparator.cpp $(SOURCES) $(DEPS)