#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Drop {
public:
    int numerator; // чисельник
    int denominator; // знаменник
Drop(int numerator, int denominator) : numerator(numerator), denominator(denominator) {}
};

class H_entry {
public:
    Drop key;
    int hash;
    H_entry* next;

    H_entry(Drop k, int h) : key(k), hash(h), next(nullptr) {}
};

class HashTable {
private:
    vector<H_entry*> table;
    vector<Drop> keys; // Вектор для зберігання ключів
    int size;

public:
    HashTable(int s) : size(s) {
        table.resize(size, nullptr);
    }

    int hash(Drop key, int i) {
        int a = 7; // випадково обране натуральне число
        int b = 11; // випадково обране натуральне число
        int n = findPrime(size); // Знаходимо найближче просте число до розміру таблиці
        return ((a * abs(key.numerator) + b * abs(key.denominator)) + i * b) % n;
    }

    int findPrime(int n) {
        for (int i = n - 1; i >= 2; --i) {
            bool isPrime = true;
            for (int j = 2; j <= sqrt(i); ++j) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return i;
        }
        return 2; // Повертаємо 2 як найменше просте число, якщо нічого інше не знайдено
    }

    void insert(Drop key) {
        if (getHash(key) != -1) {
            cerr << "Key " << key.numerator << "/" << key.denominator << " already exists in the hash table." << endl;
            return;
        }
        int i = 0;
        int h;
        do {
            h = hash(key, i);
            if (table[h] == nullptr) {
                table[h] = new H_entry(key, h);
                keys.push_back(key); // Додаємо ключ до вектора
                return;
            }
            i++;
        } while (i < size);
        cerr << "Hash table is full, failed to insert key " << key.numerator << "/" << key.denominator << endl;
    }

    int getHash(Drop key) {
        int i = 0;
        int h;
        do {
            h = hash(key, i);
            H_entry* entry = table[h];
            while (entry != nullptr) {
                if (entry->key.numerator == key.numerator && entry->key.denominator == key.denominator) {
                    return entry->hash;
                }
                entry = entry->next;
            }
            i++;
        } while (table[h] != nullptr && i < size);
        return -1; // Ключ не знайдено
    }

    // Функція для виводу хешування в порядку зростання ключів
    void printHash() {
        sort(keys.begin(), keys.end(), [](const Drop& a, const Drop& b) {
            return (double)a.numerator / a.denominator < (double)b.numerator / b.denominator;
        }); // Сортуємо ключі
        for (Drop key : keys) {
            cout << "Hash for " << key.numerator << "/" << key.denominator << ": " << getHash(key) << endl;
        }
    }
};

int main() {
    HashTable Hashing(6); // Розмір діапазону

    // Додати ключі
    Hashing.insert(Drop(3, 7));
    Hashing.insert(Drop(1, 5));
    Hashing.insert(Drop(2, 6));
    Hashing.insert(Drop(2, 6));

    Hashing.printHash();

    return 0;
}
