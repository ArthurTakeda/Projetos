#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// ================= ESTRUTURAS DE DADOS ================= //

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_VENDAS 100
#define MAX_PAGAMENTOS 100

typedef struct {
    int codigo;
    char nome_completo[50];
    char nome_social[50];
    char cpf[15];
    char rua_numero[50];
    char bairro[30];
    char celular_whats[20];
} Cliente;

typedef struct {
    int codigo;
    char descricao[50];
    char categoria[20]; // "Alimento", "Material de Limpeza", "Panificação"
    float preco_compra;
    float margem_lucro; // em percentual
    float preco_venda;
    int quantidade_estoque;
    int estoque_minimo;
} Produto;

typedef struct {
    int numero_venda;
    int codigo_item;
    char descricao_item[50];
    float preco_venda;
    int quantidade_itens;
    float valor_total_item;
    char pagamento; // 'A' (Aberto) ou 'P' (Pago)
} Venda;

typedef struct {
    int numero_venda;
    float valor_pago;
    char tipo; // 'D' (Dinheiro), 'C' (Cartão), 'DC' (Dinheiro e Cartão)
} Pagamento;

// ================= VARIÁVEIS GLOBAIS ================= //

Cliente clientes[MAX_CLIENTES];
int total_clientes = 0;

Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;

Venda vendas[MAX_VENDAS];
int total_vendas = 0;

Pagamento pagamentos[MAX_PAGAMENTOS];
int total_pagamentos = 0;

float valor_abertura_caixa = 0.0;
bool caixa_aberto = false;

// ================= PROTÓTIPOS DE FUNÇÕES ================= //

// Funções de Menu
void menu_principal();
void menu_cadastros();
void menu_vendas();
void menu_abertura_caixa();
void menu_fechamento_caixa();
void menu_relatorios();

// Funções de Cadastro
void cadastrar_cliente();
void cadastrar_produto();

// Funções de Venda
void nova_venda();
void retirada_caixa();
void pagamento_venda();

// Funções de Caixa
void abrir_caixa();
void fechar_caixa();

// Funções de Relatório
void listar_clientes();
void listar_produtos();
void listar_vendas();

// Funções Auxiliares
int buscar_produto(int codigo);
float calcular_preco_venda(float preco_compra, float margem_lucro);
void limpar_buffer();
void pausar_tela();
void finalizar_venda(int numero_venda);
float calcular_total_venda(int numero_venda);

// Funções de Arquivo
void salvar_dados();
void carregar_dados();

// ================= FUNÇÃO MAIN ================= //

int main() {
    carregar_dados();
    menu_principal();
    salvar_dados();
    return 0;
}

// ================= IMPLEMENTAÇÃO DAS FUNÇÕES ================= //

