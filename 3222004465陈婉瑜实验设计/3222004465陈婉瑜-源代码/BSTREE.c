#include<stdio.h>
#include<stdlib.h>

#define ElemType int
#define KeyType int

typedef enum { false, true } Status;

/* 二叉排序树的节点结构定义 */
typedef struct BSTNode
{
    int data;
    struct BSTNode* lchild, * rchild;
} BSTNode, *BSTree;


Status InitBSTree(BSTree* T); //初始化构造一棵空的二叉查找树T 
Status InsertBST(BSTree* T, ElemType e);//向二叉排序树 T 中插入目标元素 e
BSTree SearchBST(BSTree T, KeyType key);//在 T 二叉排序树中查找 key
Status Delete(BSTree* p);//删除 p 结点
Status DeleteBST(BSTree* T, ElemType key);//删除二叉排序树中已有的元素key
Status destroyBST(BSTree *root);//销毁二叉查找树 
void INOrderTraverse(BSTree T);//中序遍历二叉排序树并打印 



//初始化构造一棵空的二叉查找树T 
Status InitBSTree(BSTree* T) {
    
    *T =NULL;
        return true;  // 返回成功状态
    
}
	

//销毁二叉查找树 
Status destroyBST(BSTree* root) {
    if (*root != NULL) {
        // 递归地销毁左子树和右子树
        destroyBST(&((*root)->lchild));
        destroyBST(&((*root)->rchild));

        // 释放当前节点
        free(*root);
        *root = NULL; // 将根指针置为 NULL，避免悬挂指针
        return true;  // 返回成功状态
    }
    return false ;  // 如果 root 为空，返回错误状态
}



//在 T 二叉排序树中查找 key
BSTree SearchBST(BSTree T, KeyType key) {
    //如果 T 为空，则查找失败，返回NULL；
    if(T==NULL)	return NULL;
	
	//查找成功，返回指向存有目标元素结点的指针
    if (!T || key == T->data) {
        return T;
    }
    else if (key < T->data) {
        //继续去左子树中查找目标元素
        return SearchBST(T->lchild, key);
    }
    else {
        //继续去右子树中查找目标元素
        return SearchBST(T->rchild, key);
    }
}

//向二叉排序树 T 中插入目标元素 e
Status InsertBST(BSTree* T, ElemType e) {
    //如果本身为空树，则直接添加 e 为根结点
    if ((*T) == NULL)
    {
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->data = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        return true;
    }
    //如果找到目标元素，插入失败
    else if (e == (*T)->data)
    {
        return false;
    }
    //如果 e 小于当前结点的值，表明应该将 e 插入到该结点的左子树中
    else if (e < (*T)->data) {
        InsertBST(&(*T)->lchild, e);
    }
    //如果 e 大于当前结点的值，表明应该将 e 插入到该结点的右子树中
    else
    {
        InsertBST(&(*T)->rchild, e);
    }
}

//实现删除 p 结点的函数
Status Delete(BSTree* p)
{
    BSTree q = NULL, s = NULL;
    //情况 1，结点 p 本身为叶子结点，右孩子也为 NULL，用 NULL 直接替换 p 结点即可
    //情况 2,结点 p 只有一个孩子
    if (!(*p)->lchild) { //左子树为空，只需用结点 p 的右子树根结点代替结点 p 即可；
        q = *p;
        *p = (*p)->rchild;
        free(q);
    }
    else if (!(*p)->rchild) {//右子树为空，只需用结点 p 的左子树根结点代替结点 p 即可；
        q = *p;
        *p = (*p)->lchild;
        free(q);
    }
    //情况 3，结点 p 有两个孩子
    else {
        q = *p;
        s = (*p)->lchild;
        //遍历，找到结点 p 的直接前驱，最终 s 指向的就是前驱结点，q 指向的是 s 的父结点
        while (s->rchild)
        {
            q = s;
            s = s->rchild;
        }
        //直接改变结点 p 的值
        (*p)->data = s->data;
        //删除 s 结点
        //如果 q 和 p 结点不同，删除 s 后的 q 将没有右子树，因此将 s 的左子树作为 q 的右子树
        if (q != *p) {
            q->rchild = s->lchild;
        }
        //如果 q 和 p 结点相同，删除 s 后的 q（p） 将没有左子树，因此将 s 的左子树作为 q（p）的左子树
        else {
            q->lchild = s->lchild;
        }
        free(s);
    }
    return true;
}

