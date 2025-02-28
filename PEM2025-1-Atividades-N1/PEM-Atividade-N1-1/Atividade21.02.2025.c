/*-------------------------------------------------------*
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Calcular media candidatos        *
* Data - 28/02/2025                                      * 
* Autor: OSEIAS RIBEIRO DA SILVA;                        * 
*--------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

// Diretivas de pre-processamento
#define MAX_CANDIDATOS 50
#define MAX_NOTAS_PE 4
#define MAX_NOTAS_AC 5
#define MAX_NOTAS_PP 10
#define MAX_NOTAS_EB 3

// Função para calcular a média de um conjunto de notas, excluindo a maior e a menor
double calcular_nota(double notas[], int tamanho) {
    double soma = 0.0;
    double maior = notas[0], menor = notas[0];
    int removidoMaior = 0, removidoMenor = 0;

    // Encontra a maior e a menor nota
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
    }

    // Soma as notas, removendo apenas uma ocorrência de cada (maior e menor)
    for (int i = 0; i < tamanho; i++) {
        if (notas[i] == maior && removidoMaior == 0) {
            removidoMaior = 1;
            continue;
        }
        if (notas[i] == menor && removidoMenor == 0) {
            removidoMenor = 1;
            continue;
        }
        soma += notas[i];
    }

    // Se o problema pede a soma das notas centrais, retorne 'soma'.
    // Se for a média, descomente a linha abaixo:
    // return soma / (tamanho - 2);
    return soma;
}


int main() {
    char nomes[MAX_CANDIDATOS][100];
    double nota_PE[MAX_CANDIDATOS], nota_AC[MAX_CANDIDATOS], nota_PP[MAX_CANDIDATOS], nota_EB[MAX_CANDIDATOS];
    double nota_final[MAX_CANDIDATOS];
    int num_candidatos;

    // Solicita o número de candidatos
    printf("Digite o numero de candidatos (max %d): ", MAX_CANDIDATOS);
    scanf("%d", &num_candidatos);
    if (num_candidatos > MAX_CANDIDATOS) {
        printf("Numero de candidatos excede o maximo permitido.\n");
        return 1;
    }
    getchar();  // Limpa o buffer do teclado

    // Processamento de cada candidato
    for (int i = 0; i < num_candidatos; i++) {
        printf("\nDigite o nome do candidato %d: ", i + 1);
        fgets(nomes[i], sizeof(nomes[i]), stdin);
        nomes[i][strcspn(nomes[i], "\n")] = '\0'; // Remove o '\n'

        double notas_pe[MAX_NOTAS_PE], notas_ac[MAX_NOTAS_AC], notas_pp[MAX_NOTAS_PP], notas_eb[MAX_NOTAS_EB];

        // Entrada das notas da Prova Escrita (PE)
        printf("Digite as %d notas da Prova Escrita (PE): ", MAX_NOTAS_PE);
        for (int j = 0; j < MAX_NOTAS_PE; j++) {
            scanf("%lf", &notas_pe[j]);
        }

        // Entrada das notas da Análise Curricular (AC)
        printf("Digite as %d notas da Analise Curricular (AC): ", MAX_NOTAS_AC);
        for (int j = 0; j < MAX_NOTAS_AC; j++) {
            scanf("%lf", &notas_ac[j]);
        }

        // Entrada das notas da Prova Prática (PP)
        printf("Digite as %d notas da Prova Pratica (PP): ", MAX_NOTAS_PP);
        for (int j = 0; j < MAX_NOTAS_PP; j++) {
            scanf("%lf", &notas_pp[j]);
        }

        // Entrada das notas da Entrevista em Banca Avaliadora (EB)
        printf("Digite as %d notas da Entrevista em Banca Avaliadora (EB): ", MAX_NOTAS_EB);
        for (int j = 0; j < MAX_NOTAS_EB; j++) {
            scanf("%lf", &notas_eb[j]);
        }
        getchar();  // Limpa o buffer do teclado após a leitura dos números

        // Calcula a média de cada categoria (excluindo a maior e a menor nota)
        double media_pe = calcular_nota(notas_pe, MAX_NOTAS_PE);
        double media_ac = calcular_nota(notas_ac, MAX_NOTAS_AC);
        double media_pp = calcular_nota(notas_pp, MAX_NOTAS_PP);
        double media_eb = calcular_nota(notas_eb, MAX_NOTAS_EB);

        nota_PE[i] = media_pe;
        nota_AC[i] = media_ac;
        nota_PP[i] = media_pp;
        nota_EB[i] = media_eb;

        // Calcula a nota final com os pesos correspondentes
        nota_final[i] = (media_pe * 0.3) + (media_ac * 0.1) + (media_pp * 0.4) + (media_eb * 0.2);
    }

    // Ordena os candidatos por nota final em ordem decrescente (método bolha)
    for (int i = 0; i < num_candidatos - 1; i++) {
        for (int j = i + 1; j < num_candidatos; j++) {
            if (nota_final[i] < nota_final[j]) {
                // Troca os nomes
                char temp_nome[100];
                strcpy(temp_nome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], temp_nome);

                // Troca as notas finais
                double temp = nota_final[i];
                nota_final[i] = nota_final[j];
                nota_final[j] = temp;

                // Troca as médias individuais (opcional, se precisar exibi-las)
                temp = nota_PE[i];
                nota_PE[i] = nota_PE[j];
                nota_PE[j] = temp;

                temp = nota_AC[i];
                nota_AC[i] = nota_AC[j];
                nota_AC[j] = temp;

                temp = nota_PP[i];
                nota_PP[i] = nota_PP[j];
                nota_PP[j] = temp;

                temp = nota_EB[i];
                nota_EB[i] = nota_EB[j];
                nota_EB[j] = temp;
            }
        }
    }

    // Exibe a classificação dos 15 melhores candidatos (ou de todos, se houver menos de 15)
    int qtd_melhores = (num_candidatos < 15 ? num_candidatos : 15);
    printf("\nClassificacao dos %d Melhores Candidatos:\n", qtd_melhores);
    for (int i = 0; i < qtd_melhores; i++) {
        printf("%d. %s - Nota Final: %.2lf\n", i + 1, nomes[i], nota_final[i]);
    }

    return 0;
}