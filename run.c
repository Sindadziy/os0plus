

#include<stdio.h>

#include<string.h>

#include<stdlib.h>

#include<pthread.h>
#define HAVE_STRUCT_TIMESPEC

void* ThreadFuc(void* t);
char** argvs;


typedef struct

{

	int c_custkey;    	   //顾客编号

	char c_mkgsegment[20]; //对应的某个市场部门

}customer;				   //顾客结构体 



typedef struct

{

	int o_orderkey;    	 //订单号 

	int o_custkey;    	 //顾客编号

	char o_orderdate[10];//订货日期 

}orders;				 //订单



typedef struct

{

	int l_orderkey;//订单号

	double l_extendedprice;//额外价格

	char l_shipdate[10];//发货日期 

}lineitem; //商品信息 



typedef struct

{

	int l_orderkey;//订单号

	char o_orderdate[10];//订货日期 

	double l_extendedprice;//额外价格

}select_result;





customer * read_customer_txt() //读取customer。txt内容 

{

	FILE * fp;

	customer *a=NULL;

	a = (customer *)malloc(100*sizeof(customer));

	int i=0;

	char b;

	fp = fopen("/home/customer.txt","r");

	if(NULL==fp)

	{

		printf("error!");

		return NULL;

	}

	while(!feof(fp))

	{	

		//printf("%d  ",i);

		fscanf(fp,"%d%c%s",&a[i].c_custkey,&b,&a[i].c_mkgsegment);

		//printf("%d%c%s\n",a[i].c_custkey,b,a[i].c_mkgsegment);

		i++;

	}

	fclose(fp);

	return a;

}

orders * read_orders_txt()//读取orders.txt内容 

{

	int i =0; 

	orders * a=NULL;

	a = (orders * )malloc(4000*sizeof(orders));

	char b,c;

	long long d;

	FILE *fp;

	fp = fopen("/home/orders.txt","r");

	if(fp == NULL)

	{

		printf("error!");

		return NULL;

	}

	while(!feof(fp))

	{	

		//printf("%d!",i);

		fscanf(fp,"%d%c%lld%c%s",&a[i].o_orderkey,&b,&d,&c,&a[i].o_orderdate);

		a[i].o_custkey=d%100;

		i++;

	}

	fclose(fp);

	return a;

}



lineitem * read_lineitem_txt()//读取lineitem.txt内容

{

	FILE * fp;

	lineitem * l=NULL;

	l = (lineitem *)malloc(1000*sizeof(lineitem));

	int i=0;

	char b,c;

	fp = fopen("/home/lineitem.txt","r");

	if(fp==NULL)

	{

		printf("error!");

		return NULL;

	}

	while(!feof(fp))

	{

		//printf("%d!",i);

		fscanf(fp,"%d%c%lf%c%s",&l[i].l_orderkey,&c,&l[i].l_extendedprice,&b,&l[i].l_shipdate);

		//printf("%d,%lf,%s\n",l[i].l_orderkey,l[i].l_extendedprice,l[i].l_shipdate);

		i++;

	}

	fclose(fp);

	return l; 

}



select_result * select1(customer * cus,orders * ord,lineitem * item,char * order_date,char * ship_date,char * ship_type)

