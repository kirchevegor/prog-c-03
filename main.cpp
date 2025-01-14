#include <iostream>
#include <stdexcept>

// Последовательный контейнер (массив)
template <typename T>
class SequentialContainer {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 1.5;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    SequentialContainer() : data(nullptr), capacity(0), size(0) {}

    ~SequentialContainer() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) {
            resize();
        }
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    size_t get_size() const {
        return size;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << (i < size - 1 ? ", " : "\n");
        }
    }
};

// Двунаправленный связанный список
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++size;
    }

    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
        } else {
            Node* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }
        if (!newNode->next) tail = newNode;
        ++size;
    }

    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
        delete current;
        --size;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << (current->next ? ", " : "\n");
            current = current->next;
        }
    }

    size_t get_size() const {
        return size;
    }
};

// Односвязный связанный список
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        ++size;
    }

    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        Node* current = head;
        if (index == 0) {
            head = current->next;
            delete current;
        } else {
            Node* prev = nullptr;
            for (size_t i = 0; i < index; ++i) {
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            delete current;
        }
        --size;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << (current->next ? ", " : "\n");
            current = current->next;
        }
    }

    size_t get_size() const {
        return size;
    }
};

int main() {
    // Демонстрация для SequentialContainer
    std::cout << "SequentialContainer:" << std::endl;
    SequentialContainer<int> seqCont;
    for (int i = 0; i < 10; ++i) {
        seqCont.push_back(i);
    }
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;
    seqCont.erase(2);
    seqCont.erase(4);
    seqCont.erase(5);
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;
    seqCont.insert(0, 10);
    seqCont.insert(4, 20);
    seqCont.push_back(30);
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;

    // Демонстрация для DoublyLinkedList
    std::cout << "\nDoublyLinkedList:" << std::endl;
    DoublyLinkedList<int> doublyList;
    for (int i = 0; i < 10; ++i) {
        doublyList.push_back(i);
    }
    doublyList.print();
    std::cout << "Size: " << doublyList.get_size() << std::endl;
    doublyList.erase(2);
    doublyList.erase(4);
    doublyList.erase(5);
    doublyList.print();
    std::cout << "Size: " << doublyList.get_size() << std::endl;
    doublyList.insert(0, 10);
    doublyList.insert(4, 20);
    doublyList.push_back(30);
    doublyList.print();
    std::cout << "Size: " << doublyList.get_size() << std::endl;

    // Демонстрация для SinglyLinkedList
    std::cout << "\nSinglyLinkedList:" << std::endl;
    SinglyLinkedList<int> singlyList;
    for (int i = 0; i < 10; ++i) {
        singlyList.push_back(i);
    }
    singlyList.print();
    std::cout << "Size: " << singlyList.get_size() << std::endl;
    singlyList.erase(2);
    singlyList.erase(4);
    singlyList.erase(5);
    singlyList.print();
    std::cout << "Size: " << singlyList.get_size() << std::endl;
    singlyList.insert(0, 10);
    singlyList.insert(4, 20);
    singlyList.push_back(30);
    singlyList.print();
    std::cout << "Size: " << singlyList.get_size() << std::endl;

    return 0;
}
