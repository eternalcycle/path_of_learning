/*解答代码与问题分析*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int DataType;

typedef struct SLNode{
  DataType data;
  struct SLNode* next;  //标记A
}SLNode;

void ListInitiate(SLNode** head){
  *head=(SLNode*)malloc(sizeof(SLNode));
  (*head)->next=NULL;
}

void ListInsert_first(SLNode* head,int i,int l){
  SLNode* p,* q;
  int j;
  p=head;
  j=-1;
  while(p->next!=NULL&&j<i-1){
    p=p->next;
    j++;
  }
  //最后可以计数到p->next=NULL和j=i-1
  //我们可以这么想：head->头节点->a0->a1->a2->a3->...->ai-1->ai->ai+1->...->an->NULL
  //                       -1   0   1   2   3        i-1
  /*                                                  /\          */
  //                                                  ||
  //                                                最终j到这里,p指向这里
  //i的范围：0->size-1   即我们的指针指到的最前处为头节点，最后处为最后一个节点的前一个节点；此即为前插法
  //即插到我们传进函数的那个i的前方
  q=(SLNode*)malloc(sizeof(SLNode));
  q->data=l;
  q->next=p->next;
  p->next=q;
}//前插法

void ListDelet(SLNode* head,int i,DataType* x){
  SLNode* p;
  int j;
  p=head;
  j=-1;
  while(p->next!=NULL&&j<i-1){
    //我们必须指到要删的结点的前一个结点才能删掉我们要删的结点
    //所以我们使用了P-next->next!=NULL;
    //而至于具体移动情况同上
    p=p->next;
    j++;
  }
  SLNode* temp;
  temp=p->next;//这么写是错误的：p->next->data
  *x=temp->data;
  p->next=p->next->next;//标记2
  free(temp);
}//删除

void ListGet(SLNode* head,int i,DataType* x,SLNode** y){
  SLNode* p;
  int j;
  p=head;
  j=-1;
while(p->next!=NULL&&j<i-1){
  p=p->next;
  j++;
}
  *x=p->next->data;
  *y=p->next;
}//取数据

void CreateNode(SLNode* temp,int i){
  SLNode* p;
  p=(SLNode*)malloc(sizeof(SLNode));
  p->next=NULL;
  p->data=i;
  temp->next=p;
}

int main(int argc, char *argv[])
{
  int M;
  scanf("%d",&M);
  int X[M];
  for(int i=0;i<M;i++)scanf("%d",&X[i]);
  SLNode* m,*head;
  SLNode** a;
  a=&head;
  ListInitiate(a);
  m=head;
  for(int i=1;i<11;i++){
    CreateNode(m,i);
    m=m->next;
  }          //标记C
  for(int outer=0;outer<M;outer++){
    for(int inner=0;inner<10;inner++){
      DataType x;//标记D
      SLNode* y=NULL;
      ListGet(head,inner,&x,&y);
      if(x==X[outer]){
        ListInsert_first(head, 0, x);  // 直接插入数据到头部
        ListDelet(head, inner + 1, &x);  // 删除原节点
        break;
      }
    }
    for(int i=0;i<10;i++){
      DataType x,y;
      ListGet(head,i,&x,&y);
      printf("%d ",x);
    }
    printf("\n");
  }
  return 0;
}