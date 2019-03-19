//Pislari Vadim 
//main.c

#include "struct_funct.c"

TCel* verificare(TCel* first,char color[MAX]);
int add(TList* nr_liste, char color[MAX],TCel* aux);
void insert_ord(TList* L,TCel* aux);
void show_b(TCel* actual, char color[MAX], FILE *out);
void eliberare(TCel* nr_liste);
void show_gol(char color[MAX], FILE *out);
void play(TCel *nr_liste, int nr);
void show_moves(TCel *nr_liste, char color[30], int nr, FILE *out);

int main(int argc, char const *argv[])
{
    //deschiderea fisierelor de citire si de scriere
    FILE *in = fopen(argv[1], "rt");
    if(!in){
        printf("eroare de deschidere");
        return -1;
    }
    FILE *out = fopen(argv[2],"wt");
    if(!out){
        printf("eroare de deschidere");
        return -1;
    }

    //LISTA GENERICA cu elemente repartizate pe culori
    int n,i;
    fscanf(in, "%d", &n);
    //variabila care pastreaza inceputul listei de jocuri repartizate pe culori
    TCel *nr_liste = NULL;
    for(i = 0; i != n; i++){
        char comand[MAX];
        //Se determina ce functie este apelata in fisier 
        fscanf(in,"%s", comand);
        if(strcmp(comand,"add") == 0){
            char color[MAX];
            int *value=malloc(sizeof(int));
            fscanf(in,"%s%d",color,value);

            //se determina daca mai exista element cu culoarea indicata
            TCel *actual = verificare(nr_liste,color);
            //daca nu mai exista culoarea asta se adauga o noua stiva
            if(actual==NULL){   
                Properties *P = calloc(sizeof(Properties), 1);
                //se copia informatia in celula
                strcpy(P->color,color);
                P->dimension = 1;
                P->a_fost_coada_generata = 0;
                TCel *aux_l = alocation(P);
                add(&nr_liste, color, aux_l);
                //se creaza celula care se insereaza ordonat in stiva
                TCel *aux_s = alocation(value);
                insert_ord(&P->stiva, aux_s);
            }
             else{
                //daca exista culoarea se insereaza in stiva corespunzatoare o noua celula
                Properties *P = (Properties*)actual->info;
                P->dimension++;
                TCel *aux_s = alocation(value);
                insert_ord(&P->stiva,aux_s);
            }
        }
        if(strcmp(comand,"play") == 0){
            char color[MAX];
            int nr;
            fscanf(in,"%s%d",color,&nr);
            //se cauta stiva corespunzatoare
            TCel *actual = verificare(nr_liste,color);
            if(actual) play(actual,nr);
        }
        if(strcmp(comand,"show") == 0){
            char color[MAX];
            fscanf(in,"%s",color);
            //se cauta stiva corespunzatoare
            TCel *actual = verificare(nr_liste,color);
            //daca nu exista stiva se afiseaza 3 tije goale
            if(!actual) show_gol(color,out);
            else show_b(actual,color,out);
        }
        if(strcmp(comand,"show_moves") == 0){
            char color[MAX];
            int nr;
            fscanf(in,"%s%d",color,&nr);
            //se cauta stiva corespunzatoare
            TCel *actual = verificare(nr_liste,color);
            if(actual) show_moves(actual,color,nr,out);
        }
    }
    eliberare(nr_liste);
	fclose(in);
    fclose(out);
    return 0;
}
