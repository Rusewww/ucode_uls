all: uls clean

uls: obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic obj/*.o -o uls -I inc

obj: src/*.c inc/*.h
	@mkdir -p obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c src/*.c -I inc
	@mv *.o obj

clean:
	@rm -rf obj

uninstall: clean
	@rm -f uls
	@make -C libmx uninstall

reinstall: uninstall all
