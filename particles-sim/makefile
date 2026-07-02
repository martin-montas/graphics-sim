SRC_DIR := ./src

CXX := g++
CXXFLAGS := -g -std=c++20  
LDFLAGS := -lSDL2

COMMON_OBJS := main.o particle.o   simulator.o  global.o \

particles: $(COMMON_OBJS)
	$(CXX) $^ -g -o $@ $(LDFLAGS)

# =====================================================
# COMPILATION RULES
# =====================================================
main.o: main.cpp
	$(CXX) -c $< $(CXXFLAGS)

particle.o: src/particle.cpp src/particle.hpp
	$(CXX) -c $< $(CXXFLAGS)

simulator.o: src/simulator.cpp src/simulator.hpp
	$(CXX) -c $< $(CXXFLAGS)


global.o: src/global.cpp src/global.hpp
	$(CXX) -c $< $(CXXFLAGS)

# =====================================================
# UTILITIES
# =====================================================

clean:
	rm -f *.o particles

format:
	find . \( -name "*.cpp" -o -name "*.hpp" \) | \
	xargs clang-format -style=llvm -i

lint:
	cpplint $(shell find . \( -name "*.cpp" -o -name "*.hpp" \))

count:
	find . \( -name "*.cpp" -o -name "*.hpp"  \) | xargs wc -l

t:
	./sm83.sh

