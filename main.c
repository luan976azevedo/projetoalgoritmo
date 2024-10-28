#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int matricula;
    char nome[100];
    float nota;
} Aluno;

void cadastrarAluno(const char *nomeArquivo, int *totalAlunos) {
    FILE *arquivo = fopen(nomeArquivo, "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Aluno novoAluno;
    novoAluno.matricula = *totalAlunos + 1;
    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novoAluno.nome);
    printf("Digite a nota do aluno: ");
    scanf("%f", &novoAluno.nota);

    fwrite(&novoAluno, sizeof(Aluno), 1, arquivo);
    fclose(arquivo);

    (*totalAlunos)++;
    printf("Aluno cadastrado com sucesso!\n");
}

void listarAlunos(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Aluno aluno;
    printf("Lista de alunos cadastrados:\n");
    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        printf("Matrícula: %d\n", aluno.matricula);
        printf("Nome: %s\n", aluno.nome);
        printf("Nota: %.2f\n\n", aluno.nota);
    }

    fclose(arquivo);
}

void buscarAluno(const char *nomeArquivo, int matricula) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Aluno aluno;
    int encontrado = 0;
    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula == matricula) {
            printf("Aluno encontrado:\n");
            printf("Matrícula: %d\n", aluno.matricula);
            printf("Nome: %s\n", aluno.nome);
            printf("Nota: %.2f\n\n", aluno.nota);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
    }

    fclose(arquivo);
}

void removerAluno(const char *nomeArquivo, int matricula) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

