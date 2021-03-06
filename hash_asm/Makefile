CPP=g++

CPPFLAGS=-c -pg -O1

ALLCOMPFLAGS=-g -std=c++14 -Werror -fmax-errors=1 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -finput-charset=CP1251 -fexec-charset=UTF-8 -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -fchkp-first-field-has-own-bounds -fchkp-narrow-to-innermost-array -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr


hash_table: main.o hash_asm.o list.o enc.o
	$(CPP) -pg -O0 -Wall main.o list.o enc.o hash_asm.o -o hash_table

copy: hash_table
	cp hash_table ../


0: hash_table
	./hash_table > /dev/null

1: main.o list.o enc.o
	$(CPP) -pg -O0 -Wall main.o list.o enc.o hash_asm1.cpp -o hash_table
	./hash_table > /dev/null

2: main.o list.o enc.o
	$(CPP) -pg -O0 -Wall main.o list.o enc.o hash_asm2.cpp -o hash_table
	./hash_table > /dev/null

asm: main.o list.o enc.o search_asm.o hash_asm.o
	$(CPP) -O1 main.o list.o enc.o hash_asm.o search_asm.o -o hash_table
	./hash_table > /dev/null



profile: hash_table
	gprof ./hash_table > profile
	vim profile

valgrind: hash_table
	valgrind --tool=callgrind ./hash_table > /dev/null


main.o: main.cpp
	$(CPP) $(CPPFLAGS) main.cpp

list.o: list/list.cpp
	$(CPP) $(CPPFLAGS) list/list.cpp

enc.o: ../../1_sem/make_enc/enc.cpp
	$(CPP) $(CPPFLAGS) ../../1_sem/make_enc/enc.cpp

hash_asm.o: hash_asm.cpp
	$(CPP) $(CPPFLAGS) hash_asm.cpp

search_asm.o: search_asm.s
	nasm -felf64 search_asm.s



clean:
	rm -rf *.o
