#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LIVROS 999
#define MAX_CLIENTES 999
#define MAX_VENDAS 999
#define MAX_ALUGUEIS 999

// Estruturas
typedef struct {
    int id;
    char nome[100];
    int quantidade;
    float valor;
} Livro;

typedef struct {
    int id;
    char nome[100];
} Cliente;

typedef struct {
    char nomeCliente[100];
    char nomeLivro[100];
    int quantidade;
    float valorTotal;
} Venda;

typedef struct {
    char nomeCliente[100];
    char nomeLivro[100];
} Aluguel;

// Variáveis globais
Livro livros[MAX_LIVROS];
Cliente clientes[MAX_CLIENTES];
Venda vendas[MAX_VENDAS];
Aluguel alugueis[MAX_ALUGUEIS];
int livroCount = 0, clienteCount = 0, vendaCount = 0, aluguelCount = 0;

// Funções auxiliares
int buscarClientePorNome(char *nome) {
    for (int i = 0; i < clienteCount; i++) {
        if (strcmp(clientes[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarLivroPorNome(char *nome) {
    for (int i = 0; i < livroCount; i++) {
        if (strcmp(livros[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void cadastrarLivro() {
    if (livroCount >= MAX_LIVROS) {
        printf("Capacidade de livros atingida!\n");
        return;
    }
    printf("Digite o nome do livro: ");
    scanf(" %[^\n]s", livros[livroCount].nome);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &livros[livroCount].quantidade);
    printf("Digite o valor do livro: ");
    scanf("%f", &livros[livroCount].valor);
    livros[livroCount].id = livroCount + 1;
    livroCount++;
    printf("Livro cadastrado com sucesso!\n");
}

void cadastrarCliente() {
    if (clienteCount >= MAX_CLIENTES) {
        printf("Capacidade de clientes atingida!\n");
        return;
    }
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", clientes[clienteCount].nome);
    clientes[clienteCount].id = clienteCount + 1;
    clienteCount++;
    printf("Cliente cadastrado com sucesso!\n");
}

void alugarLivro() {
    char nomeCliente[100], nomeLivro[100];
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", nomeCliente);
    printf("Digite o nome do livro: ");
    scanf(" %[^\n]s", nomeLivro);

    int clienteIndex = buscarClientePorNome(nomeCliente);
    int livroIndex = buscarLivroPorNome(nomeLivro);

    if (clienteIndex == -1 || livroIndex == -1) {
        printf("Cliente ou livro não encontrado!\n");
        return;
    }

    if (livros[livroIndex].quantidade == 0) {
        printf("Livro em falta!\n");
        return;
    }

    livros[livroIndex].quantidade--;
    strcpy(alugueis[aluguelCount].nomeCliente, nomeCliente);
    strcpy(alugueis[aluguelCount].nomeLivro, nomeLivro);
    aluguelCount++;
    printf("Livro alugado com sucesso!\n");
}

void venderLivro() {
    char nomeCliente[100], nomeLivro[100];
    int quantidade;
    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", nomeCliente);
    printf("Digite o nome do livro: ");
    scanf(" %[^\n]s", nomeLivro);
    printf("Digite a quantidade: ");
    scanf("%d", &quantidade);

    int clienteIndex = buscarClientePorNome(nomeCliente);
    int livroIndex = buscarLivroPorNome(nomeLivro);

    if (clienteIndex == -1 || livroIndex == -1) {
        printf("Cliente ou livro não encontrado!\n");
        return;
    }

    if (livros[livroIndex].quantidade < quantidade) {
        printf("Quantidade em falta!\n");
        return;
    }

    livros[livroIndex].quantidade -= quantidade;
    strcpy(vendas[vendaCount].nomeCliente, nomeCliente);
    strcpy(vendas[vendaCount].nomeLivro, nomeLivro);
    vendas[vendaCount].quantidade = quantidade;
    vendas[vendaCount].valorTotal = quantidade * livros[livroIndex].valor;
    vendaCount++;
    printf("Venda realizada com sucesso! Valor total: R$%.2f\n", vendas[vendaCount - 1].valorTotal);
}

void relatorioVendas() {
    printf("Relatório de Vendas:\n");
    for (int i = 0; i < vendaCount; i++) {
        printf("Cliente: %s | Livro: %s | Quantidade: %d | Valor Total: R$%.2f\n",
               vendas[i].nomeCliente, vendas[i].nomeLivro, vendas[i].quantidade, vendas[i].valorTotal);
    }
}

void relatorioEstoque() {
    printf("Relatório de Estoque:\n");
    for (int i = 0; i < livroCount; i++) {
        printf("Livro: %s | Quantidade: %d\n", livros[i].nome, livros[i].quantidade);
    }
}

void relatorioEstoqueValor() {
    printf("Relatório de Estoque com Valor:\n");
    for (int i = 0; i < livroCount; i++) {
        printf("Livro: %s | Quantidade: %d | Valor: R$%.2f\n",
               livros[i].nome, livros[i].quantidade, livros[i].valor);
    }
}

void relatorioClientes() {
    printf("Relatório de Clientes:\n");
    for (int i = 0; i < clienteCount; i++) {
        printf("Cliente: %s\n", clientes[i].nome);
    }
}

// Função principal
int main() {
    int opcao;

    printf("BIBLIOTECA MULTIVIX VILA VELHA\n");

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Cadastrar Pessoa\n");
        printf("3 - Alugar Livro\n");
        printf("4 - Vender Livro\n");
        printf("5 - Relatório de Vendas\n");
        printf("6 - Relatório de Estoque\n");
        printf("7 - Relatório de Estoque com Valor\n");
        printf("8 - Relatório de Clientes\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarLivro();
                break;
            case 2:
                cadastrarCliente();
                break;
            case 3:
                alugarLivro();
                break;
            case 4:
                venderLivro();
                break;
            case 5:
                relatorioVendas();
                break;
            case 6:
                relatorioEstoque();
                break;
            case 7:
                relatorioEstoqueValor();
                break;
            case 8:
                relatorioClientes();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
