#include <iostream>
#include <fstream>   // Para criar e escrever arquivos
#include <cstdlib>   
#include <ctime>     

using namespace std;

// Classe carta de Bingo 5x5
class BingoCard {
private:
    int card[5][5];  // Matriz que guarda os números da carta
    int used[5];     //  números únicos por coluna

public:
  
    // Função que gera um número aleatório único dentro de um intervalo

    int numerosunicos(int min, int max, int used_count) {
        int num;
        bool unique;
        do {
            // Gera número aleatório no intervalo [min, max]
            num = rand() % (max - min + 1) + min;
            unique = true;

            // Verifica se o número já foi usado na coluna
            for (int i = 0; i < used_count; i++) {
                if (used[i] == num) {
                    unique = false; // Se já foi usado, tenta outro
                    break;
                }
            }
        } while (!unique); // Repete até achar um número único

        return num; // Retorna o número único
    }

    // Construtor da carta de Bingo   
    BingoCard() {
      
        int min_range[5] = {1, 21, 41, 61, 81};
        int max_range[5] = {20, 40, 60, 80, 100};

        for (int col = 0; col < 5; col++) {
            int used_count = 0; // Contador de números já usados na coluna

            for (int row = 0; row < 5; row++) {
                // Espaço central da carta (posição 2,2) é "livre"
                if (col == 2 && row == 2) {
                    card[row][col] = 0; // Representa o espaço livre
                    continue;           // Pula para a próxima célula
                }

                // Gera número único na coluna
                int num = numerosunicos(min_range[col], max_range[col], used_count);

                used[used_count++] = num; // Marca o número como usado
                card[row][col] = num;     // Armazena na carta
            }
        }
    }

  
    // Função que imprime a carta na tela e grava no arquivo

    void print(int id, ofstream &outFile) const {
        // Cabeçalho
        cout << "\nCarta " << id << ":\n\n";
        cout << " B\t I\t N\t G\t O\n";
        outFile << "\nCarta " << id << ":\n\n";
        outFile << " B\t I\t N\t G\t O\n";

        // Percorre cada célula da carta
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 5; col++) {
                // Espaço central "**" (livre)
                if (row == 2 && col == 2) {
                    cout << "**\t";
                    outFile << "**\t";
                } else {
                    cout << card[row][col] << "\t";     // Imprime número na tela
                    outFile << card[row][col] << "\t";  // Grava número no arquivo
                }
            }
            cout << "\n";
            outFile << "\n";
        }
    }
};


int main(int argc, char* argv[]) {
    // Verifica se o usuário passou a quantidade de cartas como argumento
    if (argc != 2) {
        cout << "Uso correto: ./generatecards [number_of_cards]\n";
        return 1;
    }

    int num_cards = atoi(argv[1]); // Converte argumento para número inteiro

    // Valida o número de cartas
    if (num_cards <= 0) {
        cout << "O número de cartas deve ser maior que zero.\n";
        return 1;
    }

    srand(time(NULL)); // Inicializa semente aleatória

    // Cria arquivo de saída "cartas.txt"
    ofstream outFile("cartas.txt");
    if (!outFile) { // Verifica se o arquivo foi criado com sucesso
        cout << "Erro ao criar o arquivo cartas.txt\n";
        return 1;
    }

    // Gera e imprime cada carta
    for (int i = 1; i <= num_cards; i++) {
        BingoCard card;       // Cria uma carta
        card.print(i, outFile); // Imprime na tela e grava no arquivo
    }

    outFile.close(); // Fecha o arquivo
    cout << "\nCartas gravadas em cartas.txt com sucesso!\n";

    return 0;
}
