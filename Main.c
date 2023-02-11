/*
  * - Turn LED on and off.
  # - Cycle through default colours.
  D - Cycle through Custom Colours.
  C - Cycle through RGB values.
  A - Increase RGB values.
  B - Decrease RGB values.
  1-9 - Store that RGB value. 
*/

//==================================================\\

// LiquidCrystal - Version: Latest
#include <LiquidCrystal.h>
// Keypad - Version: Latest
#include <Keypad.h>

//==================================================\\

#define led_RedPin 9
#define led_GreenPin 10
#define led_BluePin 11
#define lcd_ContrastPin 8

#define rows 4
#define cols 4

//==================================================\\

int CycleRGB = 0;

int DefaultColourTracker = 0;
String rgb_DefaultColours[7] = {"r", "o", "y", "g", "a", "b", "w"};

int rgb_Value[3] = {255, 255, 255};

int KeyNum;

int CycleCustomRGB = 0;

int rgb_CustomColours[9][3] = 
{
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

byte PowerButton[8] = {
  B00000,
  B00100,
  B01110,
  B10101,
  B10001,
  B10001,
  B01110,
  B00000
};

char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte RowPins[rows] = {12, 13, A5, A4};
byte ColPins[cols] = {A3, A2, A1, A0};

Keypad keypad = Keypad(makeKeymap(keys), RowPins, ColPins, 4, 4);

boolean ToggleCircuit = false;

int lcd_Menus = 0;
/*
  -1 = Off Off
  0 = Off
  1 = On
  2 = Default
  3 = Default Colours
  4 = RGB Values
  5 = Value Stored
*/

//==================================================\\

void SetupPINS() {
  pinMode(led_BluePin, OUTPUT);
  pinMode(led_RedPin, OUTPUT);
  pinMode(led_GreenPin, OUTPUT);
}

void rgb(int red, int green, int blue) {
  analogWrite(led_RedPin, red);
  analogWrite(led_GreenPin, green);
  analogWrite(led_BluePin, blue);
}

void Toggle()
{
  if (ToggleCircuit)
  {
    rgb(0, 0, 0);
    ToggleCircuit = false;
    lcd_Menus = 0;
  }
  else if (ToggleCircuit == false)
  {
    rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    ToggleCircuit = true;
    lcd_Menus = 1;
  }
}

void lcdMenus(int menu)
{
  if (menu == -1)
  {
    lcd.noDisplay();
    analogWrite(lcd_ContrastPin, 0);
  }
  else if (menu == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("    LED Off    ");
    lcd.setCursor(0, 1);
    lcd.print("    Press ");
    lcd.setCursor(10, 1);
    lcd.write(2);
    lcd.setCursor(11, 1);
    lcd.print("    ");
    delay(2000);
    lcd_Menus = -1;
  }
  else if (menu == 1)
  {
    lcd.display();
    analogWrite(lcd_ContrastPin, 255);
    lcd.setCursor(0, 0);
    lcd.print("    LED On      ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(1000);
    lcd_Menus = 2;
  }
  else if ((menu == 2) || (menu == 2 && CycleRGB == 0) || (menu == 2 && CycleCustomRGB == 9))
  {
    lcd.setCursor(0, 0);
    lcd.print(" Current Values ");
    lcd.setCursor(0, 1);
    lcd.print("RGB= ");
    lcd.print(rgb_Value[0]);
    lcd.print(",");
    lcd.print(rgb_Value[1]);
    lcd.print(",");
    lcd.print(rgb_Value[2]);
    lcd.print("     ");
    rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
  }
  else if (menu == 3 && CycleRGB == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("(-/+)        Red");
    lcd.setCursor(0, 1);
    lcd.print("Value = ");
    lcd.print(rgb_Value[0]);
  }
  else if (menu == 3 && CycleRGB == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("(-/+)      Green");
    lcd.setCursor(0, 1);
    lcd.print("Value = ");
    lcd.print(rgb_Value[1]);
  }
  else if (menu == 3 && CycleRGB == 3)
  {
    lcd.setCursor(0, 0);
    lcd.print("(-/+)       Blue");
    lcd.setCursor(0, 1);
    lcd.print("Value = ");
    lcd.print(rgb_Value[2]);
  }
  else if (menu == 4)
  {
    lcd.setCursor(0, 0);
    lcd.print("Slot: ");
    lcd.print(CycleCustomRGB + 1);
    lcd.setCursor(0,1);
    lcd.print("RGB= ");
    lcd.print(rgb_CustomColours[CycleCustomRGB][0]);
    lcd.print(",");
    lcd.print(rgb_CustomColours[CycleCustomRGB][1]);
    lcd.print(",");
    lcd.print(rgb_CustomColours[CycleCustomRGB][2]);
    lcd.print("     ");
    rgb(rgb_CustomColours[CycleCustomRGB][0], rgb_CustomColours[CycleCustomRGB][1], rgb_CustomColours[CycleCustomRGB][2]);
  }
  else if (menu == 5)
  {
    lcd.setCursor(0, 0);
    lcd.print("  Value Stored  ");
    lcd.setCursor(0, 1);
    lcd.print("In Slot: ");
    lcd.print(KeyNum);
    delay(2000);
    lcd_Menus = 2;
  }
}

void SetLED()
{
  if (rgb_DefaultColours[DefaultColourTracker].equals("w"))
  {
    rgb_Value[0] = 255;
    rgb_Value[1] = 255;
    rgb_Value[2] = 255;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("r"))
  {
    rgb_Value[0] = 255;
    rgb_Value[1] = 0;
    rgb_Value[2] = 0;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("g"))
  {
    rgb_Value[0] = 0;
    rgb_Value[1] = 255;
    rgb_Value[2] = 0;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("b"))
  {
    rgb_Value[0] = 0;
    rgb_Value[1] = 0;
    rgb_Value[2] = 255;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("o"))
  {
    rgb_Value[0] = 255;
    rgb_Value[1] = 69;
    rgb_Value[2] = 0;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("y"))
  {
    rgb_Value[0] = 255;
    rgb_Value[1] = 255;
    rgb_Value[2] = 0;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("a"))
  {
    rgb_Value[0] = 0;
    rgb_Value[1] = 255;
    rgb_Value[2] = 255;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }

  else if (rgb_DefaultColours[DefaultColourTracker].equals("p"))
  {
    rgb_Value[0] = 255;
    rgb_Value[1] = 0;
    rgb_Value[2] = 255;

    if (ToggleCircuit)
    {
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }
}

void In_DefaultColourTracker()
{
  if (ToggleCircuit)
  {
    DefaultColourTracker++;
    if (DefaultColourTracker > 6 || DefaultColourTracker < 0)
      DefaultColourTracker = 0;
  }
}

void CycleRGBColour()
{
  if (ToggleCircuit)
  {
    CycleRGB++;
    if (CycleRGB > 3 || CycleRGB < 0)
      CycleRGB = 0;
    if (CycleRGB == 0)
      lcd_Menus = 2;
  }
}

void CycleCustomRGBColour()
{
  if (ToggleCircuit)
  {
    CycleCustomRGB++;
    if (CycleCustomRGB > 9 || CycleCustomRGB < 0)
      CycleCustomRGB = 0;
    if (CycleCustomRGB == 9)
      lcd_Menus = 2;
  }
}

void ChangeValueN()
{
  if (ToggleCircuit)
  {
    if (CycleRGB == 1)
    {
      rgb_Value[0] = rgb_Value[0] - 10;
      if (rgb_Value[0] < 0)
      {
        rgb_Value[0] = 0;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }

    else if (CycleRGB == 2)
    {
      rgb_Value[1] = rgb_Value[1] - 10;
      if (rgb_Value[1] < 0)
      {
        rgb_Value[1] = 0;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }

    else if (CycleRGB == 3)
    {
      rgb_Value[2] = rgb_Value[2] - 10;
      if (rgb_Value[2] < 0)
      {
        rgb_Value[2] = 0;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }
}

void ChangeValueP()
{
  if (ToggleCircuit)
  {
    if (CycleRGB == 1)
    {
      rgb_Value[0] = rgb_Value[0] + 10;
      if (rgb_Value[0] > 255)
      {
        rgb_Value[0] = 255;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }

    else if (CycleRGB == 2)
    {
      rgb_Value[1] = rgb_Value[1] + 10;
      if (rgb_Value[1] > 255)
      {
        rgb_Value[1] = 255;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }

    else if (CycleRGB == 3)
    {
      rgb_Value[2] = rgb_Value[2] + 10;
      if (rgb_Value[2] > 255)
      {
        rgb_Value[2] = 255;
      }
      rgb(rgb_Value[0], rgb_Value[1], rgb_Value[2]);
    }
  }
}

void StoreColour(int slot)
{
  if (slot == 1)
  {
    rgb_CustomColours[0][0] = rgb_Value[0];
    rgb_CustomColours[0][1] = rgb_Value[1];
    rgb_CustomColours[0][2] = rgb_Value[2];
  }
  else if (slot == 2)
  {
    rgb_CustomColours[1][0] = rgb_Value[0];
    rgb_CustomColours[1][1] = rgb_Value[1];
    rgb_CustomColours[1][2] = rgb_Value[2];
  }
  else if (slot == 3)
  {
    rgb_CustomColours[2][0] = rgb_Value[0];
    rgb_CustomColours[2][1] = rgb_Value[1];
    rgb_CustomColours[2][2] = rgb_Value[2];
  }
  else if (slot == 4)
  {
    rgb_CustomColours[3][0] = rgb_Value[0];
    rgb_CustomColours[3][1] = rgb_Value[1];
    rgb_CustomColours[3][2] = rgb_Value[2];
  }
  else if (slot == 5)
  {
    rgb_CustomColours[4][0] = rgb_Value[0];
    rgb_CustomColours[4][1] = rgb_Value[1];
    rgb_CustomColours[4][2] = rgb_Value[2];
  }
  else if (slot == 6)
  {
    rgb_CustomColours[5][0] = rgb_Value[0];
    rgb_CustomColours[5][1] = rgb_Value[1];
    rgb_CustomColours[5][2] = rgb_Value[2];
  }
  else if (slot == 7)
  {
    rgb_CustomColours[6][0] = rgb_Value[0];
    rgb_CustomColours[6][1] = rgb_Value[1];
    rgb_CustomColours[6][2] = rgb_Value[2];
  }
  else if (slot == 8)
  {
    rgb_CustomColours[7][0] = rgb_Value[0];
    rgb_CustomColours[7][1] = rgb_Value[1];
    rgb_CustomColours[7][2] = rgb_Value[2];
  }
  else if (slot == 9)
  {
    rgb_CustomColours[8][0] = rgb_Value[0];
    rgb_CustomColours[8][1] = rgb_Value[1];
    rgb_CustomColours[8][2] = rgb_Value[2];
  }
}

void CheckKey()
{
  char key = keypad.getKey();

  switch (key)
  {
    case '*':
      lcd.clear();
      Toggle();
      break;
    case '#':
      lcd.clear();
      SetLED();
      In_DefaultColourTracker();
      break;
    case 'D':
      lcd.clear();
      lcd_Menus = 4;
      CycleCustomRGBColour();
      break;
    case 'C':
      lcd.clear();
      lcd_Menus = 3;
      CycleRGBColour();
      break;
    case 'A':
      lcd.clear();
      ChangeValueP();
      break;
    case 'B':
      lcd.clear();
      ChangeValueN();
      break;
    case '1':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 1;
      StoreColour(1);
      break;
    case '2':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 2;
      StoreColour(2);
      break;
    case '3':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 3;
      StoreColour(3);
      break;
    case '4':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 4;
      StoreColour(4);
      break;
    case '5':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 5;
      StoreColour(5);
      break;
    case '6':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 6;
      StoreColour(6);
      break;
    case '7':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 7;
      StoreColour(7);
      break;
    case '8':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 8;
      StoreColour(8);
      break;
    case '9':
      lcd.clear();
      lcd_Menus = 5;
      KeyNum = 9;
      StoreColour(9);
      break;
    default:
      Serial.println("Unknown Key!\nKey: ");
      Serial.print(key);
  }
}

//==================================================\\

void setup()
{
  Serial.begin(9600);
  Serial.println("Serial has started!");

  SetupPINS();

  analogWrite(lcd_ContrastPin, 255);
  lcd.begin(16, 2);
  lcd.createChar(2, PowerButton);
}

void loop()
{
  lcdMenus(lcd_Menus);
  CheckKey();
}

//==================================================\\
