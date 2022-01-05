all: uls

uls: libmx.a obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -I inc obj/*.o libmx/libmx.a -o uls

obj: ../clone/src ../clone/inc
	@mkdir -p obj
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic -I inc -c src/*.c
	@mv *.o obj

libmx.a: libmx/src/*.c libmx/inc/*.h
	@make -C libmx

clean:
	@rm -rf obj
	@make -C libmx clean

uninstall: clean
	@rm -f uls
	@make -C libmx uninstall

reinstall: uninstall all
