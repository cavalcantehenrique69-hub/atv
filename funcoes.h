#include <stdio.h>
#include "funcoes.h"


void exibirMenu() {
    printf("\n==========================================\n");
    printf("         CONTROLE DE ESTOQUE\n");
    printf("==========================================\n");
    printf("1. Cadastrar produtos\n");
    printf("2. Consultar estoque\n");
    printf("3. Registrar venda\n");
    printf("4. Consultar produtos que precisam de reposicao\n");
    printf("5. Registrar entrada de mercadorias\n");
    printf("6. Encerrar o programa\n");
    printf("------------------------------------------\n");
}


void exibirTitulo(char titulo[]) {
    printf("\n------------------------------------------\n");
    printf("%s\n", titulo);
    printf("------------------------------------------\n");
}


void limparBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


int lerInteiro(char mensagem[]) {
    int numero;
    int retorno;

    printf("%s", mensagem);
    retorno = scanf("%d", &numero);

    while (retorno != 1) {
        limparBuffer();
        printf("Entrada invalida! Digite um numero.\n");
        printf("%s", mensagem);
        retorno = scanf("%d", &numero);
    }

    return numero;
}


float lerReal(char mensagem[]) {
    float numero;
    int retorno;

    printf("%s", mensagem);
    retorno = scanf("%f", &numero);

    while (retorno != 1) {
        limparBuffer();
        printf("Entrada invalida! Digite um numero.\n");
        printf("%s", mensagem);
        retorno = scanf("%f", &numero);
    }

    return numero;
}


int lerCodigoProduto(int total) {
    int codigo;

    codigo = lerInteiro("Codigo do produto: ");

    while (codigo < 1 || codigo > total) {
        printf("Codigo invalido! Digite um valor entre 1 e %d.\n", total);
        codigo = lerInteiro("Codigo do produto: ");
    }

    return codigo - 1;
}


void cadastrarProdutos(char nomes[10][50], float precos[10], int quantidades[10], int *total) {
    int i;
    int quantos;
    int vagas;
    int posicao;

    exibirTitulo("CADASTRO DE PRODUTOS");

    vagas = 10 - *total;

    if (vagas == 0) {
        printf("O estoque ja esta cheio! Limite de 10 produtos.\n");
        return;
    }

    printf("Ainda e possivel cadastrar %d produto(s).\n", vagas);
    quantos = lerInteiro("Quantos produtos deseja cadastrar? ");

    while (quantos < 1 || quantos > vagas) {
        printf("Quantidade invalida! Digite um valor entre 1 e %d.\n", vagas);
        quantos = lerInteiro("Quantos produtos deseja cadastrar? ");
    }

    for (i = 0; i < quantos; i++) {
        posicao = *total;

        printf("\n>>> Produto numero %d <<<\n", posicao + 1);

        printf("Nome (sem espacos): ");
        scanf("%49s", nomes[posicao]);

        precos[posicao] = lerReal("Preco unitario: R$ ");
        while (precos[posicao] <= 0) {
            printf("O preco precisa ser maior que zero!\n");
            precos[posicao] = lerReal("Preco unitario: R$ ");
        }

        quantidades[posicao] = lerInteiro("Quantidade em estoque: ");
        while (quantidades[posicao] < 0) {
            printf("A quantidade nao pode ser negativa!\n");
            quantidades[posicao] = lerInteiro("Quantidade em estoque: ");
        }

        *total = *total + 1;
        printf("Produto cadastrado com sucesso! Codigo: %d\n", posicao + 1);
    }
}


void consultarEstoque(char nomes[10][50], float precos[10], int quantidades[10], int total) {
    int i;

    exibirTitulo("CONSULTA DE ESTOQUE");

    if (total == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        return;
    }

    printf("%-8s %-20s %-12s %-10s\n", "Codigo", "Nome", "Preco (R$)", "Qtd");
    printf("------------------------------------------------------\n");

    for (i = 0; i < total; i++) {
        printf("%-8d %-20s %-12.2f %-10d\n", i + 1, nomes[i], precos[i], quantidades[i]);
    }

    printf("------------------------------------------------------\n");
    printf("Total de produtos cadastrados: %d\n", total);
    printf("Valor total do estoque: R$ %.2f\n", valorTotalEstoque(precos, quantidades, total));
}


void registrarVenda(char nomes[10][50], float precos[10], int quantidades[10], int total) {
    int posicao;
    int quantidade;
    float valorVenda;

    exibirTitulo("REGISTRO DE VENDA");

    if (total == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        return;
    }

    posicao = lerCodigoProduto(total);

    printf("Produto escolhido: %s\n", nomes[posicao]);
    printf("Quantidade disponivel: %d\n", quantidades[posicao]);

    quantidade = lerInteiro("Quantidade que o cliente deseja comprar: ");

    while (quantidade <= 0) {
        printf("A quantidade precisa ser maior que zero!\n");
        quantidade = lerInteiro("Quantidade que o cliente deseja comprar: ");
    }

   
    if (quantidade <= quantidades[posicao]) {
        quantidades[posicao] = quantidades[posicao] - quantidade;
        valorVenda = calcularFaturamento(precos[posicao], quantidade);

        printf("\nVenda realizada com sucesso!\n");
        printf("Produto: %s\n", nomes[posicao]);
        printf("Quantidade vendida: %d\n", quantidade);
        printf("Valor total da venda: R$ %.2f\n", valorVenda);
        printf("Estoque restante: %d\n", quantidades[posicao]);
    } else {
        printf("\nA venda nao pode ser realizada!\n");
        printf("Estoque insuficiente. Disponivel: %d | Pedido: %d\n", quantidades[posicao], quantidade);
    }
}


void alertaReposicao(char nomes[10][50], int quantidades[10], int total) {
    int i;
    int contador = 0;

    exibirTitulo("ALERTA DE REPOSICAO");

    if (total == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (quantidades[i] < 5) {
            printf("Produto: %s | Quantidade atual: %d\n", nomes[i], quantidades[i]);
            contador++;
        }
    }

    if (contador == 0) {
        printf("Nenhum produto com menos de 5 unidades. Estoque em dia!\n");
    } else {
        printf("\n%d produto(s) precisam de reposicao.\n", contador);
    }
}


void entradaMercadorias(char nomes[10][50], int quantidades[10], int total) {
    int posicao;
    int quantidade;

    exibirTitulo("ENTRADA DE MERCADORIAS");

    if (total == 0) {
        printf("Nenhum produto cadastrado ainda.\n");
        return;
    }

    posicao = lerCodigoProduto(total);

    printf("Produto escolhido: %s\n", nomes[posicao]);
    printf("Quantidade atual: %d\n", quantidades[posicao]);

    quantidade = lerInteiro("Quantidade de unidades recebidas: ");

    
    while (quantidade <= 0) {
        printf("Quantidade invalida! Digite um valor maior que zero.\n");
        quantidade = lerInteiro("Quantidade de unidades recebidas: ");
    }

    quantidades[posicao] = quantidades[posicao] + quantidade;

    printf("\nEntrada registrada com sucesso!\n");
    printf("Nova quantidade de %s: %d\n", nomes[posicao], quantidades[posicao]);
}


float calcularFaturamento(float preco, int quantidade) {
    float total;

    total = preco * quantidade;

    return total;
}


float valorTotalEstoque(float precos[10], int quantidades[10], int total) {
    int i;
    float soma = 0;

    for (i = 0; i < total; i++) {
        soma = soma + (precos[i] * quantidades[i]);
    }

    return soma;
}
