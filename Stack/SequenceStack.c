#include <stdio.h>  
#include <stdlib.h>  
  
#define Stack_Size 50  
typedef int StackElementType;  
  
typedef struct {  
    StackElementType elem[Stack_Size];   /* 用来存放栈中元素的一维数组 */  
    int top;         /* 用来存放栈顶元素的下标，top为-1表示空栈 */  
} SeqStack;  
  
// 初始化顺序栈  
void InitStack(SeqStack *stack) {  
    stack->top = -1;  
}  
  
// 判断栈是否为空  
int IsEmpty(SeqStack *stack) {  
    return stack->top == -1;  
}  
  
// 判断栈是否满  
int IsFull(SeqStack *stack) {  
    return stack->top == Stack_Size - 1;  
}  
  
// 进栈操作  
int Push(SeqStack *stack, StackElementType elem) {  
    if (IsFull(stack)) {  
        printf("Stack is full, cannot push element.\n");  
        return 0; // 进栈失败  
    }  
    stack->elem[++(stack->top)] = elem;  
    return 1; // 进栈成功  
}  
  
// 出栈操作  
int Pop(SeqStack *stack, StackElementType *elem) {  
    if (IsEmpty(stack)) {  
        printf("Stack is empty, cannot pop element.\n");  
        return 0; // 出栈失败  
    }  
    *elem = stack->elem[(stack->top)--];  
    return 1; // 出栈成功  
}  
  
// 读栈顶元素  
int GetTop(SeqStack *stack, StackElementType *elem) {  
    if (IsEmpty(stack)) {  
        printf("Stack is empty, cannot get top element.\n");  
        return 0; // 读取失败  
    }  
    *elem = stack->elem[stack->top];  
    return 1; // 读取成功  
}  
  
// 打印栈元素  
void PrintStack(SeqStack *stack) {  
    if (IsEmpty(stack)) {  
        printf("Stack is empty.\n");  
        return;  
    }  
    printf("Stack elements: ");  
    for (int i = 0; i <= stack->top; i++) {  
        printf("%d ", stack->elem[i]);  
    }  
    printf("\n");  
}  
  
int main() {  
    SeqStack stack;  
    StackElementType elem;  
  
    // 初始化栈  
    InitStack(&stack);  
  
    // 进栈操作  
    Push(&stack, 10);  
    Push(&stack, 20);  
    Push(&stack, 30);  
  
    // 打印栈元素  
    PrintStack(&stack);  
  
    // 读栈顶元素  
    if (GetTop(&stack, &elem)) {  
        printf("Top element is: %d\n", elem);  
    }  
  
    // 出栈操作  
    if (Pop(&stack, &elem)) {  
        printf("Popped element is: %d\n", elem);  
    }  
  
    // 再次打印栈元素  
    PrintStack(&stack);  
  
    return 0;  
}