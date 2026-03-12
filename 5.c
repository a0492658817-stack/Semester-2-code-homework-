#include <stdio.h>
#include <math.h>

int main() {
    int incall, outcall, localcall;   // 網內、網外、市話通話秒數
    int inmsg, outmsg;                 // 網內、網外簡訊數

    scanf("%d %d %d %d %d", &incall, &outcall, &localcall, &inmsg, &outmsg);

    // 三種資費方案資料
    int monthly[3] = { 183, 383, 983 };

    int free_in_call[3] = { 500, 600, 700 };
    int free_out_call[3] = { 400, 500, 600 };
    int free_local[3] = { 300, 400, 500 };
    int free_in_msg[3] = { 10, 20, 30 };
    int free_out_msg[3] = { 15, 25, 35 };

    double rate_in_call[3] = { 0.08,   0.07,   0.06 };
    double rate_out_call[3] = { 0.1393, 0.1304, 0.1087 };
    double rate_local[3] = { 0.1349, 0.1217, 0.1018 };
    double rate_in_msg[3] = { 1.1287, 1.1127, 0.9572 };
    double rate_out_msg[3] = { 1.4803, 1.2458, 1.1243 };

    int best_plan = 0;
    int best_cost = 2147483647;

    for (int i = 0; i < 3; i++) {
        double total = 0.0;

        if (incall > free_in_call[i])
            total += (incall - free_in_call[i]) * rate_in_call[i];

        if (outcall > free_out_call[i])
            total += (outcall - free_out_call[i]) * rate_out_call[i];

        if (localcall > free_local[i])
            total += (localcall - free_local[i]) * rate_local[i];

        if (inmsg > free_in_msg[i])
            total += (inmsg - free_in_msg[i]) * rate_in_msg[i];

        if (outmsg > free_out_msg[i])
            total += (outmsg - free_out_msg[i]) * rate_out_msg[i];

        // 月租費可抵等額通信費
        if (total < monthly[i])
            total = monthly[i];

        int final_cost = (int)total;   // 無條件捨去

        if (final_cost < best_cost) {
            best_cost = final_cost;
            best_plan = monthly[i];
        }
    }

    printf("%d\n", best_cost);
    printf("%d\n", best_plan);

    return 0;
}