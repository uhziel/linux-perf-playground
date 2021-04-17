/*
 * $ perf buildid-cache --add ./task_interval
 * $ sudo perf probe sdt_task_interval:enter_task
 * $ sudo perf probe sdt_task_interval:leave_task
 * 
 * $ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -g ./task_interval
 * $ sudo perf record -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -ga
 * $ sudo perf stat -e "{sdt_task_interval:enter_task,sdt_task_interval:leave_task}" -g ./task_interval # 统计接受到的消息总数
 * task 1
 * task 2
 * task 3
 * task 4
 * task 5
 * task 6
 * ^C./task_interval: Interrupt
 * 
 *  Performance counter stats for './task_interval':
 * 
 *                  6      sdt_task_interval:enter_task
 *                  5      sdt_task_interval:leave_task
 * 
 *        5.334456760 seconds time elapsed
 * 
 *        0.002950000 seconds user
 *        0.000000000 seconds sys
 * 
 * $ sudo perf probe -x ./task_interval -V do_task
 * Available variables at do_task
 *         @<do_task+0>
 *                 int     id
 * $ sudo perf probe -x ./task_interval -L do_task
 * <do_task@/home/zhulei/workspace/linux-perf-playground/task_interval.c:0>
 *       0  int do_task(int id) {
 *       1         DTRACE_PROBE1(task_interval, enter_task, id);
 *       2         printf("task %d\n", id);
 *       3         sleep(1);
 *       4         DTRACE_PROBE1(task_interval, leave_task, id);
 *       5  }
 * 
 *          int main() {
 *                 for (int i = 1; ; i++) {
 * # 设置观察点在 do_task 的第二行，并记录此时变量 id 的值
 * $ sudo perf probe -x ./task_interval --add 'do_task:2 id'
 * Added new event:
 *   probe_task_interval:do_task_L2 (on do_task:2 in /home/zhulei/workspace/linux-perf-playground/task_interval with id)
 * 
 * You can now use it in all perf tools, such as:
 * 
 * 	perf record -e probe_task_interval:do_task_L2 -aR sleep 1
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
