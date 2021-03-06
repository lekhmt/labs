// файл main.c с чистым кодом - без дефайнов и цветного вывода

// вариант 6 - определить значение нетерминальной вершины двоичного дерева с максимальной глубиной

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "headers/tree.h"
#include "headers/queue.h"

const int STRING_CAPACITY  = 512;

void check_next_vertex(tree t, queue* r, bool* previous){
    tree left = get_left(t);
    tree right = get_right(t);
    if (!is_empty(left) || !is_empty(right)){
        if (*previous){
            *previous = false;
            q_clear(r);
            q_push(r, t);
        } else {
            q_push(r, t);
        }
    }
}

void value(tree t, queue* r){
    queue a, b;
    q_create(&a);
    q_create(&b);
    q_push(&a, t);
    if (!is_empty(get_left(t)) || !is_empty(get_right(t))){
        q_push(r, t);
    }
    while (!q_is_empty(&a)) {
        while (!q_is_empty(&a)) {
            bool previous = true;
            tree elem = q_pop(&a);
            if (!is_empty(get_left(elem))) {
                q_push(&b, get_left(elem));
                check_next_vertex(get_left(elem), r, &previous);
            }
            if (!is_empty(get_right(elem))) {
                q_push(&b, get_right(elem));
                check_next_vertex(get_right(elem), r, &previous);
            }
        }
        if (!q_is_empty(&b)) {
            queue tmp = a;
            a = b;
            b = tmp;
        }
    }
    q_destroy(&a);
    q_destroy(&b);

}

bool is_command(char* word){
    char* commands[] = {"insert", "delete", "print", "value", "exit", "clear", "help"};
    bool result = false;
    for (int i = 0; i < 7; ++i){
        if (strcmp(word, commands[i]) == 0){
            result = true;
        }
    }
    return result;
}

bool is_spaces(char* word){
    bool result = true;
    for (int i = 0; i < strlen(word); ++i){
        if (word[i] != ' ' && word[i] != '\n' && word[i] != '\t'){
            result = false;
        }
    }
    return result;
}

void clear_from_tabs(char* word){
    for (int i = 0; i < strlen(word); ++i){
        if (word[i] == '\t'){
            word[i] = ' ';
        }
    }
}

void help(){
    printf("future help function\n");
}

int main(int argc, char* argv[]){

    tree t = create();

    if (argc != 1){
        if (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--preset") == 0){
            t = insert(t, SEVEN);
            t = insert(t, TWO);
            t = insert(t, FIVE);
            t = insert(t, TEN);
            t = insert(t, NINE);
            t = insert(t, ZERO);
            t = insert(t, ONE);
            t = insert(t, FOUR);
            t = insert(t, SIX);
        } else {
            fprintf(stderr, "Undefined option \"%s\"\n", argv[1]);
            exit(1);
        }
    }

    char word[STRING_CAPACITY];

    printf("cmd: ");
    scanf("%s", word);
    clear_from_tabs(word);

    while (strcmp(word, "exit") != 0){

        if (!is_command(word)){
            printf("Error: \"%s\" is not a command\n", word);
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "insert") == 0){
            fgets(word, STRING_CAPACITY, stdin);
            clear_from_tabs(word);
            if (strcmp(word, "\n") == 0 || is_spaces(word)){
                printf("Error: missing argument for \"insert\"\n");
                printf("cmd: ");
                scanf("%s", word);
                clear_from_tabs(word);
                continue;
            }
            char* w;
            w = strtok(word, " ");
            while (w != NULL){
                Number n = get_enum_number(w);
                if (n == ERROR){
                    printf("Error: invalid argument \"%s\"\n", w);
                } else {
                    t = insert(t, n);
                }
                w = strtok(NULL, " ");
            }
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "delete") == 0){
            fgets(word, STRING_CAPACITY, stdin);
            clear_from_tabs(word);
            if (strcmp(word, "\n") == 0 || is_spaces(word)){
                printf("Error: missing argument for \"delete\"\n");
                printf("cmd: ");
                scanf("%s", word);
                clear_from_tabs(word);
                continue;
            }
            char* w;
            w = strtok(word, " ");
            while (w != NULL){
                Number n = get_enum_number(w);
                if (n == ERROR){
                    printf("Error: invalid argument \"%s\"\n", w);
                } else {
                    t = delete(t, n);
                }
                w = strtok(NULL, " ");
            }
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "print") == 0){
            fgets(word, STRING_CAPACITY, stdin);
            clear_from_tabs(word);
            if (strcmp(word, "\n") != 0){
                printf("Note: function \"print\" takes no arguments\n");
            }
            if (!is_empty(t)){
                print(t, 0);
            } else {
                printf("Note: tree is empty\n");
            }
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "value") == 0){
            fgets(word, STRING_CAPACITY, stdin);
            clear_from_tabs(word);
            if (strcmp(word, "\n") != 0){
                printf("Note: function \"value\" takes no arguments\n");
            }
            queue result;
            q_create(&result);
            if (!is_empty(t)){
                value(t, &result);
            } else {
                printf("Note: tree is empty\n");
                printf("cmd: ");
                scanf("%s", word);
                clear_from_tabs(word);
                continue;
            }
            if (q_is_empty(&result)){
                printf("Note: no matching vertex");
            }
            while (!q_is_empty(&result)){
                tree elem = q_pop(&result);
                printf("%s ", get_enum_name(get_value(elem)));
            }
            q_destroy(&result);
            printf("\n");
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "clear") == 0){
            fgets(word, STRING_CAPACITY, stdin);
            clear_from_tabs(word);
            if (strcmp(word, "\n") != 0){
                printf("Note: function \"clear\" takes no arguments\n");
            }
            if (!is_empty(t)){
                clear(t);
                t = create();
            } else {
                printf("Note: tree is empty\n");
            }
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

        if (strcmp(word, "help") == 0){
            help();
            printf("cmd: ");
            scanf("%s", word);
            clear_from_tabs(word);
            continue;
        }

    }

    clear(t);

}
