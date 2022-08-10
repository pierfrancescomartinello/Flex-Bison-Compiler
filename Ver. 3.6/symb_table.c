#include "symb_table.h"

//Definizioni di variabili globali
//Puntatori alla testa e alla coda della lista delle Tappe
Tappa *tappa_list_head = NULL;
Tappa *tappa_list_tail = NULL;

//Puntatori alla testa e alla coda della lista dei DettagliTappa
DettagliTappa* head_detTmp = NULL;
DettagliTappa* tail_detTmp = NULL;

//Puntatori alla testa e alla coda della lista dei Dettagli
Dettagli* head_catTmp = NULL;
Dettagli* tail_catTmp = NULL; 

//Hashtable per conservare i valori di Sconto e Prezzo
Dettagli* scontoHash[HASHSIZE];
Dettagli* prezzoHash[HASHSIZE];

//Fine definizioni variabili globali

//Implementazioni
//Implementazioni di funzioni per l'analisi della prima parte dell'input
Tappa *setTappa(char* nome, char* place){
    //Creazione della tappa
    Tappa *t;
    assert(t != NULL);
    t = (Tappa *)malloc(sizeof(*t));
    t->nome = strdup(nome);
    t->location = strdup(place);
    
    //Aggiunta della tappa t alla lista delle Tappe
    if(tappa_list_head == NULL){
        tappa_list_head = t;
        tappa_list_tail = tappa_list_head;
        tappa_list_head->next = NULL;
    }else{
        tappa_list_tail->next = t;
        tappa_list_tail = t;
        tappa_list_tail->next = NULL;
    }
    return t;
}

void detBind(){
    //Prende l'ultima tappa e l'ultimo insieme di dettagli esaminati e li unisce
    Tappa* last = tappa_list_tail;
    DettagliTappa* headdet = head_detTmp;
    DettagliTappa* taildet = tail_detTmp;
    assert(last != NULL);
    assert(headdet != NULL);
    assert(taildet != NULL);
    last->firstDetTappa = headdet;
    last->lastDetTappa = taildet;

    head_detTmp = NULL;
    tail_detTmp = NULL;
}

void catBind(){
    //Prende l'ultima tappa e l'ultima categoria e li unisce
    DettagliTappa* last = tail_detTmp;
    Dettagli* headcat = head_catTmp;
    Dettagli* tailcat = tail_catTmp;

    assert(last != NULL);
    assert(headcat != NULL);
    assert(tailcat != NULL);

    last->firstDettagli = headcat;
    last->lastDettagli = tailcat;

    head_catTmp = NULL;
    tail_catTmp = NULL;
}

//Inizializzazione dell'insieme dei dettagli
void detInit(char* nominativo){
    DettagliTappa* d;
    d = (DettagliTappa *)malloc(sizeof(*d));
    assert(d != NULL);
    d->nominativo_tipo = strdup(nominativo);

   if(head_detTmp == NULL){
        head_detTmp = d;
        head_detTmp->next = NULL;
        tail_detTmp = head_detTmp;
        
    }else{
        tail_detTmp->next = d;
        tail_detTmp = d;
        tail_detTmp->next = NULL;
    }
}

//Inizializzazione del dettaglio
void catInit(char *categoria, int biglietti){
    Dettagli* p;
    assert(p != NULL);
    p = (Dettagli *)malloc(sizeof(*p));
    p->categoria = strdup(categoria);
    p->val = biglietti;

    if(head_catTmp == NULL){
        head_catTmp = p;
        p->next = NULL;
        tail_catTmp = head_catTmp;
    }else{
        tail_catTmp->next = p;
        tail_catTmp = p;
        tail_catTmp->next = NULL;
    }
}


//Implementazioni di funzioni per l'analisi della seconda parte dell'input
//Inserimento del prezzo letto all'interno della hashtable
void setPrezzo(char* tipo, int prezzo){
    Dettagli* tmp;
    tmp = (Dettagli *)malloc(sizeof(*tmp));
    assert(tmp != NULL);
    tmp->categoria = strdup(tipo);
    tmp->val = prezzo;

    insert(tmp, prezzoHash);
}


//Implementazioni di funzioni per l'analisi della terza parte dell'input
 //Inserimento dello sconto letto all'interno della hashtable
 void setSconto(char* categoria, int sconto){
    Dettagli* tmp;
    char a;
    tmp = (Dettagli *)malloc(sizeof(*tmp));
    assert(tmp != NULL);
    tmp->categoria =  strdup(categoria);
    
    tmp->val = sconto;

    insert(tmp, scontoHash);
}

