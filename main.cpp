#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
template <class T>
class SafeQueue {
private:
std::queue<T> mainQueue;
std::mutex door;
public:
    void Push(const T& value) {
        door.lock();
        mainQueue.push(value);
        door.unlock();
    }
    T Pop() {
        door.lock();
        mainQueue.pop();
        door.unlock();
        return mainQueue.front();
    }
    bool TryPop(T&value) {
        if(door.try_lock()){
            value =mainQueue.front();
            mainQueue.pop();
            return true;
        } else return false;
    }
};
int main() {
SafeQueue<int>q;
q.Push(5);
q.Push(5);
q.Push(4);
q.Push(8);
q.Push(1);
q.Pop();
}
