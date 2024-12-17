#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dlfcn.h>
#include "types.h"

// Declaração das funções da biblioteca libpsc.so
extern Products *products_get();
extern Users *users_get();
extern bool cart_put(Cart *cart);
extern void free_products(Products *products);
extern void free_users(Users *users);

void listar_utilizadores(Users *users) {
    printf("\nUtilizadores:\n");
    for (size_t i = 0; i < users->count; i++) {
        printf("ID: %d, Nome: %s\n", users->items[i].id, users->items[i].name);
    }
}

int comparar_preco_asc(const void *a, const void *b) {
    double diff = ((Product *)a)->price - ((Product *)b)->price;
    return (diff > 0) - (diff < 0);
}

int comparar_preco_desc(const void *a, const void *b) {
    double diff = ((Product *)b)->price - ((Product *)a)->price;
    return (diff > 0) - (diff < 0);
}

void listar_produtos(Products *products, const char *categoria, const char *criterio) {
    Product *produtos_filtrados = malloc(products->count * sizeof(Product));
    size_t count = 0;

    for (size_t i = 0; i < products->count; i++) {
        if (strcmp(products->items[i].category, categoria) == 0 || strcmp(categoria, "todos") == 0) {
            produtos_filtrados[count++] = products->items[i];
        }
    }

    if (count == 0) {
        // Se a categoria não for encontrada, listar todos os produtos
        for (size_t i = 0; i < products->count; i++) {
            produtos_filtrados[i] = products->items[i];
        }
        count = products->count;
    }
    char *msg;
    if (strcmp(criterio, "<") == 0) {
        qsort(produtos_filtrados, count, sizeof(Product), comparar_preco_asc);
        msg = "preço crescente";
    } else if (strcmp(criterio, ">") == 0) {
        qsort(produtos_filtrados, count, sizeof(Product), comparar_preco_desc);
        msg = "preço decrescente";
    }

    printf("\nProdutos na categoria '%s' (%s):\n", categoria, msg);
    for (size_t i = 0; i < count; i++) {
        printf("ID: %d, Nome: %s, Preço: %.2f, Categoria: %s, Desconto: %.2f, Stock: %ld\n ",
               produtos_filtrados[i].id, produtos_filtrados[i].title,
               produtos_filtrados[i].price, produtos_filtrados[i].category,
               produtos_filtrados[i].discountPercentage, produtos_filtrados[i].stock);
    }

    free(produtos_filtrados);
}

