/*
$ sudo apt install systemtap-sdt-dev


$ make
$ readelf -n hello_usdt
Displaying notes found in: .note.stapsdt
  Owner                 Data size       Description
  stapsdt              0x00000027       NT_STAPSDT (SystemTap probe descriptors)
    Provider: hello_usdt
    Name: hi
    Location: 0x0000000000001129, Base: 0x0000000000002004, Semaphore: 0x0000000000000000
    Arguments:


$ perf buildid-cache --add ./hello_usdt # 导入其中的 sdt events
$ perf list | grep sdt_hello_usd
  sdt_hello_usdt:hi                                  [SDT event]
$ sudo perf probe sdt_hello_usdt:hi # 使用 sdt events 添加 probe
$ sudo perf probe -vx /home/zhulei/workspace/linux-perf-playground/hello_usdt main # 使用函数名添加 uprobe
$ sudo perf probe -l # 查看已启用的 probes
  probe_hello_usdt:main (on main@hello_usdt.c in /home/zhulei/workspace/linux-perf-playground/hello_usdt)
  sdt_hello_usdt:hi    (on main:1@hello_usdt.c in /home/zhulei/workspace/linux-perf-playground/hello_usdt)


$ sudo perf record -e sdt_hello_usdt:hi ./hello_usdt # 执行示例程序并采样
hi
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.022 MB perf.data (1 samples) ]
$ sudo perf script # 显示采样结果
      hello_usdt 25473 [000]  6590.643780: sdt_hello_usdt:hi: (555607111139)


$ sudo perf record -e sdt_hello_usdt:hi -g ./hello_usdt # 加上触发消息时的调用栈数据
hi
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.022 MB perf.data (1 samples) ]
zhulei@zhulei-omv:~/workspace/linux-perf-playground$ sudo perf script
hello_usdt 25988 [002]  6809.337687: sdt_hello_usdt:hi: (563818511139)
            563818511139 main+0x4 (/home/zhulei/workspace/linux-perf-playground/hello_usdt)                        ▒
            7f35c392009b __libc_start_main+0xeb (/usr/lib/x86_64-linux-gnu/libc-2.28.so)
        41fd89415541f689 [unknown] ([unknown])

$ sudo perf record -e "{probe_hello_usdt:main,sdt_hello_usdt:hi}" -g ./hello_usdt # 记录一组消息
hi
[ perf record: Woken up 1 times to write data ]
[ perf record: Captured and wrote 0.023 MB perf.data (2 samples) ]
zhulei@zhulei-omv:~/workspace/linux-perf-playground$ sudo perf script
hello_usdt 26872 [001]  7207.380659: probe_hello_usdt:main: (560025c30135)
            560025c30135 main+0x0 (/home/zhulei/workspace/linux-perf-playground/hello_usdt)
        41fd89415541f689 [unknown] ([unknown])

hello_usdt 26872 [001]  7207.380666:     sdt_hello_usdt:hi: (560025c30139)
            560025c30139 main+0x4 (/home/zhulei/workspace/linux-perf-playground/hello_usdt)
            7fcb9ac5c09b __libc_start_main+0xeb (/usr/lib/x86_64-linux-gnu/libc-2.28.so)
        41fd89415541f689 [unknown] ([unknown])
 */

#include <sys/sdt.h>
#include <stdio.h>

int main() {
	DTRACE_PROBE(hello_usdt, hi);
	printf("hi\n");
	return 0;
}
