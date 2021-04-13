all: hello_usdt task_interval

hello_usdt: hello_usdt.c
	gcc -g -o hello_usdt hello_usdt.c

task_interval: task_interval.c
	gcc -g -o task_interval task_interval.c

clean:
	rm hello_usdt task_interval
