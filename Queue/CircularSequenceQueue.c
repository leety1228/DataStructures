#include <stdio.h>  
#include <stdbool.h>  
#include <stdlib.h>  
  
#define MaxSize 100  // 定义队列的最大容量（实际可用空间为MaxSize-1）  
typedef int ElemType;  // 定义队列元素的类型  
  
// 定义顺序队列结构体  
typedef struct {  
    ElemType data[MaxSize];  // 存储队列元素的数组  
    int front;               // 队首指针  
    int rear;                // 队尾指针，指向队列的最后一个元素的下一个位置（如果队列不为空）  
} SqQueue;  
  
// 初始化队列  
void InitQueue(SqQueue *q) {  
    q->front = 0;  // 初始化为0  
    q->rear = 0;   // 初始化为0，表示队列为空时，rear不指向任何有效元素  
}  
  
// 判断队列是否为空  
bool IsEmpty(SqQueue *q) {  
    return q->front == q->rear;  // 当队首指针和队尾指针相等时，队列为空  
}  
  
// 判断队列是否已满（保留一个空间作为约定）  
bool IsFull(SqQueue *q) {  
    return (q->rear + 1) % MaxSize == q->front;  // 使用模运算来判断是否已满  
}  
  
// 入队操作  
bool EnQueue(SqQueue *q, ElemType element) {  
    if (IsFull(q)) {  
        printf("Queue is full!\n");  
        return false;  // 队列已满，入队失败  
    }  
    q->data[q->rear] = element;  // 存储元素  
    q->rear = (q->rear + 1) % MaxSize;  // 将队尾指针后移（使用模运算实现循环）  
    return true;  // 入队成功  
}  
  
// 出队操作  
bool DeQueue(SqQueue *q, ElemType *element) {  
    if (IsEmpty(q)) {  
        printf("Queue is empty!\n");  
        return false;  // 队列为空，出队失败  
    }  
    *element = q->data[q->front];  // 取出队首元素  
    q->front = (q->front + 1) % MaxSize;  // 将队首指针后移（使用模运算实现循环）  
    return true;  // 出队成功  
}  
  
// 获取队头元素  
bool GetFront(SqQueue *q, ElemType *element) {  
    if (IsEmpty(q)) {  
        return false;  // 队列为空，无法获取队头元素  
    }  
    *element = q->data[q->front];  // 获取队首元素的值  
    return true;  // 获取成功  
}  
  
// 打印队列元素（从front到rear-1，注意循环队列的特性）  
void PrintQueue(SqQueue *q) {  
    if (IsEmpty(q)) {  
        printf("Queue is empty!\n");  
        return;  
    }  
    int i = q->front;  
    while (i != q->rear) {  
        printf("%d ", q->data[i]);  
        i = (i + 1) % MaxSize;  // 使用模运算来遍历数组  
    }  
    printf("\n");  
}  
  
int main() {  
    SqQueue q;  
    InitQueue(&q);  
  
    // 测试入队操作  
    EnQueue(&q, 1);  
    EnQueue(&q, 2);  
    EnQueue(&q, 3);  
    EnQueue(&q, 4);  // 此时队列已满（如果MaxSize为4）  
  
    // 打印队列元素  
    PrintQueue(&q);  
  
    // 测试获取队头元素  
    ElemType frontElem;  
    if (GetFront(&q, &frontElem)) {  
        printf("Front element: %d\n", frontElem);  
    }  
  
    // 测试出队操作  
    ElemType dequeuedElem;  
    while (DeQueue(&q, &dequeuedElem)) {  
        printf("Dequeued element: %d\n", dequeuedElem);  
    }  
  
    // 再次打印队列元素（此时应为空）  
    PrintQueue(&q);  
  
    return 0;  
}