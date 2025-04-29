#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//contador de registros //codigo de sessao login
//int userCont = 2, loginCode = 0;

// Estrutura 'produtos' representa um item à venda
// - codigoProduto: identificador numérico do produto
// - nomeProduto: nome do produto (até 20 caracteres)
// - valorProduto: preço do produto
// - estoqueProduto: quantidade disponível no estoque
struct produtos {
    int codigoProduto;
    char nomeProduto[20];
    float valorProduto;
    float estoqueProduto;
};

struct usuarios {
    int usuario;
    char login[20];
    char senha[20];
    bool administrador;
};

/*struct usuarios colaborador[userCont] = { // alterar para calloc e ponteiro
    {0, "teste", "teste", 0},
    {1, "admin", "admin", 1}
};*/


// Lista de produtos da categoria Limpeza
struct produtos limpeza[7] = {
    {1, "Produto 1", 7.90, 10},
    {2, "Produto 2", 7.80, 10},
    {3, "Produto 3", 7.75, 10},
    {4, "Produto 4", 7.70, 10},
    {5, "Produto 5", 7.70, 10},
    {6, "Produto 6", 7.70, 10},
    {7, "Produto 7", 7.70, 10}};


// Lista de produtos da categoria Alimentos
struct produtos alimentos[7] ={
    {1, "Produto 8", 7.90, 10},
    {2, "Produto 9", 7.80, 10},
    {3, "Produto 10", 7.75, 10},
    {4, "Produto 11", 7.70, 10},
    {5, "Produto 12", 7.70, 10},
    {6, "Produto 13", 7.70, 10},
    {7, "Produto 14", 7.70, 10}};



// Lista de produtos da categoria Padaria (estoque iniciado em 0)
struct produtos padaria[7] ={
    {1, "Produto 15", 7.90, 0},
    {2, "Produto 16", 7.80, 0},
    {3, "Produto 17", 7.75, 0},
    {4, "Produto 18", 7.70, 0},
    {5, "Produto 19", 7.70, 0},
    {6, "Produto 20", 7.70, 0},
    {7, "Produto 21", 7.70, 0}};


// Variáveis globais para controle do sistema:
// - opcao: controla seleções de menu
// - quantidade: define quantos itens o cliente deseja comprar
// - estoqueTemp: armazena os itens temporariamente no carrinho
// - carrinhoX: total de cada categoria no carrinho
// - totalX: acumulador de vendas por categoria
// - total, totalDesconto, falta: controle financeiro da compra atual
// - pagamento, troco, faturamento, valorAbertura: movimentação do caixa
// - caixaAberto: indica se o caixa está disponível
int opcao = 0, quantidade = 0, estoqueTemp[21] = {0};
float carrinhoLimpeza = 0, carrinhoAlimentos = 0, carrinhoPadaria = 0, totalLimpeza = 0, totalAlimentos = 0, totalPadaria = 0, total = 0, totalDesconto = 0, falta = 0;
float guardaDesconto = 0, descontoInformado = 0, pagamento = 0, troco = 0, faturamento = 0, valorAbertura = 0;
bool caixaAberto = false;

// ===== FUNÇÕES/PROTOTIPAGENS ===== //
void menuPrincipal(void);
void menuLimpeza(void);
void menuAlimento(void);
void menuPadaria(void);
void menuPagamento(void);
void menuFalta(void);

