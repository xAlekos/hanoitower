#include <stdio.h>
#include <stdlib.h>
#define M 25
#define N 142
struct nodo{
    int dato;
    struct nodo* next;
};

typedef struct nodo* stack;

struct piolo{
    stack pila;
    int num;
};

typedef struct piolo* piolo;

struct torrehanoi{
    piolo piolo1;
    piolo piolo2;
    piolo piolo3;
};


typedef struct torrehanoi* hanoi;
void dpush(char schermo[M][N],int dim,int piolo,stack* head);


int push(stack* head ,int elem){
    stack nuovonodo=(stack)malloc(sizeof(struct nodo));
    nuovonodo->dato=elem;
    if(*head==NULL){
        nuovonodo->next=NULL;
        *head=nuovonodo;
        return 0;
    }
     //Lista non vuota//
    nuovonodo->next=*head;
    *head=nuovonodo;
    return 0;
}

int pop(stack* head){
    stack b;
    int a;
    if ((*head)->next==NULL){
        a=(*head)->dato;
        free(*head);
        *head=NULL;
        return a;
    }
    b=*head;
    *head=(*head)->next;
    a=b->dato;
    free(b);
    return a;
}

void stampa(stack head){
    while (head!=NULL){
        printf("%d ", head->dato);
        head=head->next;
    }
}

int conta(stack head){
    int n=0;
    while (head!=NULL){
        n+=1;
        head=head->next;
    }
    return n;
}

void creaschermo(char schermo[M][N]){
    int i,j;
    for(i=0;i<M;i++)
        for(j=0;j<N;j++)
            schermo[i][j]=' ';
}

void refreshscreen(char schermo[M][N]){
    int i,j;
    for(i=0;i<M;i++){
    printf("          ");
        for(j=0;j<N;j++)
           printf("%c", schermo[i][j]);
        printf("\n");
    }
}

void draw_piolo(char schermo[M][N],int x, int y){
    int i;
    for(i=0;i<20;i++){
        schermo[x++][y]='|';
    }
}

void draw_base(char schermo[M][N],int y){
    int offy=y+1;
    int offy2=y-1;
 for(int i=2;i<N-2;i++){
    schermo[y][i]= '-';
 }
  for(int i=1;i<N-1;i++){
    schermo[offy][i]= '-';
 }  
 for(int i=3;i<N-3;i++){
    schermo[offy2][i]= '-';
 }
}
void drawtower(char schermo[M][N]){
    draw_piolo(schermo,2,20);
    draw_piolo(schermo,2,60);
    draw_piolo(schermo,2,100);
    draw_base(schermo,M-2);
}

hanoi inizializzatorre(char schermo[M][N],int n){
    hanoi torre=(hanoi)malloc(sizeof(struct torrehanoi));
    torre->piolo1=(piolo)malloc(sizeof(struct piolo));
    torre->piolo2=(piolo)malloc(sizeof(struct piolo));
    torre->piolo3=(piolo)malloc(sizeof(struct piolo));
    torre->piolo1->num=1;
    torre->piolo2->num=2;
    torre->piolo3->num=3;
    torre->piolo2->pila=NULL;
    torre->piolo3->pila=NULL;
    for(int i=n;i>0;i--){
        dpush(schermo,i,1,&(torre->piolo1->pila));
    }
    drawtower(schermo);
    refreshscreen(schermo);
    return torre;
}

void draw_disk(char schermo[M][N],int dim,int piolo,int altezza){
    int posy=21-2*altezza;
    int posx;
    switch(piolo){
        case 1:posx=20;break;
        case 2:posx=60;break;
        case 3:posx=100;break;
    }
    int posx_tmp=posx;
    for(int i=0;i<2*dim;i++){
        schermo[posy][++posx]='_';
    }
    schermo[posy][++posx]='|';
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy][--posx]='_';
    }
    schermo[posy][--posx]='|';
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy-1][++posx]='_';
    }
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy-1][--posx]='_';
    }
    posx=posx_tmp;
    
}

void del_disk(char schermo[M][N],int dim,int piolo,int altezza){
    int posy=21-2*altezza;
    int posx;
    switch(piolo){
        case 1:posx=20;break;
        case 2:posx=60;break;
        case 3:posx=100;break;
    }
    int posx_tmp=posx;
    schermo[posy][posx]='|';
    schermo[posy-1][posx]='|';
    for(int i=0;i<2*dim;i++){
        schermo[posy][++posx]=' ';
    }
    schermo[posy][++posx]=' ';
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy][--posx]=' ';
    }
    schermo[posy][--posx]=' ';
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy-1][++posx]=' ';
    }
    posx=posx_tmp;
    for(int i=0;i<2*dim;i++){
        schermo[posy-1][--posx]=' ';
    }
    posx=posx_tmp;

}

