#include <stdio.h>  
#include <stdbool.h>  
#include <stdlib.h>  
  
#define MaxSize 100  // 定义队列的最大容量  
typedef int ElemType;  // 定义队列元素的类型  
  
// 定义顺序队列结构体  
typedef struct {  
    ElemType data[MaxSize];  // 存储队列元素的数组  
    int front;               // 队首指针，指向队列的第一个元素  
    int rear;                // 队尾指针，指向队列的最后一个元素（如果队列不为空）  
} SqQueue;  
  
// 初始化队列  
void InitQueue(SqQueue *q) {  
    q->front = -1;  // 初始化为-1，表示队列为空  
    q->rear = -1;   // 初始化为-1，表示队列为空  
}  
  
// 判断队列是否为空  
bool IsEmpty(SqQueue *q) {  
    return q->front == -1;  // 当队首指针为-1时，队列为空  
}  
  
// 判断队列是否已满  
bool IsFull(SqQueue *q) {  
    return q->rear == MaxSize - 1;  // 当队尾指针达到MaxSize - 1时，队列已满  
}  
  
// 入队操作  
bool EnQueue(SqQueue *q, ElemType element) {  
    if (IsFull(q)) {  
        printf("Queue is full!\n");  
        return false;  // 队列已满，入队失败  
    }  
    q->rear++;  // 先将队尾指针后移  
    q->data[q->rear] = element;  // 再存储元素  
    if (q->front == -1) {  
        q->front = 0;  // 如果队列之前为空，则设置队首指针  
    }  
    return true;  // 入队成功  
}  
  
// 出队操作  
bool DeQueue(SqQueue *q, ElemType *element) {  
    if (IsEmpty(q)) {  
        printf("Queue is empty!\n");  
        return false;  // 队列为空，出队失败  
    }  
    *element = q->data[q->front];  // 取出队首元素  
    q->front++;  // 将队首指针后移  
    if (q->front > q->rear) {  
        q->front = q->rear = -1;  // 如果队首指针超过队尾指针，则重置队列为空  
    }  
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
  
// 打印队列元素  
void PrintQueue(SqQueue *q) {  
    if (IsEmpty(q)) {  
        printf("Queue is empty!\n");  
        return;  
    }  
    for (int i = q->front; i <= q->rear; i++) {  
        printf("%d ", q->data[i]);  
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