

all: bin/pam_test


bin/pam_test: src/pam_test.c
	mkdir -p bin
	gcc -o bin/pam_test src/pam_test.c -lpam -lpam_misc

