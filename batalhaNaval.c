#include <stdio.h>
#include <stdlib.h> // >>> MODIFICAÇÃO <<< Necessário para usar abs()

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // >>> MODIFICAÇÃO <<< Tamanho fixo para as matrizes de habilidades

/////////////////////////////////// NIVEL INICIANTE //////////////////////////////////////////////////////////


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

/////////////////////////////////////////////NIVEL INTERMEDIARIO ////////////////////////////////////////////////////////////////////


/* >>> MODIFICAÇÃO <<<
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
} */

/////////////////////////////////////// NIVEL MESTRE ///////////////////////////////////////////////

// >>> MODIFICAÇÃO <<<
// Exibe o tabuleiro com diferentes símbolos
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
            else if (tabuleiro[i][j] == 5)
                printf(" * "); // >>> MODIFICAÇÃO <<< símbolo para área afetada por habilidades
            else
                printf(" ~ ");
        }
        printf("\n");
    }
}

// (funções de navio - sem modificação)
int estaOcupado(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    return tabuleiro[linha][coluna] != 0;
}

int posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        else if (direcao == 'E') { l += i; c -= i; }

        if (l >= TAM_TABULEIRO || c >= TAM_TABULEIRO || l < 0 || c < 0)
            return 0;
        if (estaOcupado(tabuleiro, l, c))
            return 0;
    }

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

// >>> MODIFICAÇÃO <<<
// Gera matriz em forma de cone apontando para baixo
void gerarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == 0 && j == 2) matriz[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) matriz[i][j] = 1;
            else if (i == 2) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// >>> MODIFICAÇÃO <<<
// Gera matriz em forma de cruz (vertical e horizontal)
void gerarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == 2 || j == 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// >>> MODIFICAÇÃO <<<
// Gera matriz em forma de octaedro (losango usando distância de Manhattan)
void gerarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// >>> MODIFICAÇÃO <<<
// Aplica a matriz de habilidade ao tabuleiro, centrada na coordenada (origemLinha, origemColuna)
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = origemLinha - offset + i;
            int c = origemColuna - offset + j;

            if (l >= 0 && l < TAM_TABULEIRO && c >= 0 && c < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[l][c] == 0)
                    tabuleiro[l][c] = 5; // >>> MODIFICAÇÃO <<< marca área de habilidade no tabuleiro
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // (navios - igual ao código anterior)
    posicionarNavio(tabuleiro, 2, 1, 'H');
    posicionarNavio(tabuleiro, 0, 5, 'V');
    posicionarNavio(tabuleiro, 4, 4, 'D');
    posicionarNavio(tabuleiro, 6, 8, 'E');

    // >>> MODIFICAÇÃO <<< Criação das 3 matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // >>> MODIFICAÇÃO <<< Preenchimento dinâmico das matrizes
    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    // >>> MODIFICAÇÃO <<< Aplicação das habilidades ao tabuleiro
    aplicarHabilidade(tabuleiro, cone, 3, 3);      // Cone centrado em (3,3)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);      // Cruz centrada em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 2);  // Octaedro centrado em (7,2)

    // Exibir tabuleiro final com navios e áreas afetadas
    exibirTabuleiro(tabuleiro);

    return 0;
}