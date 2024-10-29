#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define PRECO_REFEICAO_KG 45.0 // Defini como 30
#define PESO_MEDIO_REFEICAO 1.0 // Média de 500g por refeição - Para dar valores mais realistas
#define DESVIO_PADRAO_PESO 1.0 // Aumento do desvio padrão para variar mais os preços das refeições
#define PRECO_QUENTINHA_FIXO 20.0 
#define PRECO_EMBALAGEM_QUENTINHA 0.5 

typedef enum {REFEICAO, BEBIDA, QUENTINHA} Item; //enum para os tipos de produtos

typedef struct { // Struct para venda/mês
    char nomeMes[20];
    float valorVenda;
} VendasMes;

float CalcularPrecoTotal(Item tipo, float preco, float peso, int quantidade) { // Cálculo de preços para os tipos de produtos
    float total = 0;
    switch (tipo) {
        case REFEICAO:
            total = peso * preco * quantidade;
            break;
        case QUENTINHA:
            total = PRECO_QUENTINHA_FIXO + (quantidade * PRECO_EMBALAGEM_QUENTINHA);
            break;
        case BEBIDA:
            total = preco * quantidade;
            break;
    }
    return total;
}

float GerarVendaDiaria() {
    float totalVenda = 0;
    for (int i = 0; i < 100; i++) {
        // Randomizar os tipos de item
        Item tipo = rand() % 3;
        float preco, peso;
        int quantidade;
        switch (tipo) {
            case REFEICAO: {
                float pesoMedio = PESO_MEDIO_REFEICAO;
                float desvioPadrao = DESVIO_PADRAO_PESO;
                peso = pesoMedio + (rand() / (float)RAND_MAX) * desvioPadrao * 2 - desvioPadrao; // Peso normalmente distribuído ao redor da média
                preco = PRECO_REFEICAO_KG;
                quantidade = rand() % 6 + 1; // Gerar quantidade diária aleatória de refeições
                break;
            }
            case QUENTINHA:
                preco = PRECO_QUENTINHA_FIXO;
                quantidade = rand() % 6 + 1; // Gerar quantidade diária aleatória de quentinhas
                break;
            case BEBIDA:
                preco = ((float)(rand() % 300) / 100.0) + 3.0; // Bebidas variam de R$3.00 a R$5.99
                quantidade = rand() % 5 + 1; // Gerar quantidade diária aleatória de bebidas
                break;
        }
        totalVenda += CalcularPrecoTotal(tipo, preco, peso, quantidade);
    }
    return totalVenda;
}

