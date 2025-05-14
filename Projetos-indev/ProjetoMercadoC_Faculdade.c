#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//contador de registros //codigo de sessao login
int user_cont = 1, limpeza_cont = 10, alimentos_cont = 10, padaria_cont = 10, cadastrados_cont = 10, login_code = 0;

// Estrutura 'produtos' representa um item à venda
// - codigo_produto: identificador numérico do produto
// - nome_produto: nome do produto (até 20 caracteres)
// - valor_produto: preço do produto
// - estoque_produto: quantidade disponível no estoque
typedef struct {
    int codigo_produto;
    char nome_produto[20];
    float valor_produto;
    float estoque_produto;
} produtos;

typedef struct {
    int id_usuario;
    char login[20];
    char senha[20];
    int nivel_acesso; // 1 - adm // 2 - gerente // 3 - cadastrados
} usuarios;

usuarios **cadastrados = NULL;
// Lista de produtos da categoria Limpeza
produtos **limpeza = NULL;
// Lista de produtos da categoria Alimentos
produtos **alimentos = NULL;
// Lista de produtos da categoria Padaria (estoque iniciado em 0)
produtos **padaria = NULL;

// Variáveis globais para controle do sistema:
// - opcao: controla seleções de menu
// - quantidade: define quantos itens o cliente deseja comprar
// - estoque_temp: armazena os itens temporariamente no carrinho
// - carrinhoX: total de cada categoria no carrinho
// - totalX: acumulador de vendas por categoria
// - total, total_desconto, falta: controle financeiro da compra atual
// - pagamento, troco, faturamento, valor_abertura: movimentação do caixa
// - status_caixa: indica se o caixa está disponível
int opcao = 0, quantidade = 0, estoque_temp[21] = {0};
float carrinho_limpeza = 0, carrinho_alimentos = 0, carrinho_padaria = 0, total_limpeza = 0, total_alimentos = 0, total_padaria = 0, total = 0, total_desconto = 0, falta = 0;
float guarda_desconto = 0, desconto_informado = 0, pagamento = 0, troco = 0, faturamento = 0, valor_abertura = 0;
bool status_caixa = false;

// ===== FUNÇÕES/PROTOTIPAGENS ===== //
void menu_principal(void);
void menu_limpeza(void);
void menu_alimento(void);
void menu_padaria(void);
void menu_pagamento(void);
void menu_falta(void);
void login_acesso(void);
void menu_cancelar(void);
void menu_caixa(void);
void acesso_adm(void);
void registrar_usuarios(void);
void listar_usuarios(void);

// Calcula e aplica desconto conforme o total:
// - Até R$50: 5% de desconto
// - Até R$200: 10% de desconto
// - Acima disso: desconto personalizado informado pelo usuário
float aplicar_desconto(float);

