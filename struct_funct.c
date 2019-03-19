//Pislari Vadim 
//strut_funct.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

//structura generica pentru stive, coada si lista de culori
typedef struct list{
void *info;
struct list *next;
}TCel, *TList;

//celula care este ca informatia in lista de stive repartizate pe culori
//contine 3 stive reprezentand cele 3 tije si o coada cu toate operatiile
//simulate la inceput de program
typedef struct cel{
    char color[MAX];
    int dimension;
    TList stiva,stiva1,stiva2,coada;
    int a_fost_coada_generata;
}Properties;

//celula care este ca informatie pentru coada de miscari realizate
//contine sursa si destinatia miscarii
typedef struct coda_miscari{
    char source,destination;
}queue;


//functie de alocare
TCel* alocation (void *P){
 TCel* C = malloc(sizeof(TCel));
 C->next= NULL;
 C->info= P;
 return C;
}

//realizeaza inserarea la inceput de stiva
void Push(TList* L,TCel* aux){
    TCel* next = *L;
    *L = aux;
    (*L)->next = next;
}

//elimina si returneaza primul element din stiva
TCel* Pop(TList* L){
    TCel *aux = *L; 
    *L = (*L)->next;
    return aux;
}

//inserarea ordonata a turnurilor in prima tija (stiva)
void insert_ord(TList *L,TCel *aux){
    //RECURENTA FRUMOASA xd.
    if(!*L){
        Push(L,aux);
        return;
    }
    int *n = (int *) (*L)->info;
    int *d = (int *) aux->info;
    if(*d > *n) Push(L,aux);
    else{
        //daca nu este pozitia buna de inserare se scoate elementul
        //si cu ajutorul recurentei se va adauga la sfarsit astfel
        //nu e nevoie de o stiva aditionala
        TCel *select= Pop(L);
        insert_ord(L,aux);
        Push(L,select);
    }
}

//extrage un element din coada
TCel* extragere(TList* coada){
    TCel *aux = *coada;
    *coada= (*coada)->next;
    return aux;
}

//extrage ultimul element
TCel* extragere_ult(TList* coada){
    TCel *aux = *coada,*ret,*ant=NULL;
    for( ; aux->next!=NULL ; ant = aux, aux = aux->next);
    //se verifica daca nu are doar un singur element
    if(ant == NULL) {
        ret = *coada;
        *coada = NULL;
        return ret;
    }
    ret = aux;
    ant->next=NULL;
    return ret;
}

//adauga un element la coada
void adauga(TList *coada, TCel *cel){
    TCel *aux = *coada, *ant=NULL;
    for( ; aux != NULL; ant = aux, aux = aux->next);
    //se verifica daca coada nu e nuka
    if(!ant){
        *coada = cel;
        return;
    }
    ant->next=cel;
}


//adaugare in lista de culori
int add(TList* L, char color[MAX],TCel* aux){
    if(*L == NULL){
            *L = aux;
            return 1;
    }
    TCel* ant = NULL, *first = *L;
    //se gaseste ulimul element
    for( ;first != NULL; ant = first, first = first->next);
    ant->next = aux;
    return 1;
}


//verifica daca exista in lista repartizata pe culori un element cu culoarea indicata
//returneaza NULL daca nu s-a gasit si valoarea pointerului daca exista
TCel* verificare(TCel* first,char color[MAX]){
if (!first) return NULL;
else{
    for( ; first!=NULL ; first=first->next){
        Properties* P = (Properties*) first->info;
        if(strcmp(color,P->color)==0){return first;}
    }
}
return NULL;
}

//afiseaza daca cele 3 tije sunt goale
void show_gol(char color[MAX], FILE *out){
    fprintf(out,"A_%s:",color);
    fprintf(out,"\n");
    fprintf(out,"B_%s:",color);
    fprintf(out,"\n");
    fprintf(out,"C_%s:",color);
    fprintf(out,"\n");
}

