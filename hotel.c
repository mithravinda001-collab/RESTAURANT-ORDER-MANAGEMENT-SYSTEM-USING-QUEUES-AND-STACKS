#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct {
 int orderId;
 char item[50];
} Order;
typedef struct {
 Order orders[MAX];
 int front, rear;
} Queue;
typedef struct {
 Order orders[MAX];
 int top;
} Stack;
void initQueue(Queue *q) {
 q->front = q->rear = -1;
}
int isQueueEmpty(Queue *q) {
 return q->front == -1;
}
int isQueueFull(Queue *q) {
 return (q->rear + 1) % MAX == q->front;
}
void enqueue(Queue *q, Order order) {
 if (isQueueFull(q)) {
 printf("\nOrder queue is full! Cannot accept more orders.\n");
 return;
 }
 if (isQueueEmpty(q)) {
 q->front = q->rear = 0;
 } else {
10
 q->rear = (q->rear + 1) % MAX;
 }
 q->orders[q->rear] = order;
 printf("Order #%d for '%s' placed successfully.\n", order.orderId, order.item);
}
Order dequeue(Queue *q) {
 Order order = {-1, ""};
 if (isQueueEmpty(q)) {
 printf("\nNo pending orders.\n");
 return order;
 }
 order = q->orders[q->front];
 if (q->front == q->rear) {
 q->front = q->rear = -1;
 } else {
 q->front = (q->front + 1) % MAX;
 }
 return order;
}
void displayQueue(Queue *q) {
 if (isQueueEmpty(q)) {
 printf("\nNo pending orders.\n");
 return;
 }
 printf("\n--- Pending Orders ---\n");
 int i = q->front;
 while (1) {
 printf("- Order #%d : %s\n", q->orders[i].orderId, q->orders[i].item);
 if (i == q->rear) break;
 i = (i + 1) % MAX;
 }
}
void initStack(Stack *s) {
 s->top = -1;
}
int isStackEmpty(Stack *s) {
 return s->top == -1;
}
int isStackFull(Stack *s) {
11
 return s->top == MAX - 1;
}
void push(Stack *s, Order order) {
 if (isStackFull(s)) {
 printf("\nCompleted orders stack is full!\n");
 return;
 }
 s->orders[++s->top] = order;
 printf("Order #%d completed and stored.\n", order.orderId);
}
Order pop(Stack *s) {
 Order order = {-1, ""};
 if (isStackEmpty(s)) {
 printf("\nNo completed orders yet.\n");
 return order;
 }
 order = s->orders[s->top--];
 return order;
}
void displayStack(Stack *s) {
 if (isStackEmpty(s)) {
 printf("\nNo completed orders yet.\n");
 return;
 }
 printf("\n--- Completed Orders (Latest First) ---\n");
 for (int i = s->top; i >= 0; i--) {
 printf(" - Order #%d : %s\n", s->orders[i].orderId, s->orders[i].item);
 }
}
int main() {
 Queue pendingOrders;
 Stack completedOrders;
 initQueue(&pendingOrders);
 initStack(&completedOrders);

 int choice, orderId = 1;
 char item[50];

 printf("=== RESTAURANT ORDER MANAGEMENT SYSTEM ===\n");

12
 do {
 printf("\n===== Main Menu =====\n");
 printf("1. Place Order\n");
 printf("2. View Pending Orders\n");
 printf("3. Process Next Order\n");
 printf("4. View Completed Orders\n");
 printf("5. Retrieve Last Completed Order\n");
 printf("6. Exit\n");
 printf("Enter your choice: ");
 scanf("%d", &choice);
 getchar();

 switch (choice) {
 case 1:
 printf("Enter food item: ");
 fgets(item, sizeof(item), stdin);
 item[strcspn(item, "\n")] = 0;
 Order newOrder = {orderId++, ""};
 strcpy(newOrder.item, item);
 enqueue(&pendingOrders, newOrder);
 break;

 case 2:
 displayQueue(&pendingOrders);
 break;

 case 3: {
 Order nextOrder = dequeue(&pendingOrders);
 if (nextOrder.orderId != -1) {
 push(&completedOrders, nextOrder);
 }
 break;
 }

 case 4:
 displayStack(&completedOrders);
 break;

 case 5: {
 Order lastOrder = pop(&completedOrders);
 if (lastOrder.orderId != -1) {
 printf("\nRetrieved Last Completed Order: #%d - %s\n",
 lastOrder.orderId, lastOrder.item);
 }
13
 break;
 }

 case 6:
 printf("\nExiting system. Thank you!\n");
 break;

 default:
 printf("\nInvalid choice! Please try again.\n");
 }
 } while (choice != 6);

 return 0;
}