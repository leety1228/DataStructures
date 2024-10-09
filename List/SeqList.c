#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
#define MAXSIZE 100  // 线性表存储空间的初始化分配量
#define ElemType int  
#define OK 1
#define ERROR 0

typedef int Status;
ElemType *elemI = NULL;   // 第i个元素值

  
typedef struct {  
    ElemType elem[MAXSIZE];  //线性表占用的数组空间
    int last;  //记录线性表中最后一个元素在数组elem[]中的位置（下标值），空表置为-1
} SeqList;  
  
void InitList(SeqList *L) {  
    L->last = -1;  
}  
  
void InputList(SeqList *L, int n) {  
    int i;  
    for (i = 0; i < n; i++) {  
        scanf("%d", &L->elem[i]);  
    }  
    L->last = n - 1;  
}  

/*
    @method: 判断链表是否为空
    @param：SeqList *L
    @return：OK 链表为空 ERROR 链表非空
*/
/*Status IsEmpty(SeqList *L) {
    if(L->last == -1) {
        printf("当前链表为空！");
        return OK;
    }else{
        printf("当前链表为非空！");
        return ERROR;
    }
}*/

/*
    @method: 取表中第i个元素       
    @param：SeqList *L
    		int i 第i个元素 
    @return：OK 链表为空 ERROR 链表非空
*/
Status GetData(SeqList *L, int i) {
    if(i > L->last || i < 1 || L->last == -1) {
    	printf("ERROR!");
        return ERROR;
    }
    
    /* 取出第i个元素的值赋给*elemI */
    elemI = (ElemType *)malloc(sizeof(ElemType)); //分配内存 
    *elemI = L->elem[i-1];
    return OK;
}

/*
	@method: 查找某个元素是否在链表中       
    @param：SeqList *L 链表 
    		ElemType e 被查找元素 
    @return：-1 未找到；其他值，e的下标 
*/ 
int Locate(SeqList *L, ElemType e) {
	int i = 0;
	 
	if(L->last == -1){
		printf("当前链表为空！");
		return -1;
	} 
	
	while((i <= L->last) && (L->elem[i] != e)) {
		i++;
	}
	if(i <= L->last) {
		printf("链表中存在元素%d, 该元素为第%d个元素", e, i+1);
		return i+1;
	}else{
		printf("链表中不存在元素%d！", e);
		return -1;
	}
}
  
void AddRandomElements(SeqList *L, int m) {  
    srand(time(NULL));  
    int i, randomValue;  
    for (i = 0; i < m; i++) {  
        randomValue = rand() % 100; // 生成0-99的随机整数  
        if (L->last < MAXSIZE - 1) {  
            L->elem[++L->last] = randomValue;  
        } else {  
            printf("顺序表已满，无法添加元素！\n");  
            break;  
        }  
    }  
}  
  
void PrintList(SeqList L) {  
    int i;  
    for (i = 0; i <= L.last; i++) {  
        printf("%d ", L.elem[i]); 
//        if(i != L.last) {
//            printf("->");
//        }
    }  
    printf("\n");  
}  
  
/*
	@method: 插入下标为i的某个元素      
    @param：SeqList *L 链表 
    		int i 插入元素位置 
    		ElemType e 被插入元素 
    @return：
*/   
void InsertElement(SeqList *L, int i, ElemType e) {  
	/*首先判断插入位置是否合法*/
    if (i < 1 || i > L->last + 1 || L->last == MAXSIZE - 1) {  
        printf("插入位置不合法或顺序表已满！\n");  
        return;  
    }  
    int j;  
    /*为插入元素而移动位置*/
    for (j = L->last; j >= i - 1; j--) {  
        L->elem[j + 1] = L->elem[j];  
    } 
	/*在C语言中数组第i个元素的下标为i-1*/  
    L->elem[i - 1] = e;  
    L->last++;  
}  

/*
	@method: 在顺序表L中删除第i个数据元素，并用指针参数e返回其值     
    @param：SeqList *L 链表 
    		int i 插入元素位置 
    		ElemType *e 被删除元素 
    @return：OK 删除成功；ERROR 删除失败 
*/  
int DeleteList(SeqList *L, int i, ElemType *e) {
	int k;
	if((i < 1) || (i > L->last + 1)) {
		printf("删除位置不合法！\n");
		return ERROR;
	} 
	
	*e = L->elem[i - 1]; //将删除的元素 存放到e所指向的变量中
	for(k = i; k <= L->last; k++){
		L->elem[k - 1] = L->elem[k]; //将后面的元素依次前移 
	} 

	L->last--; //链表元素个数减一 
	return OK;
}
  
int main() {  
    SeqList L;  
    InitList(&L);  
  
    int n, i, e, status;
	ElemType *elem = (ElemType *)malloc(sizeof(ElemType));  
    printf("请输入顺序表的元素个数：");  
    scanf("%d", &n);  
    InputList(&L, n);
    printf("顺序表L的元素为：");
    PrintList(L);
    
//    printf("请输入要查找的元素：");  
//    scanf("%d", &e); 
//    status = Locate(&L, e);
//    if(status != -1) {
//    	prinf("%d为链表中的第%d个元素", e, status); 
//	}else{
//		prinf("链表中不存在元素%d！", e); 
//	}
    
//    printf("取出第i个元素的值赋给*elemI:");
//    scanf("%d", &i);
//    status = GetData(&L, i);
//    printf("GetData返回值为：%d, 第%d个元素为%d!", status, i, *elemI);
  
//    printf("输入5个随机元素进行添加：\n");  
//    AddRandomElements(&L, 5); 
//  
//    printf("顺序表L的元素为：");  
//    PrintList(L);  
  
//    printf("请输入要插入的位置i和元素e：");  
//    scanf("%d%d", &i, &e);
//    InsertElement(&L, i, e);
//    printf("顺序表L的元素为：");  
//    PrintList(L);

	printf("请输入要删除的位置i：");
	scanf("%d", &i);
	status = DeleteList(&L, i, elem);
	if(status == 1) {
		printf("删除元素%d后，顺序表L的元素为：", *elem);
    	PrintList(L);
	}else{
		printf("输入的元素位置不合法！顺序表L的元素为：");
	}
	
    //释放内存
	//free(elemI); 
}
