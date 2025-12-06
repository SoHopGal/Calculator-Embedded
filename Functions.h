#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"

void DrawGUI();
bool TP_InBox(int x1, int y1, int x2, int y2);
void animateButtonPress(int x1, int y1, int x2, int y2, const char * value);