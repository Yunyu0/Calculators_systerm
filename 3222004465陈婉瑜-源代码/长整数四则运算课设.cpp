#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>


//双向循环链表 
typedef struct Node{
    int data;
		//表头结点数据域的符号代表长整数的符号
		//其绝对值表示元素结点数目
    struct Node *prior,*next;
}Node,*LinkList;//双向循环链表 

// 销毁双向循环链表的
void destroyList(LinkList &head) {
    if (head == nullptr) {
        // 空链表，无需销毁
        return;
    }

    // 遍历链表，释放每个节点的内存
    Node *current = head;
    Node *nextNode;

    do {
        nextNode = current->next;
        delete current;
        current = nextNode;
    } while (current != head);

    // 将头指针置空，表示链表已被销毁
    head = nullptr;
}

//初始化一个双向循环链表
void InitList(LinkList &L)
{
	L=(LinkList)malloc(sizeof(Node));
	L->data=0;
	L->next=L;
	L->prior=L;
}

//在链表尾部插入一个值为x的结点
void ListInsert(LinkList &L,int x)
{
	LinkList p=(LinkList)malloc(sizeof(Node));
	LinkList q=L->prior;
	p->data=x;
	p->next=L;
	p->prior=q;
	q->next=p;
	L->prior=p;
	if(L->data>=0)L->data++;
	else L->data--;
}


//处理链表结点数据>9999应向前进位情况 
void IN(LinkList &L)
{
	LinkList p=L->next;
	while(p!=L)
	{
		while(p->data>9999)//产生进位
		{
			int in=p->data/10000;//进位值 
			if(p->next==L)ListInsert(L,0);//尾结点最高位发生进位 ，尾部插入新结点 
			
			p->next->data=p->next->data+in;//高位加上进位数值 
			p->data%=10000;//进位完成后减去进位值 
		}
		p=p->next;
	}
	while(L->prior->data==0&&abs(L->data)>1){
//	删除链表尾部最高位多余的0 
		if(L->data==0)return;
		LinkList a=L->prior;
		LinkList b=a->prior;
		b->next=L;
		L->prior=b;
		free(a);
//		更新头结点数据域存储的结点个数值 
		if(L->data>=0)L->data--; 
		else L->data++;}
	
}	

//比较两个数的绝对值大小：a<b返回0  a>b返回1 a=b返回2 
int Compare(LinkList a,LinkList b)
{
	if(abs(a->data)!=abs(b->data))//存储结点个数不同时 
	{
		if(abs(a->data)>abs(b->data))return 1;
		else return 0;
	}
	
	LinkList p=a->prior,q=b->prior;//从尾结点，最高位开始比较大小 
	while(p!=a&&q!=b)
	{
		if(p->data!=q->data)
		{
			if(p->data>q->data)return 1;
			else return 0;
		}
		p=p->prior;
		q=q->prior;
	}
	return 2;
}	

