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
Aluno alunos[100];
    int total = 0;
    int encontrado = 0;
    Aluno aluno;

    while (fread(&aluno, sizeof(Aluno), 1, arquivo)) {
        if (aluno.matricula != matricula) {
            alunos[total++] = aluno;
        } else {
            encontrado = 1;
        }
    }
    fclose(arquivo);

    if (!encontrado) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula);
        return;
    }

    arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        fwrite(&alunos[i], sizeof(Aluno), 1, arquivo);
    }
    fclose(arquivo);

    printf("Aluno removido com sucesso!\n");
}

void gerarRelatorio(const char *nomeArquivoBinario, const char *nomeArquivoTexto) {
    FILE *arquivoBinario = fopen(nomeArquivoBinario, "rb");
    FILE *arquivoTexto = fopen(nomeArquivoTexto, "w");

    if (arquivoBinario == NULL || arquivoTexto == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Aluno aluno;
    fprintf(arquivoTexto, "Relatório de Alunos:\n\n");
    while (fread(&aluno, sizeof(Aluno), 1, arquivoBinario)) {
        fprintf(arquivoTexto, "Matrícula: %d\n", aluno.matricula);
        fprintf(arquivoTexto, "Nome: %s\n", aluno.nome);
        fprintf(arquivoTexto, "Nota: %.2f\n\n", aluno.nota);
    }

    fclose(arquivoBinario);
    fclose(arquivoTexto);
    printf("Relatório gerado com sucesso!\n");
}

int main() {
    int totalAlunos = 0;
    int opcao, matricula;
    const char *nomeArquivoBinario = "alunos.bin";
    const char *nomeArquivoTexto = "relatorio.txt";

    do {
        printf("\n1. Cadastrar Aluno\n");
        printf("2. Listar Alunos\n");
        printf("3. Buscar Aluno\n");
        printf("4. Remover Aluno\n");
        printf("5. Gerar Relatório\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarAluno(nomeArquivoBinario, &totalAlunos);
                break;
            case 2:
                listarAlunos(nomeArquivoBinario);
                break;
            case 3:
                printf("Digite a matrícula do aluno a ser buscado: ");
                scanf("%d", &matricula);
                buscarAluno(nomeArquivoBinario, matricula);
                break;
            case 4:
                printf("Digite a matrícula do aluno a ser removido: ");
                scanf("%d", &matricula);
                removerAluno(nomeArquivoBinario, matricula);
                break;
            case 5:
                gerarRelatorio(nomeArquivoBinario, nomeArquivoTexto);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