// Menu Principal
void menu_principal() {
    int opcao;
    do {
        system("cls");
        printf("=== Menu Principal ===\n");
        printf("1. Cadastros\n");
        printf("2. Vendas\n");
        printf("3. Abertura de Caixa\n");
        printf("4. Fechamento de Caixa\n");
        printf("5. Relatórios\n");
        printf("6. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: menu_cadastros(); break;
            case 2: menu_vendas(); break;
            case 3: menu_abertura_caixa(); break;
            case 4: menu_fechamento_caixa(); break;
            case 5: menu_relatorios(); break;
            case 6: break;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 6);
}

// Menu de Cadastros
void menu_cadastros() {
    int opcao;
    do {
        system("cls");
        printf("=== Cadastros ===\n");
        printf("1. Cadastro de Clientes\n");
        printf("2. Cadastro de Produtos\n");
        printf("3. Retornar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: cadastrar_cliente(); break;
            case 2: cadastrar_produto(); break;
            case 3: return;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 3);
}

// Menu de Vendas
void menu_vendas() {
    int opcao;
    do {
        system("cls");
        printf("=== Vendas ===\n");
        printf("1. Nova Venda\n");
        printf("2. Retirada de Caixa (Sangria)\n");
        printf("3. Pagamento\n");
        printf("4. Retornar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: nova_venda(); break;
            case 2: retirada_caixa(); break;
            case 3: pagamento_venda(); break;
            case 4: return;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 4);
}

// Menu de Abertura de Caixa
void menu_abertura_caixa() {
    int opcao;
    do {
        system("cls");
        printf("=== Abertura de Caixa ===\n");
        printf("1. Abrir o caixa\n");
        printf("2. Retornar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: abrir_caixa(); break;
            case 2: return;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 2);
}

// Menu de Fechamento de Caixa
void menu_fechamento_caixa() {
    int opcao;
    do {
        system("cls");
        printf("=== Fechamento de Caixa ===\n");
        printf("1. Fechar o caixa\n");
        printf("2. Retornar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: fechar_caixa(); break;
            case 2: return;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 2);
}

// Menu de Relatórios
void menu_relatorios() {
    int opcao;
    do {
        system("cls");
        printf("=== Relatórios ===\n");
        printf("1. Listagem dos Clientes\n");
        printf("2. Listagem dos Produtos\n");
        printf("3. Listagem das Vendas\n");
        printf("4. Retornar ao Menu Principal\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: listar_clientes(); break;
            case 2: listar_produtos(); break;
            case 3: listar_vendas(); break;
            case 4: return;
            default: printf("Opção inválida!\n"); pausar_tela();
        }
    } while (opcao != 4);
}

// Cadastro de Cliente
void cadastrar_cliente() {
    if (total_clientes < MAX_CLIENTES) {
        printf("=== Cadastro de Cliente ===\n");
        printf("Código: ");
        scanf("%d", &clientes[total_clientes].codigo);
        limpar_buffer();
        printf("Nome Completo: ");
        fgets(clientes[total_clientes].nome_completo, sizeof(clientes[total_clientes].nome_completo), stdin);
        clientes[total_clientes].nome_completo[strcspn(clientes[total_clientes].nome_completo, "\n")] = '\0';
        printf("Nome Social: ");
        fgets(clientes[total_clientes].nome_social, sizeof(clientes[total_clientes].nome_social), stdin);
        clientes[total_clientes].nome_social[strcspn(clientes[total_clientes].nome_social, "\n")] = '\0';
        printf("CPF: ");
        fgets(clientes[total_clientes].cpf, sizeof(clientes[total_clientes].cpf), stdin);
        clientes[total_clientes].cpf[strcspn(clientes[total_clientes].cpf, "\n")] = '\0';
        printf("Rua/Número: ");
        fgets(clientes[total_clientes].rua_numero, sizeof(clientes[total_clientes].rua_numero), stdin);
        clientes[total_clientes].rua_numero[strcspn(clientes[total_clientes].rua_numero, "\n")] = '\0';
        printf("Bairro: ");
        fgets(clientes[total_clientes].bairro, sizeof(clientes[total_clientes].bairro), stdin);
        clientes[total_clientes].bairro[strcspn(clientes[total_clientes].bairro, "\n")] = '\0';
        printf("Celular/Whats: ");
        fgets(clientes[total_clientes].celular_whats, sizeof(clientes[total_clientes].celular_whats), stdin);
        clientes[total_clientes].celular_whats[strcspn(clientes[total_clientes].celular_whats, "\n")] = '\0';

        total_clientes++;
        printf("Cliente cadastrado com sucesso!\n");
        pausar_tela();
    } else {
        printf("Limite máximo de clientes atingido!\n");
        pausar_tela();
    }
}

// Cadastro de Produto
void cadastrar_produto() {
    if (total_produtos < MAX_PRODUTOS) {
        printf("=== Cadastro de Produto ===\n");
        printf("Código: ");
        scanf("%d", &produtos[total_produtos].codigo);
        limpar_buffer();
        printf("Descrição: ");
        fgets(produtos[total_produtos].descricao, sizeof(produtos[total_produtos].descricao), stdin);
        produtos[total_produtos].descricao[strcspn(produtos[total_produtos].descricao, "\n")] = '\0';
        printf("Categoria (Alimento, Material de Limpeza, Panificação): ");
        fgets(produtos[total_produtos].categoria, sizeof(produtos[total_produtos].categoria), stdin);
        produtos[total_produtos].categoria[strcspn(produtos[total_produtos].categoria, "\n")] = '\0';
        printf("Preço de Compra: ");
        scanf("%f", &produtos[total_produtos].preco_compra);
        limpar_buffer();
        printf("Margem de Lucro (%%): ");
        scanf("%f", &produtos[total_produtos].margem_lucro);
        limpar_buffer();
        produtos[total_produtos].preco_venda = calcular_preco_venda(produtos[total_produtos].preco_compra, produtos[total_produtos].margem_lucro);
        printf("Quantidade em Estoque: ");
        scanf("%d", &produtos[total_produtos].quantidade_estoque);
        limpar_buffer();
        printf("Estoque Mínimo: ");
        scanf("%d", &produtos[total_produtos].estoque_minimo);
        limpar_buffer();

        total_produtos++;
        printf("Produto cadastrado com sucesso!\n");
        pausar_tela();
    } else {
        printf("Limite máximo de produtos atingido!\n");
        pausar_tela();
    }
}

// Nova Venda
void nova_venda() {
    int numero_venda = total_vendas + 1;
    int codigo_produto;
    int quantidade;
    char novo_item;
    float total_venda = 0.0;
    int item_atual = 0;

    if (!caixa_aberto) {
        printf("Caixa fechado! Abra o caixa antes de iniciar uma venda.\n");
        pausar_tela();
        return;
    }

    printf("=== Nova Venda ===\n");

    do {
        printf("\n--- Itens Disponíveis ---\n");
        printf("Código\tDescrição\tCategoria\tPreço Venda\tQtd Estoque\n");
        for (int i = 0; i < total_produtos; i++) {
            printf("%d\t%s\t%s\tR$ %.2f\t%d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].categoria, produtos[i].preco_venda, produtos[i].quantidade_estoque);
        }

        printf("Informe o código do produto a ser comprado: ");
        scanf("%d", &codigo_produto);

        int indice_produto = buscar_produto(codigo_produto);
        if (indice_produto == -1) {
            printf("Produto não encontrado!\n");
            pausar_tela();
            continue;
        }

        printf("Informe a quantidade: ");
        scanf("%d", &quantidade);
        limpar_buffer();

        if (quantidade <= 0) {
            printf("Quantidade inválida!\n");
            pausar_tela();
            continue;
        }

        if (quantidade > produtos[indice_produto].quantidade_estoque) {
            printf("Você deseja vender %d produtos. Há somente %d em estoque! Continuar (s/n)? ", quantidade, produtos[indice_produto].quantidade_estoque);
            char continuar;
            scanf(" %c", &continuar);
            if (tolower(continuar) != 's') {
                printf("Venda cancelada.\n");
                pausar_tela();
                return;
            }
        }

        if (produtos[indice_produto].quantidade_estoque == 0) {
            printf("Não é possível vender produtos com estoque ZERADO!\n");
            pausar_tela();
            continue;
        }

        // Adicionar item à venda
        vendas[total_vendas].numero_venda = numero_venda;
        vendas[total_vendas].codigo_item = produtos[indice_produto].codigo;
        strcpy(vendas[total_vendas].descricao_item, produtos[indice_produto].descricao);
        vendas[total_vendas].preco_venda = produtos[indice_produto].preco_venda;
        vendas[total_vendas].quantidade_itens = quantidade;
        vendas[total_vendas].valor_total_item = produtos[indice_produto].preco_venda * quantidade;
        vendas[total_vendas].pagamento = 'A'; // Aberto
        total_vendas++;

        total_venda += vendas[total_vendas - 1].valor_total_item;

        printf("Item adicionado à venda.\n");
        printf("Total da venda até o momento: R$ %.2f\n", total_venda);

        printf("Novo item no carrinho de compra (s/n)? ");
        scanf(" %c", &novo_item);
        limpar_buffer();

        if (tolower(novo_item) == 'n') {
            finalizar_venda(numero_venda);
            return;
        }

    } while (tolower(novo_item) == 's');
}

// Finaliza a venda, calcula o total e aplica descontos
void finalizar_venda(int numero_venda) {
    float total_venda = 0.0;
    float desconto = 0.0;

    total_venda = calcular_total_venda(numero_venda);

    printf("\n=== Resumo da Venda ===\n");
    printf("Código\tDescrição\tPreço Venda\tQtd\tTotal\n");
    for (int i = 0; i < total_vendas; i++) {
        if (vendas[i].numero_