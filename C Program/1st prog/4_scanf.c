
#include <stdio.h>

int main()
{
    char name[25];
    int age;

    int hindi, eng, mth, sst, pys, since;
    int total;
    float percentage;

    // Name
    printf("Enter your name: ");
    scanf("%s", name);

    printf("Your name is: %s\n", name);

    // Age
    printf("Enter your age: ");
    scanf("%d", &age);

    printf("Your age is: %d\n", age);

    // Hindi
    printf("\nEnter Hindi marks: ");
    scanf("%d", &hindi);

    // English
    printf("Enter English marks: ");
    scanf("%d", &eng);

    // Mathematics
    printf("Enter Mathematics marks: ");
    scanf("%d", &mth);

    // Social Science
    printf("Enter Social Science marks: ");
    scanf("%d", &sst);

    // Physics
    printf("Enter Physics marks: ");
    scanf("%d", &pys);

    // Since / Science
    printf("Enter Science marks: ");
    scanf("%d", &since);

    // Total marks
    total = hindi + eng + mth + sst + pys + since;

    // Percentage
    percentage = total / 6.0;

    // Result
    printf("\n========== RESULT ==========\n");

    printf("Name       : %s\n", name);
    printf("Age        : %d\n", age);

    printf("Hindi      : %d\n", hindi);
    printf("English    : %d\n", eng);
    printf("Mathematics: %d\n", mth);
    printf("Social Sci.: %d\n", sst);
    printf("Physics    : %d\n", pys);
    printf("Science    : %d\n", since);

    printf("----------------------------\n");
    printf("Total      : %d / 600\n", total);
    printf("Percentage : %.2f%%\n", percentage);

    return 0;
}