#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Estrutura de Contato ---
#define MAX_CONTATOS 100
#define MAX_NOME 50
#define MAX_TELEFONE 15

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    int ativo; // 1 para ativo, 0 para excluido/vazio
} Contato;

// Variável global para a agenda e o contador de contatos
Contato agenda[MAX_CONTATOS];
int total_contatos = 0;

// --- Funções ---
void mostrarMenu();
void incluirContato();
void consultarContatos();
void excluirContato();
void inicializarAgenda();

// --- Função Principal ---
int main() {
    int opcao;
    inicializarAgenda();

    do {
        mostrarMenu();
        printf("Escolha uma opcao: ");
        if (scanf("%i", &opcao) != 1) { // Limpa o buffer de entrada
            while (getchar() != '\n');
            opcao = 0; // Define uma opção inválida
        }

        switch (opcao) {
            case 1:
                incluirContato();
                break;
            case 2:
                consultarContatos();
                break;
            case 3:
                excluirContato();
                break;
            case 4:
                system("cls");
                printf("\nSaindo da agenda de contatos. Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida. Por favor, escolha uma opcao entre 1 e 4.\n");
        }
    } while (opcao != 4);

    return 0;
}

// Inicializa o array de contatos
void inicializarAgenda() {
    int i;
    for (i = 0; i < MAX_CONTATOS; i++) {
        agenda[i].ativo = 0;
    }
}

// Opções do menu
void mostrarMenu() {
    printf("\n--- Agenda de Contatos ---\n");
    printf("1. Incluir Contato\n");
    printf("2. Consultar Contatos (Listar)\n");
    printf("3. Excluir Contato\n");
    printf("4. Sair\n");
    printf("----------------------------\n");
}

// Função para incluir um novo contato
void incluirContato() {
    if (total_contatos >= MAX_CONTATOS) {
        printf("\nAgenda cheia! Nao e possivel incluir mais contatos.\n");
        return;
    }

    // Encontra a primeira posição livre (onde ativo é 0)
    int i;
    for (i = 0; i < MAX_CONTATOS; i++) {
        if (agenda[i].ativo == 0) {
            break;
        }
    }
    
    // Limpa o buffer antes de ler strings
    while (getchar() != '\n'); 

    printf("\n--- Incluir Contato ---\n");
    printf("Nome: ");
    fgets(agenda[i].nome, MAX_NOME, stdin);
    // Remove o '\n' lido pelo fgets, se existir
    agenda[i].nome[strcspn(agenda[i].nome, "\n")] = 0; 

    printf("Telefone: ");
    fgets(agenda[i].telefone, MAX_TELEFONE, stdin); 
    agenda[i].telefone[strcspn(agenda[i].telefone, "\n")] = 0; // Remove o '\n' lido pelo fgets

    agenda[i].ativo = 1;
    total_contatos++;
    printf("Contato '%s' incluido com sucesso!\n", agenda[i].nome);
    system("cls");
}

// Função para listar os contatos ativos
void consultarContatos() {
    system("cls");
    if (total_contatos == 0) {
        printf("\nAgenda vazia. Nao ha contatos para listar.\n");
        return;
    }

    printf("\n--- Lista de Contatos (%i encontrado(s)) ---\n", total_contatos);
    printf("  ID | Nome                                         | Telefone\n");
    printf("-----|----------------------------------------------|----------------\n");
    int encontrado = 0;
    int i;
    for (i = 0; i < MAX_CONTATOS; i++) {
        if (agenda[i].ativo == 1) {
            printf(" %3i | %-44s | %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
            encontrado = 1;
        }
    }
    if (!encontrado) {
         printf("   Nenhum contato ativo para exibir.\n");
    }
    printf("---------------------------------------------------------------------\n");
}

// Função para excluir um contato (marcar como inativo)
void excluirContato() {
    int id;

    if (total_contatos == 0) {
        printf("\nAgenda vazia. Nao ha contatos para excluir.\n");
        return;
    }
    
    // Lista os contatos para que o usuário escolha o ID
    consultarContatos(); 
    
    printf("\n--- Excluir Contato ---\n");
    printf("Digite o ID do contato a ser excluido (1 a %i): ", MAX_CONTATOS);
    if (scanf("%i", &id) != 1) {
        printf("ID invalido.\n");
        // Limpa o buffer de entrada
        while (getchar() != '\n');
        return;
    }

    // Ajusta o ID para o índice do array (ID 1 -> índice 0)
    int indice = id - 1;

    if (indice >= 0 && indice < MAX_CONTATOS && agenda[indice].ativo == 1) {
        printf("Tem certeza que deseja excluir o contato '%s'? (s/n): ", agenda[indice].nome);
        char confirmacao;
        // Limpa o buffer
        while (getchar() != '\n'); 
        scanf(" %c", &confirmacao);

        if (confirmacao == 's' || confirmacao == 'S') {
            agenda[indice].ativo = 0; // Marca como inativo (excluído)
            
            total_contatos--;
            printf("Contato '%s' excluido com sucesso!\n", agenda[indice].nome);
        } else {
            printf("Exclusao cancelada.\n");
        }
    } else {
        printf("ID %d invalido ou contato ja excluido.\n", id);
    }
    system("cls");
}