//加法函数 
void Add(LinkList a,LinkList b,LinkList &c)//a+b=c
{
	//同号相加 
	if(a->data*b->data>0)
	{
		LinkList p=a->next,q=b->next;
		//两个链表都未加完所有结点数
		while(p!=a&&q!=b)
		{
			ListInsert(c,p->data+q->data);
			p=p->next;
			q=q->next;
		}
//		两个数结点数不同，其中一个所有结点数已遍历相加完 
		while(p!=a)
		{
			ListInsert(c,p->data);
			p=p->next;
		}
		while(q!=b)
		{
			ListInsert(c,q->data);
			q=q->next;
		}
		
		if(a->data<0||b->data<0) c->data=-1*(c->data);
		//负数相加更新得数的头结点数据为负数 
	}

	else	//异号相加 
	{	
//	判断绝对值较大的数作为被减数，得数符号与被减数同号 
		switch(Compare(a,b))
		{	
		case 0://绝对值a<b
	            {
					LinkList p=a->next,q=b->next;
//					 两个数位数都未遍历完，两数相减 
					while(p!=a&&q!=b)
						{ 
							if(q->data<p->data)//不够减则向上借位
							{
								q->next->data--;//高位-1 
								q->data+=10000;
							}
							ListInsert(c,q->data-p->data);
							p=p->next;
							q=q->next;
						}
//						被减数未遍历完，减数遍历完 
						while(q!=b)
						{
							if(q->data<0)//借位
							{
								q->next->data--;//高位-1 
								q->data+=10000;
								}
							ListInsert(c,q->data);
							q=q->next;
						}
						if(b->data<0)c->data=-c->data;
						break;	
					}
				case 1://a>b
						{
							LinkList p=a->next,q=b->next;
							while(p!=a&&q!=b)
							{
								if(p->data<q->data)//借位
								{
									p->next->data--;
									p->data+=10000;
								}
								ListInsert(c,p->data-q->data);
								p=p->next;
								q=q->next;
							}
			     	while(p!=a)	{
		               	if(p->data<0)//借位
						{
				       	p->next->data--;//高位-1 
						p->data+=10000;
								}					
								ListInsert(c,p->data);
								p=p->next;
							}
							if(a->data<0)c->data=-c->data;//绝对值较大者确定符号
							break;				
						}
			case 2://a=b 
				ListInsert(c,0);
				return;
		
		}
	}
	IN(c);//处理结果进位
}
 
//减法函数a-b=a+(-b)=c
void subtract(LinkList a,LinkList b,LinkList &c)
{
	b->data=-b->data;
	Add(a,b,c);
	b->data=-b->data;
}

//乘法函数 a*b=c
void multiply(LinkList a,LinkList b,LinkList &c)
{
	//其中有一个数为0
	if((abs(a->data)==1&&a->next->data==0)||(abs(b->data)==1&&b->next->data==0))
	{
		ListInsert(c,0);
		return;
	}
//	积的最高位数以0占位 
	for(int i=1;i<=(abs(a->data)+abs(b->data));i++)
	ListInsert(c,0);
	
	LinkList p=a->next;
	
	for(int i=1;p!=a;p=p->next,i++)
	{
		LinkList q=b->next;
		for(int j=1;q!=b;q=q->next,j++)
		{
			int k=i+j-1;
			
			LinkList t=c;
			while(k--)t=t->next;
			t->data+=p->data*q->data;//乘完后各个相应位数相加 
		}
	}
	//ab异号，积为负数 
	if(a->data*b->data<0)c->data=-1*c->data;
	IN(c);
}

//除法函数a/b=c
void divide(LinkList a,LinkList b,LinkList &c)
{
	//a<b，商小于1，不显示小数，结果为0 
	if(Compare(a,b)==0)
	{
		ListInsert(c,0);
		return;
	}
	for(int i=1;i<=abs(a->data);i++)
	ListInsert(c,0);//商的最大位数 
	
	int flag=0; //flag=1,b由负转正数，=0没有改变 
	//b为负数时转正数，以便于做减法 
	if(b->data<0)
	{
		b->data=-b->data;
		flag=1;
	}
	
	LinkList tmp;
	InitList(tmp);
	
    LinkList p=a->prior;
	for(LinkList t=c->prior;t!=c;t=t->prior,p=p->prior)
	{//将a高位部分拷给新建一个链表tmp，相当于翻转链表a存到tmp 
		LinkList q=(LinkList)malloc(sizeof(Node));
		q->data=p->data;
		q->next=tmp->next;
		q->prior=tmp;
		
		tmp->next->prior=q;
		tmp->next=q;
		tmp->data++;
		
//把除法转换为从高到低位的减法
		while(Compare(tmp,b))
		{
			t->data++;
			LinkList r;//余数
			InitList(r);
			subtract(tmp,b,r);
			
//		删除链表尾部高位多余的0 
			while(tmp->data!=0){
				if(tmp->data==0)return;
				LinkList a=tmp->prior;
				LinkList b=a->prior;
				b->next=tmp;
				tmp->prior=b;
				free(a);
				if(tmp->data>=0)tmp->data--;
				else tmp->data++;
				}
				
			InitList(tmp);
			for(LinkList p=r->next;p!=r;p=p->next)
			ListInsert(tmp,p->data);//把余数r拷给tmp
			
		}
	}
//	把b转回原来的正负 
	if(flag)b->data=-1*b->data;
	if(a->data*b->data<0)c->data=-c->data;//ab异号
	IN(c);
}

