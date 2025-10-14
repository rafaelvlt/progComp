#include <bits/stdc++.h>

using namespace std;

void generateAndProcessPermutations(vector<int>& items) {
    // Ordenar para garantir que todas as permutações sejam geradas.
    sort(items.begin(), items.end());

    int count = 0;
    do {
        // Bloco de processamento da permutação atual
        // Exemplo: apenas imprimir
        printf("%d: {", ++count);
        for (size_t i = 0; i < items.size(); ++i) {
            printf(" %d", items[i]);
        }
        printf(" }\n");

    } while (next_permutation(items.begin(), items.end()));
}

// Exemplo de uso
void demoPermutations() {
    vector<int> my_items = {3, 1, 2};
    generateAndProcessPermutations(my_items);
}
