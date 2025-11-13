/**
 * @brief Algoritmo de Edmonds-Karp para Max Flow.
 *
 * Complexidade: O(V * E^2)
 *
 * Usa BFS para encontrar caminhos de aumento.
 *
 * @param s Vértice de origem.
 * @param t Vértice de sumidouro.
 * @param V Número total de vértices.
 * @param AdjList Lista de adjacência (estrutura do grafo).
 * @param res Matriz de capacidade residual (passada por referência).
 * res[u][v] = capacidade de u para v.
 * @return O valor do fluxo máximo.
 */
ll edmondsKarp(int s, int t, int V, const vector<vector<int>>& AdjList, 
               vector<vector<ll>>& res) {
    
    ll mf = 0; // Max Flow

    while (1) { // Loop principal
        // 1. Encontra caminho de aumento via BFS
        vector<int> p(V, -1); // Vetor de predecessores
        queue<pair<int, ll>> q;
        q.push({s, INF}); // {vértice, flow_até_aqui}
        p[s] = s;

        ll path_flow = 0;
        int u = -1;

        while (!q.empty()) {
            u = q.front().first;
            path_flow = q.front().second;
            q.pop();

            if (u == t) break; // Chegou ao sumidouro

            for (int v : AdjList[u]) {
                if (p[v] == -1 && res[u][v] > 0) { // Se v não foi visitado e há capacidade
                    p[v] = u; // Define predecessor
                    ll new_flow = min(path_flow, res[u][v]);
                    q.push({v, new_flow});
                }
            }
            if (u == t) break; // Garante saída se 't' foi o último item na fila
        }
        
        // Se o BFS não alcançou 't' (u != t), não há mais caminhos
        if (u != t) break;
        
        // 2. Encontra o gargalo (f) do caminho achado
        // (Nota: o BFS acima já poderia ter encontrado, mas esta
        // forma é mais alinhada com a augment() do CP3)
        ll f = 0;
        queue<pair<int, ll>> q_aug; // Fila separada para augment
        q_aug.push({t, INF});
        vector<int> p_aug = p; // Copia os predecessores
        
        int curr = t;
        ll minEdge = INF;
        while(curr != s) {
            minEdge = min(minEdge, res[p_aug[curr]][curr]);
            curr = p_aug[curr];
        }
        f = minEdge;

        // 3. Atualiza o grafo residual
        curr = t;
        while (curr != s) {
            int prev = p[curr];
            res[prev][curr] -= f; // Aresta direta
            res[curr][prev] += f; // Aresta reversa
            curr = prev;
        }

        mf += f; // Adiciona o flow do caminho ao total
    }

    return mf;
}

/**
 * @brief Encontra os vértices no lado S do Min-Cut.
 * Deve ser chamado APÓS a execução de edmondsKarp.
 *
 * @param s O vértice de origem.
 * @param V O número total de vértices.
 * @param res A matriz de capacidade residual (APÓS o max flow).
 * @param AdjList A lista de adjacência original.
 * @return Um vector<bool> 'visited' onde visited[i] == true
 * significa que 'i' pertence ao conjunto S.
 */
