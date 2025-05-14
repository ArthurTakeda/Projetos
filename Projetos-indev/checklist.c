#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Protótipos
void task_register(void);
void task_list(void);
void task_manager(void);
void main_menu(void);

// Variáveis globais
int task_count = 0;
typedef struct {
    int id;
    char task[100];
    bool done;
} checklist;
checklist *check = NULL;

void task_register() {
    int initial_size = 10;
    check = malloc(initial_size * sizeof(checklist));
    if (check == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    int i = 0;
    char yorn;

    do {
        system("cls");
        printf("Insert the %d task: ", (i + 1));

        // Ler a tarefa (permite espaços)
        scanf(" %[^\n]", check[i].task);

        check[i].id = i;
        check[i].done = false; // Inicializa como não concluída

        i++;
        task_count++;

        // Redimensionar se necessário
        if (task_count >= initial_size) {
            initial_size *= 2;
            checklist *temp = realloc(check, initial_size * sizeof(checklist));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                free(check);
                exit(1);
            }
            check = temp;
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &yorn); // Espaço antes do %c ignora whitespace
        yorn = tolower(yorn);

    } while (yorn != 'n' && i < 100); // Limite máximo de 100 tarefas

    main_menu();
}

void task_manager() {
    if (task_count == 0) {
        printf("No tasks available!\n");
        system("pause");
        main_menu();
        return;
    }

    int select;
    char yorn;

    do {
        system("cls");
        printf("+-----+----------------------+--------+\n");
        printf("| ID  | TASK                 | DONE   |\n");
        printf("+-----+----------------------+--------+\n");

        for (int i = 0; i < task_count; i++) {
            printf("| %-3d | %-20s | %-6s |\n",
                   check[i].id, check[i].task,
                   check[i].done ? "YES" : "NO");
        }
        printf("+-----+----------------------+--------+\n");

        printf("\nEnter task ID to modify (or -1 to exit): ");
        scanf("%d", &select);

        if (select == -1) break;

        if (select < 0 || select >= task_count) {
            printf("Invalid task ID!\n");
            system("pause");
            continue;
        }

        printf("Mark task '%s' as done? (Y/N): ", check[select].task);
        scanf(" %c", &yorn);
        yorn = tolower(yorn);

        if (yorn == 'y') {
            check[select].done = true;
        } else if (yorn == 'n') {
            check[select].done = false;
        } else {
            printf("Invalid input! Please use Y or N.\n");
        }

    } while (1); // Loop infinito até selecionar -1

    main_menu();
}

void task_list() {
    system("cls");
    if (task_count == 0) {
        printf("No tasks available!\n");
    } else {
        printf("+-----+----------------------+--------+\n");
        printf("| ID  | TASK                 | DONE   |\n");
        printf("+-----+----------------------+--------+\n");

        for (int i = 0; i < task_count; i++) {
            printf("| %-3d | %-20s | %-6s |\n",
                   check[i].id, check[i].task,
                   check[i].done ? "YES" : "NO");
        }
        printf("+-----+----------------------+--------+\n");
    }
    system("pause");
    main_menu();
}

void main_menu() {
    int select;

    do {
        system("cls");
        printf("=== CHECKLIST APP ===\n\n");
        printf("1. View Tasks\n");
        printf("2. Create New Checklist\n");
        printf("3. Manage Tasks\n");
        printf("4. Exit\n\n");
        printf("Select your option: ");
        scanf("%d", &select);

        switch (select) {
            case 1: task_list(); break;
            case 2: task_register(); break;
            case 3: task_manager(); break;
            case 4:
                free(check); // Liberar memória antes de sair
                exit(0);
            default:
                printf("Invalid option! Please try again.\n");
                system("pause");
        }
    } while (1);
}

int main() {
    main_menu();
    return 0;
}