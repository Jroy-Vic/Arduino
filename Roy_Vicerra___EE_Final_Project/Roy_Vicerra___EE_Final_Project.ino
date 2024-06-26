#include <LiquidCrystal.h>
#include <HCSR04.h>
#include <Keypad.h>

const int rs=12, en=11, d4=5, d5=4, d6 = 3, d7 = 2;
const int rs2=53, en2=52, d42=51, d52=50, d62=49, d72=48;
const int analogPin=A0;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
LiquidCrystal lcd2(rs2,en2,d42,d52,d62,d72);
HCSR04 hc(10,9);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {33,32,31,30};
byte colPins[COLS] = {37,36,35,34};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int Shrts=0;
int Pnts=0;
int Undwr=0;
int Scks=0;

int GreenLED=38;
int YellowLED=39;
int RedLED=40;

void setup()
{
  lcd.begin(16,2);
  lcd2.begin(16,2);
  Serial.begin(9600);
  pinMode(GreenLED,OUTPUT);
  pinMode(YellowLED,OUTPUT);
  pinMode(RedLED,OUTPUT);
}

void loop()
{
  Serial.println(hc.dist());
  delay(100);
  lcd2.setCursor(0,0);
  lcd2.print("Shrts:0");
  lcd2.setCursor(9,0);
  lcd2.print("Pnts:0");
  lcd2.setCursor(0,1);
  lcd2.print("Undwr:0");
  lcd2.setCursor(9,1);
  lcd2.print("Scks:0");

  while(hc.dist()<=60 && hc.dist()>0)
  {
    Load();
    Serial.println(hc.dist());
    
    delay(125);


    char key = keypad.getKey();

    if (key)
    {
      if(key=='A')
      {
        lcd2.setCursor(6,0);
        lcd2.print("??");
        Shirts();
      }
    
      if(key=='B')
      {
        lcd2.setCursor(14,0);
        lcd2.print("??");
        Pants();
      }

      if(key=='C')
      {
        lcd2.setCursor(6,1);
        lcd2.print("??");
        Underwear();
      }

      if(key=='D')
      {
        lcd2.setCursor(14,1);
        lcd2.print("??");
        Socks();
      }

      if(key=='0')
      {
        lcd2.setCursor(0,0);
        lcd2.print("Shrts:0 ");
        lcd2.setCursor(9,0);
        lcd2.print("Pnts:0 ");
        lcd2.setCursor(0,1);
        lcd2.print("Undwr:0 ");
        lcd2.setCursor(9,1);
        lcd2.print("Scks:0 ");

        Shrts=0;
        Pnts=0;
        Undwr=0;
        Scks=0;

      }
    }
  }

  lcd.setCursor(0,0);
  lcd.print("NOT IN USE          ");
  lcd.setCursor(0,1);
  lcd.print("Load: 0%           ");


 
  
  

}

void Load()
{
  int loadCap=((65.5-hc.dist())/65.5)*100;
  lcd.setCursor(0,0);
  lcd.print("IN USE           ");
  lcd.setCursor(0,1);
  lcd.print("Load Cap.:         ");
  lcd.setCursor(11,1);
  lcd.print(loadCap);
  lcd.setCursor(14,1);
  lcd.print("%");

  if(loadCap<50)
  {
    digitalWrite(GreenLED,HIGH);
  }

  if(loadCap>50 && loadCap<90)
  {
    digitalWrite(YellowLED,HIGH);
  }

  if(loadCap>=90)
  {
  lcd.setCursor(11,1);
  lcd.print("FULL    ");
  digitalWrite(RedLED,HIGH);
  }

  else
  {
    digitalWrite(RedLED,LOW);
    digitalWrite(YellowLED,LOW);
    digitalWrite(GreenLED,HIGH);
  }
}

void Shirts()
{
  char key = keypad.getKey();

  while(key == NO_KEY)
  {
    key = keypad.getKey();

    if(key=='#')
          {
            Shrts=Shrts+1;
            lcd2.setCursor(6,0);
            lcd2.print(Shrts);

            if(Shrts<10 && Shrts>=0)
            {
               lcd2.setCursor(7,0);
               lcd2.print("  ");
            }
           
          }
    
  if(key=='*')
         {
          Shrts=Shrts-1;
          lcd2.setCursor(6,0);
          lcd2.print(Shrts);
         

          if(Shrts<10 && Shrts>=0)
            {
               lcd2.setCursor(7,0);
               lcd2.print("  ");
            }
         }

  if(key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9')
  {
    Shrts=key;
    lcd2.setCursor(6,0);
    lcd2.print(Shrts);
  }

  }

}

void Pants()
{
  char key = keypad.getKey();

  while(key == NO_KEY)
  {
    key = keypad.getKey();

    if(key=='#')
          {
            Pnts=Pnts+1;
            lcd2.setCursor(14,0);
            lcd2.print(Pnts);

            if(Pnts<10 && Pnts>=0)
            {
               lcd2.setCursor(15,0);
               lcd2.print("  ");
            }
           
          }
    
  if(key=='*')
         {
          Pnts=Pnts-1;
          lcd2.setCursor(14,0);
          lcd2.print(Pnts);
         

          if(Pnts<10 && Pnts>=0)
            {
               lcd2.setCursor(15,0);
               lcd2.print("  ");
            }
         }

  if(key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9')
  {
    Pnts=key;
    lcd2.setCursor(14,0);
    lcd2.print(Pnts);
  }
  }

}

void Underwear()
{
  char key = keypad.getKey();

  while(key == NO_KEY)
  {
    key = keypad.getKey();

    if(key=='#')
          {
            Undwr=Undwr+1;
            lcd2.setCursor(6,1);
            lcd2.print(Undwr);

            if(Undwr<10 && Undwr>=0)
            {
               lcd2.setCursor(7,1);
               lcd2.print("  ");
            }
           
          }
    
  if(key=='*')
         {
          Undwr=Undwr-1;
          lcd2.setCursor(6,1);
          lcd2.print(Undwr);
        

          if(Undwr<10 && Undwr>=0)
            {
               lcd2.setCursor(7,1);
               lcd2.print("  ");
            }
         }

  if(key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9')
  {
    Undwr=key;
    lcd2.setCursor(6,1);
    lcd2.print(Undwr);
  }

  }

}

void Socks()
{
  char key = keypad.getKey();

  while(key == NO_KEY)
  {
    key = keypad.getKey();

    if(key=='#')
          {
            Scks=Scks+1;
            lcd2.setCursor(14,1);
            lcd2.print(Scks);

            if(Scks<10 && Scks>=0)
            {
               lcd2.setCursor(15,1);
               lcd2.print("  ");
            }
           
          }
    
  if(key=='*')
    {
          Scks=Scks-1;
          lcd2.setCursor(14,1);
          lcd2.print(Scks);
        

          if(Scks<10 && Scks>=0)
            {
               lcd2.setCursor(15,1);
               lcd2.print("  ");
            }


   }

   if(key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9')
  {
    Scks=key;
    lcd2.setCursor(14,1);
    lcd2.print(Scks);
  }
  }
}