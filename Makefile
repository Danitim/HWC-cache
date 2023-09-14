FLAGS = -O2
SOURCES_COMP = LIRS_Cache/stack_implementation.cpp LIRS_Cache/lirs_algorithm.cpp LIRS_Cache/lirs_file_read.cpp Ideal_Cache/ideal_cache.cpp
SOURCES_IDEAL = Ideal_Cache/ideal_cache.cpp
SOURCES_LIRS = LIRS_Cache/stack_implementation.cpp LIRS_Cache/lirs_algorithm.cpp
DEPS =

all: ideal LIRS comparator


ideal: Ideal_Cache/ideal_cache_console.cpp $(SOURCES_IDEAL)
	g++ $(FLAGS) -o ./ideal Ideal_Cache/ideal_cache_console.cpp $(SOURCES_IDEAL) $(DEPS)

LIRS: LIRS_Cache/lirs_main.cpp $(SOURCES_LIRS)
	g++ $(FLAGS) -o ./LIRS LIRS_Cache/lirs_main.cpp $(SOURCES_LIRS) $(DEPS)

comparator: comparator.cpp $(SOURCES_COMP)
	g++ $(FLAGS) -o ./compare comparator.cpp $(SOURCES_COMP) $(DEPS)