{

	int i,j,k,l=0,m=0;

	select_result * result1=NULL;

	select_result * result2=NULL;

	select_result  temp;

	result1 = (select_result *)malloc(1000*sizeof(select_result));

	result2 = (select_result *)malloc(1000*sizeof(select_result));

	//char ship[]="BUILDING";

	//printf("%s %s\n",order_date,ship_date);

	//printf("%s\n",ship_type);

	for(i=0;i<100;i++)

	{

		if(strcmp(cus[i].c_mkgsegment,ship_type)==0)

		{

		for(j=0;j<4000;j++)

		{

			for(k=0;k<1000;k++)

			if(cus[i].c_custkey==ord[j].o_custkey&&ord[j].o_orderkey==item[k].l_orderkey&&(strcmp(ord[j].o_orderdate,order_date)<0)&&(strcmp(item[k].l_shipdate,ship_date)>0))

			{

				result1[l].l_orderkey=item[k].l_orderkey;

				strcpy(result1[l].o_orderdate,ord[j].o_orderdate);

				result1[l].l_extendedprice=item[k].l_extendedprice;

				l++;

			}

		}

		}

		else continue;

	}

	/*printf("求和\n\n\n");*/

	for(i=0;i<l;i++)

	{

		//printf("%d\n",i);

		if(i==0)

		{

			result2[m].l_orderkey = result1[i].l_orderkey;

			strcpy(result2[m].o_orderdate,result1[i].o_orderdate);

			result2[m].l_extendedprice = result1[i].l_extendedprice;

			continue;

		}

		if(result1[i].l_orderkey==result1[i-1].l_orderkey)

		{

			result2[m].l_extendedprice = result2[m].l_extendedprice + result1[i].l_extendedprice;

			

		}

		else

		{

			

			m++;

			result2[m].l_orderkey = result1[i].l_orderkey;

			strcpy(result2[m].o_orderdate,result1[i].o_orderdate);

			result2[m].l_extendedprice = result1[i].l_extendedprice;

			

		}

	}

	for(i=0;i<m-1;i++)//冒泡排序 

	{

		for(j=0;j<m-1-i;j++)

		{

			if(result2[j].l_extendedprice<result2[j+1].l_extendedprice)

			{

				//printf("123");

				temp.l_extendedprice=result2[j].l_extendedprice;

				temp.l_orderkey=result2[j].l_orderkey;

				strcpy(temp.o_orderdate,result2[j].o_orderdate);

				result2[j].l_extendedprice=result2[j+1].l_extendedprice;

				result2[j].l_orderkey=result2[j+1].l_orderkey;

				strcpy(result2[j].o_orderdate,result2[j+1].o_orderdate);

				result2[j+1].l_extendedprice=temp.l_extendedprice;

				result2[j+1].l_orderkey=temp.l_orderkey;

				strcpy(result2[j+1].o_orderdate,temp.o_orderdate);

			}

		}

	}

	return result2;

}



void* run(void *t)

{

	int i;
	int q = *(int*)(void*)t;
	printf("ID:%d\n", q);
	char order_date[]=" ";

	char ship_date[]=" ";
	char ship_type[]=" ";
	strcpy(order_date, argvs[2 + q * 4]);
	strcpy(ship_date, argvs[3 + q * 4]);
	strcpy(ship_type, argvs[1 + q * 4]);
	unsigned int d=atoi(argvs[4*q + 4]);

	customer * cus = NULL;

	orders * ord = NULL;

	lineitem * item = NULL;

	cus = read_customer_txt();

	ord = read_orders_txt();

	item = read_lineitem_txt();

	int limit=d;

	//strcpy(order_date,b);

	//strcpy(ship_date,c);

	//printf("%s\n",a);

	//printf("%s %s\n",b,order_date);

	//printf("%s %s\n",c,ship_date);

	//strcpy(ship_type,a);

	select_result *result=NULL;

	result=select1(cus,ord,item,order_date,ship_date,ship_type);

	printf("l_orderkey|o_orderdate|revenue\n");

	for(i=0;i<limit;i++)

	{

		printf("%-10d|%-11s|%-20.2lf\n",result[i].l_orderkey,result[i].o_orderdate,result[i].l_extendedprice);

	}

	return 0;

}

int main(int argc,char **argv)

{

	int i;
	argvs=argv;

	//printf("%s\n",argv[4]);

	unsigned int n=atoi(argv[4]);

	//printf("%d\n",n);
	int hThread;
	pthread_t* threadID=(pthread_t*)malloc(sizeof(pthread_t)*n);
	void* retval;

	for(i=1;i<=n;i++)

	{
		pthread_t sin;
		threadID[i] = sin;

		unsigned int t=atoi(argv[4*i+4]);

		//printf("%d",t);
		hThread = pthread_create(&sin, NULL, run, (void*)&i);
		if(hThread!=0)
		{
			printf("failed!!\n");
			continue;
		}
		pthread_join(threadID[i],&retval);

		//a=run(argv[4*i+1],argv[4*i+2],argv[4*i+3],t);

	}

	return 0;

}
