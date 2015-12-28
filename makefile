

all: bin/test_pam lib/security/pam_lamp.so

install: lib/security/pam_lamp.so
	cp lib/security/pam_lamp.so /lib/security/pam_lamp.so
	cp etc/pam.d/test_lamp /etc/pam.d

uninstall: 
	rm /lib/security/pam_lamp.so
	rm /etc/pam.d/test_lamp

bin/test_pam: src/test_pam.c
	mkdir -p bin
	gcc -o bin/test_pam src/test_pam.c -lpam -lpam_misc

lib/security/pam_lamp.so: src/pam_lamp.o
	mkdir -p lib/security
	gcc -shared -o lib/security/pam_lamp.so src/pam_lamp.o -lpam
	chmod -x lib/security/pam_lamp.so

src/pam_lamp.o: src/pam_lamp.c
	gcc -fPIC -c src/pam_lamp.c -o src/pam_lamp.o
