#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

void alarmSound() {
    printf("\n\a");
    printf("====================================\n");
    printf("       ALARM! BOOK NAHI PADHI!      \n");
    printf("       📚 GET BACK TO READING!      \n");
    printf("====================================\n");

#ifdef _WIN32
    Beep(1000, 1000);
    Beep(1200, 1000);
    Beep(1000, 1000);
#endif
}

int main() {

    int minutes;
    char answer;

    printf("====================================\n");
    printf("       BOOK READING TRACKER 📚      \n");
    printf("====================================\n\n");

    printf("Kitne minutes padhna hai? ");
    scanf("%d", &minutes);

    printf("\nReading session started!\n");
    printf("Phone side me rakho aur book padho. 📖\n\n");

    for (int i = 1; i <= minutes; i++) {

#ifdef _WIN32
        Sleep(60000);   // 1 minute
#else
        sleep(60);
#endif

        printf("\n%d minute complete.\n", i);
        printf("Kya tum abhi bhi book padh rahe ho? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'n' || answer == 'N') {
            alarmSound();
            return 0;
        }
    }

    printf("\n====================================\n");
    printf("       SESSION COMPLETE! 🎉         \n");
    printf("       Great job! 📚🔥               \n");
    printf("====================================\n");

    return 0;
}