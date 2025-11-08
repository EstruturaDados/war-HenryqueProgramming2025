#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Criando a Struct - molde do território
typedef struct {
    char nome[50];
    char cor[10];
    int tropas;
} Territorio;

// Declarando as funções que vamos usar
void cadastrarTerritorios(Territorio* territorios, int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* territorios);
int validarAtaque(Territorio* atacante, Territorio* defensor);

// FUNÇÃO PRINCIPAL
int main() {
    srand(time(NULL)); // Para os dados serem aleatórios

    printf("=== Seja muito bem-vindo(a) ao jogo de estratégia War! ===\n\n");
    
    // PASSO 1: Perguntar quantos territórios
    int quantidade;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &quantidade);
    
    // PASSO 2: Alocação dinâmica (malloc)
    Territorio* territorios = (Territorio*)malloc(quantidade * sizeof(Territorio));
    
    if (territorios == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }
    
    // PASSO 3: Cadastrar territórios
    printf("\n=== CADASTRO DE TERRITÓRIOS ===\n");
    cadastrarTerritorios(territorios, quantidade);
    
    // PASSO 4: Mostrar territórios cadastrados
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n");
    exibirTerritorios(territorios, quantidade);
    
    // PASSO 5: Sistema de ataques
    printf("\n=== FASE DE ATAQUES ===\n");
    int continuar = 1;
    
    while (continuar) {
        int idxAtacante, idxDefensor;
        
        printf("\nSelecione o território ATACANTE (1 a %d): ", quantidade);
        scanf("%d", &idxAtacante);
        printf("Selecione o território DEFENSOR (1 a %d): ", quantidade);
        scanf("%d", &idxDefensor);
        
        // Ajusta índices (usuário digita 1,2,3... mas vetor é 0,1,2...)
        idxAtacante--;
        idxDefensor--;
        
        // Verifica se os números são válidos
        if (idxAtacante < 0 || idxAtacante >= quantidade || 
            idxDefensor < 0 || idxDefensor >= quantidade) {
            printf("Erro: Números inválidos! Use de 1 a %d.\n", quantidade);
            continue;
        }
        
        // Pega os territórios selecionados
        Territorio* atacante = &territorios[idxAtacante];
        Territorio* defensor = &territorios[idxDefensor];
        
        // Verifica se pode atacar
        if (validarAtaque(atacante, defensor)) {
            printf("\n=== INICIANDO ATAQUE ===\n");
            printf("%s (%s) está atacando %s (%s)\n", 
                   atacante->nome, atacante->cor, 
                   defensor->nome, defensor->cor);
            
            atacar(atacante, defensor);
            
            printf("\n=== SITUAÇÃO ATUALIZADA ===\n");
            exibirTerritorios(territorios, quantidade);
        } else {
            printf("Não é possível atacar seu próprio território!\n");
        }
        
        // Pergunta se quer continuar
        printf("\nDeseja realizar outro ataque? (1 = Sim, 0 = Não): ");
        scanf("%d", &continuar);
    }
    
    // PASSO 6: Liberar memória
    liberarMemoria(territorios);
    
    printf("\n=== JOGO FINALIZADO ===\n");
    return 0;
}

// FUNÇÃO: Cadastrar territórios
void cadastrarTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: ");
        scanf("%49s", territorios[i].nome);
        printf("Cor: ");
        scanf("%9s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        while (getchar() != '\n'); // Limpa o buffer do teclado
    }
}

// FUNÇÃO: Exibir territórios
void exibirTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
    }
    printf("\n");
}

// FUNÇÃO: Validar se o ataque é possível
int validarAtaque(Territorio* atacante, Territorio* defensor) {
    // Se as cores forem iguais, é o mesmo jogador - não pode atacar
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        return 0; // Ataque inválido
    }
    return 1; // Ataque válido
}

// FUNÇÃO: Simular ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simula dados de 1 a 6
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("🎲 Dado do atacante: %d\n", dadoAtacante);
    printf("🎲 Dado do defensor: %d\n", dadoDefensor);
    
    if (dadoAtacante > dadoDefensor) {
        // ATACANTE VENCE - conquista o território
        printf("\n>>> 🏆 VITÓRIA DO ATACANTE! <<<\n");
        printf("O território %s foi conquistado!\n", defensor->nome);
        
        // Muda a cor do território conquistado
        strcpy(defensor->cor, atacante->cor);
        
        // Transfere metade das tropas do defensor para o atacante
        int tropasConquistadas = defensor->tropas / 2;
        atacante->tropas += tropasConquistadas;
        defensor->tropas = defensor->tropas - tropasConquistadas;
        
        printf("Foram transferidas %d tropas para o atacante.\n", tropasConquistadas);
        
    } else if (dadoAtacante < dadoDefensor) {
        // DEFENSOR VENCE
        printf("\n>>> 🛡️ VITÓRIA DO DEFENSOR! <<<\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 0) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa na batalha.\n");
        }
        
    } else {
        // EMPATE
        printf("\n>>> ⚖️ EMPATE! Nenhum território mudou de dono. <<<\n");
    }
}

// FUNÇÃO: Liberar memória alocada
void liberarMemoria(Territorio* territorios) {
    free(territorios);
    printf("Memória liberada com sucesso!\n");
}
