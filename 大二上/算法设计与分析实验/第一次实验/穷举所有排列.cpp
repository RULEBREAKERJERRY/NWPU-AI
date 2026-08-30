#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void generatePermutations(char s[], int start, int end) {
    if (start == end) {
        for (int i = 0; i <= end; ++i) {
            std::cout << s[i];
        }
        std::cout << std::endl;
        return;
    }
    for (int i = start; i <= end; ++i) {
        std::swap(s[start], s[i]);
        generatePermutations(s, start + 1, end);
        std::swap(s[start], s[i]);
    }
}

int main() {
    int n;
    std::cin >> n;
    if (n > 0 && n < 10) {
        char letters[10];
        for (int i = 0; i < n; ++i) {
            letters[i] = 'a' + i;
        }
        generatePermutations(letters, 0, n - 1);
    }
    return 0;
}