void login_acesso() {
    login_code = -1;
    // Cria vetor de ponteiros para usuarios, com 1 usuário inicial
    usuarios **cadastrados = malloc(sizeof(usuarios *) * cadastrados_cont);
    if (cadastrados == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    // Aloca e inicializa o primeiro usuário (admin)
    cadastrados[0] = malloc(sizeof(usuarios));
    if (cadastrados[0] == NULL) {
        printf("Erro de alocação de memória.\n");
        free(cadastrados);
        return;
    }

    cadastrados[0]->id_usuario = 0;
    strcpy(cadastrados[0]->login, "admin");
    strcpy(cadastrados[0]->senha, "admin");
    cadastrados[0]->nivel_acesso = 1;

    // Variáveis temporárias
    char login_temp[40];
    char senha_temp[40];

    do {
        system("cls");
        printf("Usuario:\n");
        fgets(login_temp, sizeof(login_temp), stdin);
        printf("Senha:\n");
        fgets(senha_temp, sizeof(senha_temp), stdin);

        // Remove o \n que o fgets coloca
        login_temp[strcspn(login_temp, "\n")] = '\0';
        senha_temp[strcspn(senha_temp, "\n")] = '\0';

        login_code = -1; // reinicia

        for (int i = 0; i < cadastrados_cont; i++) {
            if (strcmp(login_temp, cadastrados[i]->login) == 0 &&
                strcmp(senha_temp, cadastrados[i]->senha) == 0) {
                printf("Login realizado com sucesso!\n");
                login_code = i;
                system("pause");
                menu_principal();
                break;
                }
        }

        if (login_code == -1) {
            printf("Login e/ou senha invalidos! Tente novamente..\n");
            system("pause");
        }

    } while (login_code == -1);

    // Liberação da memória alocada
    for (int i = 0; i < cadastrados_cont; i++) {
        free(cadastrados[i]);
    }
    free(cadastrados);
}

void registrar_produtos() {
    do {
        system("cls");
        printf("Selecione a categoria\n");
        printf("1- Alimento");
        printf("2- Padaria");
        printf("3- Alimentos");
        printf("4- Voltar");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                alimentos_cont += 1;
                alimentos = realloc(alimentos, alimentos_cont * sizeof(produtos));
                if (alimentos == NULL) {
                    printf("Erro ao alocar produtos\n");
                }
                system("cls");
                alimentos[alimentos_cont]->codigo_produto = alimentos_cont;
                printf("Informe o nome do produto:\n");
                fgets(alimentos[alimentos_cont]->nome_produto, 20, stdin);
                alimentos[alimentos_cont]->nome_produto[strcspn(alimentos[alimentos_cont]->nome_produto, "\n")] = '\0';
                do {
                    printf("Informe o valor do produto:\n");
                    scanf("%f", &alimentos[alimentos_cont]->valor_produto);
                } while (alimentos[alimentos_cont]->valor_produto < 0);
                do {
                    printf("Informe o estoque do produto:\n");
                    scanf("%f", &alimentos[alimentos_cont]->estoque_produto);
                } while (alimentos[alimentos_cont]->estoque_produto < 0);
                getchar();alimentos_cont++; break;
            case 2:
                padaria_cont += 1;
                padaria = realloc(padaria, padaria_cont * sizeof(produtos));
                if (padaria == NULL) {
                    printf("Erro ao alocar produtos\n");
                }
                system("cls");
                padaria[padaria_cont]->codigo_produto = padaria_cont;
                printf("Informe o nome do produto:\n");
                fgets(padaria[padaria_cont]->nome_produto, 20, stdin);
                padaria[padaria_cont]->nome_produto[strcspn(padaria[padaria_cont]->nome_produto, "\n")] = '\0';
                do {
                    printf("Informe o valor do produto:\n");
                    scanf("%f", &padaria[padaria_cont]->valor_produto);
                }while (padaria[padaria_cont]->valor_produto < 0);
                do {
                    printf("Informe o estoque do produto:\n");
                    scanf("%f", &padaria[padaria_cont]->estoque_produto);
                }while (padaria[padaria_cont]->estoque_produto < 0);
                getchar();padaria_cont++; break;
            case 3:
                limpeza_cont += 1;
                limpeza = realloc(limpeza, limpeza_cont * sizeof(produtos));
                if (limpeza == NULL) {
                    printf("Erro ao alocar produtos\n");
                }
                system("cls");
                limpeza[limpeza_cont]->codigo_produto = limpeza_cont;
                printf("Informe o nome do produto:\n");
                fgets(limpeza[limpeza_cont]->nome_produto, 20, stdin);
                limpeza[limpeza_cont]->nome_produto[strcspn(limpeza[limpeza_cont]->nome_produto, "\n")] = '\0';
                do {
                    printf("Informe o valor do produto:\n");
                    scanf("%f", &limpeza[limpeza_cont]->valor_produto);
                }while (limpeza[limpeza_cont]->valor_produto < 0);
                do {
                    printf("Informe o estoque do produto:\n");
                    scanf("%f", &limpeza[limpeza_cont]->estoque_produto);
                }while (limpeza[limpeza_cont]->estoque_produto < 0);
                getchar();limpeza_cont++; break;
            case 4: return; break;
        }
    }while (opcao != 4);
    

}