void BubbleSort(VendasMes vet[], int n) { // Ordenação BubbleSort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vet[j].valorVenda < vet[j + 1].valorVenda) {
                VendasMes temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

int main() {
    const int DiasAno = 365;
    const int DiaMes = 30;
    float totalAnual = 0;
    char *nomesMeses[] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};
    int escolha;
    VendasMes VendasAnuais[12];
    float VendasMensais[12] = {0}; // Inicializando com 0
    float totaisSemanais[12][3] = {0}; // 12 meses e 3 tipos de itens (refeição, quentinha, bebida)
    int quantSemanais[12][3] = {0};

    setlocale(LC_ALL, "pt_BR.UTF-8"); // Colocando no formato da moeda daqui do Brasil

    unsigned int gerar = (unsigned int) time(NULL);
    srand(gerar); //Geração dos dados de forma aleatória

    for (int dia = 1; dia <= DiasAno; dia++) {
        int mesAtual = (dia - 1) / DiaMes; // Determina o mês atual
        VendasMensais[mesAtual] += GerarVendaDiaria();
    }

    do {
        printf("Escolha o tipo de relatorio:\n");
        printf("1 - Relatorio Semanal\n");
        printf("2 - Relatorio Mensal geral\n");
        printf("3 - Relatorio Anual\n");
        printf("4 - Buscar por mes para obter um relatorio mensal\n");
        printf("0 - Sair\n");
        scanf("%d", &escolha);
        getchar();
        printf("\n");

        switch (escolha) {
            case 1:
    // Relatório Semanal de 4 semanas
    for (int mes = 0; mes < 12; mes++) {
        printf("Relatorio do mes de %s:\n\n", nomesMeses[mes]);
        int diasNoMes = (mes == 11) ? 31 : 30;
        int semanasNoMes = 4;
        int diasPorSemana = diasNoMes / semanasNoMes;

        for (int semana = 0; semana < semanasNoMes; semana++) {
            printf("Relatorio da semana %d:\n", semana + 1);
            float totalRefeicao = 0; // Variáveis para rastrear os totais semanais de refeição, quentinha e bebidas
            float totalQuentinha = 0;
            float totalBebidas = 0;
            int quantidadeRefeicao = 0; // Variáveis para rastrear as quantidades semanais de refeição, quentinha e bebidas
            int quantidadeQuentinha = 0;
            int quantidadeBebidas = 0;

            int primeiroDiaSemana = semana * diasPorSemana + 1;
            int ultimoDiaSemana = (semana == semanasNoMes - 1) ? diasNoMes : primeiroDiaSemana + diasPorSemana - 1;

            for (int dia = primeiroDiaSemana; dia <= ultimoDiaSemana; dia++) {
                // Gera vendas diárias para refeições
                int quantidadeDiariaRefeicao = rand() % 6 + 1; // Gerar quantidade diária aleatória de refeições
                quantidadeRefeicao += quantidadeDiariaRefeicao; // Atualizar a quantidade semanal de refeições
                totalRefeicao += CalcularPrecoTotal(REFEICAO, PRECO_REFEICAO_KG, PESO_MEDIO_REFEICAO, 1) * quantidadeDiariaRefeicao;

                // Gera vendas diárias para quentinhas
                int quantidadeDiariaQuentinha = rand() % 6 + 1; // Gerar quantidade diária aleatória de quentinhas
                quantidadeQuentinha += quantidadeDiariaQuentinha; // Atualizar a quantidade semanal de quentinhas
                totalQuentinha += CalcularPrecoTotal(QUENTINHA, PRECO_QUENTINHA_FIXO, 0, 1) * quantidadeDiariaQuentinha;

                // Gera vendas diárias para bebidas
                int quantidadeDiariaBebidas = rand() % 5 + 1; // Gerar quantidade diária aleatória de bebidas
                quantidadeBebidas += quantidadeDiariaBebidas; // Atualizar a quantidade semanal de bebidas
                totalBebidas += CalcularPrecoTotal(BEBIDA, ((float)(rand() % 300) / 100.0) + 3.0, 0, 1) * quantidadeDiariaBebidas;
            }

            quantSemanais[mes][REFEICAO] += quantidadeRefeicao;
            quantSemanais[mes][QUENTINHA] += quantidadeQuentinha;
            quantSemanais[mes][BEBIDA] += quantidadeBebidas;

            // Atualiza a matriz de totais semanais
            totaisSemanais[mes][REFEICAO] += totalRefeicao;
            totaisSemanais[mes][QUENTINHA] += totalQuentinha;
            totaisSemanais[mes][BEBIDA] += totalBebidas;

            printf("Quantidade de refeicoes vendidas na semana: %d\n", quantidadeRefeicao);
            printf("Quantidade de quentinhas vendidas na semana: %d\n", quantidadeQuentinha);
            printf("Quantidade de bebidas vendidas na semana: %d\n\n", quantidadeBebidas);
            printf("Valor total de refeicoes na semana: R$%.2f\n", totalRefeicao);
            printf("Valor total de quentinhas na semana: R$%.2f\n", totalQuentinha);
            printf("Valor total de bebidas na semana: R$%.2f\n", totalBebidas);
            printf("Total vendido na semana: R$%.2f\n\n", totalRefeicao + totalQuentinha + totalBebidas);
        }
    }
            break;
            case 2:
            // Relatório Mensal
            for (int mes = 0; mes < 12; mes++) {
                printf("Relatorio do mes de %s:\n", nomesMeses[mes]);

            // Obtém os totais mensais de cada tipo de item do array totaisSemanais
            float totalRefeicao = totaisSemanais[mes][REFEICAO];
            float totalQuentinha = totaisSemanais[mes][QUENTINHA];
            float totalBebidas = totaisSemanais[mes][BEBIDA];

            int quantidadeRefeicao = quantSemanais[mes][REFEICAO];
            int quantidadeQuentinha = quantSemanais[mes][QUENTINHA];
            int quantidadeBebidas = quantSemanais[mes][BEBIDA];
        
            printf("Total vendido de refeicao: R$%.2f\n", totalRefeicao);
            printf("Total vendido de quentinha: R$%.2f\n", totalQuentinha);
            printf("Total vendido de bebidas: R$%.2f\n\n", totalBebidas);

            printf("Quantidade de refeicao: %d\n", quantidadeRefeicao);
            printf("Quantidade de quentinha: %d\n", quantidadeQuentinha);
            printf("Quantidade de bebidas: %d\n", quantidadeBebidas);

            // Calcula e imprime o total vendido no mês
            float totalMensal = totalRefeicao + totalQuentinha + totalBebidas;
            printf("Total vendido no mes: R$%.2f\n\n", totalMensal);

            // Armazena o total mensal no array VendasMensais
            VendasMensais[mes] = totalMensal;
        }
            break;
            case 3:
            // Copiar os valores mensais para o array VendasAnuais
            for (int mes = 0; mes < 12; mes++) {
                strcpy(VendasAnuais[mes].nomeMes, nomesMeses[mes]);
                VendasAnuais[mes].valorVenda = VendasMensais[mes]; // Corrigindo para VendasMensais
                totalAnual += VendasMensais[mes];
            }

            // Ordenar os valores anuais usando o BubbleSort
            BubbleSort(VendasAnuais, 12);

            // Imprimir o relatório anual
            printf("Relatorio anual:\n");
            printf("Total vendido no ano: R$%.2f\n\n", totalAnual);
            printf("Meses com maiores vendas:\n");
            for (int i = 0; i < 12; i++) {
                printf("%s: R$%.2f\n", VendasAnuais[i].nomeMes, VendasAnuais[i].valorVenda);
            }
            printf("\n");
            break;
            case 4:
            printf("Digite o nome do mes para visualizar o relatorio mensal: ");
            char nomeMes[20];
            scanf("%s", nomeMes);
            getchar();

            int indiceMes = -1;
            // Procurar o índice do mês inserido
            for (int i = 0; i < 12; i++) {
            if (strcmp(nomeMes, nomesMeses[i]) == 0) {
            indiceMes = i;
            break;
            }
            }
            if (indiceMes != -1) {
            printf("Relatorio do mes de %s:\n", nomeMes);

            // Obtém os totais mensais de cada tipo de item do array totaisSemanais
            float totalRefeicao = totaisSemanais[indiceMes][REFEICAO];
            float totalQuentinha = totaisSemanais[indiceMes][QUENTINHA];
            float totalBebidas = totaisSemanais[indiceMes][BEBIDA];

            int quantidadeRefeicao = quantSemanais[indiceMes][REFEICAO];
            int quantidadeQuentinha = quantSemanais[indiceMes][QUENTINHA];
            int quantidadeBebidas = quantSemanais[indiceMes][BEBIDA];

            printf("Total vendido de refeicao: R$%.2f\n", totalRefeicao);
            printf("Total vendido de quentinha: R$%.2f\n", totalQuentinha);
            printf("Total vendido de bebidas: R$%.2f\n\n", totalBebidas);

            printf("Quantidade de refeicao: %d\n", quantidadeRefeicao);
            printf("Quantidade de quentinha: %d\n", quantidadeQuentinha);
            printf("Quantidade de bebidas: %d\n", quantidadeBebidas);

            // Calcula e imprime o total vendido no mês
            float totalMensal = totalRefeicao + totalQuentinha + totalBebidas;
            printf("Total vendido no mes: R$%.2f\n\n", totalMensal);

            // Armazena o total mensal no array VendasMensais
            VendasMensais[indiceMes] = totalMensal;
            } else {
                    printf("Mes nao encontrado!\n");
            }
            break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Escolha invalida!\n");
                break;
        
        }

    } while (escolha != 0);

    return 0;
}