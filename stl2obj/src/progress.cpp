#include <iostream>
#include <math.h>

using namespace std;

float old_progress = 0.0;

void progress(float current, float total, string text = "") {
    int barWidth = 70;
    float progress = current / total;
    progress = round(progress * 100) / 100;

    if (old_progress != progress) {
        old_progress = progress;
        cout << text << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) {
                cout << "=";
            }
            else if(i == pos) {
                cout << ">";
            }
            else {
                cout << " ";
            }
        }
        cout << "] " << int(progress * 100) << " %\r";
        cout.flush();
    }
}
