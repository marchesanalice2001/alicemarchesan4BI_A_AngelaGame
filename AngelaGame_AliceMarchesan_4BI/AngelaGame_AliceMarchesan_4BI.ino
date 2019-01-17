
#define GIOCATORE 7
#define COMPUTER 4
#define PIU 8
#define MENO 2
#define VINTO1 9
#define VINTO2 9
#define PERSO 6
#define INVIO 2




int turno = 0; // dice di chi è il turno
int traguardo = 50; // dice fino a che numero devi arrivare 
int somma = 0; // somma dei numeri lanciati che deve raggiungere il traguardo
int giococomp = 0; // dice se devi giocare contro un computer o con un giocatore dipende se voglio fare anche il computer
int iniziogioco = 0; // dice quando puoi iniziare il gioco dopo aver scelto il traguardo
int ultimovalore = 0; // mi dice il valore ultimo che hanno inserito cosi da togliere la possibilità di inserire lo stessonumero
int numeriPossibili[7]; // array di valori che posso premere da far vedere sul LCD



void setup() {
  // put your setup code here, to run once:
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

// foto cell come leggere la seriale
}

void Controchi()
{
  int tempo = 10;
  bool premuto = false;
  while (!premuto)
  {
    if (giocatore() > tempo )
    {
      giococomp = 1;
      premuto = true;
      break;
    }
    if (computer() > tempo )
    {
      giococomp = 2;
      premuto = true;
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

void Deciditraguardo() // AUMENTA E DIMINUISCE IL VALORE DA RAGGIUNGERE FINCHE NON PREMO INVIO
{
   while(digitalRead (INVIO) == HIGH) 
   {
    if(digitalRead (PIU) == HIGH)
    {
      if(traguardo < 99)
      {
        traguardo++;
      }
    }
    if(digitalRead (MENO) == HIGH)
    {
      if(traguardo > 30)
      {
        traguardo--;
      }
    }
   }
}

int ValoriPossibili()
{
  if(somma == 0)
  {
    for(int i = 0; i = 6; i++)
    {
      numeriPossibili[i] = i;
    }
  }
  else
  {
      for(int i = 0; i = 6; i++)
    {
      numeriPossibili[i] = NULL;
    }
    if(ultimovalore == 1)
    {
      
    }
  }
}


 
 





void ControlloVittoria()
{
  if(somma == traguardo)
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
  if(somma > traguardo)
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
}




void loop() {
  // put your main code here, to run repeatedly:

    Controchi();
    Deciditraguardo();//metodo che sceglie contro chi devi giocare e a che cifra vuoi arrivare
    if(iniziogioco != 0) // fa iniziare il gioco solo se hai scelto il numero di inizio e con chi giochi
    {
      while(somma < traguardo)
      {
          if(turno == 0) //gioca giocatore 1
          {
            
            //metodo che fa giocare il primo giocatore e posso scegliere anche 0 e passi il turno
            //mi dai anche il numero ultimo  // all'interno chiamo metodo che restituisce le opzioni che posso mettere per il giocatore dopo
            //vedo strutture gioco fiammiferi
          }
          if(turno == 1 && giococomp == 1) // gioca giocatore 2
          {
            //metodo che fa giocare il primo giocatore e posso scegliere anche 0 e passi il turno
            //mi dai anche il numero ultimo  // all'interno chiamo metodo che restituisce le opzioni che posso mettere per il giocatore dopo
            //vedo strutture gioco fiammiferi
            // devo aspettare che l'utente metta il pulsante
            //richiao metodo che mi fa giocare con il giocatore 1
            //alla fine di ogni volta metodo che fa il controllo e non deve superare sennò perdi se è uguale vince chi ha il turno quindi devo fare il controllo prima di cambiare il turno
          }
         if(turno == 2 && giococomp == 2) //se gioco con il computer forse
           {
               //faccio ogni volta un numero casuale che devo controllare che non sia uguare a quelli che non posso fare e lo aggiungo alla somma
               // controllo che possa raggiungere il numero scelto
           }
      }
      ControlloVittoria();//controlla chi ha raggiunto il traguardo
    }
}
