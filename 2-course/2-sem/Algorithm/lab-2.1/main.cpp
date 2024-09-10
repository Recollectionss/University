#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

// Визначення кольорів вершин дерева
enum Color { RED, BLACK };

// Структура відрізка
template <typename T>
struct Segment {
    complex<T> start; // Початкова точка відрізка
    complex<T> end;   // Кінцева точка відрізка

    // Конструктор
    Segment(const complex<T>& start, const complex<T>& end) : start(start), end(end) {}
};

// Структура вершини дерева
template <typename T>
struct Node {
    Segment<T> segment; // Відрізок, який зберігається в цій вершині
    Color color;        // Колір вершини
    Node *left, *right, *parent; // Вказівники на дочірні та батьківську вершини

    // Конструктор
    Node(const Segment<T>& segment) : segment(segment), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Клас для червоно-чорного дерева відрізків
template <typename T>
class RedBlackTree {
private:
    Node<T>* root; // Корінь дерева

    // Функція для лівого повороту
    void leftRotate(Node<T>* x) {
        Node<T>* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Функція для правого повороту
    void rightRotate(Node<T>* x) {
        Node<T>* y = x->left;
        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    // Функція для вставки в дерево
    void insertFixup(Node<T>* z) {
        while (z != root && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<T>* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node<T>* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Функція для вставки нового відрізка
    void insert(const Segment<T>& segment) {
        Node<T>* z = new Node<T>(segment);
        Node<T>* y = nullptr;
        Node<T>* x = root;

        while (x != nullptr) {
            y = x;
            if (z->segment.start < x->segment.start)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == nullptr)
            root = z;
        else if (z->segment.start < y->segment.start)
            y->left = z;
        else
            y->right = z;

        insertFixup(z);
    }

public:
    // Конструктор з масивом комплексних чисел
    RedBlackTree(const vector<complex<T>>& arr) : root(nullptr) {
        // Створюємо відрізки з елементів масиву та вставляємо їх у дерево
        for (size_t i = 0; i < arr.size(); i += 2) {
            Segment<T> segment(arr[i], arr[i + 1]);
            insert(segment);
        }
    }

    // Деструктор
    ~RedBlackTree() {
        // Реалізація видалення дерева залишається за межами цього прикладу
    }

    // Функція для знаходження мінімального відрізку
    Segment<T> findMinSegment() const {
        Node<T>* node = root;
        while (node->left != nullptr)
            node = node->left;
        return node->segment;
    }

    // Функція для знаходження максимального відрізку
    Segment<T> findMaxSegment() const {
        Node<T>* node = root;
        while (node->right != nullptr)
            node = node->right;
        return node->segment;
    }

    // Функція для знаходження довжини відрізків
    T findSegmentLength(const Segment<T>& segment) const {
        return abs(segment.end - segment.start);
    }
};

int main() {
    // Масив комплексних чисел
    vector<complex<double>> complexArray = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}};

    // Створення дерева відрізків
    RedBlackTree<double> tree(complexArray);

    // Знаходження та виведення мінімального та максимального відрізків
    Segment<double> minSegment = tree.findMinSegment();
    Segment<double> maxSegment = tree.findMaxSegment();
    cout << "Minimum segment: (" << minSegment.start.real() << ", " << minSegment.start.imag() << ") - ("
         << minSegment.end.real() << ", " << minSegment.end.imag() << ")" << endl;
    cout << "Maximum segment: (" << maxSegment.start.real() << ", " << maxSegment.start.imag() << ") - ("
         << maxSegment.end.real() << ", " << maxSegment.end.imag() << ")" << endl;

    return 0;
}

