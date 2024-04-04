#include <iostream>
#include <vector>
#include <atomic>
#include <mutex>
#include <memory>
#include <climits>
#include <random>

// Define the maximum level of the skip list
const int MAX_LEVEL = 16;

// Random level generator
int randomLevel()
{
    static std::default_random_engine generator;
    static std::geometric_distribution<int> distribution(0.5); // p = 0.5
    return std::min(distribution(generator) + 1, MAX_LEVEL);
}

// Node structure
template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    std::vector<std::atomic<Node<Key, Value> *>> forward;
    Node(int level, Key k, Value v) : key(k), value(v), forward(level + 1) {}
};

// Concurrent skip list class
template <typename Key, typename Value>
class ConcurrentSkipList
{
private:
    std::atomic<Node<Key, Value> *> head;
    std::atomic<int> level;
    std::mutex mtx; // Mutex for concurrent access

public:
    ConcurrentSkipList() : head(new Node<Key, Value>(MAX_LEVEL, Key(), Value())), level(0) {}

    // Search for a key in the skip list
    bool search(const Key &key, Value &value)
    {
        Node<Key, Value> *x = head.load();
        for (int i = level.load(); i >= 0; --i)
        {
            Node<Key, Value> *next = x->forward[i].load();
            while (next && next->key < key)
            {
                x = next;
                next = x->forward[i].load();
            }
        }
        x = x->forward[0].load();
        if (x && x->key == key)
        {
            value = x->value;
            return true;
        }
        return false;
    }

    // Insert a key-value pair into the skip list
    void insert(const Key &key, const Value &value)
    {
        std::vector<Node<Key, Value> *> update(MAX_LEVEL + 1);
        Node<Key, Value> *x = head.load();
        for (int i = level.load(); i >= 0; --i)
        {
            Node<Key, Value> *next = x->forward[i].load();
            while (next && next->key < key)
            {
                x = next;
                next = x->forward[i].load();
            }
            update[i] = x;
        }
        x = x->forward[0].load();
        if (x && x->key == key)
        {
            x->value = value; // Update value if key already exists
            return;
        }

        int newLevel = randomLevel();
        if (newLevel > level.load())
        {
            for (int i = level.load() + 1; i <= newLevel; ++i)
            {
                update[i] = head.load();
            }
            level.store(newLevel);
        }

        Node<Key, Value> *newNode = new Node<Key, Value>(newLevel, key, value);
        for (int i = 0; i <= newLevel; ++i)
        {
            newNode->forward[i].store(update[i]->forward[i].load());
            update[i]->forward[i].store(newNode);
        }
    }

    // Delete a key from the skip list
    void erase(const Key &key)
    {
        std::vector<Node<Key, Value> *> update(MAX_LEVEL + 1);
        Node<Key, Value> *x = head.load();
        for (int i = level.load(); i >= 0; --i)
        {
            Node<Key, Value> *next = x->forward[i].load();
            while (next && next->key < key)
            {
                x = next;
                next = x->forward[i].load();
            }
            update[i] = x;
        }
        x = x->forward[0].load();
        if (x && x->key == key)
        {
            for (int i = 0; i <= level.load(); ++i)
            {
                if (update[i]->forward[i].load() != x)
                    break;
                update[i]->forward[i].store(x->forward[i].load());
            }
            delete x; // Free the memory
            while (level.load() > 0 && !head.load()->forward[level.load()].load())
            {
                level.fetch_sub(1);
            }
        }
    }

    // Function to print the skip list layer by layer
    void print()
    {
        std::cout << "Skip List:" << std::endl;
        for (int i = level.load(); i >= 0; --i)
        {
            Node<Key, Value> *node = head.load()->forward[i].load();
            std::cout << "Level " << i << ": ";
            while (node)
            {
                std::cout << "(" << node->key << ", " << node->value << ") ";
                node = node->forward[i].load();
            }
            std::cout << std::endl;
        }
    }
};

#include <thread>

int main()
{
    ConcurrentSkipList<int, std::string> skipList;

    // Create threads for inserting elements
    std::thread insertThread1([&skipList]()
                              { skipList.insert(1, "One"); });
    std::thread insertThread2([&skipList]()
                              { skipList.insert(2, "Two"); });
    std::thread insertThread3([&skipList]()
                              { skipList.insert(3, "Three"); });
    std::thread insertThread4([&skipList]()
                              { skipList.insert(4, "Four"); });
    std::thread insertThread5([&skipList]()
                              { skipList.insert(5, "Five"); });
    std::thread insertThread6([&skipList]()
                              { skipList.insert(6, "Six"); });
    std::thread insertThread7([&skipList]()
                              { skipList.insert(7, "Seven"); });                          

    // Wait for insert threads to finish
    insertThread1.join();
    insertThread2.join();
    insertThread3.join();
    insertThread4.join();
    insertThread5.join();
    insertThread6.join();
    insertThread7.join();

    // Create threads for searching elements
    std::thread searchThread1([&skipList]()
                              {
        std::string value;
        if (skipList.search(1, value)) {
            std::cout << "Thread 1: Found " << value << std::endl;
        } else {
            std::cout << "Thread 1: Not found" << std::endl;
        } });

    std::thread searchThread2([&skipList]()
                              {
        std::string value;
        if (skipList.search(2, value)) {
            std::cout << "Thread 2: Found " << value << std::endl;
        } else {
            std::cout << "Thread 2: Not found" << std::endl;
        } });

    // Wait for search threads to finish
    searchThread1.join();
    searchThread2.join();
    skipList.print();
    // Create a thread for deleting an element
    std::thread deleteThread([&skipList]()
                             {
        skipList.erase(2);
        std::cout << "Thread 3: Deleted key 2" << std::endl; });

    deleteThread.join();

    // Check if the deleted element is still present f
    std::thread searchThread3([&skipList]()
                              {
        std::string value;
        if (skipList.search(2, value)) {
            std::cout << "Thread 4: Found " << value << std::endl;
        } else {
            std::cout << "Thread 4: Not found" << std::endl;
        } });

    searchThread3.join();
    skipList.print();

    return 0;
}