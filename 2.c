#include <stdio.h>
#define  _CRT_SECURE_NO_WARNINGS
int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int on1 = 0, on2 = 0, on3 = 0;  // 一二三壘是否有人
    int score = 0;
    int outs = 0;

    int hits[3] = { a, b, c };

    for (int i = 0; i < 3; i++) {
        int k = hits[i];

        if (k == 0) {
            outs++;
            if (outs == 3) {
                // 三出局，壘包清空
                on1 = on2 = on3 = 0;
                outs = 0;
            }
            continue;
        }

        if (k == 4) {
            // 全壘打：壘上所有人 + 擊球員得分，壘包清空
            score += on1 + on2 + on3 + 1;
            on1 = on2 = on3 = 0;
            continue;
        }

        // 1~3 壘打：倒序移動，避免覆蓋
        // 先處理會回本壘得分的人
        if (k == 3) {
            score += on1 + on2 + on3;  // 三壘打：壘上都回來得分
            on1 = on2 = on3 = 0;
            on3 = 1;                   // 擊球員到三壘
        }
        else if (k == 2) {
            // 二壘打：二壘、三壘都回來；一壘去三壘；擊球員到二壘
            score += on2 + on3;
            int new3 = on1;
            on1 = 0;
            on2 = 1;
            on3 = new3;
        }
        else { // k == 1
            // 一壘打：三壘回來；二->三；一->二；擊球員->一
            score += on3;
            int new3 = on2;
            int new2 = on1;
            on1 = 1;
            on2 = new2;
            on3 = new3;
        }
    }

    printf("%d\n", score);
    printf("%d %d %d\n", on1, on2, on3);

    return 0;
}