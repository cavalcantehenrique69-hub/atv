#ifndef FUNCOES_H
#define FUNCOES_H


void exibirMenu();
void exibirTitulo(char titulo[]);
void limparBuffer();
int lerInteiro(char mensagem[]);
float lerReal(char mensagem[]);
int lerCodigoProduto(int total);


void cadastrarProdutos(char nomes[10][50], float precos[10], int quantidades[10], int *total);
void consultarEstoque(char nomes[10][50], float precos[10], int quantidades[10], int total);
void registrarVenda(char nomes[10][50], float precos[10], int quantidades[10], int total);
void alertaReposicao(char nomes[10][50], int quantidades[10], int total);
void entradaMercadorias(char nomes[10][50], int quantidades[10], int total);
float calcularFaturamento(float preco, int quantidade);
float valorTotalEstoque(float precos[10], int quantidades[10], int total);

#endif
