CXX = g++
CXXFLAGS = -std=c++17 `llvm-config-18 --cxxflags` -fexceptions -I./src
LDFLAGS = `llvm-config-18 --ldflags --libs --system-libs`
LEX = flex
YACC = bison

OBJS = src/lexer.yy.o src/parser.tab.o src/semantics.o src/codegen.o src/compiler.o src/main.o
TARGET = novusc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

src/lexer.yy.cpp: src/lexer.l src/parser.tab.hpp
	$(LEX) -o src/lexer.yy.cpp src/lexer.l

src/parser.tab.cpp src/parser.tab.hpp: src/parser.y
	$(YACC) -d -o src/parser.tab.cpp src/parser.y

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/*.yy.cpp src/*.tab.cpp src/*.tab.hpp $(TARGET)
