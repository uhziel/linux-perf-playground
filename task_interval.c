/*

$ perf buildid-cache --add ./task_interval
$ sudo perf probe sdt_task_interval:enter_task
$ sudo perf probe sdt_task_interval:leave_task

$ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -g ./task_interval
$ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -ga
 */

#include <sys/sdt.h>
#include <stdio.h>
#include <unistd.h>

int do_task(int id) {
	DTRACE_PROBE1(task_interval, enter_task, id);
	printf("task %d\n", id);
	sleep(1);
	DTRACE_PROBE1(task_interval, leave_task, id);
}

int main() {
	for (int i = 1; ; i++) {
		do_task(i);
	}
	return 0;
}
