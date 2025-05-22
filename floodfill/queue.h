#ifndef QUEUE_H
#define QUEUE_H

#include <queue>  


// Define a struct to represent each queue node with coordinates (x, y) and manhattan distance.
struct QueueNode {
    int x, y, distance;
    QueueNode(int _x, int _y, int _dist) : x(_x), y(_y), distance(_dist) {}
};

// Queue class to store QueueNode objects
class Queue {
public:
    Queue() = default;  
    ~Queue() = default; 

    // Add an item to the back of queue
    void push(int x, int y, int distance);

    // Remove an item from the front the queue
    QueueNode pop();

    // Check if the queue is empty
    bool isEmpty() const;

private:
    std::queue<QueueNode> queue;  // Store QueueNode objects
};
#endif // QUEUE_H