// Calcula e aplica desconto conforme o total:
// - Até R$50: 5% de desconto
// - Até R$200: 10% de desconto
// - Acima disso: desconto personalizado informado pelo usuário
float aplicarDesconto(float);
void menuCancelar(void);
void menuCaixa(void);
/*void acessoAdministrativo(void);
void registrarUsuarios(void);
void listarUsuarios(void);


void registrarUsuarios() { //está ok basta apenas alterar depois quando implementar ponteiros e alocação
    int permissao = 0;
    system("clear");
    printf("Informe o login:");
    fgets(colaborador[userCont].login,sizeof(colaborador[userCont].login), stdin);
    colaborador[userCont].login[strcspn(colaborador[userCont].login, "\n")] = '\0';
    printf("Informe a senha:");
    fgets(colaborador[userCont].senha, sizeof(colaborador[userCont].senha), stdin);
    colaborador[userCont].senha[strcspn(colaborador[userCont].senha, "\n")] = '\0';
    getchar();
    system("clear");
    while (permissao != 1 && permissao != 2) {
        printf("Permissão de administrador?\n");
        printf("1- SIM\n");
        printf("2- NAO\n");
        scanf("%d",&permissao);
        if(permissao == 1) {
            colaborador[userCont].administrador = 1;
        } else {
            colaborador[userCont].administrador = 0;
        }
    }
    userCont++;
}

void listarUsuarios() {
    printf("<Lista de usuarios>");
    printf("Codigo\tUsuario\tPermissao");
    for (int i = 0; i < userCont; i++) {
        printf("%d\t%s", colaborador[i].usuario, colaborador[i].login);
        if (colaborador[i].administrador == 1) {
            printf("\tAdministrador\n");
        } else if (colaborador[i].administrador == 0) {
            printf("\tColaborador\n");
        }
    }
    printf("1 - Editar usuario\n"); // só dá pra criar após fazer aloc e ponteiros
    printf("2 - Remover usuario\n"); // só dá pra criar após fazer aloc e ponteiros
    printf("3 - Voltar\n");
    scanf("%d",&opcao);
    switch (opcao) {
        case 1:
        case 2:
        case 3:
        default:
    }
}

void acessoAdministrativo() { // ainda com muitas coisas p alterar
    system("clear");
    if (colaborador[loginCode].administrador == 0) {
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
                listarUsuarios();
                break;
            case 2:
                registrarUsuarios();
                break;
            case 3:
                listarProdutos();
                break;
            case 4:
                registrarProdutos();
                break;
            case 5:
                return;
            default:
                system("clear");
                printf("Valor invalido, tente novamente...\n");
        }
    } while (opcao != 5);

}*/

// Menu para gerenciamento do caixa:
// - Opção de abrir: solicita valor inicial e estoque para padaria
// - Opção de fechar: mostra totais e reseta variáveis
// - Evita abertura dupla ou fechamento sem estar aberto
void menuCaixa() {
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
            if (caixaAberto == true) {
                printf("\nO caixa já está aberto, feche para realizar uma nova abertura");
                system("pause");
                menuCaixa();
            }
            printf("\nInforme o valor de abertura\n");
            printf("Valor: ");
            scanf("%f", &valorAbertura);
            if(valorAbertura < 0){
                printf("Valor inserido invalido\n");
                system("pause");
                menuCaixa();
            }
            printf("\nInforme o estoque da padaria");
            for (int i = 0; i < 7; i++) {
                do {
                    printf("\nInforme a quantidade de %s em estoque: ", padaria[i].nomeProduto);
                    scanf("%f", &acrescentaEstoque);
                    if (acrescentaEstoque < 0)
                        printf("Informe um valor valido\n");
                } while (acrescentaEstoque < 0);
                padaria[i].estoqueProduto = acrescentaEstoque;
            }
            caixaAberto = true;
            printf("O caixa foi aberto!\n");
            system("pause");
            menuPrincipal();
            break;
        case 2:
            if ( caixaAberto == true) {
                printf("Total Limpeza: %.2f R$\n", totalLimpeza);
                printf("Total Alimentos: %.2f R$\n", totalAlimentos);
                printf("Total Padaria: %.2f R$\n", totalPadaria);
                printf("Total Faturamento: %.2f R$\n", faturamento);
                printf("Valor de abertura: %.2f R$\n", valorAbertura);
                totalLimpeza = totalAlimentos = totalPadaria = faturamento = valorAbertura= 0;
                caixaAberto = false;
            }
            else if (caixaAberto == false) {
                printf("O caixa está fechado\n");
                system("pause");
                menuCaixa();
            }
            printf("O caixa foi fechado!\n");
            system("pause");
            menuPrincipal();
            break;
        case 3:
            menuPrincipal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menuCaixa();
            break;
        }
    }while(opcao != 3);
}


