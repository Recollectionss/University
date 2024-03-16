//
//  main.cpp
//  AiC
//
//  Created by Илья Гончаренко on 25.11.2023.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функція для обчислення відстані Левенштейна-Дамерау та отримання послідовності операцій
int LevenshteinDistance(string str1, string str2) {
    int len1 = str1.length();
    int len2 = str2.length();

    // Створення матриці для зберігання відстаней між підстрічками
    vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));

    for (int i = 0; i <= len1; ++i) {
        for (int j = 0; j <= len2; ++j) {
            // Ініціалізація базових значень для порожніх рядків
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});

            // Перевірка можливості виконання операції транспозиції (Damerau)
            if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1])
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + 1);
        }
    }

    // Виведення послідовності операцій для перетворення рядка str1 в рядок str2
    int i = len1, j = len2;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && str1[i - 1] == str2[j - 1]) {
            // Символи співпадають, переходимо до попередніх позицій
            --i;
            --j;
        } else if (i > 0 && j > 0 && str1[i - 1] != str2[j - 1] && dp[i][j] == dp[i - 1][j - 1] + 1) {
            // Заміна символу
            cout << "Replace '" << str1[i - 1] << "' at position " << i << " with '" << str2[j - 1] << "'" << endl;
            --i;
            --j;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            // Видалення символу
            cout << "Delete '" << str1[i - 1] << "' at position " << i << endl;
            --i;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            // Вставка символу
            cout << "Insert '" << str2[j - 1] << "' at position " << i + 1 << endl;
            --j;
        } else if (i > 1 && j > 1 && str1[i - 1] == str2[j - 2] && str1[i - 2] == str2[j - 1] && dp[i][j] == dp[i - 2][j - 2] + 1) {
            // Транспозиція
            cout << "Transpose '" << str1[i - 2] << "' at position " << i - 1 << " and '" << str1[i - 1] << "' at position " << i << endl;
            i -= 2;
            j -= 2;
        }
    }

    return dp[len1][len2];
}

int main() {
    setlocale(LC_ALL, "uk_UA.utf8");
    string str1 = "hello";
    string str2 = "wrolddddd";

    int distance = LevenshteinDistance(str1, str2);

    cout << "Відстань Левенштейна-Дамерау між рядками '" << str1 << "' та '" << str2 << "': " << distance << endl;

    return 0;
}