void registrar_usuarios() { //está ok basta apenas alterar depois quando implementar ponteiros e alocação
    cadastrados_cont += 1;
    cadastrados = realloc(cadastrados, cadastrados_cont * sizeof(produtos));
    if (cadastrados == NULL) {
        printf("Erro ao alocar usuarios");
    }
    int permissao = 0;
    system("cls");
    printf("Informe o login:");
    fgets(cadastrados[user_cont]->login,sizeof(cadastrados[user_cont]->login), stdin);
    cadastrados[user_cont]->login[strcspn(cadastrados[user_cont]->login, "\n")] = '\0';
    printf("Informe a senha:");
    fgets(cadastrados[user_cont]->senha, sizeof(cadastrados[user_cont]->senha), stdin);
    cadastrados[user_cont]->senha[strcspn(cadastrados[user_cont]->senha, "\n")] = '\0';
    getchar();
    system("cls");
    while (permissao != 1 && permissao != 2 && permissao != 3) {
        printf("Permissão de acesso?\n");
        printf("1- ADMINISTRATIVO\n");
        printf("2- GERENTE\n");
        printf("3- COLABORADOR\n");
        scanf("%d",&permissao);
        if(permissao == 1) {
            cadastrados[user_cont]->nivel_acesso = 1;
        } else if (permissao == 2) {
            cadastrados[user_cont]->nivel_acesso = 2;
        } else if (permissao == 3) {
            cadastrados[user_cont]->nivel_acesso = 3;
        }
    }
    user_cont++;
}

void listar_usuarios() {
    printf("<Lista de usuarios>");
    printf("Codigo\tUsuario\tPermissao");
    for (int i = 0; i < user_cont; i++) {
        printf("%d\t%s", cadastrados[i]->id_usuario, cadastrados[i]->login);
    }
}

void listar_produtos() {
    do {
        printf("<Lista de produtos>");
        printf("1 - Limpeza\n"); // só dá pra criar após fazer aloc e ponteiros
        printf("2 - Alimentos\n"); // só dá pra criar após fazer aloc e ponteiros
        printf("3 - Padaria\n"); // só dá pra criar após fazer aloc e ponteiros
        printf("4 - Voltar\n");
        printf("Selecione a listagem que deseja\n");
        scanf("%d",&opcao);
        switch (opcao) {
            case 1: // limpeza
                system("cls");
                printf("Cod | \tNome\t|\tValor\t| Estoque \n");
                for (int i = 0; i < 7; i++) {
                    printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), limpeza[i]->nome_produto, limpeza[i]->valor_produto, limpeza[i]->estoque_produto);
                }
                system("pause");
                break;
            case 2: // alimentos
                system("cls");
                printf("Cod | \tNome\t|\tValor\t| Estoque \n");
                for (int i = 0; i < 7; i++) {
                    printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), alimentos[i]->nome_produto, alimentos[i]->valor_produto, alimentos[i]->estoque_produto);
                }
                system("pause");
                break;
            case 3: //padaria
                system("cls");
                printf("Cod | \tNome\t|\tValor\t| Estoque \n");
                for (int i = 0; i < 7; i++) {
                    printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), padaria[i]->nome_produto, padaria[i]->valor_produto, padaria[i]->estoque_produto);
                }
                system("pause");
                break;
            case 4: return; break;
            default: printf("Opcao invalida\n"); break;
        }
    } while (opcao != 4);
}

void acesso_adm() { // ainda com muitas coisas p alterar
    system("cls");
    if (cadastrados[login_code]->nivel_acesso != 1) {
        printf("Você não tem permissao para acessar esta area\n");
        return;
    }
    do {
        printf("1 - Listar usuarios\n");
        printf("2 - Registrar usuario\n");
        printf("3 - Listar produtos\n");
        printf("4 - Registrar produtos\n");
        printf("5 - Voltar\n");
        scanf("%d",&opcao);
        switch (opcao) {
            case 1:
                listar_usuarios();
                break;
            case 2:
                registrar_usuarios();
                break;
            case 3:
                listar_produtos();
                break;
            case 4:
                registrar_produtos();
                break;
            case 5:
                return;
            default:
                system("cls");
                printf("Valor invalido, tente novamente...\n");
        }
    } while (opcao != 5);

}

