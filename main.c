#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int hour; // 时
    int min;  // 分
    int sec;  // 秒
} Time_s;     // 时间结构体

/**
 * @brief 时间转化
 * @note  将正常的时间转化为运行时间
 *
 * @param hour
 * @param min
 * @param sec
 * @return int
 */
int Time_Trans(int hour, int min, int sec)
{
    return (hour - 7) * 3600 + min * 60 + sec;
}

/**
 * @brief 反向时间转化
 * @note  将运行时间转化回普通时间
 *
 * @param time
 * @return Time_s
 */
Time_s Time_TransBack(int time)
{
    Time_s Time = {0, 0, 0};
    Time.hour = time / 3600 + 7;
    time %= 3600;
    Time.min = time / 60;
    time %= 60;
    Time.sec = time;
    return Time;
}

typedef struct
{
    int time;
    char *name;
} Example_s;

void bubble_sort(Example_s arr[], int n)
{
    int i, j;
    Example_s temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].time > arr[j + 1].time)
            {
                // 交换相邻的两个元素
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void swap(Example_s *a, Example_s *b)
{
    Example_s temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Example_s arr[], int low, int high)
{
    Example_s pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].time < pivot.time)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(Example_s arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

int main(void)
{
    char names[100][51]; // 名称
    Example_s example[54001];
    int example_num; // 要生成的数量
    int food_num;    // 食物、套餐总数
    FILE *fp = fopen("input.txt", "w");
    FILE *dict = fopen("dict.dic", "r");

    Time_s TimeBeginStruct;
    Time_s TimeEndStruct;

    int time_begin, time_end;

    printf("请输入样例时间下限(格式h m s): ");
    scanf("%d%d%d", &TimeBeginStruct.hour, &TimeBeginStruct.min, &TimeBeginStruct.sec);
    getchar();
    printf("请输入样例时间上限(格式h m s): ");
    scanf("%d%d%d", &TimeEndStruct.hour, &TimeEndStruct.min, &TimeEndStruct.sec);
    getchar();

    time_begin = Time_Trans(TimeBeginStruct.hour, TimeBeginStruct.min, TimeBeginStruct.sec);
    time_end = Time_Trans(TimeEndStruct.hour, TimeEndStruct.min, TimeEndStruct.sec);

    printf("请输入要生成的测试样例数量:");
    scanf("%d", &example_num);
    for (food_num = 0; food_num < 100; food_num++)
    {
        fscanf(dict, "%s", names[food_num]);
        if (strcmp(names[food_num], "-1") == 0)
        {
            food_num--;
            break;
        }
    }

    // 设置随机数种子
    srand(time(NULL));

    // 创建一个数组来存储已经生成的随机数
    unsigned char random_numbers[54002] = {0};

    // 生成example_num个不重复的随机数
    int count = 0;
    while (count < example_num)
    {
        int random_num = rand() % time_end;
        if (random_numbers[random_num] == 0 && random_num >= time_begin)
        {
            random_numbers[random_num] = 1;
            example[count].time = random_num;
            random_num = rand() % (food_num + 1);
            example[count].name = names[random_num];
            count++;
        }
    }

    bubble_sort(example, example_num);

    fprintf(fp, "%d\n", example_num);
    Time_s t;

    for (int i = 0; i < example_num; i++)
    {
        t = Time_TransBack(example[i].time);
        fprintf(fp, "%02d:%02d:%02d %s\n", t.hour, t.min, t.sec, example[i].name);
        printf("%02d:%02d:%02d %s\n", t.hour, t.min, t.sec, example[i].name);
    }

    fclose(fp);

    return 0;
}