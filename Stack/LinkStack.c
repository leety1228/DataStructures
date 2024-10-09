#include <stdio.h>  
#include <stdlib.h>  
  
// 定义栈元素的数据类型  
typedef int StackElementType;  
  
// 定义链式栈的节点结构体  
typedef struct node {  
    StackElementType data;     // 数据域  
    struct node *next;         // 指针域，指向下一个节点  
} LinkStackNode;  
  
// 定义链式栈为LinkStackNode*的类型别名  
typedef LinkStackNode *LinkStack;  
  
// 初始化链式栈，返回栈顶指针  
LinkStack InitStack() {  
    // 创建一个头节点，头节点不存储数据，仅作为链表的头部  
    LinkStack stack = (LinkStack)malloc(sizeof(LinkStackNode));  
    if (stack == NULL) {  
        printf("Memory allocation failed\n");  
        exit(EXIT_FAILURE);  
    }  
    stack->next = NULL; // 头节点的next指向NULL，表示栈为空  
    // 注意：这里我们返回的是头节点的指针，实际栈顶元素应该通过stack->next来访问  
    return stack;  
}  
  
// 进栈操作，向链式栈中添加元素  
void Push(LinkStack stack, StackElementType elem) {  
    // 创建一个新节点  
    LinkStackNode *newNode = (LinkStackNode *)malloc(sizeof(LinkStackNode));  
    if (newNode == NULL) {  
        printf("Memory allocation failed\n");  
        exit(EXIT_FAILURE);  
    }  
    newNode->data = elem; // 将数据赋值给新节点  
    newNode->next = stack->next; // 新节点的next指向当前栈顶元素  
    stack->next = newNode; // 头节点的next指向新节点，完成入栈操作  
}  
  
// 出栈操作，从链式栈中移除元素并返回  
StackElementType Pop(LinkStack stack, int *success) {  
    // 检查栈是否为空  
    if (stack->next == NULL) {  
        *success = 0; // 出栈失败  
        return -1; // 返回一个特殊值表示出栈失败（这里假设-1不会作为正常数据出现）  
    }  
    // 获取栈顶元素  
    LinkStackNode *topNode = stack->next;  
    StackElementType elem = topNode->data;  
    // 移动栈顶指针到下一个元素  
    stack->next = topNode->next;  
    // 释放栈顶元素所占用的内存  
    free(topNode);  
    *success = 1; // 出栈成功  
    return elem;  
}  
  
// 读栈顶元素，不移除栈顶元素并返回其值  
StackElementType GetTop(LinkStack stack, int *success) {  
    // 检查栈是否为空  
    if (stack->next == NULL) {  
        *success = 0; // 读栈顶失败  
        return -1; // 返回一个特殊值表示读栈顶失败（这里假设-1不会作为正常数据出现）  
    }  
    // 获取栈顶元素的值  
    StackElementType elem = stack->next->data;  
    *success = 1; // 读栈顶成功  
    return elem;  
}  
  
// 打印栈元素，从栈底到栈顶依次打印  
void PrintStack(LinkStack stack) {  
    LinkStackNode *currentNode = stack->next; // 从头节点的下一个节点开始遍历  
    while (currentNode != NULL) {  
        printf("%d -> ", currentNode->data);  
        currentNode = currentNode->next;  
    }  
    printf("NULL\n"); // 打印链表末尾的NULL标志  
}  
  
// 释放链式栈所占用的内存（可选，通常在程序结束时调用）  
void DestroyStack(LinkStack stack) {  
    LinkStackNode *currentNode = stack->next; // 从头节点的下一个节点开始遍历  
    LinkStackNode *nextNode;  
    while (currentNode != NULL) {  
        nextNode = currentNode->next; // 保存下一个节点的指针  
        free(currentNode); // 释放当前节点的内存  
        currentNode = nextNode; // 移动到下一个节点继续释放  
    }  
    // 注意：这里我们没有释放头节点的内存，因为头节点是在InitStack中分配的，并且作为栈的“外壳”存在  
    // 如果需要释放头节点的内存，请在调用DestroyStack之后将栈的指针设为NULL，并在合适的时候释放头节点  
    // 但通常情况下，我们不会在DestroyStack中释放头节点，因为它可能还会被用来判断栈是否为空（即stack->next == NULL）  
}  
  
int main() {  
    LinkStack stack = InitStack(); // 初始化栈  
  
    // 进栈操作  
    Push(stack, 10);  
    Push(stack, 20);  
    Push(stack, 30);  
  
    // 打印栈元素  
    PrintStack(stack);  
  
    // 读栈顶元素  
    int success;  
    StackElementType topElem = GetTop(stack, &success);  
    if (success) {  
        printf("Top element is: %d\n", topElem);  
    } else {  
        printf("Failed to get top element\n");  
    }  
  
    // 出栈操作  
    StackElementType poppedElem = Pop(stack, &success);  
    if (success) {  
        printf("Popped element is: %d\n", poppedElem);  
    } else {  
        printf("Failed to pop element\n");  
    }  
  
    // 再次打印栈元素  
    PrintStack(stack);  
  
    // 释放栈所占用的内存（可选）  
    // DestroyStack(stack); // 注意：调用DestroyStack后，stack指针将变为悬空指针，不应再使用  
    // 如果需要继续使用栈，请不要调用DestroyStack或在调用后重新初始化栈  
  
    return 0;  
}