void dpush(char schermo[M][N],int dim,int piolo,stack* head){
    draw_disk(schermo,dim,piolo,conta(*head));
    push(head,dim);
}

int dpop(char schermo[M][N],int piolo,stack* head){
    int dim=pop(head);
    del_disk(schermo,dim,piolo,conta(*head));
    return dim;
}

void muovi(char schermo[M][N],piolo from, piolo to){
    int dim;
    dim=dpop(schermo,from->num,&from->pila);
    dpush(schermo,dim,to->num,&to->pila);
    refreshscreen(schermo);
}

int sceltadischi(){
    int dischi;
    printf("Quanti dischi vuoi?\nMassimo: 10\n");
    do{
        scanf("%d",&dischi);
    }
    while(dischi<0 || dischi > 10);
}

int menu(){
    int scelta;
    printf("\t\t\t TORRE DI HANOI\n\n");
    printf(" 1: Gioca\n 2: Risolutore\n");
    scanf("%d",&scelta);
    return scelta;
}

int islegal(int uno, int due,hanoi torre){
    stack primo;
    stack secondo;
    switch(uno){
        case 1: primo=torre->piolo1->pila;break;
        case 2: primo=torre->piolo2->pila;break;
        case 3: primo=torre->piolo3->pila;break;
    }
    switch(due){
        case 1: secondo=torre->piolo1->pila;break;
        case 2: secondo=torre->piolo2->pila;break;
        case 3: secondo=torre->piolo3->pila;break;
    }
    if(primo==NULL)
        return 0;
    if(secondo==NULL)
        return 1;
    if(primo->dato>secondo->dato)
        return 0;
    
    else
        return 1;
    
}

void readinput(char schermo[M][N],int uno, int due,hanoi torre){
     piolo from;
     piolo to;
     switch(uno){
        case 1: from=torre->piolo1;break;
        case 2: from=torre->piolo2;break;
        case 3: from=torre->piolo3;break;
    }
    switch(due){
        case 1: to=torre->piolo1;break;
        case 2: to=torre->piolo2;break;
        case 3: to=torre->piolo3;break;
    }
    muovi(schermo,from,to);
}

void checkwin(int *game,hanoi torre,int dischi){
    if(conta(torre->piolo3->pila)==dischi)
        *game=0;    
}

int islegal1(int uno,hanoi torre){
    stack primo;
    stack secondo;
    switch(uno){
        case 1: primo=torre->piolo1->pila;break;
        case 2: primo=torre->piolo2->pila;break;
        case 3: primo=torre->piolo3->pila;break;
    }
    if(primo==NULL)
        return 0;
    else
        return 1;
    
}
void interattiva(){
    int game=1;
    int mosse=1;
    int mossa1=0;
    int mossa2=0;
    int input1;
    int input2;
    char schermo[M][N];
    int dischi;
    creaschermo(schermo);
    hanoi torre=inizializzatorre(schermo,dischi = sceltadischi());
    while(game==1){
        while(mossa1==0){
            printf("\t\tDa quale torre vuoi spsotare il disco?\n");
            do{
                scanf("%d",&input1);
            }
            while(input1<1 || input1>4 || islegal1(input1,torre) == 0);
            
            mossa1=1;
        }
        while(mossa2==0){
            printf("\t\tA quale torre vuoi spsotare il disco?\n");
            do{
                scanf("%d",&input2);
            }
            while( input1<1 || input1>4 || islegal(input1, input2,torre)==0 );
            mossa2=1;
        }
        readinput(schermo,input1,input2,torre);
        printf("\t\t\tMosse: %d \n",mosse++);
        mossa1=0;
        mossa2=0;
        checkwin(&game,torre,dischi);
    }
    printf("\t\t\t\t\t\t\t\t  *HAI VINTO*\n\t\t\t\t\t\t\t        CONGRATULAZIONI");
}


void risolvi(char schermo[M][N],piolo source, piolo aux, piolo target ,int dischi){
    if (dischi==1)
        muovi(schermo,source,target);
    else{
        risolvi(schermo,source,target,aux,dischi-1);
        muovi(schermo,source,target);
        risolvi(schermo,aux,source,target,dischi-1);

    }
}

void risolutore(){
    int game=1;
    int mossa1=0;
    int mossa2=0;
    int input1;
    int input2;
    char schermo[M][N];
    int dischi;
    creaschermo(schermo);
    hanoi torre=inizializzatorre(schermo,dischi = sceltadischi());
    risolvi(schermo,torre->piolo1,torre->piolo2,torre->piolo3,dischi);
}

int main(){
    switch(menu()){
        case 1:interattiva(); break;
        case 2:risolutore(); break;
        
    }
    

}