// Menu para gerenciamento do caixa:
// - Opção de abrir: solicita valor inicial e estoque para padaria
// - Opção de fechar: mostra totais e reseta variáveis
// - Evita abertura dupla ou fechamento sem estar aberto
void menu_caixa() {
    float acrescentaEstoque = 0;

    do {
        system("cls");
        printf("< Menu Caixa >\n");
        printf("1 - Abrir\n");
        printf("2 - Fechar\n");
        printf("3 - Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            if (status_caixa == true) {
                printf("\nO caixa já está aberto, feche para realizar uma nova abertura");
                system("pause");
                menu_caixa();
            }
            printf("\nInforme o valor de abertura\n");
            printf("Valor: ");
            scanf("%f", &valor_abertura);
            if(valor_abertura < 0){
                printf("Valor inserido invalido\n");
                system("pause");
                menu_caixa();
            }
            printf("\nInforme o estoque da padaria");
            for (int i = 0; i < 7; i++) {
                do {
                    printf("\nInforme a quantidade de %s em estoque: ", padaria[i]->nome_produto);
                    scanf("%f", &acrescentaEstoque);
                    if (acrescentaEstoque < 0)
                        printf("Informe um valor valido\n");
                } while (acrescentaEstoque < 0);
                padaria[i]->estoque_produto = acrescentaEstoque;
            }
            status_caixa = true;
            printf("O caixa foi aberto!\n");
            system("pause");
            menu_principal();
            break;
        case 2:
            if ( status_caixa == true) {
                printf("Total Limpeza: %.2f R$\n", total_limpeza);
                printf("Total Alimentos: %.2f R$\n", total_alimentos);
                printf("Total Padaria: %.2f R$\n", total_padaria);
                printf("Total Faturamento: %.2f R$\n", faturamento);
                printf("Valor de abertura: %.2f R$\n", valor_abertura);
                total_limpeza = total_alimentos = total_padaria = faturamento = valor_abertura= 0;
                status_caixa = false;
            }
            else if (status_caixa == false) {
                printf("O caixa está fechado\n");
                system("pause");
                menu_caixa();
            }
            printf("O caixa foi fechado!\n");
            system("pause");
            menu_principal();
            break;
        case 3:
            menu_principal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menu_caixa();
            break;
        }
    }while(opcao != 3);
}


// Cancela a venda atual e devolve itens do carrinho para o estoque original
void menu_cancelar() {
    system("cls");
    printf("Deseja realmente cancelar as vendas?\n");
    printf("1 - Confirmar\n");
    printf("2 - Voltar\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    int k = 0;
    int m = 0;
    switch (opcao) {
        case 1:
            carrinho_limpeza = carrinho_padaria = carrinho_alimentos = 0;
            // DEVOLVE PRODUTOS DA LIMPEZA AO ESTOQUE
            for (int i = 0; i < 7; i++)
                limpeza[i]->estoque_produto += estoque_temp[i];
            // DEVOLVE PRODUTOS DE ALIMENTOS AO ESTOQUE
            for (int j = 7; j < 14; j++) {
                alimentos[k]->estoque_produto += estoque_temp[j];
                k++;
            }
            // DEVOLVE PRODUTOS DA PADARIA AO ESTOQUE
            for (int l = 14; l < 21; l++) {
                padaria[m]->estoque_produto += estoque_temp[l];
                m++;
            }
            printf("\nVenda cancelada! Produtos devolvidos ao estoque\n");
            system("pause");
            menu_principal();
            break;
        case 2:
            menu_principal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menu_principal();
            break;
    }
}


// Calcula e aplica desconto conforme o total:
// - Até R$50: 5% de desconto
// - Até R$200: 10% de desconto
// - Acima disso: desconto personalizado informado pelo usuário
float aplicar_desconto(float x) {
    if (x <= 50) {
        guarda_desconto = x * 0.05;
    return total_desconto = x - guarda_desconto;
    }
    else if (x <= 200) {
        guarda_desconto = x * 0.10;
    return total_desconto = x - guarda_desconto;
    } else {
        printf("Informe o desconto a ser aplicado\n");
        scanf("%f", &desconto_informado);
        desconto_informado = desconto_informado / 100;
        guarda_desconto = x * desconto_informado;
        return total_desconto = x - guarda_desconto;
    }
}


// Menu para lidar com pagamentos pendentes (valores parciais):
// - Permite completar com dinheiro ou cartão
// - Atualiza valores pendentes e calcula troco se necessário
void menu_falta() {
    do {
        system("cls");
        printf("Menu Pagamento Pendente\n");
        printf("1 - Dinheiro\n");
        printf("2 - Cartao\n");
        printf("3 - Voltar\n");
        printf("Opcao:");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("\nFalta pagar: %.2f R$\n", falta);
                printf("Informe o valor pago: ");
                scanf("%f", &pagamento);
                if ( pagamento > 0 ) {
                    if ( pagamento >= falta) {
                        printf("\nPagamento realizado com sucesso!\n");
                        total_alimentos += carrinho_alimentos;
                        total_padaria += carrinho_padaria;
                        total_limpeza += carrinho_limpeza;
                        faturamento += falta;
                        troco = pagamento - falta;
                        carrinho_alimentos = carrinho_padaria = carrinho_limpeza = total = total_desconto = falta = 0;
                        if (troco != 0)
                            printf("Troco: %.2f R$\n", troco);
                        system("pause");
                        menu_principal();
                    }
                    else if (pagamento < falta && pagamento > 0) {
                        faturamento += pagamento;
                        falta = falta - pagamento;
                        printf("Ainda restou valores\n");
                        system("pause");
                        menu_falta();
                    }
                } else {
                    printf("Valor invalido, tente novamente...\n");
                    menu_falta();
                }
            case 2:
                printf("1 - Pagamento realizado\n");
                printf("2 - Pagamento nao realizado\n");
                printf("3 - Voltar");
                printf("Opcao: ");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Pagamento Realizado!\n");
                    total_alimentos += carrinho_alimentos;
                    total_padaria += carrinho_padaria;
                    total_limpeza += carrinho_limpeza;
                    faturamento += falta;
                    carrinho_alimentos = carrinho_padaria = carrinho_limpeza = total = total_desconto = falta = 0;
                }
                else if (opcao == 2) {
                    printf("Pagamento Nao Realizado\n");
                    system("pause");
                    menu_falta();
                }
                else if (opcao == 3) {
                    menu_falta();
                } else {
                    printf("Opcao invalida\n");
                    system("pause");
                    menu_falta();
                }
                break;

            case 3:
                menu_principal();
                break;
            default:
                printf("Opcao invalida\n");
                system("pause");
                menu_falta();
                break;

        }

    }while (opcao != 3);

}


