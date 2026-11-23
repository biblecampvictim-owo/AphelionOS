#include "initgraphics.h"
#include "drawing.h"
void g_rectangle(void){
    for (int y = 30; y < 160; y++) { 
        for (int x = 60; x < 290; x++) {
            draw_pixels(x, y, -1);

        }
    }
}

void g_rectangleoutline(void) {
    for (int y = 50; y < 150; y++) {
        for (int x = 50; x < 270; x++) {

            if (x == 50 || x == 269 || y == 50 || y == 149) {
                draw_pixels(x, y, 5);
            }
        }
    }
}

void g_largewhitecircle(void) {
    int centerX = 160;
    int centerY = 100;
    int radius = 50;

    for (int y = centerY - radius; y < centerY + radius; y++) {
        for (int x = centerX - radius; x < centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            if (dx * dx + dy * dy <= radius * radius) {
                draw_pixels(x, y, 7); 
            }
        }
    }
}
//will be a option (eventually)
void g_oval(void) {

}
//simple early implementation
void g_circleoutline(void) {
    int centerX = 180;
    int centerY = 150;
    int radius = 10;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}

void g_circleoutline1(void) {
    int centerX = 130;
    int centerY = 120;
    int radius = 10;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}
// + (x) = r 
// + (y) = u
void g_circleoutline2(void) {
    int centerX = 200;
    int centerY = 75;
    int radius = 20;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}

void g_circleoutline3(void) {
    int centerX = 135;
    int centerY = 60;
    int radius = 10;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}

void g_circleoutline4(void) {
    int centerX = 175;
    int centerY = 110;
    int radius = 5;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}

void g_circleoutline5(void) {
    int centerX = 140;
    int centerY = 90;
    int radius = 5;

    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            int distance = dx * dx + dy * dy;

            if (distance >= (radius - 1) * (radius - 1) &&
                distance <= (radius + 1) * (radius + 1)) {
                draw_pixels(x, y, 0);
            }
        }
    }
}

void g_stars(void) {
    int centerX = 150;
    int centerY = 120;
    int radius = 2;

    for (int y = centerY - radius; y < centerY + radius; y++) {
        for (int x = centerX - radius; x < centerX + radius; x++) {

            int dx = x - centerX;
            int dy = y - centerY;

            if (dx * dx + dy * dy <= radius * radius) {
            }
        }
    }
}

void g_triangle(void) {
    int topX = 160;
    int topY = 50;

    int leftX = 100;
    int rightX = 220;
    int bottomY = 150;

    for (int y = topY; y <= bottomY; y++) {
        for (int x = leftX; x <= rightX; x++) {

            int leftEdge = topX - (topX - leftX) * (y - topY) / (bottomY - topY);
            int rightEdge = topX + (rightX - topX) * (y - topY) / (bottomY - topY);

            if (x >= leftEdge && x <= rightEdge) {
                draw_pixels(x, y, 8);
            }
        }
    }
}

void g_triangleoutline(void) {
    int topX = 160;
    int topY = 50;

    int leftX = 100;
    int rightX = 220;
    int bottomY = 150;

    for (int y = topY; y <= bottomY; y++) {
        int leftEdge = topX - (topX - leftX) * (y - topY) / (bottomY - topY);
        int rightEdge = topX + (rightX - topX) * (y - topY) / (bottomY - topY);

        draw_pixels(leftEdge, y, 10);
        draw_pixels(rightEdge, y, 10);
    }

    for (int x = leftX; x <= rightX; x++) {
        draw_pixels(x, bottomY, 10);
    }
}