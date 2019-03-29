#define GIOCATORE 13
#define COMPUTER 10
#define PIU 10
#define MENO 13
#define VINTO1 7
#define VINTO2 6
#define PERSO 9
#define INVIO 8
#include <LiquidCrystal.h>
#include <avr/io.h>
#include <avr/wdt.h>
#define Reset_AVR()   wdt_enable(WDTO_30MS); //reset

int turno = 0; // dice di chi è il turno
int traguardo = 60; // dice fino a che numero devi arrivare 
int somma = 0; // somma dei numeri lanciati che deve raggiungere il traguardo
int giococomp = 0; // dice se devi giocare contro un computer o con un giocatore dipende se voglio fare anche il computer
int valori[6];//array con tutti ivalori che si potranno scegliere e viene aggiornato sempre
int ultimovalore = 0; //mi dice che valore ha scelto il giocatore prima
int s = 0;//serve per non far passare il turno se non hai scelto un numero diverso da 0
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  
void setup() {
  randomSeed(millis());
  pinMode(GIOCATORE, INPUT);
  pinMode(COMPUTER, INPUT);
  pinMode(PIU, INPUT);
  pinMode(MENO, INPUT);
  pinMode(INVIO, INPUT);
  pinMode(VINTO1, OUTPUT);
  pinMode(VINTO2, OUTPUT);
  pinMode(PERSO, OUTPUT);
  digitalWrite(VINTO1, LOW);
  digitalWrite(VINTO2, LOW);
  digitalWrite(PERSO, LOW);
  pinMode(A0, OUTPUT);
lcd.clear();
lcd.begin(16, 2);
}
void scrivi ( String n, String m) // metodo che scrive sul'lcd
{
      lcd.begin(16, 2);
      lcd.print(n);
      lcd.setCursor(0, 1);
      lcd.print(m);
}
void Controchi()//metodo che mi dice se sarò contro un giocatore o contro un computer
{
  bool premuto = false;
  while (!premuto)
  {
    if (digitalRead (GIOCATORE) == HIGH )
    {
      giococomp = 1;
      premuto = true;
      scrivi("scelto un altro","giocatore");
    }
    if (digitalRead (COMPUTER) == HIGH)
    {
      giococomp = 2;
      premuto = true;
      scrivi("scelto computer","");
    }
  }
}
void Deciditraguardo() // mi decide il traguardo da raggiungere per vincere
{
   while(digitalRead (INVIO) == LOW) 
   {  delay (70);
      scrivi("traguardo",String(traguardo));
      if(digitalRead (PIU) == HIGH && traguardo < 99)   { traguardo++;  delay (200);}
      if(digitalRead (MENO) == HIGH && traguardo > 30 ) { traguardo--;  delay (200);}
   }
}
void Riempi ( int n, int m)//mi riempie l'array con i valori che il giocatore puo scegliere
{
  int o = 0;
  for( int i = 0; i <= 6; i++)
     {
        if(i != n && i!= m )
          {
              valori[o] = i;
              o++; 
           }
           else{ valori[o] = NULL;}
      } 
}
void Carica(int ultimo)// mi dice che valori sono da non mettere nell'array
{
   for( int i = 0; i <= 6; i++)
      {
         if(ultimo == 1 || ultimo == 6)   { Riempi(1,6);}      
         if(ultimo == 2 || ultimo == 5)   { Riempi(2,5);}
         if(ultimo == 3 || ultimo == 4)   { Riempi(3,4);}
      }
}
void DammiValori(int u) // mi da un'array di numeri che posso scegliere quando gioco nel caso iniziale
{
    Carica(u);
   if(somma == 0)
   {
      for( int i = 0; i <= 6; i++) { valori[i] = i;  }
   }
}

