#include <iostream>
#include <queue>
#include <complex>

using namespace std;

// const int bucketSize = 5;

struct node {
    int size;
    bool isLeaf;
    complex<double> *keys;
    node **ptr;
};

class Btree {
private:
    node* root;

public:
    Btree() {
        root = NULL;
    }

    void insert(complex<double> key) {
        if (root == NULL) {
            root = new node;
            root->size = 0;
            root->isLeaf = true;
            root->keys = new complex<double>[2 * bucketSize - 1];
            root->ptr = new node*[2 * bucketSize];
            root->keys[0] = key;
            root->size = 1;
        } else {
            if (root->size == 2 * bucketSize - 1) {
                // Реалізуйте розщеплення кореневого вузла, якщо він заповнений
            } else {
                insertNonFull(root, key);
            }
        }
    }

    void insertNonFull(node* currentNode, complex<double> key) {
        int i = currentNode->size - 1;
        if (currentNode->isLeaf) {
            while (i >= 0 && key < currentNode->keys[i]) {
                currentNode->keys[i + 1] = currentNode->keys[i];
                i--;
            }
            currentNode->keys[i + 1] = key;
            currentNode->size++;
        } else {
            while (i >= 0 && key < currentNode->keys[i]) {
                i--;
            }
            if (currentNode->ptr[i + 1]->size == 2 * bucketSize - 1) {
                // Реалізуйте розщеплення дочірнього вузла, якщо він заповнений
            } else {
                insertNonFull(currentNode->ptr[i + 1], key);
            }
        }
    }


    void display(node* tNode) {
        if (tNode) {
            for (int j = 0; j < tNode->size; j++) {
                cout << tNode->keys[j] << " ";
            }
            cout << "\t";
            if (!tNode->isLeaf) {
                for (int j = 0; j < tNode->size + 1; j++)
                    if (tNode->ptr[j] != NULL)
                        q.push(tNode->ptr[j]);
            }
            cout << endl;
        }
    }

    node* findParent(node* current, node* child) {
        node* parent;
        if (current->isLeaf || (current->ptr[0])->isLeaf)
            return NULL;

        for (int i = 0; i < current->size + 1; i++) {
            if (current->ptr[i] == child) {
                parent = current;
                return parent;
            }
            else {
                parent = findParent(current->ptr[i], child);
                if (parent != NULL)
                    return parent;
            }
        }
        return parent;
    }

    node* getRoot() {
        return root;
    }
    // Пошук елемента у B+ дереві
    bool search(const T& key, Node* node) {
        if (node == nullptr) {
            return false; // Досягнуто кінця дерева, елемент не знайдено
        }

        // Якщо поточний вузол - лист, шукаємо ключ у його списку
        if (node->isLeaf) {
            for (int i = 0; i < node->numKeys; ++i) {
                if (node->keys[i] == key) {
                    return true; // Знайдено елемент
                }
            }
            return false; // Елемент не знайдено у листовому вузлі
        }

        // Якщо поточний вузол - не лист, рекурсивно шукаємо у відповідному піддереві
        int i = 0;
        while (i < node->numKeys && key > node->keys[i]) {
            ++i;
        }
        return search(key, node->children[i]);
    }

    // Видалення елемента з B+ дерева
    void remove(const T& key, Node* node) {
        if (node == nullptr) {
            return; // Елемент не знайдено
        }

        // Шукаємо індекс елемента в поточному вузлі
        int i = 0;
        while (i < node->numKeys && key > node->keys[i]) {
            ++i;
        }

        // Якщо поточний вузол - лист, видаляємо елемент, якщо він знайдений
        if (node->isLeaf) {
            if (i < node->numKeys && node->keys[i] == key) {
                for (int j = i; j < node->numKeys - 1; ++j) {
                    node->keys[j] = node->keys[j + 1];
                }
                node->numKeys--;
            }
            return;
        }

        // Якщо поточний вузол - не лист, рекурсивно видаляємо у відповідному піддереві
        remove(key, node->children[i]);
    }

};

int main() {
    Btree node;
    cout << "The size of bucket is " << bucketSize << "! " << endl;

    node.insert(complex<double>(1.0, 2.0));
    node.insert(complex<double>(3.0, 4.0));
    node.insert(complex<double>(5.0, 6.0));
    node.display(node.getRoot());

    return 0;
}
