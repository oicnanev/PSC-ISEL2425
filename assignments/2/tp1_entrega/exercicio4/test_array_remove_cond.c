#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    const char *name;
    int number;
};

// Instâncias dos estudantes
    static struct student student1 = {"Alberto", 1001};
    static struct student student2 = {"Bruno", 1502};
    static struct student student3 = {"Carolina", 2003};
    static struct student student4 = {"David", 1999};
    static struct student student5 = {"Eduardo", 3456};
    static struct student student6 = {"Filipa", 3256};
    static struct student student7 = {"Guilherme", 1499};
    static struct student student8 = {"Helena", 4799};
    static struct student student9 = {"Irene", 3476};
    static struct student student10 = {"Joaquim", 4949};

    // Array de ponteiros para struct student
    static struct student *students[] = {
        &student1, 
        &student2, 
        &student3, 
        &student4,
        &student5,
        &student6,
        &student7,
        &student8,
        &student9,
        &student10,
    };

    size_t size = sizeof(students) / sizeof(students[0]);

// Declaração da função assembly
extern size_t array_remove_cond(
    void **array,
    size_t size,
    int (*eval)(const void *, const void *),
    void *context
);

// Função de verificação
// Retorna 1 se o número do estudante for maior que o valor do contexto
int eval(const void *student_ptr, const void *context) {
    const struct student *student = student_ptr;
    int threshold = *(const int *)context;
    return student->number > threshold;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <número limite>\n", argv[0]);
        return 1;
    }

    // Converte o argumento do executável para o número limite
    int threshold = atoi(argv[1]);

    // Exibe o array original
    printf("Array original:\n");
    for (size_t i = 0; i < size; i++) {
        printf("Estudante: %s, Número: %d\n", students[i]->name, students[i]->number);
    }

    // Chama array_remove_cond para remover estudantes com número maior que o limite
    size = array_remove_cond((void **)students, size, eval, &threshold);

    // Exibe o array após a remoção
    printf("\nArray após a remoção:\n");
    for (size_t i = 0; i < size; i++) {
        printf("Estudante: %s, Número: %d\n", students[i]->name, students[i]->number);
    }

    return 0;
}
