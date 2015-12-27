

all: bin/test_pam


bin/test_pam: src/test_pam.c
	mkdir -p bin
	gcc -o bin/test_pam src/test_pam.c -lpam -lpam_misc

