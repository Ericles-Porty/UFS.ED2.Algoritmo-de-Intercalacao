//
// Created by Vanessa Braganholo.
// Updated by Raphael Oliveira.

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <io.h>
#define F_OK 0
#define ACCESS _access
#else

#include <unistd.h>

#define ACCESS access
#endif

#define AFTER_TEST after();
#define NOME_ARQUIVO_SAIDA "saida.dat"

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "ufftest.h"
#include "cliente.h"
#include "lista_clientes.h"
#include "nomes.h"
#include "intercalacao.h"

Nomes *nomes = NULL;

void after() {
    Nomes *atual = nomes;
    while (atual) {
        remove(atual->nome);
        atual = atual->prox;
    }
    libera_nomes(nomes);
    nomes = NULL;
}

int file_exist(char *filename) {
    return (ACCESS(filename, F_OK) != -1);
}

BEGIN_TESTS();

/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A ALGORITMO BASICO DE INTERCALAÇÃO
 * *******************************************************************
 *********************************************************************/


    TEST("Teste 1 Intercalacao Basico. Arquivo p1.dat vazio deve criar saida.dat vazio.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"), NULL);

        entrada = cria_clientes(0);
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        intercalacao_basico(NOME_ARQUIVO_SAIDA, 1, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(0);
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 2 Intercalacao Basico. Duas particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria"));
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        intercalacao_basico(NOME_ARQUIVO_SAIDA, 2, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(6,
                                cliente(1, "Joao"),
                                cliente(3, "Marcos"),
                                cliente(5, "Maria"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 3 Intercalacao Basico. Tres particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"),
                cria_nomes(cria_str("p2.dat"),
                           cria_nomes(cria_str("p3.dat"),
                        NULL)));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria")
                                );
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(2, "Carol")
                                );
        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        intercalacao_basico(NOME_ARQUIVO_SAIDA, 3, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(7,
                                cliente(1, "Joao"),
                                cliente(2, "Carol"),
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(5, "Maria"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 4 Intercalacao Basico. Quatro particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"), NULL))));

        entrada = cria_clientes(6,
                      cliente(1, "Joao"),
                      cliente(3, "Matheus"),
                      cliente(5, "Maria"),
                      cliente(10, "Mirtes"),
                      cliente(20, "Mariana"),
                      cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        intercalacao_basico(NOME_ARQUIVO_SAIDA, 4, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(20,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 5 Intercalacao Basico. Onze particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                   cria_nomes(cria_str("p3.dat"),
                                           cria_nomes(cria_str("p4.dat"),
                                                      cria_nomes(cria_str("p5.dat"),
                                                                 cria_nomes(cria_str("p6.dat"),
                                                                            cria_nomes(cria_str("p7.dat"),
                                                                                       cria_nomes(cria_str("p8.dat"),
                                                                                                  cria_nomes(cria_str("p9.dat"),
                                                                                                             cria_nomes(cria_str("p10.dat"),
                                                                                                                        cria_nomes(cria_str("p11.dat"),
                                                                                                                     NULL)))))))))));

        entrada = cria_clientes(5,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(7,
                                cliente(10, "Mirtes"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(11, "Leonel"),
                                cliente(15, "Alice"),
                                cliente(100, "Juca"));

        salva_clientes("p5.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(19, "Juliana"),
                                cliente(25, "Maria"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(72, "Ana Clara"));

        salva_clientes("p6.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(32, "Josias"),
                                cliente(73, "Jonas"),
                                cliente(102, "Alessandra"));

        salva_clientes("p7.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(24, "Bruno"),
                                cliente(29, "Carlos"),
                                cliente(98, "Amanda"));

        salva_clientes("p8.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(34, "Marcel")
                                );

        salva_clientes("p9.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(12, "Flavio"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(63, "Jasmine")
                                );

        salva_clientes("p10.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(6, "Messias"),
                                cliente(52, "Daniel")
        );

        salva_clientes("p11.dat", entrada);
        libera_clientes(entrada);

        intercalacao_basico(NOME_ARQUIVO_SAIDA, 11, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(42,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(6, "Messias"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(11, "Leonel"),
                                cliente(12, "Flavio"),
                                cliente(15, "Alice"),
                                cliente(19, "Juliana"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(24, "Bruno"),
                                cliente(25, "Maria"),
                                cliente(29, "Carlos"),
                                cliente(32, "Josias"),
                                cliente(34, "Marcel"),
                                cliente(35, "Marceu"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(52, "Daniel"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(60, "Hugo"),
                                cliente(63, "Jasmine"),
                                cliente(72, "Ana Clara"),
                                cliente(73, "Jonas"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"),
                                cliente(98, "Amanda"),
                                cliente(100, "Juca"),
                                cliente(102, "Alessandra")
                                );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

/*********************************************************************
 * *******************************************************************
 * TESTES RELACIONADOS A INTERCALACAO COM ARVORE DE VENCEDORES
 * *******************************************************************
 *********************************************************************/

    TEST("Teste 6 Intercalacao Arvore Vencedores. Arquivo p1.dat vazio deve criar saida.dat vazio.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"), NULL);

        entrada = cria_clientes(0);
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        intercalacao_arv_vencedores(NOME_ARQUIVO_SAIDA, 1, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(0);

        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 7 Intercalacao Arvore Vencedores. Duas particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria"));
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        intercalacao_arv_vencedores(NOME_ARQUIVO_SAIDA, 2, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(6,
                                cliente(1, "Joao"),
                                cliente(3, "Marcos"),
                                cliente(5, "Maria"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 8 Intercalacao Arvore Vencedores. Tres particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        Nomes *p;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 NULL)));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria")
        );
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(2, "Carol")
        );
        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        intercalacao_arv_vencedores(NOME_ARQUIVO_SAIDA, 3, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(7,
                                cliente(1, "Joao"),
                                cliente(2, "Carol"),
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(5, "Maria"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 9 Intercalacao Arvore Vencedores. Quatro particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"), NULL))));

        entrada = cria_clientes(6,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(10, "Mirtes"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        intercalacao_arv_vencedores(NOME_ARQUIVO_SAIDA, 4, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(20,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 10 Intercalacao Arv Vencedores. Onze particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        Nomes *p;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"),
                                                            cria_nomes(cria_str("p5.dat"),
                                                                       cria_nomes(cria_str("p6.dat"),
                                                                                  cria_nomes(cria_str("p7.dat"),
                                                                                             cria_nomes(cria_str("p8.dat"),
                                                                                                        cria_nomes(cria_str("p9.dat"),
                                                                                                                   cria_nomes(cria_str("p10.dat"),
                                                                                                                              cria_nomes(cria_str("p11.dat"),
                                                                                                                                         NULL)))))))))));

        entrada = cria_clientes(5,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(7,
                                cliente(10, "Mirtes"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(11, "Leonel"),
                                cliente(15, "Alice"),
                                cliente(100, "Juca"));

        salva_clientes("p5.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(19, "Juliana"),
                                cliente(25, "Maria"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(72, "Ana Clara"));

        salva_clientes("p6.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(32, "Josias"),
                                cliente(73, "Jonas"),
                                cliente(102, "Alessandra"));

        salva_clientes("p7.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(24, "Bruno"),
                                cliente(29, "Carlos"),
                                cliente(98, "Amanda"));

        salva_clientes("p8.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(34, "Marcel")
        );

        salva_clientes("p9.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(12, "Flavio"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(63, "Jasmine")
        );

        salva_clientes("p10.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(6, "Messias"),
                                cliente(52, "Daniel")
        );

        salva_clientes("p11.dat", entrada);
        libera_clientes(entrada);

        intercalacao_arv_vencedores(NOME_ARQUIVO_SAIDA, 11, nomes);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(42,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(6, "Messias"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(11, "Leonel"),
                                cliente(12, "Flavio"),
                                cliente(15, "Alice"),
                                cliente(19, "Juliana"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(24, "Bruno"),
                                cliente(25, "Maria"),
                                cliente(29, "Carlos"),
                                cliente(32, "Josias"),
                                cliente(34, "Marcel"),
                                cliente(35, "Marceu"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(52, "Daniel"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(60, "Hugo"),
                                cliente(63, "Jasmine"),
                                cliente(72, "Ana Clara"),
                                cliente(73, "Jonas"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"),
                                cliente(98, "Amanda"),
                                cliente(100, "Juca"),
                                cliente(102, "Alessandra")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
        }



/*********************************************************************
* *******************************************************************
* TESTES RELACIONADOS A INTERCALACAO OTIMA
* *******************************************************************
*********************************************************************/

    TEST("Teste 11 Intercalacao Otima. Arquivo p1.dat vazio deve criar saida.dat vazio.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"), NULL);

        entrada = cria_clientes(0);
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 1, nomes, 3);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(0);

        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 12 Intercalacao Otima. Duas particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        nomes = cria_nomes(cria_str("p1.dat"), cria_nomes(cria_str("p2.dat"), NULL));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria"));
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 2, nomes, 3);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(6,
                                cliente(1, "Joao"),
                                cliente(3, "Marcos"),
                                cliente(5, "Maria"),
                                cliente(6, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA))
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes)
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 13 Intercalacao Otima. Tres particoes.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        Nomes *p;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 NULL)));

        entrada = cria_clientes(2,
                                cliente(1, "Joao"),
                                cliente(5, "Maria")
        );
        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim"));
        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(2, "Carol")
        );
        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 3, nomes, 3);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(7,
                                cliente(1, "Joao"),
                                cliente(2, "Carol"),
                                cliente(3, "Marcos"),
                                cliente(4, "Ana"),
                                cliente(5, "Maria"),
                                cliente(7, "Bia"),
                                cliente(10, "Joaquim")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
        
    }

    TEST("Teste 14 Intercalacao Otima. Quatro particoes.");
    if (!skip) {
        
        ListaClientes *entrada, *oraculo, *saida;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"), NULL))));

        entrada = cria_clientes(6,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(10, "Mirtes"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 4, nomes, 3);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(20,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"));
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 15 Intercalacao Otima. Onze particoes com f = 3.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        Nomes *p;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"),
                                                            cria_nomes(cria_str("p5.dat"),
                                                                       cria_nomes(cria_str("p6.dat"),
                                                                                  cria_nomes(cria_str("p7.dat"),
                                                                                             cria_nomes(cria_str("p8.dat"),
                                                                                                        cria_nomes(cria_str("p9.dat"),
                                                                                                                   cria_nomes(cria_str("p10.dat"),
                                                                                                                              cria_nomes(cria_str("p11.dat"),
                                                                                                                                         NULL)))))))))));

        entrada = cria_clientes(5,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(7,
                                cliente(10, "Mirtes"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(11, "Leonel"),
                                cliente(15, "Alice"),
                                cliente(100, "Juca"));

        salva_clientes("p5.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(19, "Juliana"),
                                cliente(25, "Maria"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(72, "Ana Clara"));

        salva_clientes("p6.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(32, "Josias"),
                                cliente(73, "Jonas"),
                                cliente(102, "Alessandra"));

        salva_clientes("p7.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(24, "Bruno"),
                                cliente(29, "Carlos"),
                                cliente(98, "Amanda"));

        salva_clientes("p8.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(34, "Marcel")
        );

        salva_clientes("p9.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(12, "Flavio"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(63, "Jasmine")
        );

        salva_clientes("p10.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(6, "Messias"),
                                cliente(52, "Daniel")
        );

        salva_clientes("p11.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 11, nomes, 3);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(42,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(6, "Messias"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(11, "Leonel"),
                                cliente(12, "Flavio"),
                                cliente(15, "Alice"),
                                cliente(19, "Juliana"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(24, "Bruno"),
                                cliente(25, "Maria"),
                                cliente(29, "Carlos"),
                                cliente(32, "Josias"),
                                cliente(34, "Marcel"),
                                cliente(35, "Marceu"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(52, "Daniel"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(60, "Hugo"),
                                cliente(63, "Jasmine"),
                                cliente(72, "Ana Clara"),
                                cliente(73, "Jonas"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"),
                                cliente(98, "Amanda"),
                                cliente(100, "Juca"),
                                cliente(102, "Alessandra")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }

    TEST("Teste 16 Intercalacao Otima. Onze particoes com f = 5.");
    if (!skip) {
        ListaClientes *entrada, *oraculo, *saida;
        Nomes *p;

        nomes = cria_nomes(cria_str("p1.dat"),
                           cria_nomes(cria_str("p2.dat"),
                                      cria_nomes(cria_str("p3.dat"),
                                                 cria_nomes(cria_str("p4.dat"),
                                                            cria_nomes(cria_str("p5.dat"),
                                                                       cria_nomes(cria_str("p6.dat"),
                                                                                  cria_nomes(cria_str("p7.dat"),
                                                                                             cria_nomes(cria_str("p8.dat"),
                                                                                                        cria_nomes(cria_str("p9.dat"),
                                                                                                                   cria_nomes(cria_str("p10.dat"),
                                                                                                                              cria_nomes(cria_str("p11.dat"),
                                                                                                                                         NULL)))))))))));

        entrada = cria_clientes(5,
                                cliente(1, "Joao"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(20, "Mariana"),
                                cliente(87, "Jonas"));

        salva_clientes("p1.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(0, "Julia"),
                                cliente(2, "Marcos"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(81, "Bianca"));

        salva_clientes("p2.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(7,
                                cliente(10, "Mirtes"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(35, "Marceu"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(60, "Hugo"));

        salva_clientes("p3.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(85, "Leonardo"),
                                cliente(90, "Catarina"));

        salva_clientes("p4.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(11, "Leonel"),
                                cliente(15, "Alice"),
                                cliente(100, "Juca"));

        salva_clientes("p5.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(6,
                                cliente(19, "Juliana"),
                                cliente(25, "Maria"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(72, "Ana Clara"));

        salva_clientes("p6.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(32, "Josias"),
                                cliente(73, "Jonas"),
                                cliente(102, "Alessandra"));

        salva_clientes("p7.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(3,
                                cliente(24, "Bruno"),
                                cliente(29, "Carlos"),
                                cliente(98, "Amanda"));

        salva_clientes("p8.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(1,
                                cliente(34, "Marcel")
        );

        salva_clientes("p9.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(4,
                                cliente(12, "Flavio"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(63, "Jasmine")
        );

        salva_clientes("p10.dat", entrada);
        libera_clientes(entrada);

        entrada = cria_clientes(2,
                                cliente(6, "Messias"),
                                cliente(52, "Daniel")
        );

        salva_clientes("p11.dat", entrada);
        libera_clientes(entrada);

        intercalacao_otima(NOME_ARQUIVO_SAIDA, 11, nomes, 5);

        saida = le_clientes(NOME_ARQUIVO_SAIDA);
        oraculo = cria_clientes(42,
                                cliente(0, "Julia"),
                                cliente(1, "Joao"),
                                cliente(2, "Marcos"),
                                cliente(3, "Matheus"),
                                cliente(5, "Maria"),
                                cliente(6, "Messias"),
                                cliente(7, "Bruna"),
                                cliente(8, "Vanessa"),
                                cliente(9, "Ana Maria"),
                                cliente(10, "Mirtes"),
                                cliente(11, "Leonel"),
                                cliente(12, "Flavio"),
                                cliente(15, "Alice"),
                                cliente(19, "Juliana"),
                                cliente(20, "Mariana"),
                                cliente(22, "Lucila"),
                                cliente(23, "Clarissa"),
                                cliente(24, "Bruno"),
                                cliente(25, "Maria"),
                                cliente(29, "Carlos"),
                                cliente(32, "Josias"),
                                cliente(34, "Marcel"),
                                cliente(35, "Marceu"),
                                cliente(40, "Mafalda"),
                                cliente(41, "Epaminondas"),
                                cliente(46, "Celso"),
                                cliente(47, "Martim"),
                                cliente(48, "Tatiana"),
                                cliente(52, "Daniel"),
                                cliente(55, "Fernanda"),
                                cliente(59, "Priscila"),
                                cliente(60, "Hugo"),
                                cliente(63, "Jasmine"),
                                cliente(72, "Ana Clara"),
                                cliente(73, "Jonas"),
                                cliente(81, "Bianca"),
                                cliente(85, "Leonardo"),
                                cliente(87, "Jonas"),
                                cliente(90, "Catarina"),
                                cliente(98, "Amanda"),
                                cliente(100, "Juca"),
                                cliente(102, "Alessandra")
        );
        ASSERT_TRUE(file_exist(NOME_ARQUIVO_SAIDA));
        ASSERT_EQUAL_CMP(oraculo, saida, cmp_clientes);
        libera_clientes(oraculo);
        libera_clientes(saida);
        remove(NOME_ARQUIVO_SAIDA);
    }
END_TESTS();