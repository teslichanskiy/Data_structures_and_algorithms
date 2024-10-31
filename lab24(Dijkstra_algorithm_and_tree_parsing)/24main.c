#include "parstree.h"

int main(int argc, char* argv []) {
    char input[LEN_MAX];
    int size = 0;
    char* output = NULL;
    printf("Введите выражение вида: -a * (-b) / (-c) \n");
    fgets(input, LEN_MAX, stdin);
    size = strlen(input);
    Stack* stack = read_expression(input, size);
    printf("\nДерево исходного выражения:\n");
    Tree* tree = tree_create(stack);
    print_tree(tree->root, 0);
    printf("\nПреобразованное дерево:\n");
    minuses_delete(tree->root);
    print_tree(tree->root, 0);
    printf("\nОбычная преобразованная запись\n");
    output = write_regular(tree->root);
    printf("%s\n", output);

    delete_tree(tree);
    free(output);
    stack_free(stack);
    return 0;
}