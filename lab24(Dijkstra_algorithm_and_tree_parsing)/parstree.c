#include "parstree.h"

TreeNode* new_node(type_elem type, bool negative) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (node == NULL) return NULL;
    node->type = type;
    node->negative = negative;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return node;
}

Stack* stack_create() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (TreeNode**)malloc(sizeof(TreeNode*) * STACK_SIZE);
    s->top = -1;
    return s;
}

bool stack_empty(Stack* s) {
    return s->top == -1;
}

void stack_push(Stack* s, TreeNode* n) {
    if (s == NULL) {
        return;
    }
    s->data[++s->top] = n;
}


TreeNode* stack_pop(Stack* s) {
    if (s == NULL || stack_empty(s)) {
        return NULL;
    }
    return s->data[s->top--];
}


TreeNode* stack_peek(Stack* s) {
    if (s == NULL || stack_empty(s)) {
        return NULL;
    }
    return s->data[s->top];
}

// Функция для обработки входной строки и создания стека
Stack* read_expression(char* input, int size) {
    char elements[LEN_MAX];
    int e_idx = 0;
    Stack* s_result = stack_create();
    Stack* s_oper = stack_create();
    for (int i = 0; i < size; i++) {
        char c = input[i];
        bool is_negative = false;
        if (isdigit(c)) { 
            int num = 0;
            while (i < size && isdigit(input[i])) {
                num = num * 10 + (input[i] - '0');
                i++;
            }

            i--; 

            if (e_idx > 0 && elements[e_idx - 1] == '-') {
                if (e_idx - 2 == -1 || elements[e_idx - 2] == '(') {
                    free_node(stack_pop(s_oper)); 
                    is_negative = true;
                }
            }

            elements[e_idx++] = 'A'; 

            TreeNode* node = new_node(NUMBER, is_negative);
            node->number = num;
            stack_push(s_result, node);
        }
        else if (isalpha(c)) { 
            
            if (e_idx > 0 && elements[e_idx - 1] == '-') {
                if (e_idx - 2 == -1 || elements[e_idx - 2] == '(') {
                    free_node(stack_pop(s_oper)); 
                    is_negative = true;
                }
            }

            elements[e_idx++] = 'A'; 

            TreeNode* node = new_node(VARIABLE, is_negative);
            node->variable = c;
            stack_push(s_result, node);
        } else { 
            char op = c; 

            switch (op) {
                case '+':
                case '-':
                {
                    elements[e_idx++] = op; // Добавляем оператор в массив элементов
                    TreeNode* op_node = new_node(OPERATOR, is_negative); // Создаем новый узел для оператора
                    op_node->oper = op; // Устанавливаем символ оператора
                    if (!stack_empty(s_oper)) {
                        char oper = stack_peek(s_oper)->oper; // Получаем оператор на вершине стека операторов
                        while (!stack_empty(s_oper) && (oper == '+' || oper == '-' || oper == '*' || oper == '/')) {
                            stack_push(s_result, stack_pop(s_oper)); // Перекладываем операторы с вершины стека в результат
                            oper = stack_empty(s_oper) ? ' ' : stack_peek(s_oper)->oper; // Получаем следующий оператор из стека (или пробел, если стек пуст)
                        }
                    }

                    stack_push(s_oper, op_node); // Помещаем текущий оператор в стек операторов
                    break;
                }

                case '*':
                case '/':
                {
                    elements[e_idx++] = op; // Добавляем оператор в массив элементов
                    TreeNode* op_node = new_node(OPERATOR, is_negative); // Создаем новый узел для оператора
                    op_node->oper = op; // Устанавливаем символ оператора
                    if (!stack_empty(s_oper)) {
                        char oper = stack_peek(s_oper)->oper; // Получаем оператор на вершине стека операторов
                        while (!stack_empty(s_oper) && (oper == '*' || oper == '/')) {
                            stack_push(s_result, stack_pop(s_oper)); // Перекладываем операторы с вершины стека в результат
                            oper = stack_empty(s_oper) ? ' ' : stack_peek(s_oper)->oper; // Получаем следующий оператор из стека (или пробел, если стек пуст)
                        }
                    }

                    stack_push(s_oper, op_node); // Помещаем текущий оператор в стек операторов
                    break;
                }

                case '(':
                {
                    elements[e_idx++] = op; // Добавляем открывающую скобку в массив элементов
                    TreeNode* op_node = new_node(OPERATOR, is_negative); // Создаем новый узел для оператора
                    op_node->oper = op; // Устанавливаем символ оператора
                    stack_push(s_oper, op_node); // Помещаем текущую открывающую скобку в стек операторов
                    break;
                }

                case ')':
                {
                    elements[e_idx++] = op; // Добавляем закрывающую скобку в массив элементов
                    char oper = stack_peek(s_oper)->oper; // Получаем оператор на вершине стека операторов
                    while (!stack_empty(s_oper) && (oper != '(')) {
                        stack_push(s_result, stack_pop(s_oper)); // Перекладываем операторы с вершины стека в результат до открывающей скобки
                        oper = stack_empty(s_oper) ? ' ' : stack_peek(s_oper)->oper; // Получаем следующий оператор из стека (или пробел, если стек пуст)
                    }

                    break;
                }

                default:
                    break; 
                }
        }
    }

    // Перекладываем остальные операторы
    while (!stack_empty(s_oper)) {
        TreeNode* op_node = stack_pop(s_oper);
        if (op_node->oper != '(') {
            stack_push(s_result, op_node);
        }
        else {
            free_node(op_node);
        }
    }
    free(s_oper->data);
    free(s_oper);
    return s_result;
}

