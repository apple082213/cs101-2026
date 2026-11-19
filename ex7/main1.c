#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);

    FILE *fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    time_t curtime;
    time(&curtime);
    char *time_str = ctime(&curtime);
    for (int i = 0; time_str[i] != '\0'; i++) {
        if (time_str[i] == '\n') {
            time_str[i] = '\0';
            break;
        }
    }

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", time_str);

    srand((unsigned int)time(NULL));

    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "[%d]:", i);
        if (i <= n) {
            int nums[7];
            for (int j = 0; j < 7; j++) {
                int num, duplicate;
                do {
                    duplicate = 0;
                    num = rand() % 69 + 1;
                    for (int k = 0; k < j; k++) {
                        if (nums[k] == num) {
                            duplicate = 1;
                            break;
                        }
                    }
                } while (duplicate);
                nums[j] = num;
            }

            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5 - j; k++) {
                    if (nums[k] > nums[k + 1]) {
                        int tmp = nums[k];
                        nums[k] = nums[k + 1];
                        nums[k + 1] = tmp;
                    }
                }
            }

            for (int j = 0; j < 7; j++) {
                fprintf(fp, " %02d", nums[j]);
            }
        } else {
            for (int j = 0; j < 7; j++) {
                fprintf(fp, " --");
            }
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    return 0;
}
