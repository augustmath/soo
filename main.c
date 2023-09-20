#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ENGENHARIA DE COMPUTAÇÃO - ENG. DE COMPUTAÇÃO 8° SEMESTRE
//MATHEUS AUGUSTO DE BRITO ASSIS

struct Node {
    int key;
    char *str;
    struct Node *prev;
    struct Node *next;
};

#define MAX_MEMORY_SIZE 10000
char memory[MAX_MEMORY_SIZE];
int memory_index = 0;

void *aloca(size_t size) {
    if (memory_index + size > MAX_MEMORY_SIZE) {
        printf("Erro: Memória insuficiente.\n");
        exit(1);
    }
    void *ptr = memory + memory_index;
    memory_index += size;
    return ptr;
}

void libera(void *ptr) {
    // Não é necessário fazer nada aqui
}

struct Node *createNode(int key, const char *str) {
    struct Node *node = (struct Node *)aloca(sizeof(struct Node));
    node->key = key;
    node->str = (char *)aloca(strlen(str) + 1);
    strcpy(node->str, str);
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void insertNode(struct Node **head, int key, const char *str) {
    struct Node *newNode = createNode(key, str);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

void printList(struct Node *head) {
    printf("Lista:\n");
    struct Node *current = head;
    while (current != NULL) {
        printf("Chave: %d, String: %s\n", current->key, current->str);
        current = current->next;
    }
}

void deleteNode(struct Node **head, int key) {
    struct Node *current = *head;
    while (current != NULL) {
        if (current->key == key) {
            if (current->prev != NULL)
                current->prev->next = current->next;
            if (current->next != NULL)
                current->next->prev = current->prev;
            if (current == *head)
                *head = current->next;
            libera(current->str);
            libera(current);
            return;
        }
        current = current->next;
    }
    printf("Chave %d não encontrada na lista.\n", key);
}

void changeNode(struct Node *head, int key, const char *newStr) {
    struct Node *current = head;
    while (current != NULL) {
        if (current->key == key) {
            libera(current->str);
            current->str = (char *)aloca(strlen(newStr) + 1);
            strcpy(current->str, newStr);
            return;
        }
        current = current->next;
    }
    printf("Chave %d não encontrada na lista.\n", key);
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        libera(temp->str);
        libera(temp);
    }
}

int main(void) {
    struct Node *list = NULL;
    int choice;

    while (1) {
        printf("\nMATHEUS AUGUSTO DE BRITO ASSIS\n");
        printf("\nENGENHARIA DE COMPUTAÇÃO - 8° SEMESTRE\n");
        printf("\nEscolha uma opção:\n");
        printf("1. Incluir\n");
        printf("2. Alterar\n");
        printf("3. Excluir\n");
        printf("4. Listar\n");
        printf("5. Sair\n");
        printf("Opção: ");
        scanf("%d", &choice);

        if (choice == 5) {
            freeList(list);
            break;
        }

        int key;
        char str[100];
        char temp;

        switch (choice) {
            case 1:
                printf("Informe a chave (inteiro): ");
                scanf("%d", &key);
                printf("Informe a string: ");
                scanf("%c", &temp);
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';
                insertNode(&list, key, str);
                break;
            case 2:
                printf("Informe a chave (inteiro) da entrada a ser alterada: ");
                scanf("%d", &key);
                printf("Informe a nova string: ");
                scanf("%c", &temp);
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = '\0';
                changeNode(list, key, str);
                break;
            case 3:
                printf("Informe a chave (inteiro) da entrada a ser excluída: ");
                scanf("%d", &key);
                deleteNode(&list, key);
                break;
            case 4:
                printList(list);
                break;
            default:
                printf("Opção inválida. Escolha novamente.\n");
        }
    }

    return 0;
}
