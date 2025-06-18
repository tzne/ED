#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    unsigned habilidade;
} aluno;

void quicksort(aluno alunos[], int imin, int imax);
void shuffle(aluno alunos[], unsigned tamanho);
void swap(aluno alunos[], int a, int b);
int pivo(aluno alunos[], int imin, int imax);
void quicksort(aluno alunos[], int imin, int imax);

int main() {
    unsigned short quantidade_alunos, numero_times;

    int jogadores_por_time[1000] = {0};
    scanf("%hu %hu", &quantidade_alunos, &numero_times);

    aluno alunos[quantidade_alunos];
    aluno times[numero_times][quantidade_alunos];

    for (int i = 0; i < numero_times; i++)
        jogadores_por_time[i] = 0;

    for (int i = 0; i < quantidade_alunos; i++)
        scanf("%s %u", &alunos[i].nome, &alunos[i].habilidade);

    shuffle(alunos, quantidade_alunos); // randomização para otimizar o quicksort

    quicksort(alunos, 0, quantidade_alunos-1);

    for (int i = 0; i < quantidade_alunos; i++) {
        int indice_time_atual = i % numero_times;
        int indice_novo_jogador = jogadores_por_time[indice_time_atual];

        times[indice_time_atual][indice_novo_jogador] = alunos[i];

        jogadores_por_time[indice_time_atual]++;
    }

    for (int i = 0; i < numero_times; i++) {
        printf("Time %d\n", i + 1);
        for (int j = 0; j < jogadores_por_time[i]; j++)
            printf("%s\n", times[i][j].nome);
        printf("\n");
    }

    return 0;
}



void quicksort(aluno alunos[], int imin, int imax) {
    if (imax <= imin) return;

    int i = pivo(alunos, imin, imax);

    quicksort(alunos, imin, i-1);
    quicksort(alunos, i+1, imax);
}

int pivo(aluno alunos[], int imin, int imax) {
    int i = imin, j = imax+1;

    while (1) {
        while (alunos[++i].habilidade > alunos[imin].habilidade)
            if (i == imax) break;

        while (alunos[imin].habilidade > alunos[--j].habilidade)
            if (j == imin) break;

        if (i >= j) break;

        swap(alunos, i, j);
    }
    swap(alunos, imin, j);
    return j;
}

void swap(aluno alunos[], int a, int b) {
    aluno temp = alunos[a];
    alunos[a] = alunos[b];
    alunos[b] = temp;
}

void shuffle(aluno alunos[], unsigned tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int j = i + rand() % (tamanho - i);
        swap(alunos, i, j);
    }
}