// Cancela a venda atual e devolve itens do carrinho para o estoque original
void menuCancelar() {
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
            carrinhoLimpeza = carrinhoPadaria = carrinhoAlimentos = 0;
            // DEVOLVE PRODUTOS DA LIMPEZA AO ESTOQUE
            for (int i = 0; i < 7; i++)
                limpeza[i].estoqueProduto += estoqueTemp[i];
            // DEVOLVE PRODUTOS DE ALIMENTOS AO ESTOQUE
            for (int j = 7; j < 14; j++) {
                alimentos[k].estoqueProduto += estoqueTemp[j];
                k++;
            }
            // DEVOLVE PRODUTOS DA PADARIA AO ESTOQUE
            for (int l = 14; l < 21; l++) {
                padaria[m].estoqueProduto += estoqueTemp[l];
                m++;
            }
            printf("\nVenda cancelada! Produtos devolvidos ao estoque\n");
            system("pause");
            menuPrincipal();
            break;
        case 2:
            menuPrincipal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menuPrincipal();
            break;
    }
}


// Calcula e aplica desconto conforme o total:
// - Até R$50: 5% de desconto
// - Até R$200: 10% de desconto
// - Acima disso: desconto personalizado informado pelo usuário
float aplicarDesconto(float x) {
    if (x <= 50) {
        guardaDesconto = x * 0.05;
    return totalDesconto = x - guardaDesconto;
    }
    else if (x <= 200) {
        guardaDesconto = x * 0.10;
    return totalDesconto = x - guardaDesconto;
    } else {
        printf("Informe o desconto a ser aplicado\n");
        scanf("%f", &descontoInformado);
        descontoInformado = descontoInformado / 100;
        guardaDesconto = x * descontoInformado;
        return totalDesconto = x - guardaDesconto;
    }
}


// Menu para lidar com pagamentos pendentes (valores parciais):
// - Permite completar com dinheiro ou cartão
// - Atualiza valores pendentes e calcula troco se necessário
void menuFalta() {
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
                        totalAlimentos += carrinhoAlimentos;
                        totalPadaria += carrinhoPadaria;
                        totalLimpeza += carrinhoLimpeza;
                        faturamento += falta;
                        troco = pagamento - falta;
                        carrinhoAlimentos = carrinhoPadaria = carrinhoLimpeza = total = totalDesconto = falta = 0;
                        if (troco != 0)
                            printf("Troco: %.2f R$\n", troco);
                        system("pause");
                        menuPrincipal();
                    }
                    else if (pagamento < falta && pagamento > 0) {
                        faturamento += pagamento;
                        falta = falta - pagamento;
                        printf("Ainda restou valores\n");
                        system("pause");
                        menuFalta();
                    }
                } else {
                    printf("Valor invalido, tente novamente...\n");
                    menuFalta();
                }
            case 2:
                printf("1 - Pagamento realizado\n");
                printf("2 - Pagamento nao realizado\n");
                printf("3 - Voltar");
                printf("Opcao: ");
                scanf("%d", &opcao);
                if (opcao == 1) {
                    printf("Pagamento Realizado!\n");
                    totalAlimentos += carrinhoAlimentos;
                    totalPadaria += carrinhoPadaria;
                    totalLimpeza += carrinhoLimpeza;
                    faturamento += falta;
                    carrinhoAlimentos = carrinhoPadaria = carrinhoLimpeza = total = totalDesconto = falta = 0;
                }
                else if (opcao == 2) {
                    printf("Pagamento Nao Realizado\n");
                    system("pause");
                    menuFalta();
                }
                else if (opcao == 3) {
                    menuFalta();
                } else {
                    printf("Opcao invalida\n");
                    system("pause");
                    menuFalta();
                }
                break;

            case 3:
                menuPrincipal();
                break;
            default:
                printf("Opcao invalida\n");
                system("pause");
                menuFalta();
                break;

        }

    }while (opcao != 3);

}


