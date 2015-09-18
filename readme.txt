参考：http://www.oschina.net/code/snippet_160554_5055

调试嵌入式Linux内核时，可能需要查看某个内核变量的值，/dev/kmem正好提供了访问内核虚拟内存的途径。现在的内核大都默认禁用了/dev/kmem，打开的方法是在 make menuconfig中选中 device drivers --> Character devices -->/dev/kmem virtual device support.
用 cat /proc/kallsyms | grep *** 找到要查看的变量的地址， 这个地址作为本程序的输入参数。
