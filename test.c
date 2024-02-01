#include <stdio.h>
#include <stdint.h>
#include <time.h>

int main() {
    uint32_t yourUint32TimeValue = 4218862437;
    time_t convertedTime = (time_t)yourUint32TimeValue;

    struct tm *timeInfo;
    char formattedTime[20];  // Assuming you want the format "%Y-%m-%d %H:%M:%S"

    timeInfo = localtime(&convertedTime);
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", timeInfo);

    printf("Formatted time: %s\n", formattedTime);

    return 0;
}