//删除二叉排序树中已有的元素
Status DeleteBST(BSTree* T, ElemType key)
{
    //如果当前二叉排序树不存在，则找不到 key 结点，删除失败
    if (!(*T)) {
        return false;
    }
    else
    {
        //如果 T 为目标结点，调用 Delete() 删除结点
        if (key == (*T)->data) {
            Delete(T);
            return true;
        }
        else if (key < (*T)->data) {
            //进入当前结点的左子树，继续查找目标元素
            return DeleteBST(&(*T)->lchild, key);
        }
        else {
            //进入当前结点的右子树，继续查找目标元素
            return DeleteBST(&(*T)->rchild, key);
        }
    }
}

//中序遍历二叉排序树
void INOrderTraverse(BSTree T) {
    if (T) {
        INOrderTraverse(T->lchild);//遍历当前结点的左子树
        printf("%d ", T->data);     //访问当前结点
        INOrderTraverse(T->rchild);//遍历当前结点的右子树
    }
    

}


int main(){
	
	int op=0;
    int f;
	BSTree T=NULL;

	 while(op!=6){
	 	printf("================= 二叉查找树功能 ====================\n"); 
	 	printf("============[1]初始化构建一棵空二叉查找树============\n"); 
	 	printf("====================[2]插入元素======================\n"); 
	 	printf("====================[3]删除元素======================\n");
	 	printf("====================[4]查找元素======================\n");
	 	printf("====================[5]销毁二叉排序树================\n");
		printf("====================[6]退出程序======================\n");    
	 	 printf("请选择要进行的操作：");
	 	 scanf("%d",&op);
	 	switch(op){
		 	case 1: 

			    	if(InitBSTree(&T)==true)	printf("[构建成功]\n\n"); 
			 	  break; 
			case 2: 
				   	 printf("请输入要插入的数据 \n");  
					       scanf("%d",&f);
					       Status p=InsertBST(&T, f);
					          if(p==false) printf("[ERROR!!!插入失败,数据已存在]\n");						  	
							  if(p==true)printf("[插入成功]\n");
					        printf("中序遍历二叉排序树：[");
					        INOrderTraverse(T);
					            printf("]\n\n");
							 break; 
			case 3: 	  
							 printf("请输入要删除的数据值：\n");
							 scanf("%d",&f);  
								 if(DeleteBST(&T, f)){
							 printf("[删除成功]\n");
											  }else {
											  	printf("[ERROR!!!删除失败,不存在该数据]\n");}
											  printf("中序遍历二叉排序树：[");
											  	INOrderTraverse(T);
											  	    printf("]\n\n");
											  	    
												  break; 
			case 4:  printf("请输入要查找的数据：\n");  
			     scanf("%d",&f);
						  BSTree P=SearchBST(T,f); 
						  if(P!=NULL) printf("[成功查找到数据%d] \n",P->data);  
						  if(P==NULL) printf("[ERROR!!!未查找到该数据]\n");  
						   printf("中序遍历二叉排序树：[");
						  					        INOrderTraverse(T);
						  					            printf("]\n\n");
						  break; 
			case 5: 
		            p=destroyBST(&T);
		        	if(p==true) printf("[销毁成功]\n\n"); 
		        	break; 
		
			case 6: printf("退出程序\n");break;
			default: printf("[ERROR!!!输入错误]\n"); break; 
		 			
		 }
	 } 
	 
return 0;
}

			  
			     

			 
			 
			 
			 
