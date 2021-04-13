/*

$ perf buildid-cache --add ./task_interval
$ sudo perf probe sdt_task_interval:enter_task
$ sudo perf probe sdt_task_interval:leave_task

$ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -g ./task_interval
$ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -ga
$ sudo perf stat -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -g ./task_interval # 统计接受到的消息总数
task 1
task 2
task 3
task 4
task 5
task 6
^C./task_interval: Interrupt

 Performance counter stats for './task_interval':

                 6      sdt_task_interval:enter_task
                 5      sdt_task_interval:leave_task

       5.334456760 seconds time elapsed

       0.002950000 seconds user
       0.000000000 seconds sys
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
