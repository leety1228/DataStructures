#include <stdio.h>  
#include <stdlib.h>  
  
typedef int ElemType;  
  
typedef struct Node {  
    ElemType data;  
    struct Node *next;  
} Node, *LinkList;  
  
// 初始化单链表  
LinkList InitList() {  
    LinkList L = (Node *)malloc(sizeof(Node));  
    if (L == NULL) {  
        printf("Memory allocation failed\n");  
        exit(1);  
    }  
    L->next = NULL;  
    return L;  
}  
  
// 头插法建立单链表  
void CreateListHeadInsert(LinkList L, ElemType arr[], int n) {  
    for (int i = 0; i < n; i++) {  
        Node *newNode = (Node *)malloc(sizeof(Node));  
        if (newNode == NULL) {  
            printf("Memory allocation failed\n");  
            exit(1);  
        }  
        newNode->data = arr[i];  
        newNode->next = L->next;  
        L->next = newNode;  
    }  
}  
  
// 尾插法建立单链表  
void CreateListTailInsert(LinkList L, ElemType arr[], int n) {  
    Node *tail = L;  
    for (int i = 0; i < n; i++) {  
        Node *newNode = (Node *)malloc(sizeof(Node));  
        if (newNode == NULL) {  
            printf("Memory allocation failed\n");  
            exit(1);  
        }  
        newNode->data = arr[i];  
        newNode->next = NULL;  
        tail->next = newNode;  
        tail = newNode;  
    }  
}  
  
// 插入数据（按位置插入）  
void ListInsert(LinkList L, int pos, ElemType e) {  
    if (pos <= 0) {  
        printf("Invalid position\n");  
        return;  
    }  
    Node *p = L;  
    int j = 0;  
    while (p != NULL && j < pos - 1) {  
        p = p->next;  
        j++;  
    }  
    if (p == NULL || j > pos - 1) {  
        printf("Position out of range\n");  
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
ElemType GetElem(LinkList L, int pos) {  
    Node *p = L->next;  
    int j = 0;  
    while (p != NULL && j < pos) {  
        p = p->next;  
        j++;  
    }  
    if (p == NULL || j > pos) {  
        printf("Position out of range\n");  
        exit(1);  
    }  
    return p->data;  
}  
  
// 按值查找元素  
int LocateElem(LinkList L, ElemType e) {  
    Node *p = L->next;  
    int j = 1;  
    while (p != NULL) {  
        if (p->data == e) {  
            return j;  
        }  
        p = p->next;  
        j++;  
    }  
    return 0;  
}  
  
// 求单链表长度  
int ListLength(LinkList L) {  
    Node *p = L->next;  
    int len = 0;  
    while (p != NULL) {  
        len++;  
        p = p->next;  
    }  
    return len;  
}  
  
// 删除元素  
void ListDelete(LinkList L, int pos, ElemType *e) {  
    if (pos <= 0) {  
        printf("Invalid position\n");  
        return;  
    }  
    Node *p = L;  
    int j = 0;  
    while (p->next != NULL && j < pos - 1) {  
        p = p->next;  
        j++;  
    }  
    if (p->next == NULL || j > pos - 1) {  
        printf("Position out of range\n");  
        return;  
    }  
    Node *temp = p->next;  
    *e = temp->data;  
    p->next = temp->next;  
    free(temp);  
}  
  
// 合并两个有序单链表  
LinkList MergeList(LinkList La, LinkList Lb) {  
    LinkList Lc = InitList();  
    Node *pa = La->next;  
    Node *pb = Lb->next;  
    Node *pc = Lc;  
  
    while (pa != NULL && pb != NULL) {  
        if (pa->data <= pb->data) {  
            pc->next = pa;  
            pa = pa->next;  
        } else {  
            pc->next = pb;  
            pb = pb->next;  
        }  
        pc = pc->next;  
    }  
    pc->next = (pa != NULL) ? pa : pb;  
  
    // 释放Lb的节点（可选，因为La和Lb可能是独立分配的）  
    // 如果La和Lb后续不再使用，也可以不释放  
    // Node *tmp;  
    // while (Lb->next != NULL) {  
    //     tmp = Lb->next;  
    //     Lb->next = tmp->next;  
    //     free(tmp);  
    // }  
    // free(Lb); // 如果La和Lb的头节点也需要释放  
  
    return Lc;  
}  
  
// 打印链表  
void PrintList(LinkList L) {  
    Node *p = L->next;  
    while (p != NULL) {  
        printf("%d -> ", p->data);  
        p = p->next;  
    }  
    printf("NULL\n");  
}  
  
int main() {  
    LinkList L1 = InitList();  
    LinkList L2 = InitList();  
    ElemType arr1[] = {1, 3, 5, 7};  
    ElemType arr2[] = {2, 4, 6, 8};  
  
    CreateListHeadInsert(L1, arr1, 4);  
    CreateListTailInsert(L2, arr2, 4);  
  
    printf("List 1: ");  
    PrintList(L1);  
  
    printf("List 2: ");  
    PrintList(L2);  
  
    LinkList L3 = MergeList(L1, L2);  
    printf("Merged List: ");  
    PrintList(L3);  
  
    int pos = 3;  
    ElemType e;  
    ListInsert(L3, pos, 10);  
    printf("After inserting 10 at position %d: ", pos);  
    PrintList(L3);  
  
    ElemType elem = GetElem(L3, pos);  
    printf("Element at position %d: %d\n", pos, elem);  
  
    int loc = LocateElem(L3, 6);  
    if (loc) {  
        printf("Element 6 found at position %d\n", loc);  
    } else {  
        printf("Element 6 not found\n");  
    }  
  
    int len = ListLength(L3);  
    printf("Length of the list: %d\n", len);  
  
    pos = 2;  
    ListDelete(L3, pos, &e);  
    printf("After deleting element at position %d (value: %d): ", pos, e);  
    PrintList(L3);  
  
    return 0;  
}