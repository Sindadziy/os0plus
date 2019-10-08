操作步骤：
	
1、打开终端，根据文件夹路径，cd到文件夹目录下（Linux里在文件夹名前加‘/’）。本例为home文件夹，即：cd /home
	
2、输入./compile.sh,对源程序进行编译
	（即运行gcc -run.c -o run.o -lpthread） 其中为了添加pthread.h头文件在原指令后添加-lpthread
3、输入./run.sh +参数，运行程序。例如./run.sh customer.txt orders.txt lineitem.txt 2 BUILDING 1995-02-29 1995-04-27 10 BUILDING 1995-03-28 1995-04-27 2

传参时用'$@'进行传参。


ps：若compile.sh或run.sh权限不够，输入chmod 777 compile.sh或chmod 777 run.sh赋予权限。（格式为：chmod 777 +'shell文件名'）