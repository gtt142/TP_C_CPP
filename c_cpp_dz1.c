#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF 100
#define MAX_LINES 20


void free_strs(char** str_ptr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        free(*(str_ptr + i));
    }
    free(str_ptr);
}

size_t get_strs(char*** top) {
    char** strs = NULL;
    char** s_buf = NULL;
    char* str = NULL;
    char* buf = NULL;
    char c = '\0';
    size_t buf_maxSize = 0;
    size_t nowMaxLines = 0;
    size_t lineNum = 0;
    size_t lenStr = 0;

    while (!0) {   
        lenStr = 0;
        buf_maxSize = 0;
        str = NULL;

        while (c = getchar(), c != EOF && c != '\n') {
            if (lenStr + 1 >= buf_maxSize) {
                size_t new_maxSize = !buf_maxSize ? BUF : buf_maxSize + BUF;
                buf = (char *)malloc((new_maxSize + 1) * sizeof(char));
                if (!buf) {
                    if (str) {
                        free(str);
                        free_strs(strs, lineNum);
                    }
                    printf("[error]");
                    return 0;
                }
                if (str) {
                    buf = memcpy(buf, str, (lenStr + 1));
                    free(str);
                }
                str = buf;
                buf_maxSize = new_maxSize;
            }
            str[lenStr] = c;
            str[lenStr + 1] = '\0';
            lenStr++;
        }

        

        if (lenStr > 0) {
            buf = (char *)malloc((lenStr + 1) * sizeof(char));
            if (!buf) {
                if (str) {
                    free(str);
                    free_strs(strs, lineNum);
                }
                printf("[error]");
                return 0;
            }
            if (str) {
                buf = memcpy(buf, str, (lenStr +1));
                free(str);
            }
            str = buf;


            if (lineNum >= nowMaxLines) {
                size_t new_maxLines = !nowMaxLines ? MAX_LINES : nowMaxLines + MAX_LINES;
                s_buf = (char **)malloc((new_maxLines) * sizeof(char*));
                if (!s_buf) {
                    free(str);
                    if (strs)
                    {
                        free_strs(strs, lineNum);
                    }
                    printf("[error]");
                    return 0;
                }
                if (strs) {
                    s_buf = memcpy(s_buf, strs, lineNum);
                    free(strs);
                }
                strs = s_buf;
                nowMaxLines = new_maxLines;
            }
            strs[lineNum] = str;
            lineNum++;
        }
        if (c == EOF)
            break;
    }

    *top = strs;
    return lineNum;
}

//  Копируем указатели на правильные строки.
size_t pair_brackets(char** strs, size_t numStr, char*** top) { 
    char** new_strs = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t lenStr = 0;
    size_t newStrNum = 0;
    char* char_ptr = NULL;
    char c = '\0';
    size_t l_bracket = 0;
    size_t r_bracket = 0;

    new_strs = (char**)malloc(numStr * sizeof(char*));
    if (!new_strs) {
        printf("[error]");
        return 0;   
    }
    *top = new_strs;

    for (i = 0; i < numStr; i++) {
        l_bracket = r_bracket = 0;
        lenStr = strlen(*(strs + i));
        
        for (j = 0, char_ptr = *(strs + i); j < lenStr; j++) {
            c = *(char_ptr + j);
            
            if (c == '(') {
                l_bracket++;
            }

            if (c == ')') {   
                r_bracket++;
            }
        }

        if ((l_bracket == r_bracket)) {
            *(new_strs + newStrNum) = *(strs + i);
            newStrNum++;
        }
    }

    if (newStrNum == 0)
        free(new_strs);

    return newStrNum;

}

void print_strs(char** strs, size_t n) {
    for (size_t i = 0; i < n; i++) {
        printf("%s\n", *(strs + i));
    }
}

int main () {
    char** strs = NULL;
    char** res_strs = NULL;


    const size_t num_lines = get_strs(&strs);
    if (num_lines == 0) {
        return 0;
    }


    //  Копируем указатели на правильные строки.
    const size_t num_lines2 = pair_brackets(strs, num_lines, &res_strs);
    if (num_lines2 == 0) {
        free_strs(strs, num_lines);
        return 0;
    }

    print_strs(res_strs, num_lines2);

    free_strs(strs, num_lines);
    free(res_strs);

    return 0;
}