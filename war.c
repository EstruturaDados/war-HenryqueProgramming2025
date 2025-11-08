# include <stdio.h>
# include <string.h>

// Criando a Struct

typedef struct{
    char nome[50];
    char cor [10];
    int tropas;
} Territorio;

// Declarando Funções

void cadastrarTerritorios(Territorio* territorios, int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* territorios);
int validarAtaque(Territorio* atacante, Territorio* defensor);

int main() {

    printf("=== Seja muito bem-vindo(a) ao jogo de estratégia War! ===\n\n");
    printf("Abaixo, entre com o nome, a cor e a quantidade de tropas:\n\n");

    // Declarando o Vetor

    Territorio territorios[5];

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n\n", i + 1);
        printf("Nome: ");
        scanf("%49s", territorios[i].nome);
        printf("Cor: ");
        scanf("%9s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

       while (getchar() != '\n');
    }

    // Exibindo os detalhes dos territórios

printf("\n=== Detalhes dos territórios cadastrados ===\n\n");

fflush(stdout);

for (int i = 0; i < 5; i++) {
    printf("Território %d:\n\n", i + 1);
    printf("Nome: %s\n", territorios[i].nome);
    printf("Cor: %s\n", territorios[i].cor);
    printf("Quantidade de tropas: %d\n\n", territorios[i].tropas);

    fflush(stdout);
}

return 0;
}
