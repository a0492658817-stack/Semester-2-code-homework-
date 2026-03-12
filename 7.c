#include<stdio.h>
int main() {

	int n = 0, m = 0;
	scanf("%d %d", &n, &m);
	if (n < 1 || n>2 || m < 2 || m>9) {
		printf("error");
		return 0;
	}

	char alpha = '@';
	if (n == 1) {
		for (int i = 1; i <= m; i++) {

			for (int j = m; j > i; j--) {
				printf("#");
			}
			if (alpha > 'C') alpha = 'A';
			for (int j = 1; j <= i * 2 - 1; j++) {
				if (j != 0 && j % 2 == 0) {
					printf("%c", alpha);
				}
				else {
					printf("*");
				}
			}
			alpha++;

			for (int j = m; j > i; j--) {
				printf("#");
			}
			printf("\n");
		}
	}
	else if (n == 2) {
		for (int i = 1; i <= m; i++) {
			for (int j = i; j > 0; j--) {
				printf("%d", j);
			}
			for (int j = 1; j <= 2 * (m - i + 1); j++) {
				printf("*");
			}
			for (int j = 1; j <=i; j++) {
				printf("%d", j);
			}
			printf("\n");
		}
	}
	return 0;
}