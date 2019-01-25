
#define GIOCATORE 13
#define COMPUTER 12
#define PIU 12
#define MENO 13
#define VINTO1 8
#define VINTO2 7
#define PERSO 4
#define INVIO 2


#include <avr/io.h>
#include <avr/wdt.h>
#define Reset_AVR() wdt_enable(WDTO_30MS); //reset


int turno = 0; // dice di chi è il turno
int traguardo = 50; // dice fino a che numero devi arrivare 
int somma = 0; // somma dei numeri lanciati che deve raggiungere il traguardo
int giococomp = 0; // dice se devi giocare contro un computer o con un giocatore dipende se voglio fare anche il computer
int valori[7];
int ultimovalore;




void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

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
      Serial.println("scelto un altro giocatore");
      break;
    }
    if (computer() > tempo )
    {
      giococomp = 2;
      premuto = true;
      Serial.println("scelto il computer");
      break;
    }
  }
}

int giocatore()//per verificare se è stato premuto il pulsante giocatore
{
  int inizio = millis();
  while (digitalRead (GIOCATORE) == HIGH)
  {
  }
  int fine = millis();
  int durata = fine - inizio;
  delay(100);
  return durata;
}


int computer()//per verificare se è stato premuto il pulsante computer
{
  int inizio = millis();
  while (digitalRead (COMPUTER) == HIGH)
  {
  }
  int fine = millis();
  int durata = fine - inizio;
  delay(100);
  return durata;
}

int contaTempoPIU()
{
  int inizio = millis();
  while (digitalRead (PIU) == HIGH)
  {
  }
  int fine = millis();
  int durata = fine - inizio;
  delay(100);
  return durata;
}

int contaTempoMENO()
{
  int inizio = millis();
  while (digitalRead (MENO) == HIGH)
  {
  }
  int fine = millis();
  int durata = fine - inizio;
  delay(100);
  return durata;
}

void Deciditraguardo() // AUMENTA E DIMINUISCE IL VALORE DA RAGGIUNGERE FINCHE NON PREMO INVIO
{
  int tempo = 5;
   while(digitalRead (INVIO) == LOW) 
   {
    if(digitalRead (PIU) == HIGH && contaTempoPIU() > tempo )
    {
      if(traguardo < 99)
      {
        traguardo++;
        Serial.println(traguardo);
        Serial.println("traguardo attuale");
      }
    }
    if(digitalRead (MENO) == HIGH && contaTempoMENO() > tempo )
    {
      if(traguardo > 30)
      {
        traguardo--;
        Serial.println(traguardo);
        Serial.println("traguardo attuale");
      }
    }
   }
        Serial.println(traguardo);
        Serial.println("traguardo finale");
}

void Riempi ( int n, int m)
{
  for( int i = 1; i <= 6; i++)
     {
        if(i != n && i!= m)
          {
            Serial.println(i);
              valori[i] = i;
           }
      } 
}


void DammiValori(int ultimo) // mi da un'array di numeri che posso scegliere quando gioco
{
   if(somma == 0)
   {
      for( int i = 1; i <= 6; i++)
      {
         Serial.println(i);
         valori[i] = i;
      }
   }
   else
   {
          for( int i = 0; i <= 6; i++)
            {
               valori[i] = NULL;
             }
             
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

void Gioca() // metodo che mi fa giocare e posso inserire solo i valori che mi da il metodo DammiValori()
{
  int n = 1;
  int tempo = 10;
        Serial.println("numero");
        Serial.println(n);
        
        Serial.println("ultimovalore");
        Serial.println(ultimovalore);
  DammiValori(ultimovalore);
  while(digitalRead (INVIO) == LOW) 
  {
    if(digitalRead (PIU) == HIGH && contaTempoPIU() >tempo )
    {
      if(n < 6 && valori[n]!= NULL)
      {
        n++;
        ultimovalore = valori[n];
        Serial.println(ultimovalore);
        Serial.println("ultimovalore");
        Serial.println("numero");
        Serial.println(n);
      }
    }
    if(digitalRead (MENO) == HIGH && contaTempoMENO() >tempo)
    {
      if(n > 1 && valori[n]!= NULL)
      {
        n--;
        ultimovalore = valori[n];
        Serial.println(ultimovalore);
        Serial.println("ultimovalore");
        Serial.println("numero");
        Serial.println(n);
      }
    }
    }
    somma = somma + ultimovalore;
    
        Serial.println("somma");
        Serial.println(somma);
}

void SommaPiu()//vede se ho superato la somma
{
    if(turno == 0)
    {
      if(giococomp == 2)
      {
        digitalWrite(PERSO, HIGH);
      }
      if(giococomp == 2)
      {
        digitalWrite(VINTO2, HIGH);
      }
    }
    if(turno == 2 && giococomp == 2)
    {
      //HA VINTO IL COMPUTER
      digitalWrite(VINTO1, HIGH);
    }
    if(turno == 1 && giococomp == 1)
    {
      //ha vinto il giocatore 2
      digitalWrite(VINTO1, HIGH);
    }
}

void SommaUguale()//vede se hai la somma uguale
{
    if(turno == 0)
    {
      //vinto giocatore 1
      digitalWrite(VINTO1, HIGH);
    }
    if(turno == 2 && giococomp == 2)
    {
      //HA VINTO IL COMPUTER
      digitalWrite(PERSO, HIGH);
    }
    if(turno == 1 && giococomp == 1)
    {
      //ha vinto il giocatore 2
      digitalWrite(VINTO2, HIGH);
    }
}

void ControlloVittoria()//mi controlla chi ha vinto
{
  // da compattare
  if(somma == traguardo)
  {
    SommaUguale();
    delay(5000);
    Reset_AVR(); 
  }
  if(somma > traguardo)
  {
    SommaPiu();
    delay(5000);
    Reset_AVR(); //mi resetti tutte le variabili in moda da ricominciare da capo
  } 
}

void Giocac()
{
  DammiValori(ultimovalore);
  int r = analogRead(A0) % 4;
  Serial.println(r);
  ultimovalore = valori[r];
  somma = somma + ultimovalore;
}




void loop() {
  // put your main code here, to run repeatedly:
    Controchi();//metodo che mi dice contro chi gioco 
    Deciditraguardo();//metodo che sceglie contro chi devi giocare e a che cifra vuoi arrivare
    delay(500);
    Serial.println(somma);
    Serial.println(traguardo);
    while(somma < traguardo || somma != traguardo )
      {
          if(turno == 0) //gioca giocatore 1
          {
            Gioca();// fa giocare il iocatore 1
            ControlloVittoria();//mi controlla chi ha vinto
            if(giococomp == 1) // cambia il turno per andare avanti
              {
                turno = 1;
              }
              if(giococomp == 2)
              {
                turno = 2;
              }
    Serial.println(turno);
    Serial.println("turno");
    delay(500);
          }
          if(turno == 1 && giococomp == 1) // gioca giocatore 2
          {
            Gioca();
            ControlloVittoria();
            turno = 0;
          }
         if(turno == 2 && giococomp == 2) //se gioco con il computer forse
           {
               Giocac();
               ControlloVittoria();
               turno = 0;
           }
      }
}
