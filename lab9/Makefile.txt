all:
	gcc uni.c -o uni
	./uni /dev/null 5
	./uni /dev/zero 5
	./uni /dev/urandom 5