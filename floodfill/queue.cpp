// Implementations of the Queue class

#include "queue.h"

// Push a new QueueNode to the back of the queue
void Queue::push(int x, int y, int distance) {
    queue.push(QueueNode(x, y, distance));  // Add the new QueueNode to the queue
}

// Pop a QueueNode from the front of the queue
QueueNode Queue::pop() {
    if (!isEmpty()) {
        QueueNode frontNode = queue.front();
        queue.pop();  // Remove the front element
        return frontNode;
    }
    // Returning a default-initialized QueueNode in case of error (empty queue)
    return QueueNode(-1, -1, -1);
}

// Check if the queue is empty
bool Queue::isEmpty() const {
    return queue.empty();
}