#include <iostream>
#include <unordered_map>
#include <cassert>

class LFUCache {
private: // Classes
    struct Bucket;
    class PQueue;

    struct Blob {
    public: // Data
        int _key{0};
        int _value{0};
    public: // Constructors/destructors
        Blob(int key, int value) : _key(key), _value(value) {}
    public: // Visualization
        void print() {
            std::cout << "[" << _key << ", " << _value << "]" ;
        }
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
            assert(_bucket);
            _bucket->remove(this);
            _bucket = nullptr;
        }
    public: // Utility
        void upgrade(int value) {
            _blob._value = value;
            promote();
        }
        void promote() {
            assert(_bucket);
            assert(_bucket->_frequency > 0);
            // next higher bucket
            Bucket* ptr = _bucket->insert_front(_bucket->_frequency + 1);
            remove();
            ptr->push_front(this);
        }
    public: // Visualization
        void print(const std::string& tab) {
            std::cout << tab << "[node=" << this << "] [bucket=" << _bucket << ", freq=" << _bucket->_frequency << "] ";
            _blob.print();
            std::cout << std::endl;
        }
    };

    struct Bucket {
    public: // Data
        int _frequency{1};
        // Controlled by pqueue
        Bucket* _prev{nullptr}; // front
        Bucket* _next{nullptr}; // back
        PQueue* _queue{nullptr};
        // Controlled here
        Node* _front{nullptr};
        Node* _back{nullptr};
    public: // Constructors/Destructors
        explicit Bucket(PQueue* q, int freq) : _queue(q), _frequency(freq) {}

    public: // Helpers
        Bucket* insert_front(int freq) {
            assert(_queue);
            return _queue->insert_front(this, freq);
        }
        void remove(Node* ptr) {
            assert(_front);
            assert(_back);
            if (_front == _back) {
                _front = _back = nullptr;
            } else {
                if (_front == ptr) {
                    Node* next = _front->_next;
                    next->_prev = nullptr;
                    _front->_next = nullptr;
                    _front = next;
                } else if (_back == ptr) {
                    Node* prev = _back->_prev;
                    prev->_next = nullptr;
                    _back->_prev = nullptr;
                    _back = prev;
                } else {
                    ptr->_prev->_next = ptr->_next;
                    ptr->_next->_prev = ptr->_prev;
                    ptr->_prev = nullptr;
                    ptr->_next = nullptr;
                }
            }
            if (empty()) {
                _queue->remove(this);
            }
        }
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
            if (ptr) {
                ptr->_bucket = this;
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
            if (ptr) {
                ptr->_bucket = this;
            }
        }
        Node* remove_front() {
            Node* ptr = nullptr;
            if (_front != nullptr) {
                ptr = _front;
                if (_front == _back) {
                    _front = _back = nullptr;
                } else {
                    Node* next = _front->_next;
                    next->_prev = nullptr;
                    _front->_next = nullptr;
                    _front = next;
                }
                ptr->_bucket = nullptr;
            }
            return ptr;
        }
        Node* remove_back() {
            Node* ptr = _back;
            if (_back != nullptr) {
                ptr = _back;
                if (_front == _back) {
                    _front = _back = nullptr;
                } else {
                    Node* prev = _back->_prev;
                    prev->_next = nullptr;
                    _back->_prev = nullptr;
                    _back = prev;
                }
                ptr->_bucket = nullptr;
            }
            return ptr;
        }
    public: // Visualization
        void print(const std::string& tab) {
            std::cout << tab << "[bucket=" << this << "] " << _frequency << std::endl;
            if (_front == nullptr) {
                assert(_back == nullptr);
                std::cout << tab << "[null]" << std::endl;
            } else {
                std::string tab2(tab + "    ");
                std::cout << tab << "nodes [" << std::endl;
                Node* next = _front;
                while (next) {
                    next->print(tab2);
                    next = next->_next;
                }
                std::cout << tab << "]" << std::endl;
            }
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
                ptr = new Bucket(this, 1);
                _front = _back = ptr;
            } else {
                if (_back->_frequency > 1) {
                    ptr = new Bucket(this, 1);
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
        Bucket* insert_front(Bucket* ref, int freq) {
            assert(ref);
            assert(_front);
            assert(_back);

            if (ref->_frequency == freq) {
                return ref;
            } else if (ref->_prev && ref->_prev->_frequency == freq) {
                return ref->_prev;
            }
            Bucket* ptr = nullptr;
            if (ref->_prev == nullptr ||
                ref->_prev->_frequency > freq) {
                // Add a bucket with freq
                ptr = new Bucket(this, freq);
                if (_front == ref) {
                    ptr->_next = ref;
                    _front = ptr;
                    ref->_prev = ptr;
                } else {
                    ptr->_next = ref;
                    ptr->_prev = ref->_prev;
                    ref->_prev->_next = ptr;
                    ref->_prev = ptr;
                }
            }
            return ptr;
        }
        void remove(Bucket* ptr) {
            assert(_front);
            assert(_back);
            if (_front == _back) {
                _front = _back = nullptr;
            } else {
                if (_front == ptr) {
                    Bucket* next = _front->_next;
                    next->_prev = nullptr;
                    _front->_next = nullptr;
                    _front = next;
                } else if (_back == ptr) {
                    Bucket* prev = _back->_prev;
                    prev->_next = nullptr;
                    _back->_prev = nullptr;
                    _back = prev;
                } else {
                    ptr->_prev->_next = ptr->_next;
                    ptr->_next->_prev = ptr->_prev;
                    ptr->_prev = nullptr;
                    ptr->_next = nullptr;
                }
            }
            assert(ptr->_front == nullptr);
            assert(ptr->_back == nullptr);
            delete ptr;
        }
    public: // Utility
        void push(Node* n) {
            Bucket* ptr = findOrCreateBucket();
            ptr->push_front(n);
        }
        Node* pop() {
            Node* ptr = nullptr;
            if (_back != nullptr) {
                ptr = _back->remove_back();
                if (_back->empty()) {
                    if (_back == _front) {
                        assert(_back->_front == nullptr);
                        assert(_back->_back == nullptr);
                        delete _back;
                        _front = _back = nullptr;
                    } else {
                        _back->_prev->_next = nullptr;
                        _back = _back->_prev;
                    }
                }
            }
            return ptr;
        }
    public: // Visualization
        void print() {
            std::cout << "pqueue [" << std::endl;
            std::string tab("    ");
            if (_front == nullptr) {
                assert(_back == nullptr);
                std::cout << tab << "[null]" << std::endl;
            } else {
                std::string tab2(tab + "    ");
                std::cout << tab << "buckets [" << std::endl;
                Bucket* next = _front;
                while (next) {
                    next->print(tab2);
                    next = next->_next;
                }
                std::cout << tab << "]" << std::endl;
            }
            std::cout << "]" << std::endl;
        }
    };

private: // Aliases
    using Repo = std::unordered_map<int, Node*>;

private: // Data
    int _capacity;
    Repo _repo;
    PQueue _pqueue;

public: // Visualizations
    void print(const std::string& msg) {
        std::cout << "[" << msg << "] --" << std::endl;
        _pqueue.print();
        std::cout << "repo [" << std::endl;
        for (auto& p : _repo) {
            p.second->print("    ");
        }
        std::cout << "]" << std::endl;
    }

public:
    LFUCache(int capacity) : _capacity(capacity) {

    }

    int get(int key) {
        auto iter = _repo.find(key);
        if (iter != _repo.end()) {
//            iter->second->print("--promote-key(" + std::to_string(key) + ")--");
            iter->second->promote();
            return iter->second->_blob._value;
        }

        return -1;
    }

    void put(int key, int value) {
        if (_capacity <= 0) {
            return;
        }
        auto iter = _repo.find(key);
        if (iter == _repo.end()) {
            if (_capacity <= _repo.size()) {
                Node* ptr = _pqueue.pop();
                assert(ptr);
                if (ptr != nullptr) {
                    int erased = _repo.erase(ptr->_blob._key);
                    assert(erased > 0);
                    assert(ptr->_prev == nullptr);
                    assert(ptr->_next == nullptr);
                    assert(ptr->_bucket == nullptr);
                }
                delete ptr;
            }
            Node* ptr = new Node(key, value);
            _repo.emplace(ptr->_blob._key, ptr);
            _pqueue.push(ptr); // Evict as necessary
        } else {
            iter->second->upgrade(value);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// Input
//  ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
//  [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
// Output
//  [null, null, null, 1, null, -1, 3, null, -1, 3, 4]

void runtest1() {
    LFUCache lfu(2);
    lfu.print("lfu(2)");
    lfu.put(1, 1);
    lfu.print("put(1, 1)");
    lfu.put(2, 2);
    lfu.print("put(2, 2)");
    int res0 = lfu.get(1);      // return 1
    lfu.print("get(1)=" + std::to_string(res0));
    lfu.put(3, 3);   // evicts key 2
    lfu.print("put(3, 3)");
    int res1 = lfu.get(2);      // return -1 (not found)
    lfu.print("get(2)=" + std::to_string(res1));
    int res2 = lfu.get(3);      // return 3
    lfu.print("get(3)=" + std::to_string(res2));
    lfu.put(4, 4);   // evicts key 1.
    lfu.print("put(4, 4)");
    int res3 = lfu.get(1);      // return -1 (not found)
    lfu.print("get(1)=" + std::to_string(res3));
    int res4 = lfu.get(3);      // return 3
    lfu.print("get(3)=" + std::to_string(res4));
    int res5 = lfu.get(4);      // return 4
    lfu.print("get(4)=" + std::to_string(res5));

    std::cout << "[null, null, null, 1, null, -1, 3, null, -1, 3, 4]" << std::endl;
    std::cout << "[null, null, null, " << res0 << ", null, " << res1 << ", " << res2 << ", null, " << res3 << ", " << res4 << ", " << res5 << "]" << std::endl;
}

//["LFUCache","put","get"]
//[[0],[0,0],[0]]
// [null,null,-1]
void runtest2() {
    LFUCache lfu(0);
    lfu.print("lfu(0)");
    lfu.put(0, 0);
    lfu.print("put(0, 0)");
    int res0 = lfu.get(0);      // return 1
    lfu.print("get(0)=" + std::to_string(res0));
    std::cout << "[null,null,-1]" << std::endl;
    std::cout << "[null, null, " << res0 << "]" << std::endl;
}

void runtest3() {

}
int main() {
//    runtest1();
    runtest2();
    return 0;
}
