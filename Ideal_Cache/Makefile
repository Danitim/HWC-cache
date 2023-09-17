FLAGS = -O2
SOURCES = ideal_cache.cpp
DEPS =

all: console test

console: ideal_cache_console.cpp $(SOURCES)
	g++ $(FLAGS) -o ./icache ideal_cache_console.cpp $(SOURCES) $(DEPS)

test: ideal_cache_test.cpp $(SOURCES)
	g++ $(FLAGS) -o ./test ideal_cache_test.cpp $(SOURCES) $(DEPS)