// Realiza o pagamento da compra atual:
// - Aplica desconto se necessário
// - Calcula e mostra troco
// - Armazena totais em variáveis globais de faturamento
void menuPagamento() {
    total = carrinhoAlimentos + carrinhoPadaria + carrinhoLimpeza;
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
                    totalDesconto = aplicarDesconto(total);
                }
                else if (total <= 200) {
                    printf("\nDesconto de 10%% aplicado\n");
                    totalDesconto = aplicarDesconto(total);
                } else {
                    totalDesconto = aplicarDesconto(total);
                    printf("\nDesconto de %0.f%% aplicado\n", (descontoInformado * 100));
                }
                printf("Valor total: %.2f R$\n", total);
                printf("Valor com desconto: %.2f R$\n", totalDesconto);
                printf("Informe o valor recebido:");
                scanf("%f", &pagamento);
            }else {
                menuFalta();
            }
                if (pagamento < 0) {
                    printf("Valor invalido, tente novamente...\n");
                    system("pause");
                    menuPagamento();
                }

                if (pagamento >= totalDesconto) {
                    printf("\nPagamento Realizado!\n");
                    totalAlimentos += carrinhoAlimentos;
                    totalPadaria += carrinhoPadaria;
                    totalLimpeza += carrinhoLimpeza;
                    faturamento += totalDesconto;
                    troco = pagamento - totalDesconto;
                    carrinhoAlimentos = carrinhoPadaria = carrinhoLimpeza = total = totalDesconto = 0;
                    if (troco != 0)
                        printf("Troco: %.2f R$\n", troco);
                    system("pause");
                    menuPrincipal();
                }
                else if (pagamento > 0 && pagamento < totalDesconto) {
                    printf("\nO valor integral sera cobrado\n");
                    faturamento += pagamento;
                    falta = total - pagamento;
                    system("pause");
                    menuFalta();
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
                totalAlimentos += carrinhoAlimentos;
                totalPadaria += carrinhoPadaria;
                totalLimpeza += carrinhoLimpeza;
                faturamento += total;
                carrinhoAlimentos = carrinhoPadaria = carrinhoLimpeza = total = totalDesconto = 0;
            }
            else if (opcao == 2) {
                printf("Pagamento Nao Realizado\n");
                system("pause");
                menuPagamento();
            }
            else if (opcao == 3) {
                menuPagamento();
            } else {
                printf("Opcao invalida\n");
                system("pause");
                menuPagamento();
            }
            break;

        case 3:
            menuPrincipal();
            break;
        default:
            printf("Opcao invalida\n");
            system("pause");
            menuPagamento();
            break;

        }
    }while(opcao!=3);
}


