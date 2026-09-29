#include <stdio.h>

int main()
{
    int num;
    int answer;

    printf("Enter a number: ");
    scanf("%d", &num);

    answer = num * num * num;

    printf("Answer = %d", answer);

    return 0;
}