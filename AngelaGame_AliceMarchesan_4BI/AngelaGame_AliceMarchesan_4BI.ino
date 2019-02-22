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
int traguardo = 50; // dice fino a che numero devi arrivare 
int somma = 0; // somma dei numeri lanciati che deve raggiungere il traguardo
int giococomp = 0; // dice se devi giocare contro un computer o con un giocatore dipende se voglio fare anche il computer
int valori[7];
int ultimovalore;
int s = 0;
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

void scrivi ( String n, String m)
{
      lcd.begin(16, 2);
      lcd.print(n);
      lcd.setCursor(0, 1);
      lcd.print(m);
}

void Controchi()//metodo che mi dice se sarò contro un giocatore o contro un computer
{
  int tempo = 5;
  bool premuto = false;
  while (!premuto)
  {
    if (giocatore() > tempo )
    {
      giococomp = 1;
      premuto = true;
      scrivi("scelto un altro","giocatore");
    }
    if (computer() > tempo )
    {
      giococomp = 2;
      premuto = true;
      scrivi("scelto computer","");
    }
  }
}

int giocatore()//per verificare se è stato premuto il pulsante giocatore
{
  int inizio = millis();
  while (digitalRead (GIOCATORE) == HIGH){ }
  return millis() - inizio;
}

int computer()//per verificare se è stato premuto il pulsante computer
{
  int inizio = millis();
  while (digitalRead (COMPUTER) == HIGH){}
  return millis() - inizio;
}

int contaTempoPIU() //serve sia nel metodo che mi decide il traguardo che quello che mi fa giocare il giocatore
{
  int inizio = millis();
  while (digitalRead (PIU) == HIGH){ }
  return millis() - inizio;
}

int contaTempoMENO()
{
  int inizio = millis();
  while (digitalRead (MENO) == HIGH){}
  return millis() - inizio;
}

void Deciditraguardo() // AUMENTA E DIMINUISCE IL VALORE DA RAGGIUNGERE FINCHE NON PREMO INVIO
{
   while(digitalRead (INVIO) == LOW) 
   {
    if(digitalRead (PIU) == HIGH && contaTempoPIU() > 0 && traguardo < 99)
    {
        traguardo++;
        scrivi("traguardo",String(traguardo));
    }
    if(digitalRead (MENO) == HIGH && contaTempoMENO() > 0 && traguardo > 30 )
    {
        traguardo--;
        scrivi("traguardo", String(traguardo));
    }
   }
}

void Riempi ( int n, int m)
{
  int s = 1;
  for( int i = 1; i <= 6; i++)
     {
        if(i != n && i!= m)
          {
              valori[s] = i;
              s++;
           }
      } 
}
void Cancella()
{
   for( int i = 1; i <= 7; i++)
      {
         valori[i] = NULL;
      }
}

void DammiValori(int ultimo) // mi da un'array di numeri che posso scegliere quando gioco
{
  Cancella();
   if(somma == 0)
   {
      for( int i = 1; i <= 6; i++)
      {
         valori[i] = i;
      }
   }
   else
   {
          if(ultimo == 1 || ultimo == 6)
             {
                 Riempi(1,6);
             }      
           if(ultimo == 2 || ultimo == 5)
            {
                Riempi(2,5);
              }
          if(ultimo == 3 || ultimo == 4)
              {
                Riempi(3,4);
              }
   }
}

void Gioca() // metodo principale che mi fa giocare e posso inserire solo i valori che mi da il metodo DammiValori()
{
  s = 0;
  int n = 1;
  int valorescelto = 0;
  DammiValori(ultimovalore);
  while(digitalRead (INVIO) == LOW) 
  {
    if(digitalRead (PIU) == HIGH && contaTempoPIU() > 0)
    {
      if(n < 6 && valori[n]!= NULL)
      {
        n++;
        valorescelto = valori[n];
        scrivi("valore",String(valori[n]));
      }
    }
    if(digitalRead (MENO) == HIGH && contaTempoMENO() > 0)
    {
      if(n > 1 && valori[n]!= NULL)
      {
        n--;
        valorescelto = valori[n];
        scrivi("valore",String(valori[n]));
      }
    }
  }
  ControlloSomma(valorescelto);
}

void SommaPiu()//vede se ho superato la somma
{
    if(turno == 0)
    {
      if(giococomp == 2)
      {
      scrivi("vinto","computer");
      digitalWrite(PERSO, HIGH);
      }
      if(giococomp == 1)
      {
      scrivi("vinto","giocatore 2");
        digitalWrite(VINTO2, HIGH);
      }
    }
    if(turno == 2 || turno == 1)
    {
      scrivi("vinto","giocatore 1");
      digitalWrite(VINTO1, HIGH);
    }
}

void SommaUguale()//vede se hai la somma uguale
{
    if(turno == 0)
    {
      scrivi("vinto","giocatore 1");
      digitalWrite(VINTO1, HIGH);
    }
    if(turno == 2 && giococomp == 2)
    {
      scrivi("vinto","computer");
      digitalWrite(PERSO, HIGH);
    }
    if(turno == 1 && giococomp == 1)
    {
      scrivi("vinto","giocatore 2");
      digitalWrite(VINTO2, HIGH);
    }
}

void ControlloVittoria()//mi controlla chi ha vinto
{
  if(somma == traguardo)
  {
    SommaUguale();
    delay(3000);
    Reset_AVR(); 
  }
  if(somma > traguardo)
  {
    SommaPiu();
    delay(3000);
    Reset_AVR(); //mi resetti tutte le variabili in moda da ricominciare da capo
  } 
}
 void ControlloSomma(int n)
 {
  if(n!= 0)
  {
  somma = somma + n;
  ultimovalore = n;
      scrivi("valore",String (n));
      delay(1500);
      scrivi("somma",String (somma));
      delay(1500);
  }
  else { s = 1;}
 }

void Giocac()
{
  s = 0;
  DammiValori(ultimovalore);
  int r = analogRead(A0) % 4;
  ControlloSomma(valori[r]);
}
void inizio()
{
      digitalWrite(A0, HIGH);
      scrivi("scegli contro","chi giochi");
      Controchi();//metodo che mi dice contro chi gioco 
      delay(1500);
      scrivi("scegli traguardo","");
      delay(1500);
      Deciditraguardo();//metodo che sceglie contro chi devi giocare e a che cifra vuoi arrivare
      delay(1500);
      scrivi("inizio gioco","");
      delay(1500);
}


void loop() {
    inizio();
    while(somma < traguardo || somma != traguardo )
      {
          if(turno == 0) //gioca giocatore 1
          {
              scrivi("tocca a : ","giocatore 1");
              delay(1500);
              scrivi("scegli valore ","");
              Gioca();// fa giocare il giocatore 
              ControlloVittoria();//mi controlla chi ha vinto
            if(giococomp == 1 && s == 0 ) // cambia il turno per andare avanti
              {
                turno = 1;
              }
              if(giococomp == 2 && s == 0 )
              {
                turno = 2;
              }
          }
          if(turno == 1 && giococomp == 1) // gioca giocatore 2
          {
             scrivi("tocca a : ","giocatore 2");
             delay(1500);
             scrivi("scegli valore ","");
             Gioca();
             ControlloVittoria();  
            if(s == 0)
            {          
            turno = 0;
            }
          }
         if(turno == 2 && giococomp == 2) //se gioco con il computer forse
           {
             scrivi("tocca a : ","computer");
             delay(1500);
             Giocac();
             ControlloVittoria();            
            if(s == 0)
            {          
            turno = 0;
            }
           }
      }
}
