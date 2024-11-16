#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<conio.h>


//˫��ѭ������ 
typedef struct Node{
    int data;
		//��ͷ���������ķ��Ŵ��������ķ���
		//�����ֵ��ʾԪ�ؽ����Ŀ
    struct Node *prior,*next;
}Node,*LinkList;//˫��ѭ������ 

// ����˫��ѭ�������
void destroyList(LinkList &head) {
    if (head == nullptr) {
        // ��������������
        return;
    }

    // ���������ͷ�ÿ���ڵ���ڴ�
    Node *current = head;
    Node *nextNode;

    do {
        nextNode = current->next;
        delete current;
        current = nextNode;
    } while (current != head);

    // ��ͷָ���ÿգ���ʾ�����ѱ�����
    head = nullptr;
}

//��ʼ��һ��˫��ѭ������
void InitList(LinkList &L)
{
	L=(LinkList)malloc(sizeof(Node));
	L->data=0;
	L->next=L;
	L->prior=L;
}

//������β������һ��ֵΪx�Ľ��
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


//��������������>9999Ӧ��ǰ��λ��� 
void IN(LinkList &L)
{
	LinkList p=L->next;
	while(p!=L)
	{
		while(p->data>9999)//������λ
		{
			int in=p->data/10000;//��λֵ 
			if(p->next==L)ListInsert(L,0);//β������λ������λ ��β�������½�� 
			
			p->next->data=p->next->data+in;//��λ���Ͻ�λ��ֵ 
			p->data%=10000;//��λ��ɺ��ȥ��λֵ 
		}
		p=p->next;
	}
	while(L->prior->data==0&&abs(L->data)>1){
//	ɾ������β�����λ�����0 
		if(L->data==0)return;
		LinkList a=L->prior;
		LinkList b=a->prior;
		b->next=L;
		L->prior=b;
		free(a);
//		����ͷ���������洢�Ľ�����ֵ 
		if(L->data>=0)L->data--; 
		else L->data++;}
	
}	

//�Ƚ��������ľ���ֵ��С��a<b����0  a>b����1 a=b����2 
int Compare(LinkList a,LinkList b)
{
	if(abs(a->data)!=abs(b->data))//�洢��������ͬʱ 
	{
		if(abs(a->data)>abs(b->data))return 1;
		else return 0;
	}
	
	LinkList p=a->prior,q=b->prior;//��β��㣬���λ��ʼ�Ƚϴ�С 
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

//�ӷ����� 
void Add(LinkList a,LinkList b,LinkList &c)//a+b=c
{
	//ͬ����� 
	if(a->data*b->data>0)
	{
		LinkList p=a->next,q=b->next;
		//��������δ�������н����
		while(p!=a&&q!=b)
		{
			ListInsert(c,p->data+q->data);
			p=p->next;
			q=q->next;
		}
//		�������������ͬ������һ�����н�����ѱ�������� 
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
		//������Ӹ��µ�����ͷ�������Ϊ���� 
	}

	else	//������ 
	{	
//	�жϾ���ֵ�ϴ������Ϊ�����������������뱻����ͬ�� 
		switch(Compare(a,b))
		{	
		case 0://����ֵa<b
	            {
					LinkList p=a->next,q=b->next;
//					 ������λ����δ�����꣬������� 
					while(p!=a&&q!=b)
						{ 
							if(q->data<p->data)//�����������Ͻ�λ
							{
								q->next->data--;//��λ-1 
								q->data+=10000;
							}
							ListInsert(c,q->data-p->data);
							p=p->next;
							q=q->next;
						}
//						������δ�����꣬���������� 
						while(q!=b)
						{
							if(q->data<0)//��λ
							{
								q->next->data--;//��λ-1 
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
								if(p->data<q->data)//��λ
								{
									p->next->data--;
									p->data+=10000;
								}
								ListInsert(c,p->data-q->data);
								p=p->next;
								q=q->next;
							}
			     	while(p!=a)	{
		               	if(p->data<0)//��λ
						{
				       	p->next->data--;//��λ-1 
						p->data+=10000;
								}					
								ListInsert(c,p->data);
								p=p->next;
							}
							if(a->data<0)c->data=-c->data;//����ֵ�ϴ���ȷ������
							break;				
						}
			case 2://a=b 
				ListInsert(c,0);
				return;
		
		}
	}
	IN(c);//��������λ
}
 
//��������a-b=a+(-b)=c
void subtract(LinkList a,LinkList b,LinkList &c)
{
	b->data=-b->data;
	Add(a,b,c);
	b->data=-b->data;
}

//�˷����� a*b=c
void multiply(LinkList a,LinkList b,LinkList &c)
{
	//������һ����Ϊ0
	if((abs(a->data)==1&&a->next->data==0)||(abs(b->data)==1&&b->next->data==0))
	{
		ListInsert(c,0);
		return;
	}
//	�������λ����0ռλ 
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
			t->data+=p->data*q->data;//����������Ӧλ����� 
		}
	}
	//ab��ţ���Ϊ���� 
	if(a->data*b->data<0)c->data=-1*c->data;
	IN(c);
}

