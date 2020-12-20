#include <iostream>
#include <unordered_map>

class LFUCache {
private: // Classes
    struct Bucket;

    struct Blob {
    public: // Data
        int _key{0};
        int _value{0};
    public: // Constructors/destructors
        Blob(int key, int value) : _key(key), _value(value) {}
    };

    struct Node {
    public: // Data
        Blob _blob;
        // Controlled by bucket
        Node* _prev{nullptr}; // front
        Node* _next{nullptr}; // back
        Bucket* _bucket{nullptr};
    public:// Constructors/destructors
        Node(int key, int value) : _blob(key, value) {}
    public: // Helpers
        void remove() {
            if (_bucket->_front == this) {

            }
            if (_bucket->_back == this) {

            }
        }
    public: // Utility
        void update(int value) {
        }
        void touch() {
        }
    };

    struct Bucket {
    public: // Data
        int _frequency{1};
        // Controlled by pqueue
        Bucket* _prev{nullptr}; // front
        Bucket* _next{nullptr}; // back
        // Controlled here
        Node* _front{nullptr};
        Node* _back{nullptr};
    public: // Utility
        bool empty() const {
            return (_front == nullptr);
        }
        void push_front(Node* ptr) {
            if (_front == nullptr) {
                _front = _back = ptr;
            } else {
                _front->_prev = ptr;
                ptr->_next = _front;
                _front = ptr;
            }
        }
        void push_back(Node* ptr) {
            if (_back == nullptr) {
                _front = _back = ptr;
            } else {
                _back->_next = ptr;
                ptr->_prev = _back;
                _back = ptr;
            }
        }
        Node* remove_front() {
            Node*ptr = nullptr;
            if (_front != nullptr) {
                if (_front == _back) {
                    ptr = _front;
                    _front = _back = nullptr;
                } else {
                    Node* next = _front->_next;
                    next->_prev = nullptr;
                    _front->_next = nullptr;
                    _front = next;
                }
            }
            return ptr;
        }
        Node* remove_back() {
            Node*ptr = nullptr;
            if (_back != nullptr) {
                if (_front == _back) {
                    ptr = _back;
                    _front = _back = nullptr;
                } else {
                    Node* prev = _back->_prev;
                    prev->_next = nullptr;
                    _back->_prev = nullptr;
                    _back = prev;
                }
            }
            return ptr;
        }
    };

    class PQueue {
    public: // Data
        // Contained data
        Bucket* _front{nullptr};
        Bucket* _back{nullptr};
    public: // Helpers
        Bucket* findOrCreateBucket() {
            Bucket* ptr = nullptr;
            if (_back == nullptr) {
                ptr = new Bucket();
                _front = _back = ptr;
            } else {
                if (_back->_frequency > 1) {
                    ptr = new Bucket();
                    _back->_next = ptr;
                    ptr->_prev = _back;
                    _back = ptr;
                } else {
                    ptr = _back;
                }
            }
            assert(ptr);
            return ptr;
        }

    public: // Utility
        void push(Node* n) {
            Bucket* ptr = findOrCreateBucket();
            ptr->push_front(n);
        }
        void pop() {
            if (_back != nullptr) {
                _back->remove_back();
                if (_back->empty()) {
                    if (_back == _front) {
                        delete _back;
                        _front = _back = nullptr;
                    } else {
                        _back->_prev->_next = nullptr;
                        _back = _back->_prev;
                    }
                }
            }
        }
    };

private: // Aliases
    using Repo = std::unordered_map<int, Node>;

private: // Data
    int _capacity;
    Repo _repo;
    PQueue _pqueue;

public:
    LFUCache(int capacity) : _capacity(capacity) {

    }

    int get(int key) {
        auto iter = _repo.find(key);
        if (iter != _repo.end()) {
            iter->second.touch();
            return iter->second._blob._value;
        }

        return -1;
    }

    void put(int key, int value) {
        auto iter = _repo.find(key);
        if (iter == _repo.end()) {
            Node n(key, value);
            _repo.emplace(n._blob._key, std::move(n));
            _pqueue.push(&n);
        } else {
            iter->second.update(value);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
