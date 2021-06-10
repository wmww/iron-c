example: example.c scope.c utils.c functions.h scope.h utils.h define_EVIL/define_EVIL.h define_EVIL/generated_EVIL.h
	gcc -std=c11 -o example_bin example.c

dump:
	gcc -std=c11 -E example.c