//读取一个数
int getnum(LinkList &L)
{
	char ss[100000];
	scanf("%[^\n]",ss);
	getchar();
	//检查输入数字，不是数字且不是第一位的正负号 
	for(size_t i=0;i<strlen(ss);i++)
	if(!(i==0&&(ss[0]=='-'||ss[0]=='+'))&&(!(ss[i]>='0'&&ss[i]<='9')))
			return 0;
			
//			链表每个结点存放四位数字不超过9999 
	int j=0;
	for(int i=strlen(ss)-1;i>=0;i--)
	{
		if(ss[i]>='0'&&ss[i]<='9')
		{
			j++;
			if(j==4||i==0||((i==1)&&ss[0]=='-'))
			{
				int sum=0;
				for(int k=i;k<i+j;k++)
				sum=10*sum+(ss[k]-'0');
				ListInsert(L,sum);
				j=0;
			}
		}
	}

	if(ss[0]=='-')L->data=-L->data;  //	输入负数时 
	if(L->data==0)return 0;
	IN(L);
	return 1;
}

//输出打印链表数据 
void Printdlist(LinkList &L)
{
	printf("（"); 
	LinkList p=L->prior;
	if(L->data<0)printf("-");
	while(p!=L)
	{
		if(p->next!=L)printf("%04d",p->data);
		else printf("%d",p->data);
		if(p->prior!=L)printf(",");
		p=p->prior;
	}
printf("）");
}

//乘方运算a^x=c 
void Impl(LinkList a,LinkList &c,int x){
    LinkList d;
    InitList(d);
    LinkList r;
    InitList(r);

    int flag=0;//标志输入数据是否为负数，负要变为正数，同时flag=1 
    long int sum=0;
    if(a->data<0){
        a->data=-a->data;
        flag=1;
    }

    LinkList p=a->prior;
    
    while(p!=a){//将链表存储的数转到长整型变量sum存储 
        sum=sum*1000+p->data;
        p=p->prior;
    }
    
    if(sum==0){
        printf("0的任何次乘方没有意义\n");
        return ;
    } 
    
    if(sum>0&&x==0){//任何数的0次方等于1 
        ListInsert(c,1);
        return;
    }
    
    if(x<0){//链表存储的数据无法表示小数，小数只能表示为0，无法计算 
		printf("无法计算指数n为负数的结果\n");
	}
    if(x==1){//任何数的1次方等于本身，拷贝a到c 
        for(LinkList h=a->next;h!=a;h=h->next){
            ListInsert(c,h->data);
        }
    }
    
        //x>=2
    for(LinkList p=a->next;p!=a;p=p->next){
        ListInsert(d,p->data);
    }//a拷贝到d 
    for(int i=2;i<=x;i++){
        multiply(a,d,r);
        while(d->data!=0){//删除尾部最高位多余的结点0000 
        	if(d->data==0){
			        return;
			    }
			    LinkList g=d->prior;
			    LinkList z=g->prior;
			    z->next=d;
			    d->prior=z;
			    free(g);
			    if(d->data>=0){
			        d->data--;
			    }
			    else{
			        d->data++;
			    }	
        }     
        InitList(d);
        for(LinkList p=r->next;p!=r;p=p->next){
            ListInsert(d,p->data);
        }//相乘完结果r拷贝回d 再次进入循环a*d=r 
        if(i<x){
            while(r->data!=0){//删除尾部最高位多余的结点0000 
            		if(r->data==0) return;	
            		
							    LinkList g=r->prior;
							    LinkList z=g->prior;
							    z->next=r;
							    r->prior=z;
							    free(g);
							    if(r->data>=0){
							        r->data--;
							    }
							    else{
							        r->data++;
							    }
            } 
        InitList(r);
        }
            
    }
    
//    最后乘方结果考回c返回c 
    for(LinkList h=r->next;h!=r;h=h->next){
        ListInsert(c,h->data);
    }
    if(flag){//转回原来正负号 
        a->data=-a->data;
    }
    if(a->data<0&&x%2!=0){//判断结果正负号，负数的奇数次方为负 
        c->data=-c->data;
    }
    IN(c);
}


