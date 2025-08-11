#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

/*Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // 1. Inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // 2. Define os navios como vetores com valor 3 (cada posição do navio)
    int navio1[TAM_NAVIO] = {3, 3, 3}; // navio horizontal
    int navio2[TAM_NAVIO] = {3, 3, 3}; // navio vertical

    // 3. Coordenadas iniciais dos navios (linha, coluna)
    int linhaNavio1 = 2;
    int colunaNavio1 = 4; // navio 1 - horizontal

    int linhaNavio2 = 5;
    int colunaNavio2 = 6; // navio 2 - vertical

    // 4. Verificações de limites e sobreposição
    int dentroDosLimites = 1;

    // Verifica se o navio 1 (horizontal) cabe no tabuleiro
    if (colunaNavio1 + TAM_NAVIO > TAM_TABULEIRO)
        dentroDosLimites = 0;

    // Verifica se o navio 2 (vertical) cabe no tabuleiro
    if (linhaNavio2 + TAM_NAVIO > TAM_TABULEIRO)
        dentroDosLimites = 0;

    // Verifica sobreposição entre navios
    for (int i = 0; i < TAM_NAVIO && dentroDosLimites; i++) {
        int linha1 = linhaNavio1;
        int coluna1 = colunaNavio1 + i;

        int linha2 = linhaNavio2 + i;
        int coluna2 = colunaNavio2;

        if (linha1 == linha2 && coluna1 == coluna2) {
            dentroDosLimites = 0; // há sobreposição
        }
    }

    // 5. Se tudo estiver válido, posiciona os navios
    if (dentroDosLimites) {
        // Posiciona o navio horizontal
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavio1][colunaNavio1 + i] = navio1[i];
        }

        // Posiciona o navio vertical
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavio2 + i][colunaNavio2] = navio2[i];
        }

        // 6. Exibe o tabuleiro
        exibirTabuleiro(tabuleiro);
    } else {
        printf("Erro: Navios fora dos limites ou sobrepostos.\n");
    }

    return 0;
} */

// >>> MODIFICAÇÃO <<<
// Nova função para exibir o tabuleiro com cabeçalhos e símbolos (~ para água, N para navio)
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n   ");
    for (int j = 0; j < TAM_TABULEIRO; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 3)
                printf(" N ");
            else
                printf(" ~ ");
        }
        printf("\n");
    }
}

// >>> MODIFICAÇÃO <<<
// Nova função para verificar se a posição já está ocupada (evita sobreposição)
int estaOcupado(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    return tabuleiro[linha][coluna] != 0;
}

// >>> MODIFICAÇÃO <<<
// Nova função para posicionar um navio com direção ('H', 'V', 'D', 'E')
int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (direcao == 'H') c += i;            // Horizontal
        else if (direcao == 'V') l += i;       // Vertical
        else if (direcao == 'D') { l += i; c += i; }   // Diagonal ↘
        else if (direcao == 'E') { l += i; c -= i; }   // Diagonal ↙

        // Verifica se está dentro do tabuleiro
        if (l >= TAM_TABULEIRO || c >= TAM_TABULEIRO || l < 0 || c < 0)
            return 0;

        // Verifica se já está ocupado
        if (estaOcupado(tabuleiro, l, c))
            return 0;
    }

    // Se tudo válido, posiciona o navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        tabuleiro[l][c] = 3;
    }

    return 1;
}

int main() {
    // >>> SEM MODIFICAÇÃO <<< 
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // >>> MODIFICAÇÃO <<<
    // Posiciona os 4 navios com direções específicas

    // Navio 1 - Horizontal
    if (!posicionarNavio(tabuleiro, 2, 1, 'H'))
        printf("Erro ao posicionar navio 1 (horizontal)\n");

    // Navio 2 - Vertical
    if (!posicionarNavio(tabuleiro, 0, 5, 'V'))
        printf("Erro ao posicionar navio 2 (vertical)\n");

    // Navio 3 - Diagonal ↘ (linha e coluna crescem)
    if (!posicionarNavio(tabuleiro, 4, 4, 'D'))
        printf("Erro ao posicionar navio 3 (diagonal ↘)\n");

    // Navio 4 - Diagonal ↙ (linha cresce, coluna decresce)
    if (!posicionarNavio(tabuleiro, 6, 8, 'E'))
        printf("Erro ao posicionar navio 4 (diagonal ↙)\n");

    // >>> MODIFICAÇÃO <<<
    // Exibe o tabuleiro com os navios posicionados
    exibirTabuleiro(tabuleiro);

    return 0;
}