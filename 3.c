#include <stdio.h>

int elem_to_bit(char ch) {
    if (ch < 'a' || ch > 'f') return -1;
    return ch - 'a'; // a->0, b->1, ... f->5
}

int main() {
    int S0, S1;
    char e1, e2;

    scanf_s("%d", &S0);
    scanf_s("%d", &S1);
    scanf_s(" %c", &e1);  // 前面空白吃掉換行
    scanf_s(" %c", &e2);

    int s0_ok = (S0 >= 0 && S0 <= 63);
    int s1_ok = (S1 >= 0 && S1 <= 63);

    int b1 = elem_to_bit(e1);
    int b2 = elem_to_bit(e2);
    int e1_ok = (b1 != -1);
    int e2_ok = (b2 != -1);

    // 若有任何錯誤：照規則印錯誤訊息（可能多行），不印後面5行結果
    if (!s0_ok || !s1_ok || !e1_ok || !e2_ok) {
        if (!s0_ok) printf("S0 ERROR\n");
        if (!s1_ok) printf("S1 ERROR\n");
        if (!e1_ok) printf("e1 ERROR\n");
        if (!e2_ok) printf("e2 ERROR\n");
        return 0;
    }

    // (1) S2 = S1 加入 e1
    int S2 = S1 | (1 << b1);

    // (2) e2 是否在 S2
    printf("%s\n", (S2 & (1 << b2)) ? "Y" : "N");

    // (3) S2 是否為 S0 子集合： (S2 ⊆ S0) <=> (S2 & ~S0) == 0
    printf("%s\n", ((S2 & (~S0)) == 0) ? "Y" : "N");

    // (4) 交集
    printf("%d\n", (S0 & S2));

    // (5) 聯集
    printf("%d\n", (S0 | S2));

    // (6) 差集 S0 - S2
    printf("%d\n", (S0 & (~S2)));

    return 0;
}