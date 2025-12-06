#include <Arduino.h>
#include "WaveShareDemo.h"
#include "Functions.h"

void setup()
{
  Wvshr_Init();

  // init screen
  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;  
  LCD_Init(Lcd_ScanDir, 200);
  LCD_Clear(LCD_BACKGROUND);

  // init touch - calibaration
  TP_Init();
  // TP_Calibration();

  // print gui of calculator to screen
  DrawGUI();

  Serial.println("Setup completed.");
}

// Global Variables
String equation = "";
String currentNumber = "";
float num1 = 0;
float num2 = 0;
char op = 0;

void loop()
{
  // Check touch screen get input
  TP_Scan(0);

  if (!(sTP_DEV.chStatus & TP_PRESSED))
    return;

  sTP_DEV.chStatus &= ~TP_PRESSED;

  // clear line of input / output (lambda)
  auto clearLine = [&]() {
    GUI_DrawRectangle(10, 290, 470, 315, LCD_BACKGROUND, DRAW_FULL, DOT_PIXEL_1X1);
  };

  // show equation (output)
  auto showEquation = [&]() {
    clearLine();
    GUI_DisString_EN(20, 295, equation.c_str(), &Font20, LCD_BACKGROUND, BLACK);
  };

  // Add char (lambda)
  auto addChar = [&](String c) {
    currentNumber += c;
    equation += c;
    showEquation();
  };

  // Check what get in the input
  if      (TP_InBox(20,  160, 120, 200)) { animateButtonPress(20,  160, 120, 200, "1"   ); addChar("1");  }  // 1 (Numbers)
  else if (TP_InBox(130, 160, 230, 200)) { animateButtonPress(130, 160, 230, 200, "2"   ); addChar("2");  }  // 2 (Numbers)
  else if (TP_InBox(240, 160, 340, 200)) { animateButtonPress(240, 160, 340, 200, "3"   ); addChar("3");  }  // 3 (Numbers)
  else if (TP_InBox(20,  90,  120, 130)) { animateButtonPress(20,  90,  120, 130, "4"   ); addChar("4");  }  // 4 (Numbers)
  else if (TP_InBox(130, 90,  230, 130)) { animateButtonPress(130, 90,  230, 130, "5"   ); addChar("5");  }  // 5 (Numbers)
  else if (TP_InBox(240, 90,  340, 130)) { animateButtonPress(240, 90,  340, 130, "6"   ); addChar("6");  }  // 6 (Numbers)
  else if (TP_InBox(20,  20,  120, 60 )) { animateButtonPress(20,  20,  120, 60,  "7"   ); addChar("7");  }  // 7 (Numbers)
  else if (TP_InBox(130, 20,  230, 60 )) { animateButtonPress(130, 20,  230, 60,  "8"   ); addChar("8");  }  // 8 (Numbers)
  else if (TP_InBox(240, 20,  340, 60 )) { animateButtonPress(240, 20,  340, 60,  "9"   ); addChar("9");  }  // 9 (Numbers)
  else if (TP_InBox(20,  230, 120, 270)) { animateButtonPress(20,  230, 120, 270, "0"   ); addChar("0");  }  // 0 (Numbers)
  else if (TP_InBox(130, 230, 230, 270)) { animateButtonPress(130, 230, 230, 270, "."   ); addChar(".");  }  // . (Dot)
  else if (TP_InBox(360, 150, 410, 210)) { animateButtonPress(360, 150, 410, 210, "+"   ); num1 = currentNumber.toFloat(); op = '+'; equation += " + ";   currentNumber = ""; showEquation(); } // Add + (Operation)
  else if (TP_InBox(420, 150, 470, 210)) { animateButtonPress(420, 150, 470, 210, "-"   ); num1 = currentNumber.toFloat(); op = '-'; equation += " - ";   currentNumber = ""; showEquation(); } // minus - (Operation)
  else if (TP_InBox(360, 80,  410, 140)) { animateButtonPress(360, 80,  410, 140, "*"   ); num1 = currentNumber.toFloat(); op = '*'; equation += " * ";   currentNumber = ""; showEquation(); } // multi * (Operation)
  else if (TP_InBox(420, 80,  470, 140)) { animateButtonPress(420, 80,  470, 140, "/"   ); num1 = currentNumber.toFloat(); op = '/'; equation += " / ";   currentNumber = ""; showEquation(); } // div / (Operation)
  else if (TP_InBox(360, 20,  410, 60 )) { animateButtonPress(360, 20,  410, 60,  "^"   ); num1 = currentNumber.toFloat(); op = '^'; equation += " ^ ";   currentNumber = ""; showEquation(); } // Power ^ (Operation)
  else if (TP_InBox(420, 20,  470, 60 )) { animateButtonPress(420, 20,  470, 60,  "sqrt"); num1 = currentNumber.toFloat(); op = 's'; equation += " sqrt"; currentNumber = ""; showEquation(); } // Square root sqrt
  else if (TP_InBox(360, 230, 410, 270)) { animateButtonPress(360, 230, 410, 270, "log2"); num1 = currentNumber.toFloat(); op = 'l'; equation += " log "; currentNumber = ""; showEquation(); } // Log base 2 log2
  else if (TP_InBox(420, 230, 470, 270)) { animateButtonPress(420, 230, 470, 270, "!"   ); num1 = currentNumber.toFloat(); op = '!'; equation += " ! ";   currentNumber = ""; showEquation(); } // Factorial !
  else if (TP_InBox(240, 230, 340, 270)) { 
    animateButtonPress(240, 230, 340, 270, "="   );              // Equals = 
    num2 = currentNumber.toFloat();
    float result = 0;

    if (op == '/' && num2 == 0) {                      // Check div by 0
      clearLine();
      GUI_DisString_EN(20, 295, "Error: Div by 0", &Font20, LCD_BACKGROUND, RED);
      delay(1500);

      // Clear data after wrong input
      equation = "";
      currentNumber = "";
      op = 0;
      clearLine();
      return;
    }

    switch (op) {                                           // Calculation
      case '+': result = num1 + num2;     break;
      case '-': result = num1 - num2;     break;
      case '*': result = num1 * num2;     break;
      case '/': result = num1 / num2;     break;
      case '^': result = pow(num1, num2); break;
      case 's': result = sqrt(num1);      break;
      case 'l': result = log2(num1);      break;
      case '!': {
        if (num1 < 0 || (int)num1 != num1) {
          clearLine();
          GUI_DisString_EN(20, 295, "Error: Invalid input for !", &Font20, LCD_BACKGROUND, RED);
          delay(1500);

          // Clear data after wrong input
          equation = "";
          currentNumber = "";
          op = 0;
          clearLine();
          return;
        }
        result = 1;
        for (int i = 1; i <= (int)num1; i++) 
          result *= i;
        break;
      }
    }

    equation += " = " + String(result);
    showEquation();

    // Clear data befor new input
    currentNumber = String(result);
    equation = currentNumber;
    op = 0;
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/