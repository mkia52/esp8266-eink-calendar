#include "E_ink.h"
#include <Fonts/TomThumb.h>

void drawCalender()
{
    // Serial.begin(115200);
    display.init(115200);
    display.setRotation(1);
    display.setFullWindow();

    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setRotation(3);

        // - Table Geometry Settings -
        const int startX = 7;
        const int startY = 1;
        const int tableWidth = 296 - 2 * startX;
        const int tableHeight = 128 - 2 * startY;

        const int cellWidth1 = 30;
        const int cellWidth_n = 36;
        const int cellHeight = 18;

        const int x2 = 9;
        const int y2 = 5;

        for (int i = 1; i < 7; i++)
        {
            int lineY = startY + (i * cellHeight);
            display.drawFastHLine(startX, lineY, tableWidth, GxEPD_BLACK);
            /* - - - */
        }

        display.drawFastVLine(startX + cellWidth1, startY, tableHeight - 1, GxEPD_BLACK);
        for (int i = 1; i < 7; i++)
        {
            int lineX = startX + cellWidth1 + i * cellWidth_n;
            display.drawFastVLine(lineX, startY, tableWidth, GxEPD_BLACK);
            /* | | | */
        }

        

        display.fillRect(startX + cellWidth1 + 1, startY + 1, tableWidth - cellWidth1 - 1, cellHeight - 1, GxEPD_RED);
        display.fillRect(startX + 1, startY + cellHeight, cellWidth1, tableHeight - (startY + cellHeight), GxEPD_BLACK);
        display.drawRect(startX, startY, tableWidth, tableHeight, GxEPD_BLACK);

        const char *Weekdays[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
        const char *Week_no[6] = {"W1", "W2", "W3", "W4", "W5", "W6"};
        const char *Month[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
        const int days_mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int wday = timeinfo.tm_wday;
        int mday = timeinfo.tm_mday;
        int W1_day = mday;
        int day_1 = wday;

        display.setCursor(startX + x2 - 3, startY + y2);
        display.setTextColor(GxEPD_BLACK, GxEPD_WHITE);
        display.setFont(&TomThumb);
        display.printf("%s/%d", Month[timeinfo.tm_mon], timeinfo.tm_mon);

        display.setFont(NULL);

        while (W1_day > 7)
        {
            W1_day -= 7;
        }

        for (int i = 1; i < W1_day; i++)
        {
            day_1 -= 1;
            if (day_1 < 0)
            {
                day_1 = 6;
            }
        }

        display.setTextColor(GxEPD_WHITE, GxEPD_RED);
        for (int i = 1; i < 8; i++)
        {
            int char_x = startX + cellWidth1 + 27 * (i - 1) + i * x2; // In theory, this should be int char_x = startX + cellWidth1 + cellWidth_n * (i - 1) + i * x2
            display.setCursor(char_x, startY + y2 + 1);
            display.print(Weekdays[i - 1]);
        }

        int print_day = 1;

        for (int i = 1; i < 7; i++)
        {
            display.setTextColor(GxEPD_WHITE, GxEPD_BLACK);
            int char_y = startY + cellHeight * i + y2;
            display.setCursor(startX + x2, char_y + 1);
            display.print(Week_no[i - 1]);

            for (int j = 1; j < 8; j++)
            {
                if (((print_day == 1) && ((j - 1) == day_1)) || ((print_day > 1) && (print_day <= days_mon[timeinfo.tm_mon]))) // Either x should be within 1 and last mday, or j should correspond to the first weekday of that monday ranging from indexes of 0-6.
                {
                    int char_x = startX + cellWidth1 + 27 * (j - 1) + j * x2; // In theory, this should be int char_x = startX + cellWidth1 + cellWidth_n * (i - 1) + i * x2
                    if (print_day == timeinfo.tm_mday)
                    {
                        display.fillRect(char_x - x2 + 1, char_y - y2 + 1, cellWidth_n - 1, cellHeight - 1, GxEPD_RED);
                        display.setTextColor(GxEPD_WHITE, GxEPD_RED);
                    }
                    else
                    {
                        display.setTextColor(GxEPD_BLACK, GxEPD_WHITE);
                    }
                    display.setCursor(char_x, char_y);
                    display.print(print_day);
                    print_day++;
                }
            }
        }

    } while (display.nextPage());
}
