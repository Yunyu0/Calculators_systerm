#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define KeyType int

typedef enum { false, true } Status;

/* �����������Ľڵ�ṹ���� */
typedef struct BSTNode
{
    int data;
    struct BSTNode* lchild, * rchild;
} BSTNode, *BSTree;


Status InitBSTree(BSTree* T); //��ʼ������һ�ÿյĶ��������T 
Status InsertBST(BSTree* T, ElemType e);//����������� T �в���Ŀ��Ԫ�� e
BSTree SearchBST(BSTree T, KeyType key);//�� T �����������в��� key
Status Delete(BSTree* p);//ɾ�� p ���
Status DeleteBST(BSTree* T, ElemType key);//ɾ�����������������е�Ԫ��key
Status destroyBST(BSTree *root);//���ٶ�������� 
void INOrderTraverse(BSTree T);//���������������������ӡ 



//��ʼ������һ�ÿյĶ��������T 
Status InitBSTree(BSTree* T) {
    
    *T =NULL;
        return true;  // ���سɹ�״̬
    
}
	

//���ٶ�������� 
Status destroyBST(BSTree* root) {
    if (*root != NULL) {
        // �ݹ��������������������
        destroyBST(&((*root)->lchild));
        destroyBST(&((*root)->rchild));

        // �ͷŵ�ǰ�ڵ�
        free(*root);
        *root = NULL; // ����ָ����Ϊ NULL����������ָ��
        return true;  // ���سɹ�״̬
    }
    return false ;  // ��� root Ϊ�գ����ش���״̬
}



//�� T �����������в��� key
BSTree SearchBST(BSTree T, KeyType key) {
    //��� T Ϊ�գ������ʧ�ܣ�����NULL��
    if(T==NULL)	return NULL;
	
	//���ҳɹ�������ָ�����Ŀ��Ԫ�ؽ���ָ��
    if (!T || key == T->data) {
        return T;
    }
    else if (key < T->data) {
        //����ȥ�������в���Ŀ��Ԫ��
        return SearchBST(T->lchild, key);
    }
    else {
        //����ȥ�������в���Ŀ��Ԫ��
        return SearchBST(T->rchild, key);
    }
}

//����������� T �в���Ŀ��Ԫ�� e
Status InsertBST(BSTree* T, ElemType e) {
    //�������Ϊ��������ֱ����� e Ϊ�����
    if ((*T) == NULL)
    {
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return true;
    }
    //����ҵ�Ŀ��Ԫ�أ�����ʧ��
    else if (e == (*T)->data)
    {
        return false;
    }
    //��� e С�ڵ�ǰ����ֵ������Ӧ�ý� e ���뵽�ý�����������
    else if (e < (*T)->data) {
        InsertBST(&(*T)->lchild, e);
    }
    //��� e ���ڵ�ǰ����ֵ������Ӧ�ý� e ���뵽�ý�����������
    else
    {
        InsertBST(&(*T)->rchild, e);
    }
}