//funtie de afisare a unei singure tije
void show(TCel* first, FILE *out){
    for ( ; first != NULL; first = first -> next) {   
        int *var = (int *)first->info;
        fprintf(out," %d",*var);
     }

}
//functie de afisare a celor 3 tije 
void show_b(TCel* actual, char color[MAX], FILE *out){
    Properties* P = (Properties*) actual->info;
    TCel* first = P ->stiva;

    fprintf(out,"A_%s:",color);
    show(first,out);
    fprintf(out,"\n");

    TCel* first_1 = P ->stiva1;
    fprintf(out,"B_%s:",color);
    show(first_1,out);
    fprintf(out,"\n");

    TCel* first_2 = P ->stiva2;
    fprintf(out,"C_%s:",color);
    show(first_2,out);
    fprintf(out,"\n");
}

//genereaza recursiv (simulare) coada de miscari a jocului
void generate(int nr, char a, char b, char c,TList *coada)
{
    if( nr == 0 )return;
    generate( nr-1, a, c, b, coada);
    queue *celula = malloc(sizeof(struct coda_miscari));
    celula->source = a;
    celula->destination = c;
    TCel *aux_c = alocation(celula);
    //se adauga elementu generat in oada
    adauga(coada,aux_c);
    generate( nr-1, b, a, c,coada);

}

//se elimina succesiv din coada miscarile care trebuie executate
//se realizeaza miscarea dintr-o stiva in alta
void play(TCel *list,int nr){
    Properties *P = (Properties *) list->info;
    //se verifica daca s-a generat coada de miscari  
    if (P->a_fost_coada_generata == 0){
         generate(P->dimension,'A','B','C',&P->coada);
         P->a_fost_coada_generata =1;
    }

    int i=0;
    while( P->coada ){
        i++;
        TCel *cel = extragere(&P->coada);
        queue *ext = (queue*) cel->info; 
        TCel *aux = NULL;
        //A, B, si C sunt indici a stivelor
        if(ext->source == 'A') aux = extragere_ult(&P->stiva);
        if(ext->source == 'B') aux = extragere_ult(&P->stiva1);
        if(ext->source == 'C') aux = extragere_ult(&P->stiva2);
        if(ext->destination == 'A') adauga(&P->stiva,aux);
        if(ext->destination == 'B') adauga(&P->stiva1,aux);
        if(ext->destination == 'C') adauga(&P->stiva2,aux);
        free(cel->info);
        free(cel);
        if(i == nr) break;
    }
}

//se afiseaza urmatoarele nr miscari din coada 
void show_moves(TCel *list,char color[MAX],int nr, FILE *out){
    Properties *P = (Properties *) list->info;
    // se genereaza coada daca inca nu a fost generata
    if (P->a_fost_coada_generata == 0){
         generate(P->dimension,'A','B','C',&P->coada);
         P->a_fost_coada_generata =1;
    } 
    TCel *aux = P->coada;
    int i = 0;
    fprintf(out,"M_%s:",color);
    for( ; aux != NULL ; aux = aux->next ){
        queue* actual = (queue *)aux->info;
        fprintf(out," %c->%c",actual->source,actual->destination);
        i++;
        if(i==nr) break;
    }
    fprintf(out,"\n");
}

//functie de eliberare a memoriei dintr-o stiva
void eliberare_stiva(TList* stiva){
        TCel* first = *stiva;
        TCel* ant = NULL; 
        for ( ; first !=NULL ; ant = first, first = first->next){
            free(first->info);
            free(ant);
        }
        free(ant);
}

//funtie de eliberare a intregii memorii
void eliberare(TCel* nr_liste){
    TCel* ant_l = NULL; 
    for( ; nr_liste != NULL ;ant_l = nr_liste, nr_liste = nr_liste->next){
        Properties* P = (Properties*) nr_liste->info;
        //eliberarea stivelor si a cozii
        eliberare_stiva(&P->stiva);
        eliberare_stiva(&P->stiva1);
        eliberare_stiva(&P->stiva2);
        eliberare_stiva(&P->coada);
        free(nr_liste->info);
        free(ant_l);
    }
    free(ant_l);
}
