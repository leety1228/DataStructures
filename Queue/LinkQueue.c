#include <stdio.h>  
#include <stdlib.h>  
  
// 定义队列元素类型  
typedef int QueueElementType;  
  
// 定义节点结构体  
typedef struct Node {  
    QueueElementType data;               // 数据域  
    struct Node *next;                   // 指针域  
} LinkQueueNode;  
  
// 定义队列结构体  
typedef struct {  
    LinkQueueNode *front;   // 指向队头结点（通常使用哨兵头结点）  
    LinkQueueNode *rear;    // 指向队尾结点  
} LinkQueue;  
  
// 初始化队列（使用哨兵头结点）  
void InitQueue(LinkQueue *q) {  
    q->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));  
    if (q->front == NULL) {  
        printf("Memory allocation failed for front node\n");  
        exit(1);  
    }  
    q->front->next = NULL;  
    q->rear = q->front; // 初始化时，队尾指针也指向头结点  
}  
  
// 入队操作  
void EnQueue(LinkQueue *q, QueueElementType element) {  
    LinkQueueNode *newNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));  
    if (newNode == NULL) {  
        printf("Memory allocation failed for new node\n");  
        exit(1);  
    }  
    newNode->data = element;  
    newNode->next = NULL;  
    q->rear->next = newNode; // 将新节点插入到队尾  
    q->rear = newNode;       // 更新队尾指针  
}  
  
// 队列判空操作  
int IsEmpty(LinkQueue *q) {  
    return q->front == q->rear && q->front->next == NULL;  
} 
  
// 出队操作  
int DeQueue(LinkQueue *q, QueueElementType *element) {  
    if (IsEmpty(q)) {  
        // 队列为空  
        return 0;  
    }  
    LinkQueueNode *temp = q->front->next; // 获取队头节点（实际数据节点）  
    *element = temp->data;  
    q->front->next = temp->next; // 删除队头节点  
    if (q->rear == temp) {  
        // 队列中只有一个元素，出队后队列为空  
        q->rear = q->front;  
    }  
    free(temp); // 释放已删除节点的内存  
    return 1;  
}   
  
// 获取队头元素  
int GetFront(LinkQueue *q, QueueElementType *element) {  
    if (IsEmpty(q)) {  
        // 队列为空  
        return 0;  
    }  
    *element = q->front->next->data; // 获取队头节点的数据  
    return 1;  
}  
  
// 打印队列元素  
void PrintQueue(LinkQueue *q) {  
    LinkQueueNode *current = q->front->next; // 从队头节点的下一个节点开始遍历  
    while (current != NULL) {  
        printf("%d -> ", current->data);  
        current = current->next;  
    }  
    printf("NULL\n");  
}  
  
// 销毁队列（释放所有节点的内存，除了哨兵头结点）  
void DestroyQueue(LinkQueue *q) {  
    LinkQueueNode *current = q->front;  
    while (current->next != NULL) { // 跳过哨兵头结点，释放其他所有节点  
        LinkQueueNode *temp = current;  
        current = current->next;  
        free(temp);  
    }  
    // 注意：哨兵头结点通常在队列销毁时不释放，因为它在初始化时分配且在整个队列生命周期内存在  
    // 如果需要释放哨兵头结点，请确保在InitQueue之后没有其他指针指向它，并在DestroyQueue中释放  
    // 但这样做通常不是必要的，除非你有特定的内存管理要求  
}  
  
int main() {  
    LinkQueue q;  
    InitQueue(&q);  
  
    EnQueue(&q, 10);  
    EnQueue(&q, 20);  
    EnQueue(&q, 30);  
  
    printf("Queue elements: ");  
    PrintQueue(&q);  
  
    QueueElementType frontElement;  
    if (GetFront(&q, &frontElement)) {  
        printf("Front element: %d\n", frontElement);  
    } else {  
        printf("Queue is empty\n");  
    }  
  
    QueueElementType dequeuedElement;  
    while (DeQueue(&q, &dequeuedElement)) {  
        printf("Dequeued element: %d\n", dequeuedElement);  
    }  
  
    if (IsEmpty(&q)) {  
        printf("Queue is empty after dequeue\n");  
    } else {  
        printf("Queue is not empty\n");  
    }  
  
    printf("Queue elements after dequeue: ");  
    PrintQueue(&q);  
  
    // 通常不需要在main函数中销毁队列，因为程序结束时会自动释放所有内存  
    // 但为了演示完整性，这里还是调用一下DestroyQueue函数（注意：哨兵头结点未释放）  
    DestroyQueue(&q); // 如果要释放哨兵头结点，请确保在InitQueue之后没有其他指针指向它  
  
    return 0;  
}