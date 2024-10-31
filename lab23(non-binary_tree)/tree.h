#ifndef _TREE_H //Метод условной компиляции, для предотвращения повторной компиляции кода
#define _TREE_H //Если макрос не был определен, код компилируется
//Заголовочный файл с объявлением прототипов функций, структур и станд. библиотек

#include <stdio.h> //Объявление стандартных библиотек
#include <stdlib.h>

typedef int TreeItem;  //Определение нового типа для переменных, хранящих значения узлов дерева
typedef struct _tree* Tree; //Определение новго типа - указателя на структуру _tree

typedef enum {         //Для удобства в switch case
        ADD = 1,
        DELETE = 2,
        PRINT = 3,
        NUMBER = 4
} var_cases;

Tree tree_create(TreeItem value); //Функция создания дерева (корня)
Tree search_in_tree(Tree root, TreeItem value); //Функция поиска
Tree search_left(Tree root, TreeItem value); //Функция поиска, обходит корень и левую ветвь дерева
Tree search_right(Tree root, TreeItem value); //Функция поиска, обходит корень и правую ветвь дерева
void add_node(Tree node, TreeItem value, int side); //Функция добавления узла в дерево, в качестве аргумента получает указатель на узел типа структуры _tree
int delete_node(Tree node); //Функция удаления узла, в качестве аргумента принимает указатель на узел типа структуры _tree
void print_node(TreeItem value, int inter); //Функция вывода значения каждого узла с отступами
void print_tree(Tree h, int indent); //Функция вывода дерева
int count(Tree node); //Функция подсчёта нетерминальных вершин дерева, в качестве аргумента принимает указатель на корень дерева
void delete_tree(Tree root); //Функция удаления дерева и очистки памяти
#endif //Конец блока условной компиляции