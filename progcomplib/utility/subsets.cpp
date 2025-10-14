#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> generatePowerSet(const vector<int>& original_set) {
    int n = original_set.size();
    int power_set_size = 1 << n; // 2^n
    vector<vector<int>> power_set(power_set_size); // Pré-aloca o tamanho exato

    for (int i = 0; i < power_set_size; i++) {
        for (int j = 0; j < n; j++) {
            // Se o j-ésimo bit de 'i' está ligado, o elemento 'j' pertence ao subconjunto
            if (i & (1 << j)) {
                power_set[i].push_back(original_set[j]);
            }
        }
    }
    return power_set;
}

// Exemplo de uso
void demoPowerSet() {
    vector<int> my_set = {1, 2, 3};
    vector<vector<int>> result = generatePowerSet(my_set);

    printf("Conjunto das partes de {1, 2, 3}:\n");
    for (const auto& subset : result) {
        printf("{ ");
        for (int val : subset) {
            printf("%d ", val);
        }
        printf("}\n");
    }
}
