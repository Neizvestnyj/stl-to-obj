#include <iostream>
#include <math.h>

float old_progress = 0.0;

void progress(float current, float total, std::string text = "") {
    int barWidth = 70;
    float progress = current / total;
    progress = round(progress * 100) / 100;

    if (old_progress != progress) {
        old_progress = progress;
        std::cout << text << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) {
                std::cout << "=";
            }
            else if(i == pos) {
                std::cout << ">";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << "] " << int(progress * 100) << " %\r";
        std::cout.flush();
    }
}