//阶乘运算 
void Factorial(LinkList a,LinkList &c){
    LinkList p=a->prior;
    long int sum=0;
    LinkList d,f,g;
    InitList(d);
    InitList(f);
    InitList(g);
    ListInsert(d,1);  
	   
    if(a->data<0){
       //负数没有阶乘 
        return;
    }
    while(p!=a){//将链表存储的数转到长整型变量sum存储 
        sum=sum*1000+p->data;
        p=p->prior;
    }
    if(sum==0){//0的阶乘等于1 
        ListInsert(c,1);
        return; 
    }    
    
    for(int i=1;i<=sum;i++){
        ListInsert(f,i);
        multiply(d,f,g);
        if(i<sum){//删除尾部最高位多余的结点0000 
            while(d->data!=0){
               	if(d->data==0){
			   			        return;
			   			    }
			   			    LinkList g=d->prior;
			   			    LinkList z=g->prior;
			   			    z->next=d;
			   			    d->prior=z;
			   			    free(g);
			   			    if(d->data>=0){
			   			        d->data--;
			   			    }
			   			    else{
			   			        d->data++;
			   			    } }
            InitList(d);
            for(LinkList p=g->next;p!=g;p=p->next){
                ListInsert(d,p->data);
            }//g乘积拷贝回d，继续进入循环d*f=g 
            while(f->data!=0){//删除尾部最高位多余的结点0000 
                	if(f->data==0){
							        return;
							    }
							    LinkList g=f->prior;
							    LinkList z=g->prior;
							    z->next=f;
							    f->prior=z;
							    free(g);
							    if(f->data>=0){
							        f->data--;
							    }
							    else{
							        f->data++;
							    }
            }
            InitList(f);
            while(g->data!=0){//删除尾部最高位多余的结点0000 
                	if(g->data==0){
							   return;
							  }
					 LinkList t=g->prior;
						LinkList z=t->prior;
						 z->next=g;
						  g->prior=z;
					   free(t);
							   if(g->data>=0){
						      g->data--;
					   } else{ g->data++;}
            }
            
            InitList(g);
        }
        for(LinkList p=g->next;p!=g;p=p->next){
            ListInsert(c,p->data);
        }        
    }//结果拷贝回c 
    IN(c);
    
	}