TreeNode* tree_add(TreeNode* n, Stack* s) {
    if (n == NULL) return NULL;
    if (n->type == NUMBER || n->type == VARIABLE) {
        return n;
    }

    TreeNode* temp = n;

    temp->right = tree_add(stack_pop(s), s);
    temp->left = tree_add(stack_pop(s), s);
    return temp;
}


Tree* tree_create(Stack* s) {
    Tree* t = (Tree*)malloc(sizeof(Tree));
    if (t == NULL) return NULL;

    t->root = stack_pop(s);

    t->root->right = tree_add(stack_pop(s), s);
    t->root->left = tree_add(stack_pop(s), s);
    return t;
}

// Функция для обработки унарного минуса при делении
bool minuses_delete(TreeNode* root) {
    if (root->type == NUMBER || root->type == VARIABLE) { // Если это число или переменная, возвращаем флаг 'negative' текущего узла.
        return root->negative;
    }
       
    if (root->oper == '/' || root->oper == '*') {
        bool is_negative = (minuses_delete(root->left) + minuses_delete(root->right)) % 2; //Определяем сколько отрицательных
        root->negative = is_negative; // Устанавливаем флаг 'negative' текущего узла в соответствии с результатом деления.
        root->left->negative = false; // Устанавливаем 'negative' для левого и правого поддеревьев в false
        root->right->negative = false;
        return is_negative; // Возвращаем значение is_negative, которое указывает, будет ли результат деления отрицательным.
    }

    minuses_delete(root->left);
    minuses_delete(root->right);
    return false;
}


void print_tree(TreeNode* root, int n) {
    if (root == NULL) return;
    print_tree(root->right, n + 1);
    printf("    ");
    for (int i = 0; i < n; i++) {
        if (i == n - 1) printf("     {");
        else printf("      ");
    }
    print_node(root);
    printf("\n");
    print_tree(root->left, n + 1);
}

void print_node(TreeNode* n) {
    switch (n->type) {
    case NUMBER:
        printf("%s%d ", (n->negative ? "-" : ""), n->number);
        break;
    case VARIABLE:
        printf("%s%c ", (n->negative ? "-" : ""), n->variable);
        break;
    case OPERATOR:
        printf("%s%c ", (n->negative ? "-" : ""), n->oper);
        break;
    }
}

// Функция для записи выражения
char* write_regular(TreeNode* root) {
    char* str = (char*)malloc(LEN_MAX);

    if (root == NULL) return NULL;

    if (root->type == NUMBER) {
        bool neg = root->negative;
        sprintf(str, "%s%d%s", (neg ? "(-" : ""), root->number, (neg ? ")" : ""));
    }
    else if (root->type == VARIABLE) {
        bool neg = root->negative;
        sprintf(str, "%s%c%s", (neg ? "(-" : ""), root->variable, (neg ? ")" : ""));
    }
    else {
        char* left = write_regular(root->left);
        char* right = write_regular(root->right);

        if (root->negative) {
            sprintf(str, "-(%s %c %s)", left, root->oper, right);
        }
        else {
            char op = root->oper;
            if (op == '+' || op == '-') {
                sprintf(str, "(%s %c %s)", left, root->oper, right);
            }
            else {
                sprintf(str, "%s %c %s", left, root->oper, right);
            }

        }

        free(left);
        free(right);
    }

    return str;
}

void free_node(TreeNode* n) {
    if (n == NULL) return;
    if (n->left != NULL) free_node(n->left);
    if (n->right != NULL) free_node(n->right);
    free(n);
}

void stack_free(Stack* s) {
    free(s->data);
    free(s);
}

void delete_tree(Tree* t) {
    free_node(t->root);
    t->root = NULL;
    free(t);
}