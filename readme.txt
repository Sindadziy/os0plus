�������裺
	
1�����նˣ������ļ���·����cd���ļ���Ŀ¼�£�Linux�����ļ�����ǰ�ӡ�/����������Ϊhome�ļ��У�����cd /home
	
2������./compile.sh,��Դ������б���
	��������gcc -run.c -o run.o -lpthread�� ����Ϊ�����pthread.hͷ�ļ���ԭָ������-lpthread
3������./run.sh +���������г�������./run.sh customer.txt orders.txt lineitem.txt 2 BUILDING 1995-02-29 1995-04-27 10 BUILDING 1995-03-28 1995-04-27 2

����ʱ��'$@'���д��Ρ�


ps����compile.sh��run.shȨ�޲���������chmod 777 compile.sh��chmod 777 run.sh����Ȩ�ޡ�����ʽΪ��chmod 777 +'shell�ļ���'��