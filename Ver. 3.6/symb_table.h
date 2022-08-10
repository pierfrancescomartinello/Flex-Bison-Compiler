#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//Definizione HASHSIZE
#define HASHSIZE 53

//Definizione strutture
//Dettagli è necessaria per salvare dettagli <categoria>:<val>
typedef struct detCate{
    int val;
    char* categoria;

    struct detCate* next;
} Dettagli;

//DettagliTappa è necessaria per salvare dettagli Biglietti cat.<nominativo_tipo>:(<vari DettagliCategoria>)
typedef struct dettagliTap{
    char* nominativo_tipo;

    Dettagli* firstDettagli;
    Dettagli* lastDettagli;

    struct dettagliTap* next;
} DettagliTappa;

//Tappa è necessaria per salvare le tappe descritte in input
typedef struct tap{
    char *nome;
    char *location;
    float prezzo;

    DettagliTappa* firstDetTappa;
    DettagliTappa* lastDetTappa;

    struct tap* next;
} Tappa;
//Fine delle definizioni delle strutture

//Prototipi
//Prototipi di funzioni per l'analisi della prima parte dell'input
Tappa* setTappa(char*nome, char*place); 
void detBind();
void catBind();
void detInit(char* nominativo);
void catInit(char* categoria, int biglietti);

//Prototipi di funzioni per l'analisi della seconda parte dell'input
void setPrezzo(char* tipo, int prezzo);

//Prototipi di funzioni per l'analisi della terza parte dell'input
void setSconto(char* categoria, int sconto);

//Prototipi di funzioni per la hashtable
int hash(char s);
void insert(Dettagli* toIns, Dettagli* *table);
Dettagli* lookup(char* index, Dettagli* *table);

//Prototipi di funzioni necessarie al calcolo e all'output
void priceCalc();
void price_output();
float benefitCalc(float price);
char* toLowerButNotTheFirst(char* toFix);

//Prototipo di funzione accessoria per la liberazione della memoria
void freeAll();
//Fine prototipi