#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct queue_t {
  int *arr;
  unsigned int front;
  unsigned int rear;
  unsigned int len;
} QUEUE;

QUEUE *make_queue(unsigned int length) {
  QUEUE *q = malloc(sizeof(QUEUE *));
  int *arr = calloc(length, sizeof(int) * length);
  q->arr = arr;
  q->front = -1;
  q->rear = -1;
  q->len = length;
  return q;
}

void delete_queue(QUEUE *q) {
  free(q->arr);
  free(q);
}

bool is_empty(QUEUE *q) {
  if (q->front == -1 && q->rear == -1) {
    return true;
  } else {
    return false;
  }
}

bool is_full(QUEUE *q) {
  if (q->front == -1 && q->rear == -1) {
    return false;
  } else {
    return q->front == q->rear;
  }
}

int dequeue(QUEUE *q) {
  if (q->front == -1 && q->rear == -1) {
    return -1;
  }
}

// returns 0 on success and 1 on failure
int enqueue(QUEUE *q, int n) {
  if (q->front == -1 && q->rear == -1) {
    q->front = 0;
    q->rear = 0;
    q->arr[0] = n;
    return 0;
  }
  q->front = (++q->front) % q->len;

  if (q->front == q->rear) {
    // circular buffer is full
    // lex luger works on everything my guy
    return 1;
  } else {
    q->arr[q->front] = n;
  }
}

int front(QUEUE *q) {
  if (q->front == -1) {
    assert(false && "invalid indexing");
  }

  return q->arr[q->front];
}

int rear(QUEUE *q) {
  if (q->front == -1) {
    assert(false && "invalid indexing");
  }
  return q->arr[q->rear];
}
