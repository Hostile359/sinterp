compile_flags = -g3 -O0 -Wall -Werror -std=c99

./bin/sinterp : ./build/main.o ./build/lex.o ./build/func.o
		gcc $(compile_flags) -o ./bin/sinterp ./build/main.o ./build/lex.o ./build/func.o

./build/main.o : ./src/main.c
		gcc $(compile_flags) -o build/main.o -c src/main.c

./build/lex.o : ./src/lex.c
		gcc $(compile_flags) -o build/lex.o -c src/lex.c

./build/func.o : ./src/func.c
		gcc $(compile_flags) -o build/func.o -c src/func.c

.PHONY: clean adddir open gdb
adddir :
		mkdir build bin
clean :
		rm -rf ./build/ ./bin/
open :
		./bin/sinterp script.txt
gdb :
		gdb ./bin/sinterp script.txt
