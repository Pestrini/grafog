#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    vector<vector<int>> adj_matrix; // matriz de adjacência
    vector<int> vertex_values; // valores associados a cada vértice
    vector<vector<int>> edge_values; // valores associados a cada aresta

public:
    Graph(int size) {
        // cria a matriz de adjacência com todos os valores inicializados como 0
        adj_matrix.resize(size, vector<int>(size, 0));

        // cria as estruturas para armazenar os valores dos vértices e arestas
        vertex_values.resize(size, 0);
        edge_values.resize(size, vector<int>(size, 0));
    }

    // testa se existe uma aresta do vértice x para o vértice y
    bool adjacent(int x, int y) {
        return adj_matrix[x][y] != 0;
    }

    // lista todos os vértices y tal que existe uma aresta do vértice x para o vértice y
    vector<int> neighbors(int x) {
        vector<int> neighbors;
        for (int i = 0; i < adj_matrix[x].size(); i++) {
            if (adj_matrix[x][i] != 0) {
                neighbors.push_back(i);
            }
        }
        return neighbors;
    }

    // adiciona o vértice x, se não estiver lá
    void add_vertex(int x) {
        if (x >= adj_matrix.size()) {
            int old_size = adj_matrix.size();
            adj_matrix.resize(x+1, vector<int>(x+1, 0));
            vertex_values.resize(x+1, 0);
            edge_values.resize(x+1, vector<int>(x+1, 0));

            for (int i = old_size; i < adj_matrix.size(); i++) {
                adj_matrix[i].resize(x+1, 0);
                edge_values[i].resize(x+1, 0);
            }
        }
    }

    // remove o vértice x, se estiver lá
    void remove_vertex(int x) {
        if (x < adj_matrix.size()) {
            // remove as arestas ligadas ao vértice x
            for (int i = 0; i < adj_matrix.size(); i++) {
                adj_matrix[x][i] = 0;
                adj_matrix[i][x] = 0;
                edge_values[x][i] = 0;
                edge_values[i][x] = 0;
            }

            // remove o valor associado ao vértice x
            vertex_values[x] = 0;

            // remove a linha e a coluna da matriz de adjacência correspondentes ao vértice x
            adj_matrix.erase(adj_matrix.begin() + x);
            for (int i = 0; i < adj_matrix.size(); i++) {
                adj_matrix[i].erase(adj_matrix[i].begin() + x);
                edge_values[i].erase(edge_values[i].begin() + x);
            }

            // remove o valor associado às arestas ligadas ao vértice x
            edge_values.erase(edge_values.begin() + x);
        }
    }

    // adiciona a aresta z do vértice x ao vértice y, se não estiver lá
    void add_edge(int x, int y, int z) {
        if(x < adj_matrix.size() && y < adj_matrix.size()) { // verifica se x e y são índices válidos na matriz de adjacência
            adj_matrix[x][y] = z; // adiciona a aresta de x para y com o valor z
            edge_values[x][y] = z; // define o valor associado à aresta de x para y como z
            }
    }
    // remove a aresta do vértice x para o vértice y, se estiver lá
    void remove_edge(int x, int y) {
        if (x < adj_matrix.size() && y < adj_matrix.size()) { // verifica se x e y são índices válidos na matriz de adjacência
            adj_matrix[x][y] = 0; // remove a aresta de x para y
            edge_values[x][y] = 0; // remove o valor associado à aresta de x para y
            }
    }

    // retorna o valor associado ao vértice x
    int get_vertex_value(int x) {
        return vertex_values[x];
    }

    // define o valor associado ao vértice x para v
    void set_vertex_value(int x, int v) {
        vertex_values[x] = v;
    }

    // retorna o valor associado à aresta de x para y
    int get_edge_value(int x, int y) {
        return edge_values[x][y];
    }

    // define o valor associado à aresta de x para y como v
    void set_edge_value(int x, int y, int v) {
        edge_values[x][y] = v;
    }

    // mostrar o grafo
    void print_graph() {
        cout << "Matriz de adjacência:\n";
        for (int i = 0; i < adj_matrix.size(); i++) {
            for (int j = 0; j < adj_matrix[i].size(); j++) {
                cout << adj_matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int size;
    cout << "Digite o tamanho do grafo: ";
    cin >> size;

    Graph g(size);

    int choice;
    while (true) {
        cout << "\nEscolha uma opção:\n";
        cout << "1. Verificar se há uma aresta entre dois vértices\n";
        cout << "2. Listar todos os vizinhos de um vértice\n";
        cout << "3. Adicionar um vértice\n";
        cout << "4. Remover um vértice\n";
        cout << "5. Adicionar uma aresta\n";
        cout << "6. Remover uma aresta\n";
        cout << "7. Obter o valor de um vértice\n";
        cout << "8. Definir o valor de um vértice\n";
        cout << "9. Obter o valor de uma aresta\n";
        cout << "10. Definir o valor de uma aresta\n";
        cout << "11. Mostrar Grafo\n";
        cout << "0. Sair\n";

        cin >> choice;

        if (choice == 1) {
            int x, y;
            cout << "Digite os índices dos vértices: ";
            cin >> x >> y;
            if (g.adjacent(x, y)) {
                cout << "Há uma aresta de " << x << " para " << y << endl;
            }
            else {
                cout << "Não há uma aresta de " << x << " para " << y << endl;
            }
        }
        else if (choice == 2) {
            int x;
            cout << "Digite o índice do vértice: ";
            cin >> x;
            vector<int> neighbors = g.neighbors(x);
            cout << "Os vizinhos de " << x << " são: ";
            for (int i = 0; i < neighbors.size(); i++) {
                cout << neighbors[i] << " ";
            }
            cout << endl;
        }
        else if (choice == 3) {
            int x;
            cout << "Digite o índice do vértice a ser adicionado: ";
            cin >> x;
            g.add_vertex(x);
        }
        else if (choice == 4) {
            int x;
            cout << "Digite o índice do vértice a ser removido: ";
            cin >> x;
            g.remove_vertex(x);
        }
        else if (choice == 5) {
            int x, y, z;
            cout << "Digite os índices dos vértices e o valor da aresta: ";
            cin >> x >> y >> z;
            g.add_edge(x, y, z);
        }
        else if (choice == 6) {
            int x, y;
            cout << "Digite os índices dos vértices: ";
            cin >> x >> y;
            g.remove_edge(x, y);
        }
        else if (choice == 7) {
            int x;
            cout << "Digite o índice do vértice: ";
            cin >> x;
            cout << "O valor do vértice " << x << " é: " << g.get_vertex_value(x) << endl;
        }
        else if (choice == 8) {
            int x, v;
            cout << "Digite o índice do vértice a ter o valor associado modificado: ";
            cin >> x;
            cout << "Digite o novo valor associado ao vértice: ";
            cin >> v;
            g.set_vertex_value(x, v);
        }
        else if (choice == 9) {
            int x, y;
            cout << "Digite o índice dos vértices da aresta: ";
            cin >> x >> y;
            cout << "O valor da aresta de " << x << " para " << y << " é " << get_edge_value(x, y) << ".\n";
        }
        else if (choice == 10) {
            int x, y, v;
            cout << "Digite o índice dos vértices da aresta: ";
            cin >> x >> y;
            cout << "Digite o valor da aresta: ";
            cin >> v;
            set_edge_value(x, y, v);
        }
        else if (choice == 11) {
            print_graph();
        }
        else if (choice == 0) {
            cout << "Saindo do programa..." << endl;
            return 0;
        } 
        else {
            cout << "Opção inválida. Por favor, digite um número entre 1 e 11." << endl;
        }
    }

    return 0;
}