// Menu específico da categoria Padaria:
// - Mostra lista de produtos e permite adicionar ao carrinho
// - Controla estoque e atualiza carrinho temporário
void menuPadaria() {
    do {
        system("cls");
        printf("<Menu Padaria>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < 7; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), padaria[i].nomeProduto, padaria[i].valorProduto, padaria[i].estoqueProduto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Padaria: %.2f R$\n", carrinhoPadaria);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", padaria[0].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[0].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[0].estoqueProduto -= quantidade;
                estoqueTemp[14] += quantidade;
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                carrinhoPadaria += padaria[0].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[0].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 2:
                printf("\n%s\n", padaria[1].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[1].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[1].estoqueProduto -= quantidade;
                estoqueTemp[15] += quantidade;
                carrinhoPadaria += padaria[1].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[1].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 3:
                printf("\n%s\n", padaria[2].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[2].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[2].estoqueProduto -= quantidade;
                estoqueTemp[16] += quantidade;
                carrinhoPadaria+= padaria[2].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[2].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 4:
                printf("\n%s\n", padaria[3].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[3].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[3].estoqueProduto -= quantidade;
                estoqueTemp[17] += quantidade;
                carrinhoPadaria+= padaria[3].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[3].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 5:
                printf("\n%s\n", padaria[4].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[4].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[4].estoqueProduto -= quantidade;
                estoqueTemp[18] += quantidade;
                carrinhoPadaria+= padaria[4].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[4].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 6:
                printf("\n%s\n", padaria[5].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[5].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[5].estoqueProduto -= quantidade;
                estoqueTemp[19] += quantidade;
                carrinhoPadaria+= padaria[5].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[5].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 7:
                printf("\n%s\n", padaria[6].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuPadaria();
                }
                if (quantidade > padaria[6].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuPadaria();
                }
                padaria[6].estoqueProduto -= quantidade;
                estoqueTemp[20] += quantidade;
                carrinhoPadaria+= padaria[6].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, padaria[6].nomeProduto);
                system("pause");
                menuPadaria();
                break;
            case 8:
                menuPrincipal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menuPrincipal();
                break;
        }
    }while(opcao != 8);
}


// Menu específico da categoria Alimentos:
// - Mesmo funcionamento da padaria, mas com produtos de alimentos
void menuAlimento() {
    do {
        system("cls");
        printf("<Menu Alimento>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < 7; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), alimentos[i].nomeProduto, alimentos[i].valorProduto, alimentos[i].estoqueProduto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Alimentos: %.2f R$\n", carrinhoAlimentos);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", alimentos[0].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[0].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[0].estoqueProduto -= quantidade;
                estoqueTemp[7] += quantidade;
                carrinhoAlimentos += alimentos[0].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[0].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 2:
                printf("\n%s\n", alimentos[1].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[1].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[1].estoqueProduto -= quantidade;
                estoqueTemp[8] += quantidade;
                carrinhoAlimentos += alimentos[1].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[1].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 3:
                printf("\n%s\n", alimentos[2].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[2].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[2].estoqueProduto -= quantidade;
                estoqueTemp[9] += quantidade;
                carrinhoAlimentos+= alimentos[2].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[2].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 4:
                printf("\n%s\n", alimentos[3].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[3].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[3].estoqueProduto -= quantidade;
                estoqueTemp[10] += quantidade;
                carrinhoAlimentos+= alimentos[3].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[3].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 5:
                printf("\n%s\n", alimentos[4].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[4].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[4].estoqueProduto -= quantidade;
                estoqueTemp[11] += quantidade;
                carrinhoAlimentos+= alimentos[4].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[4].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 6:
                printf("\n%s\n", alimentos[5].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[5].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[5].estoqueProduto -= quantidade;
                estoqueTemp[12] += quantidade;
                carrinhoAlimentos+= alimentos[5].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[5].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 7:
                printf("\n%s\n", alimentos[6].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuAlimento();
                }
                if (quantidade > alimentos[6].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuAlimento();
                }
                alimentos[6].estoqueProduto -= quantidade;
                estoqueTemp[13] += quantidade;
                carrinhoAlimentos+= alimentos[6].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, alimentos[6].nomeProduto);
                system("pause");
                menuAlimento();
                break;
            case 8:
                menuPrincipal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menuPrincipal();
                break;
        }
    }while(opcao != 8);
}


// Menu específico da categoria Limpeza:
// - Mesmo funcionamento das outras categorias
void menuLimpeza() {

    do {
        system("cls");
        printf("<Menu Limpeza>\n");
        printf("Cod | \tNome\t|\tValor\t| Estoque \n");
        for (int i = 0; i < 7; i++) {
            printf("%d - \t%s \t%.2f \t    (%.0f)\n", (i + 1), limpeza[i].nomeProduto, limpeza[i].valorProduto, limpeza[i].estoqueProduto);
        }
        printf("8 - Voltar\n");
        printf("Carrinho Limpeza: %.2f R$\n", carrinhoLimpeza);
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\n%s\n", limpeza[0].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[0].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[0].estoqueProduto -= quantidade;
                estoqueTemp[0] += quantidade;
                carrinhoLimpeza += limpeza[0].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[0].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 2:
                printf("\n%s\n", limpeza[1].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[1].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[1].estoqueProduto -= quantidade;
                estoqueTemp[1] += quantidade;
                carrinhoLimpeza += limpeza[1].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[1].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 3:
                printf("\n%s\n", limpeza[2].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[2].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[2].estoqueProduto -= quantidade;
                estoqueTemp[2] += quantidade;
                carrinhoLimpeza+= limpeza[2].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[2].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 4:
                printf("\n%s\n", limpeza[3].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[3].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[3].estoqueProduto -= quantidade;
                estoqueTemp[3] += quantidade;
                carrinhoLimpeza+= limpeza[3].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[3].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 5:
                printf("\n%s\n", limpeza[4].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[4].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[4].estoqueProduto -= quantidade;
                estoqueTemp[4] += quantidade;
                carrinhoLimpeza+= limpeza[4].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[4].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 6:
                printf("\n%s\n", limpeza[5].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[5].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[5].estoqueProduto -= quantidade;
                estoqueTemp[5] += quantidade;
                carrinhoLimpeza+= limpeza[5].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[5].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 7:
                printf("\n%s\n", limpeza[6].nomeProduto);
                printf("Informe a quantidade: ");
                scanf("%d", &quantidade);
                if (quantidade < 0) {
                    printf("Quantidade invalida... tente novamente");
                    system("pause");
                    menuLimpeza();
                }
                if (quantidade > limpeza[6].estoqueProduto) {
                    printf("\nEstoque insuficiente, tente novamente\n");
                    system("pause");
                    menuLimpeza();
                }
                limpeza[6].estoqueProduto -= quantidade;
                estoqueTemp[6] += quantidade;
                carrinhoLimpeza+= limpeza[6].valorProduto * quantidade;
                printf("Adicionado %d x %s ao carrinho\n", quantidade, limpeza[6].nomeProduto);
                system("pause");
                menuLimpeza();
                break;
            case 8:
                menuPrincipal();
                break;
            default:
                printf("Opcao invalida... tente novamente\n");
                system("pause");
                menuPrincipal();
                break;
        }
    }while(opcao != 8);
}


// Menu principal do sistema:
// - Direciona o usuário para as funcionalidades principais
// - Exige abertura do caixa para acessar categorias e pagamento
void menuPrincipal() {

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
        printf("Carrinho total: %.2f R$\n",(carrinhoAlimentos + carrinhoPadaria + carrinhoLimpeza));
        printf("Opcao: ");
        scanf("%d", &opcao);
        if (!caixaAberto && opcao != 5 && opcao != 7) {
            printf("O caixa está fechado, realize a abertura!\n");
            system("pause");
            continue; // volta para o começo do loop
        } else {
            switch (opcao) {
                case 1:
                    menuLimpeza();
                    break;
                case 2:
                    menuAlimento();
                    break;
                case 3:
                    menuPadaria();
                    break;
                case 4:
                    menuPagamento();
                    break;
                case 5:
                    menuCaixa();
                    break;
                case 6:
                    menuCancelar();
                    break;
                case 7:
                    //acessoAdministrativo();
                    break;
                case 8:
                    return;
                default:
                    printf("Opcao invalida... tente novamente\n");
                    system("pause");
                    menuPrincipal();
                    break;

            }
        }
    }while(opcao != 7);
}


// Função principal do programa:
// - Define a cor do terminal
// - Inicia o menu principal
int main(){
    system("color 0a");
    menuPrincipal();
return 0;
}
