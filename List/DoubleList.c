#include <stdio.h>  
#include <stdlib.h>  
  
typedef int ElemType;  
  
// 定义双向链表节点结构  
typedef struct DNode {  
    ElemType data;  
    struct DNode *prior, *next;  
} DNode, *DoubleList;  
  
// 初始化双向链表（带头结点）  
DoubleList InitList() {  
    DoubleList head = (DNode*)malloc(sizeof(DNode));  
    head->prior = NULL;  
    head->next = NULL;  
    return head;  
}  
  
// 建立双向链表（带头结点，尾插法）  
void CreateList(DoubleList head, ElemType arr[], int length) {  
    DNode *tail = head; // 尾指针初始化为头结点  
    for (int i = 0; i < length; ++i) {  
        DNode *newNode = (DNode*)malloc(sizeof(DNode));  
        newNode->data = arr[i];  
        newNode->prior = tail;  
        newNode->next = NULL;  
        tail->next = newNode; // 将新节点插入到链表末尾  
        tail = newNode;       // 更新尾指针  
    }  
}  
  
// 在指定位置前插入元素（位置从1开始计数）  
int InsertBefore(DoubleList head, int pos, ElemType elem) {  
    DNode *p = head->next; // 从第一个实际元素开始查找  
    int j = 1;  
    while (p != NULL && j < pos) {  
        p = p->next;  
        ++j;  
    }  
    if (p == NULL) { // 如果位置超出链表长度，则插入失败  
        return 0;  
    }  
    DNode *newNode = (DNode*)malloc(sizeof(DNode));  
    newNode->data = elem;  
    newNode->next = p;  
    newNode->prior = p->prior;  
    p->prior->next = newNode;  
    p->prior = newNode;  
    return 1;  
}  
  
// 删除元素（按值删除）  
int DeleteByValue(DoubleList head, ElemType value) {  
    DNode *p = head->next; // 从第一个实际元素开始查找  
    while (p != NULL) {  
        if (p->data == value) {  
            DNode *prev = p->prior;  
            DNode *next = p->next;  
            prev->next = next;  
            if (next != NULL) {  
                next->prior = prev;  
            }  
            free(p);  
            return 1;  
        }  
        p = p->next;  
    }  
    return 0; // 未找到要删除的元素  
}  
  
// 按序号查找元素  
ElemType GetElemByPos(DoubleList head, int pos, int *found) {  
    DNode *p = head->next; // 从第一个实际元素开始查找  
    int j = 1;  
    while (p != NULL && j < pos) {  
        p = p->next;  
        ++j;  
    }  
    if (p != NULL && j == pos) {  
        *found = 1;  
        return p->data;  
    } else {  
        *found = 0;  
        return -1; // 假设-1表示未找到（根据实际需求更改）  
    }  
}  
  
// 按值查找元素  
DNode* GetElemByValue(DoubleList head, ElemType value) {  
    DNode *p = head->next; // 从第一个实际元素开始查找  
    while (p != NULL) {  
        if (p->data == value) {  
            return p;  
        }  
        p = p->next;  
    }  
    return NULL; // 未找到  
}  
  
// 计算链表长度  
int ListLength(DoubleList head) {  
    int length = 0;  
    DNode *p = head->next; // 从第一个实际元素开始计数  
    while (p != NULL) {  
        ++length;  
        p = p->next;  
    }  
    return length;  
}  
  
// 合并两个有序链表（这里假设链表已经有序，合并后依然有序）  
DoubleList MergeLists(DoubleList head1, DoubleList head2) {  
    DoubleList mergedHead = InitList(); // 初始化合并后的链表头结点  
    DNode *p1 = head1->next;  
    DNode *p2 = head2->next;  
    DNode *tail = mergedHead; // 合并链表的尾指针  
  
    while (p1 != NULL && p2 != NULL) {  
        if (p1->data <= p2->data) {  
            DNode *newNode = (DNode*)malloc(sizeof(DNode));  
            newNode->data = p1->data;  
            newNode->next = NULL;  
            newNode->prior = tail;  
            tail->next = newNode;  
            tail = newNode;  
            p1 = p1->next;  
        } else {  
            DNode *newNode = (DNode*)malloc(sizeof(DNode));  
            newNode->data = p2->data;  
            newNode->next = NULL;  
            newNode->prior = tail;  
            tail->next = newNode;  
            tail = newNode;  
            p2 = p2->next;  
        }  
    }  
  
    // 将剩余节点连接到合并后的链表末尾  
    while (p1 != NULL) {  
        DNode *newNode = (DNode*)malloc(sizeof(DNode));  
        newNode->data = p1->data;  
        newNode->next = NULL;  
        newNode->prior = tail;  
        tail->next = newNode;  
        tail = newNode;  
        p1 = p1->next;  
    }  
    while (p2 != NULL) {  
        DNode *newNode = (DNode*)malloc(sizeof(DNode));  
        newNode->data = p2->data;  
        newNode->next = NULL;  
        newNode->prior = tail;  
        tail->next = newNode;  
        tail = newNode;  
        p2 = p2->next;  
    }  
  
    // 释放原链表头结点（不包含实际数据，仅作为占位符）  
    free(head1);  
    free(head2);  
  
    return mergedHead;  
}  
  
// 打印链表（用于调试）  
void PrintList(DoubleList head) {  
    DNode *p = head->next; // 从第一个实际元素开始打印  
    while (p != NULL) {  
        printf("%d ", p->data);  
        p = p->next;  
    }  
    printf("\n");  
}  
  
// 释放链表内存  
void FreeList(DoubleList head) {  
    DNode *p = head->next; // 从第一个实际元素开始释放  
    while (p != NULL) {  
        DNode *temp = p;  
        p = p->next;  
        free(temp);  
    }  
    free(head); // 释放头结点  
}  
  
int main() {  
    // 示例代码，用于测试上述函数  
    ElemType arr1[] = {1, 3, 5, 7};  
    ElemType arr2[] = {2, 4, 6, 8};  
  
    DoubleList list1 = InitList();  
    DoubleList list2 = InitList();  
  
    CreateList(list1, arr1, 4);  
    CreateList(list2, arr2, 4);  
  
    printf("List 1: ");  
    PrintList(list1);  
  
    printf("List 2: ");  
    PrintList(list2);  
  
    InsertBefore(list1, 3, 9);  
    printf("After inserting 9 before position 3 in List 1: ");  
    PrintList(list1);  
  
    DeleteByValue(list2, 4);  
    printf("After deleting 4 from List 2: ");  
    PrintList(list2);  
  
    int found;  
    ElemType elem = GetElemByPos(list1, 3, &found);  
    if (found) {  
        printf("Element at position 3 in List 1: %d\n", elem);  
    } else {  
        printf("Element at position 3 in List 1 not found.\n");  
    }  
  
    DNode* node = GetElemByValue(list2, 6);  
    if (node != NULL) {  
        printf("Element with value 6 found in List 2.\n");  
    } else {  
        printf("Element with value 6 not found in List 2.\n");  
    }  
  
    printf("Length of List 1: %d\n", ListLength(list1));  
    printf("Length of List 2: %d\n", ListLength(list2));

    DoubleList mergedHead = MergeLists(list1, list2);  
    printf("Merged List: ");  
    PrintList(mergedHead); 

    FreeList(mergedHead);  

    return 0;
}