// Realiza o pagamento da compra atual:
// - Aplica desconto se necessário
// - Calcula e mostra troco
// - Armazena totais em variáveis globais de faturamento
void menu_pagamento() {
    total = carrinho_alimentos + carrinho_padaria + carrinho_limpeza;
    do {
        system("cls");
        printf("<Menu Pagamento>\n");
        printf("1 - Dinheiro\n");
        printf("2 - Cartao\n");
        printf("3- Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            if (falta == 0) {
                if (total <= 50) {
                    printf("\nDesconto de 5%% aplicado\n");
                    total_desconto = aplicar_desconto(total);
                }
                else if (total <= 200) {
                    printf("\nDesconto de 10%% aplicado\n");
                    total_desconto = aplicar_desconto(total);
                } else {
                    total_desconto = aplicar_desconto(total);
                    printf("\nDesconto de %0.f%% aplicado\n", (desconto_informado * 100));
                }
                printf("Valor total: %.2f R$\n", total);
                printf("Valor com desconto: %.2f R$\n", total_desconto);
                printf("Informe o valor recebido:");
                scanf("%f", &pagamento);
            }else {
                menu_falta();
            }
                if (pagamento < 0) {
                    printf("Valor invalido, tente novamente...\n");
                    system("pause");
                    menu_pagamento();
                }

                if (pagamento >= total_desconto) {
                    printf("\nPagamento Realizado!\n");
                    total_alimentos += carrinho_alimentos;
                    total_padaria += carrinho_padaria;
                    total_limpeza += carrinho_limpeza;
                    faturamento += total_desconto;
                    troco = pagamento - total_desconto;
                    carrinho_alimentos = carrinho_padaria = carrinho_limpeza = total = total_desconto = 0;
                    if (troco != 0)
                        printf("Troco: %.2f R$\n", troco);
                    system("pause");
                    menu_principal();
                }
                else if (pagamento > 0 && pagamento < total_desconto) {
                    printf("\nO valor integral sera cobrado\n");
                    faturamento += pagamento;
                    falta = total - pagamento;
                    system("pause");
                    menu_falta();
                }
            break;

        case 2:
            printf("1 - Pagamento realizado\n");
            printf("2 - Pagamento nao realizado\n");
            printf("3 - Voltar");
            printf("Opcao: ");
            scanf("%d", &opcao);
            if (opcao == 1) {
                printf("Pagamento Realizado!\n");
                total_alimentos += carrinho_alimentos;
                total_padaria += carrinho_padaria;
                total_limpeza += carrinho_limpeza;
                faturamento += total;
                carrinho_alimentos = carrinho_padaria = carrinho_limpeza = total = total_desconto = 0;
            }
            else if (opcao == 2) {
                printf("Pagamento Nao Realizado\n");
                system("pause");
                menu_pagamento();
            }
            else if (opcao == 3) {
                menu_pagamento();
            } else {
                printf("Opcao invalida\n");
                system("pause");
                menu_pagamento();
            }
            break;

        case 3:
            menu_principal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menu_pagamento();
            break;

        }
    }while(opcao!=3);
}


