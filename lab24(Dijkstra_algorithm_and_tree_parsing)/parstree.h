#ifndef _PARSTREE_H_
#define _PARSTREE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN_MAX 100
#define STACK_SIZE 100

typedef enum {
    OPERATOR,
    NUMBER,
    VARIABLE
} type_elem;

typedef struct TreeNode {
    struct TreeNode* next;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
    type_elem type;
    char oper;
    int number;
    char variable;
    bool negative;
} TreeNode;

typedef struct Tree {
    TreeNode* root;
} Tree;

typedef struct {
    TreeNode* back;
    TreeNode* front;
} Queue;

typedef struct {
    TreeNode** data;
    int top;
} Stack;

TreeNode* new_node(type_elem type, bool negative);
Stack* stack_create();
void stack_push(Stack* s, TreeNode* n);
TreeNode* stack_pop(Stack* s);
TreeNode* stack_peek(Stack* s);
bool stack_empty(Stack* s);
Stack* read_expression(char* str, int l);
TreeNode* tree_add(TreeNode* n, Stack* s);
Tree* tree_create(Stack* s);
char* write_regular(TreeNode* root);
void free_node(TreeNode* n);
void delete_tree(Tree* t);
void stack_free(Stack* s);
void print_tree(TreeNode* root, int n);
void print_node(TreeNode* n);
bool minuses_delete(TreeNode* root);

#endif