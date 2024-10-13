#include <stdio.h>  
#include <stdlib.h>  
  
typedef int ElemType;  
  
typedef struct Node {  
    ElemType data;  
    struct Node *next;  
} Node, *LinkList;  
  
// 初始化循环单链表  
void InitList(LinkList *L) {  
    *L = (Node *)malloc(sizeof(Node));  
    if (*L == NULL) {  
        fprintf(stderr, "Memory allocation failed\n");  
        exit(1);  
    }  
    (*L)->next = *L;  // 初始化为循环链表，头结点指向自己  
}  
  
// 头插法建立循环单链表  
void HeadInsert(LinkList L, ElemType e) {  
    Node *newNode = (Node *)malloc(sizeof(Node));  
    if (newNode == NULL) {  
        fprintf(stderr, "Memory allocation failed\n");  
        exit(1);  
    }  
    newNode->data = e;  
    newNode->next = L->next;  
    L->next = newNode;  
}  
  
// 尾插法建立循环单链表  
void TailInsert(LinkList L, ElemType e) {  
    Node *newNode = (Node *)malloc(sizeof(Node));  
    if (newNode == NULL) {  
        fprintf(stderr, "Memory allocation failed\n");  
        exit(1);  
    }  
    newNode->data = e;  
    Node *tail = L;  
    while (tail->next != L) {  
        tail = tail->next;  
    }  
    tail->next = newNode;  
    newNode->next = L;  
}  
  
// 按序号插入数据  
void InsertByIndex(LinkList L, int index, ElemType e) {  
    if (index <= 0) {  
        printf("Invalid index\n");  
        return;  
    }  
    Node *p = L;  
    int j = 0;  
    while (p->next != L && j < index - 1) {  
        p = p->next;  
        j++;  
    }  
    if (j != index - 1) {  
        printf("Index out of range\n");  
        return;  
    }  
    Node *newNode = (Node *)malloc(sizeof(Node));  
    if (newNode == NULL) {  
        printf("Memory allocation failed\n");  
        exit(1);  
    }  
    newNode->data = e;  
    newNode->next = p->next;  
    p->next = newNode;  
}  
  
// 按序号查找元素  
ElemType FindByIndex(LinkList L, int index) {  
    if (index <= 0) {  
        printf("Invalid index\n");  
        return -1;  // 假设-1表示无效值  
    }  
    Node *p = L->next;  
    int j = 0;  
    while (p != L && j < index) {  
        p = p->next;  
        j++;  
    }  
    if (j == index) {  
        return p->data;  
    } else {  
        printf("Index out of range\n");  
        return -1;  // 假设-1表示无效值  
    }  
}  
  
// 按值查找元素  
Node* FindByValue(LinkList L, ElemType e) {  
    Node *p = L->next;  
    while (p != L) {  
        if (p->data == e) {  
            return p;  
        }  
        p = p->next;  
    }  
    return NULL;  // 未找到  
}  
  
// 求单链表长度  
int ListLength(LinkList L) {  
    int length = 0;  
    Node *p = L->next;  
    while (p != L) {  
        length++;  
        p = p->next;  
    }  
    return length;  
}  
  
// 删除元素（按值删除）  
void DeleteByValue(LinkList L, ElemType e) {  
    Node *p = L;  
    while (p->next != L) {  
        if (p->next->data == e) {  
            Node *temp = p->next;  
            p->next = p->next->next;  
            free(temp);  
            return;  
        }  
        p = p->next;  
    }  
    printf("Element not found\n");  
}  
  
// 两个有序单链表的合并（保持循环）  
LinkList MergeLists(LinkList La, LinkList Lb) {  
    LinkList Lc = NULL;  
    InitList(&Lc);  
    Node *pa = La->next;  
    Node *pb = Lb->next;  
    Node *pc = Lc;  
  
    while (pa != La && pb != Lb) {  
        if (pa->data <= pb->data) {  
            pc->next = pa;  
            pa = pa->next;  
        } else {  
            pc->next = pb;  
            pb = pb->next;  
        }  
        pc = pc->next;  
    }  
  
    // 连接剩余部分  
    pc->next = (pa == La) ? pb : pa;  
  
    // 保持循环  
    Node *tail = pc;  
    while (tail->next != Lc->next) {  
        tail = tail->next;  
    }  
    tail->next = Lc;  // 使 Lc 成为循环链表  
  
    return Lc;  
}  
  
// 打印链表  
void PrintList(LinkList L) {  
    Node *p = L->next;  
    while (p != L) {  
        printf("%d ", p->data);  
        p = p->next;  
    }  
    printf("(head)\n");  // 标记循环点  
}  
  
int main() {  
    LinkList La, Lb, Lc;  
    InitList(&La);  
    InitList(&Lb);  
  
    HeadInsert(La, 1);  
    HeadInsert(La, 2);  
    HeadInsert(La, 3);  
  
    TailInsert(Lb, 4);  
    TailInsert(Lb, 5);  
    TailInsert(Lb, 6);  
  
    printf("List A: ");  
    PrintList(La);  
  
    printf("List B: ");  
    PrintList(Lb);  
  
    InsertByIndex(La, 2, 99);  
    printf("After inserting 99 at index 2 in List A: ");  
    PrintList(La);  
  
    int index = 2;  
    printf("Element at index %d in List A: %d\n", index, FindByIndex(La, index));  
  
    ElemType value = 99;  
    printf("Element %d found in List A: %s\n", value, (FindByValue(La, value) != NULL) ? "Yes" : "No");  
  
    printf("Length of List A: %d\n", ListLength(La));  
  
    DeleteByValue(La, 99);  
    printf("After deleting 99 from List A: ");  
    PrintList(La);  
  
    Lc = MergeLists(La, Lb);  
    printf("Merged List: ");  
    PrintList(Lc);  
  
    return 0;  
}