#include <iostream>
#include <stdexcept>
#include <algorithm>

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

int main() {
    SequentialContainer<int> seqCont;

    // Добавление элементов
    for (int i = 0; i < 10; ++i) {
        seqCont.push_back(i);
    }

    // Вывод содержимого
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;

    // Удаление элементов
    seqCont.erase(2); // Удаление 3-го
    seqCont.erase(4); // Удаление 5-го
    seqCont.erase(5); // Удаление 7-го (сдвиг)

    // Вывод содержимого
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;

    // Добавление элементов
    seqCont.insert(0, 10); // В начало
    seqCont.insert(4, 20); // В середину
    seqCont.push_back(30); // В конец

    // Вывод содержимого
    seqCont.print();
    std::cout << "Size: " << seqCont.get_size() << std::endl;

    return 0;
}
