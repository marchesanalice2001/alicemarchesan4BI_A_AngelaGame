int turno = 0; // dice di chi è il turno
int traguardo = 50; // dice fino a che numero devi arrivare 
int somma = 0; // somma dei numeri lanciati che deve raggiungere il traguardo
int giococomp = 0; // dice se devi giocare contro un computer o con un giocatore dipende se voglio fare anche il computer
int iniziogioco = 0; // dice quando puoi iniziare il gioco dopo aver scelto il traguardo
int ultimovalore = 0; // mi dice il valore ultimo che hanno inserito cosi da togliere la possibilità di inserire lo stessonumero




void setup() {
  // put your setup code here, to run once:




// foto cell come leggere la seriale


}

void loop() {
  // put your main code here, to run repeatedly:

    //metodo che sceglie contro chi devi giocare e a che cifra vuoi arrivare
    if(iniziogioco != 0) // fa iniziare il gioco solo se hai scelto il numero di inizio e con chi giochi
    {
        if (giococomp == 1)// se giochi con il giocatore
        {
          if(turno == 0) //gioca giocatore 1
          {
            //metodo che fa giocare il primo giocatore e posso scegliere anche 0 e passi il turno
            //mi dai anche il numero ultimo  // all'interno chiamo metodo che restituisce le opzioni che posso mettere per il giocatore dopo
            //vedo strutture gioco fiammiferi
          }
          if(turno == 1 && giocoocomp == 1) // gioca giocatore 2
          {
            //metodo che fa giocare il primo giocatore e posso scegliere anche 0 e passi il turno
            //mi dai anche il numero ultimo  // all'interno chiamo metodo che restituisce le opzioni che posso mettere per il giocatore dopo
            //vedo strutture gioco fiammiferi
            // devo aspettare che l'utente metta il pulsante
            //richiao metodo che mi fa giocare con il giocatore 1
            //alla fine di ogni volta metodo che fa il controllo e non deve superare sennò perdi se è uguale vince chi ha il turno quindi devo fare il controllo prima di cambiare il turno
          }

          if(giococomp == 2) //se gioco con il computer forse
           {
               //faccio ogni volta un numero casuale che devo controllare che non sia uguare a quelli che non posso fare e lo aggiungo alla somma
               // controllo che possa raggiungere il numero scelto
            }
        }
    }
}