//Implementazioni delle funzioni per le hashtable
//Inserimento di un elemento generico all'interno della propia hashtable 
//(funzione richiamata da setPrezzo e setSconto)
void insert(Dettagli* toIns, Dettagli* *table){
    char l = toIns->categoria[0];
    int index = hash(l);
    Dettagli* tmp = table[index];
    if(tmp != NULL){
        while(tmp->next != NULL){
        tmp = tmp->next;
        }
        tmp->next = toIns;
    }else{
        table[index] = toIns;
    }
}

//Ricerca di un elemento all'interno della propria hashtable
Dettagli* lookup(char* indexing, Dettagli* *table){
    char l = indexing[0];
    char m;
    int index = hash(l);
    Dettagli* tmp;
    tmp=(Dettagli *)malloc(sizeof(*tmp));
    assert(tmp != NULL);
    for(tmp = table[index]; tmp != NULL; tmp = tmp->next){
        m = tmp->categoria[0];
        if( l == m) {
            return tmp;
        }
    }
    return NULL;
}

//Funzione hash
int hash(char s){
    return (127*s)%HASHSIZE;
}

//Implementazione di funzioni necessarie al calcolo e all'output
//Calcolo del ricavato ottenuto per ogni singola tappa, al netto degli sconti
void priceCalc(){
    Tappa* current = tappa_list_head;            
    DettagliTappa* currentD = current->firstDetTappa;
    Dettagli* currentDD = currentD->firstDettagli;    
    float price, pricetemp = 0.0;

    for(current = tappa_list_head; current != NULL ; current = current->next){
        for(currentD = current->firstDetTappa; currentD != NULL; currentD = currentD->next){
            for(currentDD = currentD->firstDettagli; currentDD != NULL; currentDD = currentDD->next){
                if(currentDD->val != 0) {
                   pricetemp += currentDD->val * lookup(currentD->nominativo_tipo, prezzoHash)->val * (float)(100 - lookup(currentDD->categoria, scontoHash)->val)/100;
                }
            }
            price += pricetemp;
            pricetemp = 0.0;
        }
        current->prezzo = price;
        price = 0.0;
    }
}

//Funzione per la stampa dell'output
void price_output(){
    Tappa* current;
    current = (Tappa *)malloc(sizeof(*current));
    float total_price = 0.0;
    float total_beneficenza = 0.0;
    for(current = tappa_list_head; current != NULL ; current = current->next){
        printf("%s %s\n", toLowerButNotTheFirst(current->nome), current->location);
        printf("Vendita biglietti --> euro %.2f\n", current->prezzo);
        total_price += current->prezzo;
        printf("Beneficenza --> euro %.2f\n", benefitCalc(current->prezzo));
        total_beneficenza += benefitCalc(current->prezzo);

        if(current->next == NULL){
            printf("$$$\n");
        }else{
            printf("---\n");
        }
    }
    printf("Totale vendita biglietti euro %.2f\n", total_price);
    printf("Totale Beneficenza: euro %.2f\n", total_beneficenza);
}

//Calcolo della beneficenza da donare dato il ricavato di ogni tappa
float benefitCalc(float price){
    if(price <= 3700000){
        return price*0.1;
    }else if(price > 3700000 && price <=4500000){
        return price*0.12;
    }else{
        return price*0.18;
    }
}

//Funzione ausiliaria per la capitalizzazione della prima lettera di ogni parola nella stringa definita come parametro
char* toLowerButNotTheFirst(char* toFix){
    char* toReturn;
    toReturn = (char *)malloc(sizeof(toReturn));
    toReturn[0] = toFix[0];
    for(int i = 1; i<strlen(toFix); i++){
        
        if(toFix[i-1] == ' '){
            toReturn[i] = toupper(toFix[i]);
        }else{
            toReturn[i] = tolower(toFix[i]);
        }    
    }
    toReturn[strlen(toFix)] = '\0';
    return toReturn;
}

//Prototipo di funzione accessoria per la liberazione della memoria
//Liberazione della memoria utilizzata per le hashtable
void freeAll(){
    for(int i = 0; i< HASHSIZE; i++){
        free(scontoHash[i]);
        free(prezzoHash[i]);
    }
}
//Fine dell'implementazione
