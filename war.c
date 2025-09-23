# include <stdio.h>
# include <string.h>

// Criando a Struct

typedef struct{
    char nome[50];
    char cor [10];
    int tropas;
} Territorio;

int main(){

    printf("=== Seja muito bem-vindo(a) ao jogo de estratégia War! ===");
    printf("Abaixo, entre com o nome, a cor e a quantidade de tropas:\n\n");

    // Declarando o Vetor

    Territorio territorios[5];

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", territorios[i].nome);
        printf("Cor: ");
        scanf("%s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

}
