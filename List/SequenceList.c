#include <stdio.h>  
#include <stdbool.h>
#include <stdlib.h>  
  
#define MAXSIZE 100 // 顺序链表的最大容量  
typedef int ElemType; // 元素类型，这里定义为int  
  
// 定义顺序链表结构体  
typedef struct {  
    ElemType elem[MAXSIZE]; // 存储元素的数组  
    int last; // 当前顺序链表的最后一个元素的下标（即长度减一）  
} SeqList;  
  
// 初始化顺序链表  
void InitList(SeqList *L) {  
    L->last = -1; // 初始化为空链表，last设为-1表示没有元素  
}  
  
// 插入数据（在链表末尾插入）  
bool InsertElem(SeqList *L, ElemType e) {  
    if (L->last >= MAXSIZE - 1) {  
        printf("List is full, cannot insert element.\n");  
        return false;  
    }  
    L->elem[++(L->last)] = e; // 先增加last再赋值  
    return true;  
}  
  
// 按序号查找元素  
ElemType GetElem(SeqList *L, int index) {  
    if (index < 0 || index > L->last) {  
        printf("Index out of range.\n");  
        exit(1); // 或者返回一个特殊值表示错误，但这里选择退出程序以简化处理  
    }  
    return L->elem[index];  
}  
  
// 按值查找元素（返回第一个匹配值的序号，若不存在则返回-1）  
int LocateElem(SeqList *L, ElemType e) {  
    for (int i = 0; i <= L->last; i++) {  
        if (L->elem[i] == e) {  
            return i;  
        }  
    }  
    return -1; // 未找到返回-1  
}  
  
// 求顺序链表长度  
int ListLength(SeqList *L) {  
    return L->last + 1; // length = last + 1  
}  
  
// 删除元素（按值删除第一个匹配的元素）  
bool DeleteElem(SeqList *L, ElemType e) {  
    int index = LocateElem(L, e);  
    if (index == -1) {  
        printf("Element %d not found in the list.\n", e);  
        return false;  
    }  
    // 移动后续元素以覆盖被删除的元素  
    for (int i = index; i <= L->last - 1; i++) {  
        L->elem[i] = L->elem[i + 1];  
    }  
    L->last--; // 减少last的值  
    return true;  
}  
  
// 打印顺序链表（用于测试）  
void PrintList(SeqList *L) {  
    for (int i = 0; i <= L->last; i++) {  
        printf("%d ", L->elem[i]);  
    }  
    printf("\n");  
}  
  
int main() {  
    SeqList L;  
    InitList(&L);  
  
    // 插入数据  
    InsertElem(&L, 10);  
    InsertElem(&L, 20);  
    InsertElem(&L, 30);  
    InsertElem(&L, 20); // 插入重复元素以测试删除功能  
  
    // 打印链表  
    printf("List after insertions: ");  
    PrintList(&L);  
  
    // 按序号查找元素  
    int index = 2;  
    ElemType elem = GetElem(&L, index);  
    printf("Element at index %d: %d\n", index, elem);  
  
    // 按值查找元素  
    ElemType valueToFind = 20;  
    int pos = LocateElem(&L, valueToFind);  
    if (pos != -1) {  
        printf("Element %d found at position %d\n", valueToFind, pos);  
    }  
  
    // 求链表长度  
    int length = ListLength(&L);  
    printf("List length: %d\n", length);  
  
    // 删除元素  
    ElemType elemToDelete = 20;  
    if (DeleteElem(&L, elemToDelete)) {  
        printf("Element %d deleted.\n", elemToDelete);  
    }  
    // 注意：这里只删除了第一个匹配的20，如果要删除所有匹配的20，需要循环删除  
  
    // 打印删除后的链表  
    printf("List after deleting %d: ", elemToDelete);  
    PrintList(&L);  
  
    return 0;  
}