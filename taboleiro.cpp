#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;


#define RESET "\033[0m"
#define BLUE  "\033[34m"
#define RED   "\033[31m"


vector<int> taboleiro[5][20];
vector<int> numerosSorteados; 

// Função que sorteia  números
int Sorteio(vector<int> matriz[5][20]) {

    // Vetor que guarda pares (i,j) das posições que ainda têm número
    vector<pair<int,int>> indices;

    
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 20; j++)
            // Se o vetor não estiver vazio a posição ainda tem número
            if (!matriz[i][j].empty())  //verifica se  foi sorteado se tiver ainda cheio continua
                indices.push_back({i,j});

    // Se não há mais números disponíveis para sortear
    if (indices.empty()) {//verifica se ja foi sorteado se tiver vasio é verdadeiro
        cout << "Todos os números já foram sorteados!\n";
        return -1;
    }

    // Escolhe aleatoriamente uma das posições disponíveis
    int r = rand() % indices.size();
    int i = indices[r].first;// linha do tabuleiro
    int j = indices[r].second;// coluna do tabuleiro

    // Recupera o número e esvazia a célula para impedir repetição
    int sorteado = matriz[i][j][0];
    matriz[i][j].clear();

    return sorteado;
}

// Função que verifica se um número já foi sorteado

bool jaFoiSorteado(int n) {
    // find para buscar o número no vetor de sorteados
    return find(numerosSorteados.begin(), numerosSorteados.end(), n) != numerosSorteados.end(); //Retorna true se o número n já está no vetor numerosSorteados. Retorna false caso contrário
}


// Função que imprime o tabuleiro colorido 5x20
// Números sorteados aparecem em vermelho
void Tabuleiro(vector<int> matriz[5][20]) {

    for (int i = 0; i < 5; i++) {

        // Imprime o topo da linha (bordas)
        for (int j = 0; j < 20; j++)
            cout << BLUE << "+-----" << RESET;
        cout << BLUE << "+\n" << RESET;

        // Imprime os números da linha
        for (int j = 0; j < 20; j++) {

            cout << BLUE << "| " << RESET;

            // Calcula o número correspondente à posição (i,j)
            int valorOriginal = i*20 + j + 1;

            // Se já foi sorteado, fica vermelho
            string cor = jaFoiSorteado(valorOriginal) ? RED : RESET;
            cout << cor;

            // Alinhamento manual para manter as colunas retas
            if (valorOriginal < 10)
                cout << "  " << valorOriginal; // números de 1 dígito
            else if (valorOriginal < 100)
                cout << " " << valorOriginal;  // números de 2 dígitos
            else
                cout << valorOriginal;         // números de 3 dígitos (100)

            cout << RESET << " "; // espaço final da célula
        }

        // Fecha a linha
        cout << BLUE << "|\n" << RESET;
    }

    // Imprime a borda inferior final
    for (int j = 0; j < 20; j++)
        cout << BLUE << "+-----" << RESET;
    cout << BLUE << "+\n" << RESET;
}


// Função principal
int main() {

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Preenche o tabuleiro com valores de 1 a 100
    int contador = 1;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 20; j++)
            taboleiro[i][j].push_back(contador++);

    //  mostrar tabuleiro / sortear número / esperar ENTER
    while (true) {
        system("clear"); // Limpa a tela (Linux)

        Tabuleiro(taboleiro); // Exibe o tabuleiro atualizado

        int n = Sorteio(taboleiro); // Sorteia um número
        if (n == -1) break;         // Se acabar os números, encerra

        numerosSorteados.push_back(n); // Armazena o número sorteado

        // Mostra o número em vermelho
        cout << "Número sorteado: " << RED << n << RESET << endl;

        cin.get(); 
    }

    return 0;
}