//��������a/b=c
void divide(LinkList a,LinkList b,LinkList &c)
{
	//a<b����С��1������ʾС�������Ϊ0 
	if(Compare(a,b)==0)
	{
		ListInsert(c,0);
		return;
	}
	for(int i=1;i<=abs(a->data);i++)
	ListInsert(c,0);//�̵����λ�� 
	
	int flag=0; //flag=1,b�ɸ�ת������=0û�иı� 
	//bΪ����ʱת�������Ա��������� 
	if(b->data<0)
	{
		b->data=-b->data;
		flag=1;
	}
	
	LinkList tmp;
	InitList(tmp);
	
    LinkList p=a->prior;
	for(LinkList t=c->prior;t!=c;t=t->prior,p=p->prior)
	{//��a��λ���ֿ����½�һ������tmp���൱�ڷ�ת����a�浽tmp 
		LinkList q=(LinkList)malloc(sizeof(Node));
		q->data=p->data;
		q->next=tmp->next;
		q->prior=tmp;
		
		tmp->next->prior=q;
		tmp->next=q;
		tmp->data++;
		
//�ѳ���ת��Ϊ�Ӹߵ���λ�ļ���
		while(Compare(tmp,b))
		{
			t->data++;
			LinkList r;//����
			InitList(r);
			subtract(tmp,b,r);
			
//		ɾ������β����λ�����0 
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
			ListInsert(tmp,p->data);//������r����tmp
			
		}
	}
//	��bת��ԭ�������� 
	if(flag)b->data=-1*b->data;
	if(a->data*b->data<0)c->data=-c->data;//ab���
	IN(c);
}

//��ȡһ����
int getnum(LinkList &L)
{
	char ss[100000];
	scanf("%[^\n]",ss);
	getchar();
	//����������֣����������Ҳ��ǵ�һλ�������� 
	for(size_t i=0;i<strlen(ss);i++)
	if(!(i==0&&(ss[0]=='-'||ss[0]=='+'))&&(!(ss[i]>='0'&&ss[i]<='9')))
			return 0;
			
//			����ÿ���������λ���ֲ�����9999 
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

	if(ss[0]=='-')L->data=-L->data;  //	���븺��ʱ 
	if(L->data==0)return 0;
	IN(L);
	return 1;
}

//�����ӡ�������� 
void Printdlist(LinkList &L)
{
	printf("��"); 
	LinkList p=L->prior;
	if(L->data<0)printf("-");
	while(p!=L)
	{
		if(p->next!=L)printf("%04d",p->data);
		else printf("%d",p->data);
		if(p->prior!=L)printf(",");
		p=p->prior;
	}
printf("��");
}

