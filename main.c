#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parson.h"

int g_hd_cnt;
char *g_hd_tkn[128];
char g_thead[1024];

int parse_tbl_hd() {
    int sz = (int) strlen(g_thead);

    // Trim trailing '\n'
    if ('\n' == g_thead[sz - 1]) g_thead[--sz] = '\0';

    for (int i = sz; i >= 0; --i) {
        if (('\t' == g_thead[i]) || !i) {
            char *tkn = g_thead + i;
            if (i) {
                g_thead[i] = '\0';
                tkn++;
            }
            g_hd_tkn[g_hd_cnt] = tkn;
            g_hd_cnt++;
        }
    }

    return 0;
}


int main() {
    char tsv[1024] = {0};

    if (isatty(fileno(stdin))) {
        printf("No input!\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(g_thead, sizeof g_thead, stdin) == NULL) {
        printf("Failed to read input!\n");
        exit(EXIT_FAILURE);
    }

    // Parse head
    if (0 > parse_tbl_hd()) {
        printf("Failed to parse table head!\n");
        exit(EXIT_FAILURE);
    }
    
    
    JSON_Value *root_val = json_value_init_array();
    JSON_Array *root_arr = json_value_get_array(root_val);

    char *json_str = NULL;

    // Parse body
    while (fgets(tsv, sizeof tsv, stdin) != NULL) {
        int sz = (int) strlen(tsv);

        // Trim trailing '\n'
        if ('\n' == tsv[sz - 1]) tsv[--sz] = '\0';

        JSON_Value *obj_val = json_value_init_object();
        JSON_Object *root_obj = json_value_get_object(obj_val);

        int tkcnt = 0;
        for (int i = sz; i >= 0; --i) {
            if (('\t' == tsv[i]) || !i) {
                char *tkn = tsv + i;
                if (i) {
                    tsv[i] = '\0';
                    tkn++;
                }
//                printf("[%s]: %s\n", g_hd_tkn[tkcnt], tkn);
                json_object_set_string(root_obj, g_hd_tkn[tkcnt], tkn);

                tkcnt++;
                tsv[i] = '\0';
            }
        }

        json_array_append_value(root_arr, obj_val);
    }

    json_str = json_serialize_to_string_pretty(root_val);
    puts(json_str);
    json_free_serialized_string(json_str);

    json_value_free(root_val);

    exit(EXIT_SUCCESS);
}