int main() {
    Users *users = users_get();
    if (!users) {
        fprintf(stderr, "Erro ao obter utilizadores.\n");
        return 1;
    }

    Products *products = products_get();
    if (!products) {
        fprintf(stderr, "Erro ao obter produtos.\n");
        free_users(users);
        return 1;
    }

    char command[256];
    char categoria[100], criterio[2];
    int user_id = 0, produto_id = 0, quantidade = 0;

    printf("\n\n");
    printf(" ooooooooo.   .oooooo..o   .oooooo.         .oooooo..o     .      \n"); 
    printf("`888   `Y88. d8P'    `Y8  d8P'  `Y8b       d8P'    `Y8   .o8   \n");
    printf(" 888   .d88' Y88bo.      888               Y88bo.      .o888oo  .ooooo.   ooo d8b  .ooooo. \n");
    printf(" 888ooo88P'   `'Y8888o.  888                `'Y8888o.    888   d88' `88b `888''8P d88' `88b \n");
    printf(" 888              `'Y88b 888                    `'Y88b   888   888   888  888     888ooo888 \n");
    printf(" 888         oo     .d8P `88b    ooo       oo     .d8P   888 . 888   888  888     888    .o \n");
    printf("o888o        8''88888P'   `Y8bood8P'       8''88888P'   '888'  `Y8bod8P' d888b    `Y8bod8P'\n");
    printf("\n");

    while (1) {
        printf("\n------------------------------------------------------------------------------------------\n");
        printf("\nComandos:");
        printf("\nUtilizadores \t\t\t - listar utilizadores");
        printf("\nuTilizador <id> \t\t - usar utilizador com o id escolhido");
        printf("\nProdutos <categoria> <criterio>  - listar produtos, < (preço crescente), > (preço decrescente)");
        if (user_id != 0) {
            printf("\nCarrinho \t\t\t - listar produtos que estão no carrinho");
            printf("\nfiltrar_Categorias_Carrinho \t - listar categorias de produtos que estão no carrinho");
            printf("\ncOmprar <produto> <quantidade> \t - adicionar produto ao carrinho");
            printf("\nFinalizar \t\t\t - finalizar compra");
        }
        printf("\nTerminar \t\t\t - terminar programa\n");
        printf("\nDigite o caracter inicial do comando: ");

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove o newline no final da string

        // Terminar -------------------------------------------------------------------------------------------
        if (strcmp(command, "T") == 0) {
            break;
        }
        // Utilizadores ----------------------------------------------------------------------------------------
        else if (strcmp(command, "U") == 0) {
            listar_utilizadores(users);
        }
        // UTilizador ------------------------------------------------------------------------------------------
        else if (sscanf(command, "u %d", &user_id) == 1) {
            if (user_id > 0 && user_id <= users->count) {
                printf("\nBem vindo %s\n", users->items[user_id - 1].name);
                // O carrinho do utilizador não é reinicializado aqui para manter persistência
            } else {
                printf("\nUtilizador com ID %d não encontrado.\n", user_id);
            }
        }
        // Produtos --------------------------------------------------------------------------------------------
        else if (sscanf(command, "P %s %s", categoria, criterio) == 2) {
            listar_produtos(products, categoria, criterio);
        }
        // Carrinho --------------------------------------------------------------------------------------------
        else if (strcmp(command, "C") == 0) {
            if (user_id != 0) {
                printf("\nCarrinho de compras:\n");
                double total_a_pagar = 0.0;
                for (size_t i = 0; i < users->items[user_id - 1].cart.n_products; i++) {
                    int produto_id = users->items[user_id - 1].cart.products[i].id;
                    int quantidade = users->items[user_id - 1].cart.products[i].quantity;
                    double preco = 0.0;
                    double desconto = 0.0;

                    // Encontrar o preço e o desconto do produto no array de produtos
                    for (size_t j = 0; j < products->count; j++) {
                        if (products->items[j].id == produto_id) {
                            preco = products->items[j].price;
                            desconto = products->items[j].discountPercentage;
                            break;
                        }
                    }

                    double preco_total_sem_desconto = preco * quantidade;
                    double valor_desconto = preco_total_sem_desconto * (desconto / 100);
                    double preco_total_com_desconto = preco_total_sem_desconto - valor_desconto;

                    printf("Produto ID: %d, Preço: %.2f$, Quantidade: %d, Desconto: %.2f%%, Preço total: %.2f$\n", 
                           produto_id, preco, quantidade, desconto, preco_total_com_desconto);

                    total_a_pagar += preco_total_com_desconto;
                }
                printf("\nTotal a pagar: %.2f$\n", total_a_pagar);
            } else {
                printf("\nPor favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        // filtrar_Categorias_Carrinho -----------------------------------------------------------------------------
        else if (strcmp(command, "f") == 0) {
            if (user_id != 0) {
                void *handler = dlopen("./plugins/libcatcard.so", RTLD_NOW);
                if (!handler) {
                    fprintf(stderr, "\nErro ao carregar plugin/ ou função ainda em desenvolvimento\n");
                } else {
                    void (*categcard)() = (void (*)())dlsym(handler, "categcard"); 
                    const char *dlsym_error = dlerror(); 
                    if (dlsym_error) { 
                        fprintf(stderr, "\nErro ao localizar símbolo: %s\n", dlsym_error); 
                    } else {
                        (*categcard)();
                    }
                    dlclose(handler);
                }
            } else {
                printf("\nPor favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        // cOmprar --------------------------------------------------------------------------------------------------
        else if (sscanf(command, "c %d %d", &produto_id, &quantidade) == 2) { 
            if (user_id != 0) { 
                if (produto_id > 0 && produto_id <= products->count) { 
                    // Verificar o stock 
                    for (size_t j = 0; j < products->count; j++) { 
                        if (products->items[j].id == produto_id) { 
                            if (products->items[j].stock >= quantidade) { 
                                // Adicionar ao carrinho 
                                User *user = &users->items[user_id - 1]; 
                                if (user->cart.n_products < 100) { 
                                    // Verifica se ainda há espaço no carrinho 
                                    user->cart.products[user->cart.n_products].id = produto_id; 
                                    user->cart.products[user->cart.n_products].quantity = quantidade; 
                                    user->cart.n_products++; 

                                    // Diminuir o stock 
                                    products->items[j].stock -= quantidade; 
                                    printf("\n%d produto(s) id: %d adicionado(s) ao carrinho.\n", quantidade, produto_id); 
                                } else { 
                                    printf("\nCarrinho cheio. Não é possível adicionar mais produtos.\n"); 
                                } 
                            } else { 
                                printf("\nStock insuficiente para o produto com ID %d.\n", produto_id); 
                            } break; 
                        } 
                    } 
                } else { 
                    printf("\nProduto com ID %d não encontrado.\n", produto_id); 
                } 
            } else { 
                printf("\nPor favor, faça login primeiro usando o comando 'uTilizador <id>'.\n"); 
            } 
        }
        // Finalizar ------------------------------------------------------------------------------------------------
        else if (strcmp(command, "F") == 0) {
            if (user_id != 0) {
                if (users->items[user_id - 1].cart.n_products > 0) {
                    // Criar estrutura Cart
                    Cart cart;
                    cart.user_id = user_id;
                    cart.n_products = users->items[user_id - 1].cart.n_products;
                    cart.products = malloc(cart.n_products * sizeof(cart.products[0]));
                    if (cart.products == NULL) {
                        fprintf(stderr, "\nFalha ao alocar memória para produtos. \n");
                        return false;
                    }

                    // Inicializar a memória alocada 
                    memset(cart.products, 0, cart.n_products * sizeof(cart.products[0]));

                    // Copiar os produtos
                    memcpy(cart.products, users->items[user_id - 1].cart.products, cart.n_products * sizeof(cart.products[0]));


                    // Chamar a função cart_put
                    if (cart_put(&cart)) {
                        // Calcular o total a pagar com base nos dados do carrinho do utilizador
                        double total_a_pagar = 0.0;
                        for (size_t i = 0; i < cart.n_products; i++) {
                            int produto_id = cart.products[i].id;
                            int quantidade = cart.products[i].quantity;
                            double preco = 0.0;
                            double desconto = 0.0;

                            // Encontrar o preço e o desconto do produto no array de produtos
                            for (size_t j = 0; j < products->count; j++) {
                                if (products->items[j].id == produto_id) {
                                    preco = products->items[j].price;
                                    desconto = products->items[j].discountPercentage;
                                    break;
                                }
                            }

                            double preco_total_sem_desconto = preco * quantidade;
                            double valor_desconto = preco_total_sem_desconto * (desconto / 100);
                            double preco_total_com_desconto = preco_total_sem_desconto - valor_desconto;

                            total_a_pagar += preco_total_com_desconto;
                        }

                        printf("\nCompra finalizada com sucesso! O utilizador %s pagou um total de %.2f$.\n", users->items[user_id - 1].name, total_a_pagar);

                        // Limpar o carrinho do utilizador
                        users->items[user_id - 1].cart.n_products = 0;
                        memset(users->items[user_id - 1].cart.products, 0, sizeof(users->items[user_id - 1].cart.products));
                    } else {
                        printf("\nErro ao finalizar a compra. Por favor, tente novamente.\n");
                    }
                    // Liberar a memória alocada para o carrinho temporário 
                    free(cart.products);
                } else {
                    printf("\nCarrinho vazio! Não é possível finalizar a compra.\n");
                }
            } else {
                printf("\nPor favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        else {
            printf("\nComando inválido!\n");
        }
    }

    // Libertar a memória alocada
    free_products(products);
    free_users(users);

    return 0;
}
