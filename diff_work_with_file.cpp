#pragma once

#include "diff_work_with_file.h"

size_t tree_count_nodes(Catalog* base)
{
    size_t nodes_counter = 0;
    for (size_t i = 0; i < base->length; i++)
    {
        if (base->buffer[i] == '(')
        {
            nodes_counter++;
        }
    }

    return nodes_counter;
}

static char* tree_skip_space(char* pointer, size_t* length)
{
    if (!pointer)
        return NULL;

    while (isspace(*pointer))
    {
        pointer++;
        (*length)++;

        if (*pointer == '\0')
            break;
    }
    return pointer;
}

static char* tree_skip_letters(char* pointer)
{
    if (!pointer)
        return NULL;

    while ('a' <= *pointer && *pointer <= 'z' || '0' <= *pointer && *pointer <= '9' || *pointer == '-' || *pointer == '.')
    {
        pointer++;
    }
    return pointer;
}

static char tree_look_for_close_bracket(char** pointer)
{
    if (!*pointer)
        return 0;

    while (**pointer != ')' && isspace(**pointer))
    {
        (*pointer)++;

        if (**pointer == '\0')
        {
            *pointer = NULL;
            return 0;
        }
    }
    if (**pointer == ')')
        return 1;
    else
        return 0;
}

tree_operations tree_check_operation(char str)
{
    if (str == '+')
        return OP_PLUS;
    else if (str == '-')
        return OP_SUB;
    else if (str == '*')
        return OP_MUL;
    else if (str == '/')
        return OP_DIV;
    else if (str == '^')
        return OP_POW;
    else if (str == 's')
        return OP_SIN;
    else if (str == 'c')
        return OP_COS;
    else if (str == 'l')
        return OP_LN;
    else
        return NO_OP;
}

Diff_tree* tree_read_from_base(Catalog *base)
{
    Diff_tree* new_tree = tree_init(DEF_SIZE);

    size_t nodes_amount = tree_count_nodes(base);

    char* current_stop = base->buffer;
    size_t length_went = 0;

    long long current_index = ABSENT;

    char went_global_right = 0;
    char went_local_right = 0;

    double number = 0;
    char symbol = 0;

    char input_type = NUMBER;

    long long open_brackets = 0;

    for (long long i = 0; i < nodes_amount; i++)
    {
        long long open_bracket_counter = 0;
        //printf("index at the beginning %lld\n", current_index);
        while (true)
        {
            current_stop = tree_skip_space(current_stop, &length_went);
            if (*current_stop == '(')
            {
                open_bracket_counter++;
                current_stop++;
            }
            else
                break;
        }
        for (long long j = 0; j < open_bracket_counter - 1; j++)
            tree_insert_operation(new_tree, &current_index, OP_PLUS);

        //printf("zero index %ld\n", current_index);

        //Считываем число, не получилось - символ. Пока без sqrt!!!! 
        length_went = sscanf(current_stop, "%lg", &number);
        if (length_went == 0)
        {
            symbol = *current_stop;
            if (symbol != ')')
                input_type = VARIABLE;
            else
                input_type = OPERATION;
        }
        else
            input_type = NUMBER;
        
        if (input_type == VARIABLE)
        {
            tree_insert_variable(new_tree, &current_index, symbol);
            current_stop++;
        }
        else
        {
            printf("number inputted %lg, %d\n", number, length_went);
            tree_insert_number(new_tree, &current_index, number);
            current_stop += length_went;
        }

        current_stop = tree_skip_letters(current_stop);
        //printf("first index %ld\n", current_index);
        
        while (tree_look_for_close_bracket(&current_stop))
        {
            current_stop++;
            if (current_index != ABSENT)
                current_index = new_tree->tree[current_index].parent;
        }
        current_stop = tree_skip_space(current_stop, &length_went);
        char str[MAX_OP_LEN] = "";
        if (current_stop && current_index != ABSENT)
        {
            tree_operations result = tree_check_operation(*current_stop);
            tree_change_operation(new_tree, current_index, result);
            current_stop++;
            i++;
        }
        current_stop = tree_skip_letters(current_stop);
        current_stop = tree_skip_space(current_stop, &length_went);
        //current_stop++; //вроде необязательно
        //printf("second index %ld\n", current_index);
    }

    return new_tree;
}

Diff_tree *tree_read_from_file(const char* file_name)
{
    FILE *input = text_read(file_name);
    Catalog *base = text_init(input);
    printf("%s\n", base->buffer);
    Diff_tree* new_tree = tree_read_from_base(base);

    text_delete(base);
    fclose(input);

    return new_tree;
}



//???????????????????????????????????????????????????
/*void tree_print_padding(FILE* file_name, int padding)
{
    for (int i = 0; i < padding; i++)
    {
        fprintf(file_name, "    ");
    }
}*/

//Что с этим делать, я пока не знаю
/*
void tree_write_in_file(Diff_tree* dtree, long long index, FILE* file_name, int padding)
{
    if (tree_if_lief(dtree, index))
    {
        tree_print_padding(file_name, padding);
        fprintf(file_name, "\"");
        tree_print_message_in_file(dtree, index, file_name);
        fprintf(file_name, "\"\n");

        return;
    }

    tree_print_padding(file_name, padding);

    fprintf(file_name, "\"");
    tree_print_message_in_file(dtree, index, file_name);
    fprintf(file_name, "\"\n");

    tree_print_padding(file_name, padding);
    fprintf(file_name, "[\n");

    if (dtree->tree[index].right_son != ABSENT)
    {
        tree_write_in_file(dtree, dtree->tree[index].right_son, file_name, padding + 1);
    }
    if (dtree->tree[index].left_son != ABSENT)
    {
        tree_write_in_file(dtree, dtree->tree[index].left_son, file_name, padding + 1);
    }

    tree_print_padding(file_name, padding);
    fprintf(file_name, "]\n");
}*/