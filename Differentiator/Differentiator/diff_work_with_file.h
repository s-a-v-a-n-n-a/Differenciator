#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <ctype.h>

#include "diff_consts.h"
#include "diff_tree.h"
#include "catalog_tree_read_from_file.h"


size_t       tree_count_nodes			   (Catalog* base);

static char* tree_skip_space			   (char* pointer, size_t* length);
static char* tree_skip_letters             (char* pointer);

static char  tree_look_for_close_bracket   (char** pointer);

Diff_tree*   tree_read_from_base           (Catalog* base);

Diff_tree*   tree_read_from_file           (const char* file_name);

