all: hello_usdt

hello_usdt: hello_usdt.c
	gcc -g -o hello_usdt hello_usdt.c

clean:
	rm hello_usdt
