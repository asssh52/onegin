CXXFLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
	-Wc++14-compat -Wmissing-declarations -Wcast-qual -Wchar-subscripts                             \
	-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal           \
	-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline                   \
	-Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked                     \
	-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
	-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn                         \
	-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default               \
	-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast                    \
	-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing            \
	-Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation             \
	-fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192                  \
	-Wstack-usage=8192 -fsanitize=address -fsanitize=undefined -fPIE -Werror=vla


CXX = clang++
all: main

main: main.o sorting.o structure_text.o print_strings.o process_text.o
	$(CXX) main.o sorting.o structure_text.o print_strings.o process_text.o \
	$(CXXFLAGS) -o main && clear && ./main

main.o: main.cpp myassert.hpp
	$(CXX) -c main.cpp

sorting.o: sorting.cpp sorting.hpp myassert.hpp
	$(CXX) -c sorting.cpp

structuretext.o: structure_text.cpp structure_text.hpp myassert.hpp
	$(CXX) -c structure_text.cpp

printstrings.o: print_strings.cpp print_strings.hpp myassert.hpp
	$(CXX) -c print_strings.cpp

process.o: process_text.cpp process_text.hpp myassert.hpp
	$(CXX) -c process_text.cpp

clean:
	rm -f main.o sorting.o structure_text.o process_text.o print_strings.o main