//�˷�����a^x=c 
void Impl(LinkList a,LinkList &c,int x){
    LinkList d;
    InitList(d);
    LinkList r;
    InitList(r);

    int flag=0;//��־���������Ƿ�Ϊ��������Ҫ��Ϊ������ͬʱflag=1 
    long int sum=0;
    if(a->data<0){
        a->data=-a->data;
        flag=1;
    }

    LinkList p=a->prior;
    
    while(p!=a){//������洢����ת�������ͱ���sum�洢 
        sum=sum*1000+p->data;
        p=p->prior;
    }
    
    if(sum==0){
        printf("0���κδγ˷�û������\n");
        return ;
    } 
    
    if(sum>0&&x==0){//�κ�����0�η�����1 
        ListInsert(c,1);
        return;
    }
    
    if(x<0){//����洢�������޷���ʾС����С��ֻ�ܱ�ʾΪ0���޷����� 
		printf("�޷�����ָ��nΪ�����Ľ��\n");
	}
    if(x==1){//�κ�����1�η����ڱ�������a��c 
        for(LinkList h=a->next;h!=a;h=h->next){
            ListInsert(c,h->data);
        }
    }
    
        //x>=2
    for(LinkList p=a->next;p!=a;p=p->next){
        ListInsert(d,p->data);
    }//a������d 
    for(int i=2;i<=x;i++){
        multiply(a,d,r);
        while(d->data!=0){//ɾ��β�����λ����Ľ��0000 
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
        }//�������r������d �ٴν���ѭ��a*d=r 
        if(i<x){
            while(r->data!=0){//ɾ��β�����λ����Ľ��0000 
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
    
//    ���˷��������c����c 
    for(LinkList h=r->next;h!=r;h=h->next){
        ListInsert(c,h->data);
    }
    if(flag){//ת��ԭ�������� 
        a->data=-a->data;
    }
    if(a->data<0&&x%2!=0){//�жϽ�������ţ������������η�Ϊ�� 
        c->data=-c->data;
    }
    IN(c);
}


//�׳����� 
void Factorial(LinkList a,LinkList &c){
    LinkList p=a->prior;
    long int sum=0;
    LinkList d,f,g;
    InitList(d);
    InitList(f);
    InitList(g);
    ListInsert(d,1);  
	   
    if(a->data<0){
       //����û�н׳� 
        return;
    }
    while(p!=a){//������洢����ת�������ͱ���sum�洢 
        sum=sum*1000+p->data;
        p=p->prior;
    }
    if(sum==0){//0�Ľ׳˵���1 
        ListInsert(c,1);
        return; 
    }    
    
    for(int i=1;i<=sum;i++){
        ListInsert(f,i);
        multiply(d,f,g);
        if(i<sum){//ɾ��β�����λ����Ľ��0000 
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
            }//g�˻�������d����������ѭ��d*f=g 
            while(f->data!=0){//ɾ��β�����λ����Ľ��0000 
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
            while(g->data!=0){//ɾ��β�����λ����Ľ��0000 
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
    }//���������c 
    IN(c);
    
	}


int main()
{ 
	 printf("22���������׿Խ��\n----3222004465---- \n------�����------\n\n");
	 printf("==========================\n");
	 printf("~~~~~~~~����������~~~~~~~~\n"); 
	 printf("==========================\n");
	
	while(1){ 
	LinkList a,b,c;
    InitList(a);
    InitList(b);
    InitList(c);
    int x=0;
    printf("��ѡ��Ҫ���еļ������\n");
		printf("[1]======== �ӷ�+ ========\n[2]======== ����- ========\n[3]======== �˷�* ========\n[4]======== ����/ ========\n[5]======== �׳ˣ�========\n[6]======== �˷�^n========\n");
		printf("\n");
		char op=getch();
		switch(op)
		{
			case '1':
				printf("======== �ӷ�����+ ========\n"); 
					do{
					printf("����������ĵ�һ��������������ɰ��س���\n");
					    int r= getnum(a);
					    if(r==0){
							printf("ERROR!���������ʽ����\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("����������ĵڶ���������������ɰ��س���\n");
						    int r= getnum(b);
						    if(r==0){
								printf("ERROR!���������ʽ����\n");
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
				printf("======== ��������- ========\n"); 
					do{
					printf("�����뱻������������ɰ��س���\n");

					    if(getnum(a)==0){
							printf("ERROR!���������ʽ����\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("�����������������ɰ��س���\n");

						    if(getnum(b)==0){
								printf("ERROR!���������ʽ����\n");
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
					printf("======== �˷�����* ========\n"); 
					do{
					printf("����������ĵ�һ��������������ɰ��س���\n");

					    if(getnum(a)==0){
							printf("ERROR!���������ʽ����\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("����������ĵڶ���������������ɰ��س���\n");

						    if(getnum(b)==0){
								printf("ERROR!���������ʽ����\n");
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
					printf("======== ��������/ ========\n"); 
					do{
					printf("�����뱻������������ɰ��س���\n");

					    if(getnum(a)==0){
							printf("ERROR!���������ʽ����\n");
							}
					}while(a->next==a);
					
				    	do{
				       printf("�����������������ɰ��س���\n");

						    if(getnum(b)==0){
								printf("ERROR!���������ʽ����\n");
								}
						}while(b->next==b);
					Printdlist(a);
					printf("/");
					Printdlist(b);
					printf("=");
				if(abs(b->data)==1&&b->next->data==0)//0������ 
				{	printf("ERROR!��ʽ����0������������\n");
					break;
					}
				divide(a,b,c);
				Printdlist(c);
					destroyList(a);
								destroyList(b);
								destroyList(c);
				break;
		
			case '5':
					printf("======== �׳����㣡 ========\n"); 
					do{
					printf("������Ҫ���н׳����������������ɰ��س���\n");

					    if(getnum(a)==0){
							printf("ERROR!���������ʽ����\n");
							}
					}while(a->next==a);
						
				Printdlist(a);
				printf("!=");
			     Factorial(a,c);
			      Printdlist(c);
			      if(c->next==c) printf("[ERROR]!!!����û�н׳�\n");
			       printf("\n");
			       	destroyList(a);
				   	destroyList(c);

			                break;    
			                	case '6':						
												printf("======== �˷�����^ ========\n"); 
												
												do{
												printf("������˷�����ĵ�����������ɰ��س���\n");					

												    if(getnum(a)==0){
														printf("ERROR!���������ʽ����\n");
														}
												}while(a->next==a);
													printf("������˷������ָ��n��������ɰ��س���\n");
													scanf("%d",&x);
														
											Impl(a,c,x);
										Printdlist(a);
										 printf("^%d=",x);
										 Printdlist(c);
										 destroyList(a);
										destroyList(c);
										 	printf("\n�˳�����\n");
										system("pause");
										 	return 0;
	
			default:{
				printf("��ѡ���˳�����\n");
				system("pause");
				return 0;
				}
		}
		system("pause");
		system("cls");	
}
}
