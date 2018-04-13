#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int num;
    int *a;
    int count = 0;
    int flag = 0;
    int i, temp, index, start = 0;
    scanf("%d", &num);
    a = (int *)malloc(num * sizeof(int));
    for (i = 0; i < num; i++)
    {
        //int index;
        scanf("%d", &index);
        a[index] = i;
    }
    while (1)
    {
        while (a[0] != 0)
        {
            temp = a[0];
            a[0] = a[a[0]];
            a[temp] = temp;
            flag++;
        }
        for (i = start; i < num; i++)
            if (a[i] != i)
                break;
        if (i == num)
            break;
        start = i;
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        flag++;
    }
    printf("%d\n", flag);
    return 0;
}