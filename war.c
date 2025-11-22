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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 5 
#define TAM_STRING 50

// Variável global para a cor do jogador (simplifica a verificação de vitória)
char g_corJogador[TAM_STRING]; 

// Vetor com as 5 missões estratégicas (requisito)
const char *MISSOES[NUM_MISSOES] = {
    "Destruir o exercito Verde.",
    "Conquistar 3 territorios.",
    "Destruir o exercito Amarelo.",
    "Conquistar 4 territorios.",
    "Conquistar o territorio America."
};

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
typedef struct{
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int numTropas;
} Territorio;

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
Territorio *alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void liberarMemoria(Territorio *mapa);

// Funções de interface com o usuário:
void exibirMenuPrincipal();
void exibirMapa(const Territorio *mapa);

// Funções de lógica principal do jogo:
void faseDeAtaque(Territorio *mapa);
void atacar(Territorio *atacante, Territorio *defensor); // simularAtaque() foi renomeado para atacar()

// Missões:
void atribuirMissao(char *destino, const char *missoes[], int totalMissoes); // Substitui sortearMissao()
void exibirMissao(const char *missao);
int verificarMissao(const char *missao, const Territorio *mapa, int tamanho); // Substitui verificarVitoria()

// Função utilitária:
void limparBufferEntrada();

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    setlocale(LC_ALL, "Portuguese");

    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    srand((unsigned int)time(NULL));

    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    Territorio *mapa = alocarMapa();
    
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    inicializarTerritorios(mapa);
    
    // - Define a cor do jogador e sorteia sua missão secreta.
    int escolha_territorio;
    printf("\n============== ESCOLHA SUA NACÃO ==============\n");
    exibirMapa(mapa);
    printf("Escolha o numero do territorio que voce quer comandar (1-%d): ", NUM_TERRITORIOS);
    if (scanf("%d", &escolha_territorio) != 1) { 
        limparBufferEntrada();
        escolha_territorio = -1; 
    }
    limparBufferEntrada();
    
    // Valida a escolha e atribui a cor
    if (escolha_territorio < 1 || escolha_territorio > NUM_TERRITORIOS) {
        printf("Escolha invalida. Comandando o primeiro territorio (%s) por padrao.\n", mapa[0].nome);
        escolha_territorio = 1;
    }
    // Armazena a cor do território escolhido como a cor do jogador 
    strcpy(g_corJogador, mapa[escolha_territorio - 1].corExercito);
    printf("Voce e o exercito %s. Boa sorte!\n", g_corJogador);
    
    // Aloca memória dinamicamente para a missão do jogador (Requisito)
    char *missaoJogador = (char*)malloc(TAM_STRING * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memoria para a missao.\n");
        liberarMemoria(mapa);
        return 1;
    }
    atribuirMissao(missaoJogador, MISSOES, NUM_MISSOES);
    
    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    int opcao;
    int venceu = 0;

    do {
        // - A cada iteração, exibe o mapa, a missão e o menu de ações.
        system("clear"); 
        exibirMapa(mapa);
        exibirMissao(missaoJogador);
        exibirMenuPrincipal();

        // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
        printf("Escolha sua acao: ");
        if (scanf("%d", &opcao) != 1) { 
            limparBufferEntrada();
            opcao = -1; 
        }
        limparBufferEntrada();
        
        switch(opcao){
            // Opção 1: Inicia a fase de ataque.
            case 1:
                faseDeAtaque(mapa);
                // Verifica a vitória silenciosamente após o ataque (Requisito)
                if(verificarMissao(missaoJogador, mapa, NUM_TERRITORIOS)){
                    venceu = 1;
                    printf("\n*** MISSAO CUMPRIDA! VITORIA! ***\n");
                    printf("Parabens, exercito %s. Voce cumpriu a missao: \"%s\".\n", g_corJogador, missaoJogador);
                }
                break;
            //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
            case 2:
                if(verificarMissao(missaoJogador, mapa, NUM_TERRITORIOS)){
                    venceu = 1;
                    printf("\n*** MISSAO CUMPRIDA! VITORIA! ***\n");
                    printf("Parabens, exercito %s. Voce cumpriu a missao: \"%s\".\n", g_corJogador, missaoJogador);
                } else {
                    printf("\nMissao ainda nao cumprida: %s. Continue jogando!\n", missaoJogador);
                }
                break;
            //   - Opção 0: Encerra o jogo.
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.
        if(opcao != 0 && !venceu){
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while(opcao != 0 && !venceu);

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa e missão para evitar vazamentos de memória.
    free(missaoJogador);
    liberarMemoria(mapa);
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.
Territorio *alocarMapa(){
    Territorio *mapa = (Territorio*)calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if(mapa == NULL){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    return mapa;
}

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).
void inicializarTerritorios(Territorio *mapa){
    
    const char *coresFixas[NUM_TERRITORIOS] = {"Verde", "Azul", "Vermelho", "Amarelo", "Branco"};
    
    // 1. América (Cor: Azul)
    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].corExercito, coresFixas[0]); 
    mapa[0].numTropas = 4;
    
    // 2. Europa (Cor: Verde)
    strcpy(mapa[1].nome, "Europa");
    strcpy(mapa[1].corExercito, coresFixas[1]); 
    mapa[1].numTropas = 2;

    // 3. Ásia (Cor: Vermelho)
    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].corExercito, coresFixas[2]);
    mapa[2].numTropas = 2;

    // 4. África (Cor: Amarelo)
    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].corExercito, coresFixas[3]);
    mapa[3].numTropas = 4;

    // 5. Oceania (Cor: Branco)
    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].corExercito, coresFixas[4]);
    mapa[4].numTropas = 1;
}

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.
void liberarMemoria(Territorio *mapa){
    free(mapa);
}

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.
void exibirMenuPrincipal(){
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
}

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.
void exibirMapa(const Territorio *mapa){
    printf("\n============== MAPA DO MUNDO ==============\n");
    for(int i = 0; i < NUM_TERRITORIOS; i++){
        printf("%d. %s \t(Exercito: %s \t, Tropas: %d)\n", 
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].numTropas);
    }
    printf("===========================================\n");
}

// atribuirMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.
void atribuirMissao(char* destino, const char* missoes[], int totalMissoes) {
    int index = rand() % totalMissoes;
    strcpy(destino, missoes[index]);
}

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.
void exibirMissao(const char *missao){
    printf("\n--- SUA MISSAO (Exercito %s) ---\n", g_corJogador);
    printf("%s\n", missao);
    printf("==============================\n");
}

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função atacar() para executar a lógica da batalha.
void faseDeAtaque(Territorio *mapa){
    int atq, def;

    printf("Escolha territorio atacante (1-%d): ", NUM_TERRITORIOS);
    if(scanf("%d", &atq) != 1) { limparBufferEntrada(); return; }

    printf("Escolha territorio defensor (1-%d): ", NUM_TERRITORIOS);
    if(scanf("%d", &def) != 1) { limparBufferEntrada(); return; }

    limparBufferEntrada();
    
    atq--;
    def--;

    if(atq < 0 || atq >= NUM_TERRITORIOS || def < 0 || def >= NUM_TERRITORIOS){
        printf("Territorio invalido.\n");
        return;
    }

    atacar(&mapa[atq], &mapa[def]);
}

// atacar():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move metade das tropas.
void atacar(Territorio *atacante, Territorio *defensor){
    // 1. Validações iniciais (tropas e inimigo)
    if(strcmp(atacante->corExercito, g_corJogador) != 0){
        printf("Acao invalida! Voce so pode atacar com seu proprio exercito (%s).\n", g_corJogador);
        return;
    }
    if(strcmp(atacante->corExercito, defensor->corExercito) == 0){
        printf("Acao invalida! Voce so pode atacar territorios inimigos.\n");
        return;
    }
    if(atacante->numTropas < 2){
        printf("O atacante (%s) nao tem tropas suficientes! (Minimo 2 tropas)\n", atacante->nome);
        return;
    }
    if(defensor->numTropas < 1){
        printf("O defensor (%s) nao tem tropas para defender! (Defesa automatica)\n", defensor->nome);
        return; 
    }

    // 2. Rolagem de Dados
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\nDado atacante (%s): %d\n", atacante->nome, dadoA);
    printf("Dado defensor (%s): %d\n", defensor->nome, dadoD);

    // 3. Resolução da Batalha (Atacante ganha em caso de dado maior)
    if(dadoA > dadoD){ 
        printf("\nVITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->numTropas--;

        if(defensor->numTropas == 0){
            printf("Territorio conquistado!\n");
            strcpy(defensor->corExercito, atacante->corExercito);
            
            // Requisito: Transfere cor e METADE DAS TROPAS do atacante
            int tropasTransferir = atacante->numTropas / 2;
            if (tropasTransferir < 1) tropasTransferir = 1; // Garante que pelo menos 1 tropa seja movida

            defensor->numTropas = tropasTransferir;
            atacante->numTropas -= tropasTransferir;

            printf("%d tropas foram transferidas de %s para %s.\n", tropasTransferir, atacante->nome, defensor->nome);
        }
    } else { // Defensor ganha (empate favorece o defensor, simplificando)
        printf("\nDERROTA DO ATAQUE! O atacante perdeu 1 tropa.\n");
        atacante->numTropas--;
    }
}

// verificarMissao():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.
int verificarMissao(const char *missao, const Territorio *mapa, int tamanho){
    int territorios_jogador = 0;
    int tropas_verde = 0;
    int tropas_amarelo = 0;
    int america_conquistada = 0;

    for(int i = 0; i < tamanho; i++){
        // Conta territórios e tropas
        if(strcmp(mapa[i].corExercito, g_corJogador) == 0){
            territorios_jogador++;
        }
        
        if(strcmp(mapa[i].corExercito, "Verde") == 0){
            tropas_verde += mapa[i].numTropas;
        }
        if(strcmp(mapa[i].corExercito, "Amarelo") == 0){
            tropas_amarelo += mapa[i].numTropas;
        }
        
        // Verifica a conquista da America
        if(strcmp(mapa[i].nome, "America") == 0 && strcmp(mapa[i].corExercito, g_corJogador) == 0){
            america_conquistada = 1;
        }
    }

    // Lógica de verificação baseada na string da missão
    if(strcmp(missao, MISSOES[0]) == 0){ 
        return (tropas_verde == 0);
    }
    else if(strcmp(missao, MISSOES[1]) == 0){ 
        return (territorios_jogador >= 3);
    }
    else if(strcmp(missao, MISSOES[2]) == 0){ 
        return (tropas_amarelo == 0);
    }
    else if(strcmp(missao, MISSOES[3]) == 0){ 
        return (territorios_jogador >= 4);
    }
    else if(strcmp(missao, MISSOES[4]) == 0){
        return america_conquistada;
    }

    return 0; 
}

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBufferEntrada(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}