// Menu específico da categoria Padaria:
// - Mostra lista de produtos e permite adicionar ao carrinho
// - Controla estoque e atualiza carrinho temporário
void menu_padaria() {
    do {
        system("cls");
        printf("<Menu Padaria>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < padaria_cont; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), padaria[i]->nome_produto, padaria[i]->valor_produto, padaria[i]->estoque_produto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Padaria: %.2f R$\n", carrinho_padaria);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", padaria[opcao]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[opcao]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[opcao]->estoque_produto -= quantidade;
                estoque_temp[14] += quantidade;
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                carrinho_padaria += padaria[opcao]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[opcao]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 2:
                printf("\n%s\n", padaria[1]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[1]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[1]->estoque_produto -= quantidade;
                estoque_temp[15] += quantidade;
                carrinho_padaria += padaria[1]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[1]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 3:
                printf("\n%s\n", padaria[2]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[2]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[2]->estoque_produto -= quantidade;
                estoque_temp[16] += quantidade;
                carrinho_padaria+= padaria[2]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[2]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 4:
                printf("\n%s\n", padaria[3]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[3]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[3]->estoque_produto -= quantidade;
                estoque_temp[17] += quantidade;
                carrinho_padaria+= padaria[3]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[3]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 5:
                printf("\n%s\n", padaria[4]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[4]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[4]->estoque_produto -= quantidade;
                estoque_temp[18] += quantidade;
                carrinho_padaria+= padaria[4]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[4]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 6:
                printf("\n%s\n", padaria[5]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[5]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[5]->estoque_produto -= quantidade;
                estoque_temp[19] += quantidade;
                carrinho_padaria+= padaria[5]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[5]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 7:
                printf("\n%s\n", padaria[6]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_padaria();
                }
                if (quantidade > padaria[6]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_padaria();
                }
                padaria[6]->estoque_produto -= quantidade;
                estoque_temp[20] += quantidade;
                carrinho_padaria+= padaria[6]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[6]->nome_produto);
                system("pause");
                menu_padaria();
                break;
            case 8:
                menu_principal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menu_principal();
                break;
        }
    }while(opcao != 8);
}


// Menu específico da categoria Alimentos:
// - Mesmo funcionamento da padaria, mas com produtos de alimentos
void menu_alimento() {
    do {
        system("cls");
        printf("<Menu Alimento>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < 7; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), alimentos[i]->nome_produto, alimentos[i]->valor_produto, alimentos[i]->estoque_produto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Alimentos: %.2f R$\n", carrinho_alimentos);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", alimentos[0]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[0]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[0]->estoque_produto -= quantidade;
                estoque_temp[7] += quantidade;
                carrinho_alimentos += alimentos[0]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[0]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 2:
                printf("\n%s\n", alimentos[1]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[1]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[1]->estoque_produto -= quantidade;
                estoque_temp[8] += quantidade;
                carrinho_alimentos += alimentos[1]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[1]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 3:
                printf("\n%s\n", alimentos[2]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[2]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[2]->estoque_produto -= quantidade;
                estoque_temp[9] += quantidade;
                carrinho_alimentos+= alimentos[2]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[2]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 4:
                printf("\n%s\n", alimentos[3]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[3]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[3]->estoque_produto -= quantidade;
                estoque_temp[10] += quantidade;
                carrinho_alimentos+= alimentos[3]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[3]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 5:
                printf("\n%s\n", alimentos[4]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[4]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[4]->estoque_produto -= quantidade;
                estoque_temp[11] += quantidade;
                carrinho_alimentos+= alimentos[4]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[4]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 6:
                printf("\n%s\n", alimentos[5]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[5]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[5]->estoque_produto -= quantidade;
                estoque_temp[12] += quantidade;
                carrinho_alimentos+= alimentos[5]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[5]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 7:
                printf("\n%s\n", alimentos[6]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_alimento();
                }
                if (quantidade > alimentos[6]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_alimento();
                }
                alimentos[6]->estoque_produto -= quantidade;
                estoque_temp[13] += quantidade;
                carrinho_alimentos+= alimentos[6]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[6]->nome_produto);
                system("pause");
                menu_alimento();
                break;
            case 8:
                menu_principal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menu_principal();
                break;
        }
    }while(opcao != 8);
}


// Menu específico da categoria Limpeza:
// - Mesmo funcionamento das outras categorias
void menu_limpeza() {

    do {
        system("cls");
        printf("<Menu Limpeza>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < 7; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), limpeza[i]->nome_produto, limpeza[i]->valor_produto, limpeza[i]->estoque_produto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Limpeza: %.2f R$\n", carrinho_limpeza);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", limpeza[0]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[0]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[0]->estoque_produto -= quantidade;
                estoque_temp[0] += quantidade;
                carrinho_limpeza += limpeza[0]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[0]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 2:
                printf("\n%s\n", limpeza[1]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[1]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[1]->estoque_produto -= quantidade;
                estoque_temp[1] += quantidade;
                carrinho_limpeza += limpeza[1]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[1]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 3:
                printf("\n%s\n", limpeza[2]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[2]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[2]->estoque_produto -= quantidade;
                estoque_temp[2] += quantidade;
                carrinho_limpeza+= limpeza[2]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[2]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 4:
                printf("\n%s\n", limpeza[3]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[3]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[3]->estoque_produto -= quantidade;
                estoque_temp[3] += quantidade;
                carrinho_limpeza+= limpeza[3]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[3]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 5:
                printf("\n%s\n", limpeza[4]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[4]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[4]->estoque_produto -= quantidade;
                estoque_temp[4] += quantidade;
                carrinho_limpeza+= limpeza[4]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[4]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 6:
                printf("\n%s\n", limpeza[5]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[5]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[5]->estoque_produto -= quantidade;
                estoque_temp[5] += quantidade;
                carrinho_limpeza+= limpeza[5]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[5]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 7:
                printf("\n%s\n", limpeza[6]->nome_produto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menu_limpeza();
                }
                if (quantidade > limpeza[6]->estoque_produto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menu_limpeza();
                }
                limpeza[6]->estoque_produto -= quantidade;
                estoque_temp[6] += quantidade;
                carrinho_limpeza+= limpeza[6]->valor_produto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[6]->nome_produto);
                system("pause");
                menu_limpeza();
                break;
            case 8:
                menu_principal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menu_principal();
                break;
        }
    }while(opcao != 8);
}


// Menu principal do sistema:
// - Direciona o usuário para as funcionalidades principais
// - Exige abertura do caixa para acessar categorias e pagamento
void menu_principal() {

    do{
        system("cls");
        printf("<Menu Principal>\n");
        printf("1 - Limpeza\n");
        printf("2 - Alimento\n");
        printf("3 - Padaria\n");
        printf("4 - Pagamento\n");
        printf("5 - Caixa\n");
        printf("6 - Cancelar\n");
        printf("7 - Acesso administrativo\n");
        printf("8 - Sair\n");
        printf("Carrinho total: %.2f R$\n",(carrinho_alimentos + carrinho_padaria + carrinho_limpeza));
        printf("Opcao: ");
        scanf("%d", &opcao);
        if (!status_caixa && opcao != 5 && opcao != 7) {
            printf("O caixa está fechado, realize a abertura!\n");
            system("pause");
            continue; // volta para o começo do loop
        } else {
            switch (opcao) {
                case 1:
                    menu_limpeza();
                    break;
                case 2:
                    menu_alimento();
                    break;
                case 3:
                    menu_padaria();
                    break;
                case 4:
                    menu_pagamento();
                    break;
                case 5:
                    menu_caixa();
                    break;
                case 6:
                    menu_cancelar();
                    break;
                case 7:
                    acesso_adm();
                    break;
                case 8:
                    return;
                default:
                    printf("Opcao invalida... tente novamente\n");
                    system("pause");
                    menu_principal();
                    break;

            }
        }
    }while(opcao != 8);
}


// Função principal do programa:
// - Define a cor do terminal
// - Inicia o menu principal
int main(){
    system("color 0a");
    login_acesso();
return 0;
}
