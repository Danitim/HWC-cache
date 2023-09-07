FLAGS = -O2
SOURCES = idealcache.cpp
DEPS =

all: console test

console: idealcache_console.cpp $(SOURCES)
	g++ $(FLAGS) -o ./icache idealcache_console.cpp $(SOURCES) $(DEPS)

test: idealcache_test.cpp $(SOURCES)
	g++ $(FLAGS) -o ./test idealcache_test.cpp $(SOURCES) $(DEPS)