vector<bool> getMinCut(int s, int V, const vector<vector<ll>>& res, 
                       const vector<vector<int>>& AdjList) {
    
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    // Executa um BFS/DFS final no grafo residual
    // para encontrar todos os vértices alcançáveis a partir de 's'
    // [cite: 167]
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : AdjList[u]) {
            // Se houver capacidade residual (res[u][v] > 0) e
            // 'v' não foi visitado
            if (res[u][v] > 0 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    
    // Os vértices do corte são:
    // Arestas (u, v) do GRAFO ORIGINAL onde
    // visited[u] == true (Conjunto S) E visited[v] == false (Conjunto T).
    // A soma das capacidades *originais* dessas arestas é o Min-Cut.
    
    return visited;
}


/*
 * Implementação do Algoritmo de Edmonds-Karp (Max Flow)
 * Baseado no Livro CP3, Seção 4.6.3
 *
 * Esta versão usa APENAS Listas de Adjacência, o que é ideal
 * para grafos esparsos (E << V^2).
 *
 * Complexidade: O(V * E^2)
 */

// --- Estrutura de Aresta ---
// Precisamos de uma estrutura para armazenar os detalhes da aresta,
// incluindo a aresta reversa para o fluxo.
struct Edge {
    int to;     // Vértice de destino
    ll cap;     // Capacidade da aresta
    ll flow;    // Fluxo atual na aresta
    int rev;    // Índice da aresta reversa em AdjList[to]
};

// --- Variáveis Globais ---
int V; // Número de vértices
vector<vector<Edge>> AdjList; // Lista de Adjacência (armazena arestas)
vector<int> p;     // Vetor de predecessores (armazena o *vértice* pai)
vector<Edge*> p_edge; // Vetor de predecessores (armazena a *aresta* usada)

/**
 * @brief Adiciona uma aresta (e sua reversa) ao grafo.
 * @param u Vértice de origem.
 * @param v Vértice de destino.
 * @param cap Capacidade da aresta u -> v.
 */
void add_edge(int u, int v, ll cap) {
    // Aresta direta (forward)
    Edge fwd;
    fwd.to = v;
    fwd.cap = cap;
    fwd.flow = 0;
    fwd.rev = AdjList[v].size(); // O índice da aresta reversa em AdjList[v]
    
    // Aresta reversa (backward)
    Edge bwd;
    bwd.to = u;
    bwd.cap = 0; // Arestas reversas começam com capacidade 0
    bwd.flow = 0;
    bwd.rev = AdjList[u].size(); // O índice da aresta direta em AdjList[u]

    AdjList[u].push_back(fwd);
    AdjList[v].push_back(bwd);
}

/**
 * @brief Encontra um caminho de aumento usando BFS.
 * @param s Fonte (source).
 * @param t Sumidouro (sink).
 * @return true se um caminho foi encontrado, false caso contrário.
 */
bool bfs(int s, int t) {
    p.assign(V, -1);
    p_edge.assign(V, nullptr); // Nenhuma aresta usada ainda
    
    p[s] = s; // Marca a origem como visitada (predecessor de si mesmo)
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) return true; // Chegou ao sumidouro

        // Itera sobre as arestas de 'u'
        // Usamos um loop de índice para poder modificar a aresta
        for (int i = 0; i < AdjList[u].size(); ++i) {
            Edge &e = AdjList[u][i]; // Pega a aresta por referência
            int v = e.to;
            
            // Se 'v' ainda não foi visitado E a aresta tem capacidade residual
            if (p[v] == -1 && e.cap > e.flow) {
                p[v] = u;         // Define o predecessor
                p_edge[v] = &e;   // Armazena *ponteiro* para a aresta usada
                q.push(v);
            }
        }
    }
    return false; // Não chegou ao sumidouro
}

/**
 * @brief Calcula o fluxo máximo de s para t (Edmonds-Karp).
 * @param s Fonte (source).
 * @param t Sumidouro (sink).
 * @param _V Número total de vértices.
 * @return O valor do fluxo máximo.
 */
ll edmondsKarp(int s, int t, int _V) {
    V = _V;
    AdjList.assign(V, vector<Edge>());
    // (AQUI você deve chamar add_edge() para construir seu grafo)
    // Exemplo: add_edge(0, 1, 100);

    ll mf = 0; // Max Flow

    // Loop principal: continua enquanto BFS encontrar caminho
    while (bfs(s, t)) {
        // 1. Encontra o gargalo (flow do caminho)
        ll path_flow = INF;
        for (int v = t; v != s; v = p[v]) {
            path_flow = min(path_flow, p_edge[v]->cap - p_edge[v]->flow);
        }

        // 2. Atualiza o fluxo (augment)
        for (int v = t; v != s; v = p[v]) {
            // Aumenta o fluxo na aresta direta
            p_edge[v]->flow += path_flow;

            // Diminui o fluxo na aresta reversa (aumenta capacidade residual)
            Edge &rev_edge = AdjList[v][p_edge[v]->rev];
            rev_edge.flow -= path_flow;
        }

        mf += path_flow; // Adiciona ao fluxo total
    }

    return mf;
}
