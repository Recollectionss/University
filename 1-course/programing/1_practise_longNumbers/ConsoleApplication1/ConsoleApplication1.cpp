
// Я реалізував цю задачу по принципу додавання в стопчик 

#pragma warning(disable : 6001)
#pragma warning(disable : 6292)

#include <iostream>
#include <string>

int* factorial(int);
int* multiply(int*, int, size_t);
int* add(int*, int*, size_t);
std::string It_is_rewriting_the_sum(int*, size_t);
int* check(int*, size_t&);

size_t length;

int main()
{
 
        int num = 0; // число N - факторіал якого ми шукаємо
        for (; num < 200; num++)
        {
            int* result = factorial(num);
            for (int i = 0; i < length; i++)
                std::cout << result[i];
            std::cout << "\n";
        }
        
    
}

int* factorial(int a)
{
    std::string sum = "1";
    int* prod = new int[1] {1};
    for (int i = 1; i < a + 1; i++) {
        int mult_1 = i % 10;
        int mult_2 = (i - mult_1) / 10; // розбивання числа на яке ми множемо на окремі множники (типу 15 розбиваємо на 1 і 5)
        size_t len = sum.length();

        int* smnd_1 = multiply(prod, mult_1, len); // знаходимо перший доданок
        int* smnd_2 = multiply(prod, mult_2, len); // знаходимо другий доданок

        delete[] prod;
        prod = add(smnd_1, smnd_2, len); // додавання в стопчик

        delete[] smnd_1, smnd_2;
        prod = check(prod, len); // видалення лишніх нулів спереду, якщо вони є 

        sum = It_is_rewriting_the_sum(prod, len); // запис кінцевого результату
    }
    length = sum.length();
    int* summary = new int[length];
    for (int i = 0; i < length; i++)
        summary[i] = sum[i] - '0';

    return summary;
}

int* multiply(int* big_fac, int small_fac, size_t big_fac_size)
{
    int first = 0, second = 0;
    int* num = new int[big_fac_size + 1];
    for (int i = 0; i < big_fac_size + 1; i++)
        num[i] = 0;
    for (int i = 0; i <= big_fac_size; i++) {
        if (i == big_fac_size) {
            num[0] = second;
            break;
        }
        int product = big_fac[big_fac_size - 1 - i] * small_fac + second;
        first = product % 10;
        num[big_fac_size - i] = first;
        second = product / 10;
    }
    return num;
}

int* add(int* fac_1, int* fac_2, size_t fac_size)
{
    int first = 0, second = 0, help = 0;
    int* num = new int[fac_size + 2];
    for (int i = 0; i < fac_size + 2; i++)
        num[i] = 0;

    for (int i = 0; i <= fac_size; i++) {
        first = fac_1[fac_size - i];
        int summary = first + second + help;
        if (i == fac_size) {
            num[1] = (fac_2[1] + first + help) % 10;
            num[0] = fac_2[0] + (fac_2[1] + first + help) / 10;
            break;
        }
        help = summary / 10;
        second = fac_2[fac_size - i];
        num[fac_size + 1 - i] = summary % 10;
    }
    return num;
}

std::string It_is_rewriting_the_sum(int* prod, size_t size)
{
    std::string sum;
    for (int i = 0; i < size; i++)
        sum += std::to_string(prod[i]);
    return sum;
}

int* check(int* arr, size_t& leng)
{
    leng += 2;
    size_t len = leng;

    for (int i = 0; i >= 0; i++) {
        if (arr[i] == 0) leng--;
        else break;
    }
    int* num = new int[leng];
    for (int i = 0; i < leng; i++)
        num[i] = arr[len - leng + i];

    return num;
};