//
// Created by Vanessa Braganholo.
// Updated by Raphael Oliveira.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "intercalacao.h"

#include <limits.h>
#include <string.h>

#include "cliente.h"
#include "nomes.h"

typedef struct vetor {
    TCliente *cli;
    FILE *f;
} TVet;

/*
 * Definicao de tipo para no de arvore de vencedores
 */
typedef struct No {
    TCliente *vencedor;
    struct No *endVencedor;
    FILE *f;
    struct No *pai;
    struct No *dir;
    struct No *esq;
} TNo;

void intercalacao_basico(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes) {
    int fim = 0;  // variavel que controla fim do procedimento
    FILE *out;    // declara ponteiro para arquivo

    // abre arquivo de saida para escrita
    if ((out = fopen(nome_arquivo_saida, "wb")) == NULL) {
        printf("Erro ao abrir arquivo de saida\n");
    } else {
        // cria vetor de particoes
        TVet v[num_p];

        // abre arquivos das particoes, colocando variavel de arquivo no campo f do vetor
        // e primeiro cliente do arquivo no campo cli do vetor
        for (int i = 0; i < num_p; i++) {
            v[i].f = fopen(nome_particoes->nome, "rb");
            if (v[i].f != NULL) {
                TCliente *c = le_cliente(v[i].f);
                if (c == NULL) {
                    // arquivo estava vazio
                    // coloca HIGH VALUE nessa posicao do vetor
                    v[i].cli = cliente(INT_MAX, "");
                } else {
                    // conseguiu ler cliente, coloca na posicao atual do vetor
                    v[i].cli = c;
                }
            } else {
                fim = 1;
            }
            nome_particoes = nome_particoes->prox;
        }

        while (!(fim)) {  // conseguiu abrir todos os arquivos
            int menor = INT_MAX;
            int pos_menor;
            // encontra o cliente com menor chave no vetor
            for (int i = 0; i < num_p; i++) {
                if (v[i].cli->cod_cliente < menor) {
                    menor = v[i].cli->cod_cliente;
                    pos_menor = i;
                }
            }
            if (menor == INT_MAX) {
                fim = 1;  // terminou processamento
            } else {
                // salva cliente no arquivo de saida
                salva_cliente(v[pos_menor].cli, out);
                // atualiza posicao pos_menor do vetor com proximo cliente do arquivo
                TCliente *c = le_cliente(v[pos_menor].f);
                if (c == NULL) {
                    // arquivo estava vazio
                    // coloca HIGH VALUE nessa posicao do vetor
                    v[pos_menor].cli = cliente(INT_MAX, "");
                } else {
                    v[pos_menor].cli = c;
                }
            }
        }

        // fecha arquivos das particoes de entrada
        for (int i = 0; i < num_p; i++) {
            fclose(v[i].f);
        }
        // fecha arquivo de saida
        fclose(out);
    }
}

void intercalacao_arv_vencedores(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes) {
    // TODO: Implementar essa função
}

void intercalacao_otima(char *nome_arquivo_saida, int num_p, Nomes *nome_particoes, int f) {
    int max_input_files = f - 1;
    int max_output_files = 1;

    int flag_somente_one_particao = 0;

    // Alocando espaço para os arquivos de entrada
    FILE **input_files = (FILE **)malloc(max_input_files * sizeof(FILE *));
    int opened_files = 0;

    while (!flag_somente_one_particao) {
        // Faz a primeira leitura dos arquivos de entrada
        int i = 0;
        while (!nome_particoes && opened_files < max_input_files) {
            input_files[i] = fopen(nome_particoes->nome, "rb");
            if (input_files[i] == NULL) {
                printf("Erro ao abrir arquivo de entrada\n");
                exit(1);
            }
            i++;
            opened_files++;
            nome_particoes = nome_particoes->prox;
        }
        if (opened_files == 1) {
            FILE *output_file_final;
            if ((output_file_final = fopen(nome_arquivo_saida, "wb")) == NULL) {
                printf("Erro ao abrir arquivo de saida\n");
                exit(1);
            }

            TCliente *cliente;
            while (cliente = le_cliente(input_files[0]) != NULL) {
                salva_cliente(cliente, output_file_final);
            }
            return;
        }

        // Cria o arquivo de saída
        FILE *output_file;
        char output_filename[8] = "p";
        strcat(output_filename, itoa(num_p));
        strcat(output_filename, ".dat");

        if ((output_file = fopen(output_filename, "wb")) == NULL) {
            printf("Erro ao abrir arquivo de saida\n");
            exit(1);
        }

        // Intercala os arquivos de entrada no arquivo de saída
        // TODO: Ao inves de usar indice, buscar qual o menor
        for (int i_particoes = 0; i_particoes < opened_files; i_particoes++) {
            TCliente *cliente;
            while (cliente = le_cliente(input_files[i_particoes]) != NULL) {
                salva_cliente(cliente, output_file);
            }
            fclose(input_files[i_particoes]);
        }
        fclose(output_file);

        opened_files = 0;
        num_p++;

        // Cria um novo arquivo de particoes
        Nomes *nome_particoes_aux = nome_particoes;
        while (nome_particoes_aux) {
            nome_particoes_aux = nome_particoes_aux->prox;
        }
        nome_particoes_aux = cria_nomes(cria_str(output_filename), NULL);
    }
}