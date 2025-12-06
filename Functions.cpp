#include <Arduino.h>
#include "Functions.h"
#include "WaveShareDemo.h"
#include "LCD_GUI.h"
#include "Debug.h"

// Draw the GUI of calculator
void DrawGUI() {
  // first line
  GUI_DrawRectangle(20,  20, 120, 60, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(130, 20, 230, 60, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(240, 20, 340, 60, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(360, 20, 410, 60, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);
  GUI_DrawRectangle(420, 20, 470, 60, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);

  GUI_DisNum      (60,  30, 7,      &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (170, 30, 8,      &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (280, 30, 9,      &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(380, 35, "^",    &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(425, 35, "sqrt", &Font16, LCD_BACKGROUND, WHITE);

  // second line
  GUI_DrawRectangle(20,  90, 120, 130, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(130, 90, 230, 130, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(240, 90, 340, 130, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(360, 80, 410, 140, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);
  GUI_DrawRectangle(420, 80, 470, 140, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);

  GUI_DisNum      (60,  100, 4,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (170, 100, 5,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (280, 100, 6,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(380, 100, "*", &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(440, 100, "/", &Font24, LCD_BACKGROUND, WHITE);

  // third line
  GUI_DrawRectangle(20,  160, 120, 200, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(130, 160, 230, 200, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(240, 160, 340, 200, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(360, 150, 410, 210, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);
  GUI_DrawRectangle(420, 150, 470, 210, BLUE, DRAW_FULL,  DOT_PIXEL_3X3);
  
  GUI_DisNum      (60,  170, 1,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (170, 170, 2,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisNum      (280, 170, 3,   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(380, 170, "+", &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(440, 170, "-", &Font24, LCD_BACKGROUND, WHITE);

  // forth line
  GUI_DrawRectangle(20,  230, 120, 270, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(130, 230, 230, 270, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(240, 230, 340, 270, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(360, 230, 410, 270, BLUE,  DRAW_FULL, DOT_PIXEL_3X3);
  GUI_DrawRectangle(420, 230, 470, 270, BLUE,  DRAW_FULL, DOT_PIXEL_3X3);

  GUI_DisString_EN(60,  240, "0",   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(170, 240, ".",   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(280, 240, "=",   &Font24, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(367, 245, "log2",&Font16, LCD_BACKGROUND, WHITE);
  GUI_DisString_EN(440, 240, "!",   &Font24, LCD_BACKGROUND, WHITE);
  
  // fifth line
  GUI_DrawRectangle(10, 280, 350, 315, RED, DRAW_EMPTY, DOT_PIXEL_3X3);  
}

// Check location of touch
bool TP_InBox(int x1, int y1, int x2, int y2) {
    return (sTP_Draw.Xpoint > x1 && sTP_Draw.Xpoint < x2 && sTP_Draw.Ypoint > y1 && sTP_Draw.Ypoint < y2);
}

void animateButtonPress(int x1, int y1, int x2, int y2, const char * value) {
   if ( value == "1" || value == "2" || value == "3" ||
        value == "4" || value == "5" || value == "6" ||
        value == "7" || value == "8" || value == "9" || 
        value == "." || value == "=" || value == "0"   ){
        GUI_DrawRectangle(x1, y1, x2, y2, WHITE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DrawRectangle(x1, y1, x2, y2, BLACK, DRAW_EMPTY, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 40, y1 + 10, value, &Font24, LCD_BACKGROUND, BLACK);
        delay(500);
        GUI_DrawRectangle(x1, y1, x2, y2, BLACK, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 40, y1 + 10, value, &Font24, LCD_BACKGROUND, WHITE);
        return;
    } else if (value == "+" || value == "-" || value == "*" || value == "/") {
        GUI_DrawRectangle(x1, y1, x2, y2, WHITE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_EMPTY, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 20, y1 + 20, value, &Font24, LCD_BACKGROUND, BLUE);
        delay(500);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 20, y1 + 20, value, &Font24, LCD_BACKGROUND, WHITE);
        return;

    } else if (value == "sqrt" || value == "log2") {
        GUI_DrawRectangle(x1, y1, x2, y2, WHITE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_EMPTY, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 5, y1 + 15, value, &Font16, LCD_BACKGROUND, BLUE);
        delay(500);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 5, y1 + 15, value, &Font16, LCD_BACKGROUND, WHITE);
        return;
    } else if (value == "^" || value == "!") {
        GUI_DrawRectangle(x1, y1, x2, y2, WHITE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_EMPTY, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 20, y1 + 15, value, &Font24, LCD_BACKGROUND, BLUE);
        delay(500);
        GUI_DrawRectangle(x1, y1, x2, y2, BLUE, DRAW_FULL, DOT_PIXEL_3X3);
        GUI_DisString_EN(x1 + 20, y1 + 15, value, &Font24, LCD_BACKGROUND, WHITE);
        return;
    }
}