// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.

    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    //return 0;


// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 50
#define MAX_COR 30
#define TOTAL_TERRITORIOS 5

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Cadastro dos territórios
void cadastrarTerritorios(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i+1);

        printf("Nome: ");
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa buffer
    }
}

// Exibe estado do mapa
void exibirMapa(Territorio *mapa, int n) {
    printf("\nEstado atual do mapa:\n");
    printf("--------------------------------------\n");
    printf("| %-2s | %-20s | %-10s | %-6s |\n", "ID", "Nome", "Cor", "Tropas");
    printf("--------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("| %-2d | %-20s | %-10s | %-6d |\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("--------------------------------------\n");
}

// Simula ataque entre dois territórios
void atacar(Territorio *mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas < 1) {
        printf("O território atacante não possui tropas suficientes para atacar.\n");
        return;
    }
    if (mapa[defensor].tropas < 1) {
        printf("O território defensor já não possui tropas!\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1; // 1 a 6
    int dadoDefensor = rand() % 6 + 1;

    printf("\nAtaque: %s (Cor: %s) VS %s (Cor: %s)\n", 
        mapa[atacante].nome, mapa[atacante].cor, mapa[defensor].nome, mapa[defensor].cor);
    printf("Dado atacante: %d\n", dadoAtacante);
    printf("Dado defensor: %d\n", dadoDefensor);

    if (dadoAtacante >= dadoDefensor) {
        printf("O atacante venceu!\n");
        mapa[defensor].tropas--;
        if (mapa[defensor].tropas <= 0) {
            mapa[defensor].tropas = 1;
            strcpy(mapa[defensor].cor, mapa[atacante].cor); // conquista
            printf("O território %s foi conquistado pelo exército %s!\n", mapa[defensor].nome, mapa[atacante].cor);
        }
    } else {
        printf("O defensor resistiu ao ataque!\n");
        mapa[atacante].tropas--;
    }
}

int main() {
    srand(time(NULL));
    Territorio *mapa = (Territorio*)calloc(TOTAL_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    printf("Cadastro dos territórios:\n");
    cadastrarTerritorios(mapa, TOTAL_TERRITORIOS);

    exibirMapa(mapa, TOTAL_TERRITORIOS);

    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        int atacante, defensor;
        printf("\nEscolha o território atacante (1 a %d): ", TOTAL_TERRITORIOS);
        scanf("%d", &atacante);
        getchar();
        printf("Escolha o território defensor (1 a %d): ", TOTAL_TERRITORIOS);
        scanf("%d", &defensor);
        getchar();

        if (atacante < 1 || atacante > TOTAL_TERRITORIOS || defensor < 1 || defensor > TOTAL_TERRITORIOS || atacante == defensor) {
            printf("Escolha inválida. Tente novamente.\n");
            continue;
        }

        atacar(mapa, atacante - 1, defensor - 1);
        exibirMapa(mapa, TOTAL_TERRITORIOS);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
        getchar();
    }

    free(mapa);
    printf("Fim da simulação!\n");
    return 0;
}