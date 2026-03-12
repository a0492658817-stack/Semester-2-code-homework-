#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXL 105

/* 移除字串最後面的換行 */
void remove_newline(char* s) {
    s[strcspn(s, "\n")] = '\0';
}

/* 判斷是否全為數字 */
int all_digits(const char* s) {
    int i;
    if (s[0] == '\0') return 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (!isdigit((unsigned char)s[i])) return 0;
    }
    return 1;
}

/* 比較兩個「非負整數字串」大小
   回傳:
   -1 => a < b
    0 => a == b
    1 => a > b
*/
int compare_number_string(const char* a, const char* b) {
    int la = strlen(a);
    int lb = strlen(b);

    if (la < lb) return -1;
    if (la > lb) return 1;

    int cmp = strcmp(a, b);
    if (cmp < 0) return -1;
    if (cmp > 0) return 1;
    return 0;
}

/* 檢查是否為合法整數字串（可有開頭負號） */
int is_valid_integer_core(const char* s) {
    int start = 0;
    int len = strlen(s);

    if (len < 1 || len > 50) return 0;

    if (s[0] == '-') {
        start = 1;
        if (s[1] == '\0') return 0;   // 只有 "-"
    }

    if (!all_digits(s + start)) return 0;

    /* 0 和 -0 合法 */
    if (strcmp(s + start, "0") == 0) return 1;

    /* 不能有前導零 */
    if (s[start] == '0') return 0;

    return 1;
}

/* 整數 */
int is_integer(const char* s) {
    return is_valid_integer_core(s);
}

/* 浮點數 */
int is_float_num(const char* s) {
    int len = strlen(s);
    int start = 0;
    int dot_count = 0;
    int i, dot_pos = -1;

    if (len < 3 || len > 50) return 0;

    if (s[0] == '-') {
        start = 1;
        if (s[1] == '\0') return 0;
    }

    for (i = start; s[i] != '\0'; i++) {
        if (s[i] == '.') {
            dot_count++;
            dot_pos = i;
        }
        else if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }

    if (dot_count != 1) return 0;

    /* 小數點不能在開頭或結尾 */
    if (dot_pos == start) return 0;
    if (s[dot_pos + 1] == '\0') return 0;

    /* 檢查整數部分 */
    /* 例如 01.5 不合法，0.5 合法 */
    {
        int int_len = dot_pos - start;
        if (int_len <= 0) return 0;

        if (int_len > 1 && s[start] == '0') return 0;
    }

    return 1;
}

/* 變數 */
int is_variable(const char* s) {
    int len = strlen(s);
    int i;

    if (len < 1 || len > 10) return 0;

    if (!(isalpha((unsigned char)s[0]) || s[0] == '_')) return 0;

    for (i = 1; s[i] != '\0'; i++) {
        if (!(isalnum((unsigned char)s[i]) || s[i] == '_')) return 0;
    }

    return 1;
}

/* 真分數 / 假分數共用檢查
   回傳:
   1 => proper fraction
   2 => improper fraction
   0 => 不是合法分數
*/
int fraction_type(const char* s) {
    int len = strlen(s);
    int slash = -1;
    int i, start = 0;
    char num[MAXL], den[MAXL];

    if (len < 1 || len > 10) return 0;

    if (s[0] == '-') {
        start = 1;
        if (s[1] == '\0') return 0;
    }

    for (i = start; s[i] != '\0'; i++) {
        if (s[i] == '/') {
            if (slash != -1) return 0;  // 只能有一個 '/'
            slash = i;
        }
        else if (!isdigit((unsigned char)s[i])) {
            return 0;
        }
    }

    if (slash == -1) return 0;                  // 沒有 '/'
    if (slash == start) return 0;               // 分子空
    if (s[slash + 1] == '\0') return 0;         // 分母空

    /* 切出分子與分母，分子可有負號，分母不可有負號 */
    strncpy(num, s, slash);
    num[slash] = '\0';
    strcpy(den, s + slash + 1);

    /* 分母必須全數字 */
    if (!all_digits(den)) return 0;

    /* 分子處理負號 */
    {
        char* abs_num = num;
        if (num[0] == '-') abs_num = num + 1;

        if (*abs_num == '\0') return 0;
        if (!all_digits(abs_num)) return 0;

        /* 分子、分母都不能是 0 */
        if (strcmp(abs_num, "0") == 0) return 0;
        if (strcmp(den, "0") == 0) return 0;

        /* 不能有前導零 */
        if (strlen(abs_num) > 1 && abs_num[0] == '0') return 0;
        if (strlen(den) > 1 && den[0] == '0') return 0;

        /* 比較 |分子| 和 分母 */
        {
            int cmp = compare_number_string(abs_num, den);
            if (cmp < 0) return 1;   // proper fraction
            else return 2;           // improper fraction
        }
    }
}

/* 帶分數 */
int is_mixed_fraction(const char* s) {
    int len = strlen(s);
    int space_pos = -1;
    int i;
    char left[MAXL], right[MAXL];

    if (len < 1 || len > 10) return 0;

    /* 必須只有一個空白 */
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            if (space_pos != -1) return 0;
            space_pos = i;
        }
    }

    if (space_pos == -1) return 0;
    if (space_pos == 0) return 0;
    if (s[space_pos + 1] == '\0') return 0;

    strncpy(left, s, space_pos);
    left[space_pos] = '\0';
    strcpy(right, s + space_pos + 1);

    /* 前半部必須是整數 */
    if (!is_integer(left)) return 0;

    /* 後半部必須是真分數，且不能有負號 */
    if (right[0] == '-') return 0;
    if (fraction_type(right) != 1) return 0;

    return 1;
}

int main() {
    int N, i;
    char s[MAXL];

    scanf("%d", &N);
    getchar();  // 吃掉第一行後面的換行

    for (i = 0; i < N; i++) {
        fgets(s, sizeof(s), stdin);
        remove_newline(s);

        if (is_integer(s)) {
            printf("integer\n");
        }
        else if (fraction_type(s) == 1) {
            printf("proper fraction\n");
        }
        else if (fraction_type(s) == 2) {
            printf("improper fraction\n");
        }
        else if (is_mixed_fraction(s)) {
            printf("mixed fraction\n");
        }
        else if (is_float_num(s)) {
            printf("float\n");
        }
        else if (is_variable(s)) {
            printf("variable\n");
        }
        else {
            printf("string\n");
        }
    }

    return 0;
}