void Gioca(int num) // metodo principale che mi fa giocare e posso inserire solo i valori che mi da il metodo DammiValori()
{
  s = 0; 
  int n = 0;
  DammiValori(ultimovalore);
  int valorescelto = valori[1];
  scrivi("traguardo:   "+ String(traguardo),"mancano:     "+ String(traguardo-somma)); delay(1700);
  while(digitalRead (INVIO) == LOW) 
  {
    scrivi("valore:"+String(valorescelto)+"     g."+String(num),"v.g:"+String(ultimovalore)+"   somma "+String(somma)); delay(150);
    if(digitalRead (PIU) == HIGH && n <= 5 && valori[n+1]!= 0 && valori[n+1]!= ultimovalore)
    {
        n++;
        valorescelto = valori[n];
    }
    if(digitalRead (MENO) == HIGH && n > 1)
    {
        n--;
        valorescelto = valori[n];
    }
  }   ControlloSomma(valorescelto);
}
void SommaPiu()//controllo se ho superato la somma 
{
    if(turno == 0 && giococomp == 2)
    {
      scrivi("vinto","computer");
      digitalWrite(PERSO, HIGH);
      }
    if(turno == 0 && giococomp == 1)
    {
      scrivi("vinto","giocatore 2");
      digitalWrite(VINTO2, HIGH);
    }
    if(turno == 2 || turno == 1)
    {
      scrivi("vinto","giocatore 1");
      digitalWrite(VINTO1, HIGH);
    }
}
void SommaUguale()// controllo se hai la somma uguale 
{
    if(turno == 0)
    {
      scrivi("vinto","giocatore 1");
      digitalWrite(VINTO1, HIGH);
    }
    if(turno == 2)
    {
      scrivi("vinto","computer");
      digitalWrite(PERSO, HIGH);
    }
    if(turno == 1)
    {
      scrivi("vinto","giocatore 2");
      digitalWrite(VINTO2, HIGH);
    }
}
void ControlloVittoria()//mi controlla chi ha vinto e se qualcuno ha vinto resetta tutto
{
  if(somma == traguardo)
  {
    SommaUguale();
    delay(3500);
    Reset_AVR(); 
  }
  if(somma > traguardo)
  {
    SommaPiu();
    delay(3500);
    Reset_AVR(); //mi resetti tutte le variabili in moda da ricominciare da capo
  } 
}
 void ControlloSomma(int n)//mi controlla che il valore sia piu di 0
 {
  if(n!= 0)
  {
  somma = somma + n;
  ultimovalore = n; delay(900);
  }
  else { s = 1;}
 }
int Giocac()//gioca il computer
{s=0;
  DammiValori(ultimovalore);
  int r = (analogRead(A1) % 5) +1;
  ControlloSomma(valori[r]);
  return valori[r];
}
void inizio()//parte iniziale dove l'utente decide i parametri del gioco
{
      digitalWrite(A0, HIGH);
      scrivi("scegli contro","chi giochi");
      Controchi();   delay(1000);
      Deciditraguardo();  delay(700);
      scrivi("inizio gioco",""); delay(700);
}
void loop() {
    inizio(); ultimovalore = 0; somma = 0;
    while(somma < traguardo ||somma!= traguardo)
      {
          if(turno == 0) //gioca giocatore 1
          {
              scrivi("tocca a : ","giocatore 1"); delay(1200);
              Gioca(1);// fa giocare il giocatore 
              ControlloVittoria();//mi controlla chi ha vinto
              if(giococomp == 1) { turno = 1; }
              if(giococomp == 2 ) { turno = 2; }
          }
          if(turno == 1) // gioca giocatore 2
          {
             scrivi("tocca a : ","giocatore 2"); delay(1200);
             Gioca(2);
             ControlloVittoria();  
            if(s == 0){ turno = 0;}
          }
         if(turno == 2) //se gioco con il computer 
           {
             scrivi("tocca a : ","computer");delay(1200);  
             scrivi("valore:"+String(Giocac())+"     g.c","v.g:"+String(ultimovalore)+"   somma "+String(somma));delay(1500);
             ControlloVittoria(); delay(1000);           
            if(s == 0){  turno = 0;}
           }
      }
}