int main()
{ 
	 printf("22级软件工程卓越班\n----3222004465---- \n------陈婉瑜------\n\n");
	 printf("==========================\n");
	 printf("~~~~~~~~长整数运算~~~~~~~~\n"); 
	 printf("==========================\n");
	
	while(1){ 
	LinkList a,b,c;
    InitList(a);
    InitList(b);
    InitList(c);
    int x=0;
    printf("请选择要进行的计算操作\n");
		printf("[1]======== 加法+ ========\n[2]======== 减法- ========\n[3]======== 乘法* ========\n[4]======== 除法/ ========\n[5]======== 阶乘！========\n[6]======== 乘方^n========\n");
		printf("\n");
		char op=getch();
		switch(op)
		{
			case '1':
				printf("======== 加法运算+ ========\n"); 
					do{
					printf("请输入运算的第一个加数，输入完成按回车键\n");
					    int r= getnum(a);
					    if(r==0){
							printf("ERROR!数字输入格式错误\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("请输入运算的第二个加数，输入完成按回车键\n");
						    int r= getnum(b);
						    if(r==0){
								printf("ERROR!数字输入格式错误\n");
								}
						}while(b->next==b);
				Printdlist(a);
				printf("+");
				Printdlist(b);
				printf("=");
				Add(a,b,c);
				Printdlist(c);
				destroyList(a);
				destroyList(b);
				destroyList(c);
				break;
			case '2':
				printf("======== 减法运算- ========\n"); 
					do{
					printf("请输入被减数，输入完成按回车键\n");

					    if(getnum(a)==0){
							printf("ERROR!数字输入格式错误\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("请输入减数，输入完成按回车键\n");

						    if(getnum(b)==0){
								printf("ERROR!数字输入格式错误\n");
								}
						}while(b->next==b);
				Printdlist(a);
				printf("-");
				Printdlist(b);
				printf("=");
				subtract(a,b,c);
				Printdlist(c);
					destroyList(a);
								destroyList(b);
								destroyList(c);
				break;
			case '3':
					printf("======== 乘法运算* ========\n"); 
					do{
					printf("请输入运算的第一个因数，输入完成按回车键\n");

					    if(getnum(a)==0){
							printf("ERROR!数字输入格式错误\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("请输入运算的第二个因数，输入完成按回车键\n");

						    if(getnum(b)==0){
								printf("ERROR!数字输入格式错误\n");
								}
						}while(b->next==b);
				Printdlist(a);
		    	printf("*");
				Printdlist(b);
				printf("=");
				multiply(a,b,c);
				Printdlist(c);
					destroyList(a);
								destroyList(b);
								destroyList(c);
				break;
			case '4':
					printf("======== 除法运算/ ========\n"); 
					do{
					printf("请输入被除数，输入完成按回车键\n");

					    if(getnum(a)==0){
							printf("ERROR!数字输入格式错误\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("请输入除数，输入完成按回车键\n");

						    if(getnum(b)==0){
								printf("ERROR!数字输入格式错误\n");
								}
						}while(b->next==b);
					Printdlist(a);
					printf("/");
					Printdlist(b);
					printf("=");
				if(abs(b->data)==1&&b->next->data==0)//0做除数 
				{	printf("ERROR!公式错误，0不可以做除数\n");
					break;
					}
				divide(a,b,c);
				Printdlist(c);
					destroyList(a);
								destroyList(b);
								destroyList(c);
				break;
		
			case '5':
					printf("======== 阶乘运算！ ========\n"); 
					do{
					printf("请输入要进行阶乘运算的数，输入完成按回车键\n");

					    if(getnum(a)==0){
							printf("ERROR!数字输入格式错误\n");
							}
					}while(a->next==a);
						
				Printdlist(a);
				printf("!=");
			     Factorial(a,c);
			      Printdlist(c);
			      if(c->next==c) printf("[ERROR]!!!负数没有阶乘\n");
			       printf("\n");
			       	destroyList(a);
				   	destroyList(c);

			                break;    
			                	case '6':						
												printf("======== 乘方运算^ ========\n"); 
												
												do{
												printf("请输入乘方运算的底数，输入完成按回车键\n");					

												    if(getnum(a)==0){
														printf("ERROR!数字输入格式错误\n");
														}
												}while(a->next==a);
													printf("请输入乘方运算的指数n，输入完成按回车键\n");
													scanf("%d",&x);
														
											Impl(a,c,x);
										Printdlist(a);
										 printf("^%d=",x);
										 Printdlist(c);
										 destroyList(a);
										destroyList(c);
										 	printf("\n退出程序\n");
										system("pause");
										 	return 0;
	
			default:{
				printf("您选择退出程序\n");
				system("pause");
				return 0;
				}
		}
		system("pause");
		system("cls");	
}
}