//ʵ��ɾ�� p ���ĺ���
Status Delete(BSTree* p)
{
    BSTree q = NULL, s = NULL;
    //��� 1����� p ����ΪҶ�ӽ�㣬�Һ���ҲΪ NULL���� NULL ֱ���滻 p ��㼴��
    //��� 2,��� p ֻ��һ������
    if (!(*p)->lchild) { //������Ϊ�գ�ֻ���ý�� p ������������������ p ���ɣ�
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else if (!(*p)->rchild) {//������Ϊ�գ�ֻ���ý�� p ������������������ p ���ɣ�
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    //��� 3����� p ����������
    else {
        q = *p;
        s = (*p)->lchild;
        //�������ҵ���� p ��ֱ��ǰ�������� s ָ��ľ���ǰ����㣬q ָ����� s �ĸ����
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        //ֱ�Ӹı��� p ��ֵ
        (*p)->data = s->data;
        //ɾ�� s ���
        //��� q �� p ��㲻ͬ��ɾ�� s ��� q ��û������������˽� s ����������Ϊ q ��������
        if (q != *p) {
            q->rchild = s->lchild;
        }
        //��� q �� p �����ͬ��ɾ�� s ��� q��p�� ��û������������˽� s ����������Ϊ q��p����������
        else {
            q->lchild = s->lchild;
        }
        free(s);
    }
    return true;
}

//ɾ�����������������е�Ԫ��
Status DeleteBST(BSTree* T, ElemType key)
{
    //�����ǰ���������������ڣ����Ҳ��� key ��㣬ɾ��ʧ��
    if (!(*T)) {
        return false;
    }
    else
    {
        //��� T ΪĿ���㣬���� Delete() ɾ�����
        if (key == (*T)->data) {
            Delete(T);
            return true;
        }
        else if (key < (*T)->data) {
            //���뵱ǰ��������������������Ŀ��Ԫ��
            return DeleteBST(&(*T)->lchild, key);
        }
        else {
            //���뵱ǰ��������������������Ŀ��Ԫ��
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

//�����������������
void INOrderTraverse(BSTree T) {
    if (T) {
        INOrderTraverse(T->lchild);//������ǰ����������
        printf("%d ", T->data);     //���ʵ�ǰ���
        INOrderTraverse(T->rchild);//������ǰ����������
    }
    

}


int main(){
	
	int op=0;
    int f;
	BSTree T=NULL;

	 while(op!=6){
	 	printf("================= ������������� ====================\n"); 
	 	printf("============[1]��ʼ������һ�ÿն��������============\n"); 
	 	printf("====================[2]����Ԫ��======================\n"); 
	 	printf("====================[3]ɾ��Ԫ��======================\n");
	 	printf("====================[4]����Ԫ��======================\n");
	 	printf("====================[5]���ٶ���������================\n");
		printf("====================[6]�˳�����======================\n");    
	 	 printf("��ѡ��Ҫ���еĲ�����");
	 	 scanf("%d",&op);
	 	switch(op){
		 	case 1: 

			    	if(InitBSTree(&T)==true)	printf("[�����ɹ�]\n\n"); 
			 	  break; 
			case 2: 
				   	 printf("������Ҫ��������� \n");  
					       scanf("%d",&f);
					       Status p=InsertBST(&T, f);
					          if(p==false) printf("[ERROR!!!����ʧ��,�����Ѵ���]\n");						  	
							  if(p==true)printf("[����ɹ�]\n");
					        printf("�������������������[");
					        INOrderTraverse(T);
					            printf("]\n\n");
							 break; 
			case 3: 	  
							 printf("������Ҫɾ��������ֵ��\n");
							 scanf("%d",&f);  
								 if(DeleteBST(&T, f)){
							 printf("[ɾ���ɹ�]\n");
											  }else {
											  	printf("[ERROR!!!ɾ��ʧ��,�����ڸ�����]\n");}
											  printf("�������������������[");
											  	INOrderTraverse(T);
											  	    printf("]\n\n");
											  	    
												  break; 
			case 4:  printf("������Ҫ���ҵ����ݣ�\n");  
			     scanf("%d",&f);
						  BSTree P=SearchBST(T,f); 
						  if(P!=NULL) printf("[�ɹ����ҵ�����%d] \n",P->data);  
						  if(P==NULL) printf("[ERROR!!!δ���ҵ�������]\n");  
						   printf("�������������������[");
						  					        INOrderTraverse(T);
						  					            printf("]\n\n");
						  break; 
			case 5: 
		            p=destroyBST(&T);
		        	if(p==true) printf("[���ٳɹ�]\n\n"); 
		        	break; 
		
			case 6: printf("�˳�����\n");break;
			default: printf("[ERROR!!!�������]\n"); break; 
		 			
		 }
	 } 
	 
return 0;
}

			  
			     

			 
			 
			 
			 
