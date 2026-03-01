#include <stdio.h>

int main() {
    int w, h;
    scanf("%d", &w);
    scanf("%d", &h);

    // 範圍檢查
    if (w < 20 || w > 100 || h < 100 || h > 200) {
        printf("ERROR");
        return 0;
    }

    // BMI計算
    double hm = h / 100.0;          // 公尺
    double bmi = w / (hm * hm);

    // 四捨六入五看偶
    int integer = (int)bmi;          // 整數部分
    double decimal = bmi - integer;  // 小數部分
    int first_decimal = (int)(decimal * 10);  // 小數第一位

    int result = integer;

    if (first_decimal <= 4) {
        // 捨去，不變
    }
    else if (first_decimal >= 6) {
        result = integer + 1;
    }
    else { // first_decimal == 5
        // 五看偶
        if (integer % 2 == 0) {
            result = integer + 1;
        }
        // 奇數則不變
    }

    // 輸出BMI整數值
    printf("%d\n", result);

    // 判斷範圍
    if (result < 18) {
        printf("too low");
    }
    else if (result > 24) {
        printf("too high");
    }

    return 0;
}