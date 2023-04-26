#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>


void color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


int ligne_max;
int colonne_max;



void depart_choix();
void Jouer();
void Regles();
void Quitter();
int Premier_qui_joue();

void PlateauTest(char t[ligne_max][colonne_max]);


void logique_jouer(int i,char Tableau[ligne_max][colonne_max]);
void logique_jouer_machine(int i,char Tableau[ligne_max][colonne_max]);


void Joueur_Joueur(int k);
void Joueur_Machine_facile(int k);


void Tour_joueur(char pion,char pion_adverse,int tour,char Tableau[ligne_max][colonne_max]);

void Deplacer_pion(char pion,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2]);
void Deplacer_manger(int x,int y,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2]);
int joueur_permet_manger(char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max]);
int existe_manger(char pion_adverse,int ligne,int colonne,char Tableau[ligne_max][colonne_max]);
int existe_pion(char pion,int ligne,int colonne,char Tableau[ligne_max][colonne_max]);
int adjacent_libre(int ligne,int colonne,int ligne_libre,int colonne_libre);
int existe_libre(int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max]);
int Nb_pion(char P,char Tab[ligne_max][colonne_max]);
int existe_autre_manger(char pion,char pion_adverse,char Tableau[ligne_max][colonne_max]);
void deja_prise(int k,int ligne,int colonne,int Tab1[2][100],int Tab2[2][2]);
int existe_prise_prochaine(char pion_adverse,int ligne,int colonne,char Tableau[ligne_max][colonne_max],int Tab1[2][100],int k);
int prise_parmis_exist(int ligne,int colonne,int ligne_libre,int colonne_libre,int Tab1[2][100],int k);
int un_pion_libre(char pion,char Tableau[ligne_max][colonne_max]);
int existe_libre_position(int ligne,int colonne,char Tableau[ligne_max][colonne_max]);

int adjacent_3x3(int ligne,int colonne,int ligne_libre,int colonne_libre);
int adjacent_5x9(int ligne,int colonne,int ligne_libre,int colonne_libre);
int adjacent_5x5(int ligne,int colonne,int ligne_libre,int colonne_libre);



void Tour_machine(char pion,char pion_adverse,int tour,char Tableau[ligne_max][colonne_max]);

void position_pion(int *z,char pion,char pion_adverse,int T_machine[2][45],char Tableau[ligne_max][colonne_max]);
int Machine_choix(int n);
void Deplacer_manger_machine(int x,int y,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2]);
void Deplacer_pion_machine(char pion,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2]);
void case_possible(char pion_adverse,int *z,int k,int ligne,int colonne,int T_dep_machine[2][20],int Tab1[2][100],char Tableau[ligne_max][colonne_max]);



















// Pour determiner le premier joueur qui commence
int Premier_qui_joue()
{
    int solution;
    srand(time(NULL));
    solution=rand()%2;
    return solution;
}

// Pour afficher le design du plateau
void PlateauTest(char t[ligne_max][colonne_max])
{
   /*
    printf(" _________________________________________\n");
    printf("|      0 1 2 3 4                          |\n");
    printf("|                                         |\n");
    printf("|  0   %c-%c-%c-%c-%c                          |\n",t[0][0],t[0][1],t[0][2],t[0][3],t[0][4]);
    printf("|      |\\|/|\\|/|                          |\n");
    printf("|  1   %c-%c-%c-%c-%c                          |\n",t[1][0],t[1][1],t[1][2],t[1][3],t[1][4]);
    printf("|      |/|\\|/|\\|                          |\n");
    printf("|  2   %c-%c-%c-%c-%c                          |\n",t[2][0],t[2][1],t[2][2],t[2][3],t[2][4]);
    printf("|      |\\|/|\\|/|                          |\n");
    printf("|  3   %c-%c-%c-%c-%c                          |\n",t[3][0],t[3][1],t[3][2],t[3][3],t[3][4]);
    printf("|      |/|\\|/|\\|                          |\n");
    printf("|  4   %c-%c-%c-%c-%c                          |\n",t[4][0],t[4][1],t[4][2],t[4][3],t[4][4]);
    printf("|_________________________________________|\n");

    */

    int a,b;
    int c1=0,c2=1;

    printf("\n");
    a=2*ligne_max-1;
    b=2*colonne_max-1;

    for(int i=0;i<36;i++){
        if(i==6){
            for(int j=0;j<b;j++){
                printf("%c",22);
            }
        }
        else{
            printf("%c",22);
        }
    }
    printf("\n");
    for(int i=0;i<36;i++){
        if(i==6){
            for(int j=0;j<b;j++){
                if(j%2==0){
                    printf("%d",(j/2)+1);
                }
                else{
                    printf(" ");
                }
            }
        }
        else{
            printf(" ");
        }
    }
    printf("\n");
    for(int i=0;i<36;i++){
        if(i==6){
            for(int j=0;j<b;j++){
                printf(" ");
            }
        }
        else{
            printf(" ");
        }
    }
    for(int k=0;k<a;k++){
        printf("\n");
        if(k%2==0){
            for(int i=0;i<36;i++){
                if(i==6){
                    for(int j=0;j<b;j++){
                        if(j%2==0){
                            if(t[k/2][j/2]=='N'){printf("%c",'N');}
                            else if(t[k/2][j/2]=='B'){color(15,14);printf("%c",'B');color(0,14);}
                            else{color(12,14);printf("%c",'.');color(0,14);}
                           // printf("%c",t[k/2][j/2]);
                        }
                        else{
                            printf("-");
                        }
                    }
                }
                else if(i==2){
                    printf("%d",(k/2)+1);
                }
                else{
                    printf(" ");
                }
            }
        }
        else if(k==1 || k==5){
            for(int i=0;i<36;i++){
                if(i==6){
                    for(int j=0;j<b;j++){
                        if(j%2==0){
                            printf("|");
                        }
                        else{
                            if(c1==0){
                                printf("\\");
                                c1=1;
                            }
                            else{
                                printf("/");
                                c1=0;
                            }
                        }
                    }
                }
                else{
                    printf(" ");
                }
            }
        }
        else{
            for(int i=0;i<36;i++){
                if(i==6){
                    for(int j=0;j<b;j++){
                        if(j%2==0){
                            printf("|");
                        }
                        else{
                            if(c2==0){
                                printf("\\");
                                c2=1;
                            }
                            else{
                                printf("/");
                                c2=0;
                            }
                        }
                    }
                }
                else{
                    printf(" ");
                }
            }
        }
    }
    printf("\n");
    for(int i=0;i<36;i++){
        if(i==6){
            for(int j=0;j<b;j++){
                    printf("%c",22);
            }
        }
        else{
            printf("%c",22);
        }
    }
    printf("\n");

}





 ///*****************************************     Joueur ---- Joueur     ******************************************************** ///




// Combiner les tours entre les joueurs et verifier a chaque tour d'un joeuur s'il n'existe pas de pion adverse ou si les pion adverse ne peut pas se deplacer
void logique_jouer(int i,char Tableau[ligne_max][colonne_max])
{
    char pion,pion_adverse;
    int tour=0; // on initialise un contour pour eviter les prises multiples sur le premier coup de chaque joueur

    do{
        if (i==0){ // Joueur 1 qui commence

            pion='B';
            pion_adverse='N';
            printf("\nJoueur 1 (B): \n");
            Tour_joueur(pion,pion_adverse,tour,Tableau); // Verification, traitement et execution du tour du joueur
        //
            if (Nb_pion('N',Tableau)!=0){ // verifier s'il existe au moins pion a jouer
                pion='N';
                pion_adverse='B';
                printf("\nJoueur 2 (N): \n");
                Tour_joueur(pion,pion_adverse,tour,Tableau); // Verification, traitement et execution du tour du joueur
            }
        }

        else{ // Joueur 2 qui commence
            pion='N';
            pion_adverse='B';
            printf("\nJoueur 2 (N): \n");
            Tour_joueur(pion,pion_adverse,tour,Tableau); // Verification, traitement et execution du tour du joueur
        //
            if (Nb_pion('B',Tableau)!=0){ // verifier s'il existe au moins un pion a jouer
                pion='B';
                pion_adverse='N';
                printf("\nJoueur 1 (B): \n");
                Tour_joueur(pion,pion_adverse,tour,Tableau); // Verification, traitement et execution du tour du joueur
            }
        }
        tour++;
    }while(Nb_pion('B',Tableau)!=0 && Nb_pion('N',Tableau)!=0 && un_pion_libre('B',Tableau)!=0 && un_pion_libre('N',Tableau)!=0); // A la fin de chaque tour on verifie s'il n'existe pas du pion ou s'il ne peut pas se deplacer

    //Annoncer le Vainqueur
    if (Nb_pion('B',Tableau)==0 || un_pion_libre('B',Tableau)==0) // verifier s'il n'existe pas de pion ou si le pion ne peut pas se deplacer
        printf("Le gagnant est le joueur 2 !\n");
    else
        printf("Le gagnant est le joueur 1 !\n");

}


// Tour joueur :
void Tour_joueur(char pion,char pion_adverse,int tour,char Tableau[ligne_max][colonne_max])
{
    if(un_pion_libre(pion,Tableau)!=0){  // Existe au moins un pion qui peut se deplacer sinon fin du tour du joueur

        int ligne,colonne,ligne_libre,colonne_libre;
        int j;
        int k=0,r=-1;
        int Tab2[2][2]={};
        int Tab1[2][100]={};

        /// Partie saisi des coordonnes :
        do{
            printf("Coordonnees du pion a deplacer : \n");
            scanf("%d%d",&ligne,&colonne);
            ligne=ligne-1;
            colonne=colonne-1;
            if(existe_pion(pion,ligne,colonne,Tableau)!=0){ // Verifier s'il existe un pion du joueur courant dans la position saisi (ligne,colonne)
                r=existe_autre_manger(pion,pion_adverse,Tableau)+existe_manger(pion_adverse,ligne,colonne,Tableau);
                // si r=0 : il n'exite pas de prise possible pour le joueur, donc on peut accepter son choix du pion qui peut faire juste un simple deplacement
                // si r=2 : le pion saisi permet d'effectuer une prise
                // si r=1 : Exite une prise, mais le pion choisit ne permet pas de faire une prise
                if(r==1)
                    printf("Vous avez une prise obligatoire ! %c\n",3); // Au moins une prise possible doit être réalisée s'il existe
            }
        }while(existe_pion(pion,ligne,colonne,Tableau)==0 || r==1 || existe_libre_position(ligne,colonne,Tableau)==0);
        // Pour passer a la partie du deplacement, On verifie 3 conditions :
        //    le pion dans (ligne,colonne) correspond au pion du joueur
        //    il existe au moins un deplacement a partir de (ligne,colonne)
        //    le pion saisi permet d'effectuer une prise OU il n'exite pas de prise possible pour le joueur

        /// Partie deplacement :
        do{
            do{
                printf("Coordonnes de deplacement : \n");
                scanf("%d%d",&ligne_libre,&colonne_libre);
                fflush(stdin);
                ligne_libre=ligne_libre-1;
                colonne_libre=colonne_libre-1;
                j=prise_parmis_exist(ligne,colonne,ligne_libre,colonne_libre,Tab1,k); // Savoir si le deplacement saisie a permis au joueur de faire une prise + et si le mouvement ne se repete pas
                if (existe_manger(pion_adverse,ligne,colonne,Tableau)+joueur_permet_manger(pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau)==1)
                    //Verifier si les coordonnes du deplacement saisie par le joueur (ligne_libre,colonne_libre), permet au pion de faire une prise
                    //Si ce n'est pas le cas, on verifie s'il n'existe pas une prise a partir de pion (ligne,colonne) en utilisant la fonction existe_manger
                    printf("Prise obligatoire ! \n"); // sinon on annonce un message : Prise obligatoire !
            }while(existe_libre(ligne,colonne,ligne_libre,colonne_libre,Tableau)==0|| j==0 ||(existe_manger(pion_adverse,ligne,colonne,Tableau)+joueur_permet_manger(pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau)==1));
            // Il faut verifier que la case_d'arrivee soit libre ET la case_depart joignable a la case_d'arrivee: (ligne,colonne) --> (ligne_libre,colonne_libre)
            // Le deplacement saisie a permis au joueur de faire une prise + et si le mouvement ne se repete pas
            // On reverifie la condition precedente: s'il existe au moins une prise possible, alors que le deplacement saisi ne permet pas une prise

            Deplacer_pion(pion,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2); // exectuion du deplacement
            PlateauTest(Tableau); // Afficher le plateau apres traitement du deplacement
            deja_prise(k,ligne,colonne,Tab1,Tab2);
            ligne=ligne_libre; // On change les valeurs de ligne ET colonne, pour se preparer au cas ou on a une autre prise
            colonne=colonne_libre;
            r=existe_prise_prochaine(pion_adverse,ligne,colonne,Tableau,Tab1,k);  // savoir s'il existe un prochaine movement verifiant les 2 conditions du prise multiples
            if(r==1 && Tab2[0][0]!=100 && tour!=0) // Le pion a effectue une prise + existe une prise multiple + different du 1er tour
                printf("Vous avez une autre prise ! \n");
            k++;//ici
        }while(r==1 && Tab2[0][0]!=100 && tour!=0); // Le pion a effectue une prise + existe une prise multiple + different du 1er tour
    }
}


//Return 1 : si existe un pion qui peut faire un movement , Return 0 : si n'existe aucun movement possible, ce qui entrainne une defaite
int un_pion_libre(char pion,char Tableau[ligne_max][colonne_max])
{
    int k,i,j,r,s;
    int T[16]={0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};

    for(i=0;i<ligne_max;i++){
        for(j=0;j<colonne_max;j++){
            if(Tableau[i][j]==pion){
                for(k=0;k<16;k+=2){
                    r=T[k];
                    s=T[k+1];
                    if(existe_libre(i,j,i+r,j+s,Tableau)!=0){
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}


// On parcoure les cases qui entourent un pion (ligne,colonne),
//pour verifier s'il existe au moins un chemin liant une casse_depart et une case_d'arrivee tel que la case_d'arrivee soit libre
// Return 1 : s'il existe au moins un deplacement
// Return 0 : sinon
int existe_libre_position(int ligne,int colonne,char Tableau[ligne_max][colonne_max])
{
    int k,i,j;
    int T[16]={0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
    for(k=0;k<16;k+=2)
    {
        i=T[k];
        j=T[k+1];
        if (existe_libre(ligne,colonne,ligne+i,colonne+j,Tableau)!=0)
            return 1;
    }
    return 0;
}

// Le nombre des pions d'un joueur
int Nb_pion(char P,char Tab[ligne_max][colonne_max])
{
    int a=0;
    int i,j;

    for( i=0; i<ligne_max; i++){
		for( j=0; j<colonne_max; j++){
			 if (Tab[i][j]==P)
                a++;
		}
	}
	return a;
}

// Savoir si le pion existe sur une position voulue
int existe_pion(char pion,int ligne,int colonne,char Tableau[ligne_max][colonne_max])
{
    if(ligne<ligne_max && ligne >=0 && colonne<colonne_max && colonne>=0){
        if (pion==Tableau[ligne][colonne])
            return 1;
        else
            return 0;
    }
    else
        return 0;
}


// Verifier s'il existe un chemin liant une casse_depart et une case_d'arrivee tel que la case_d'arrivee soit libre
// Return 1 : la case_d'arrivee soit libre ET la case_depart joignable a la case_d'arrivee
// Return 0 : sinon
int existe_libre(int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max])
{
    int c;
    if (Tableau[ligne_libre][colonne_libre]=='*'){
        c=adjacent_libre(ligne,colonne,ligne_libre,colonne_libre); // on stocke la reponse de : la case_depart est-il joignable a la case_d'arrivee ?
        if (c==1)
            return 1; // case_depart joignable a la case_d'arrivee
        else
            return 0;
    }
    else
        return 0;
}

// on traite 3 cas, en fonction du Fanorona choisit par le joueur
// 3 fonctions sont appelles: adjacent_3x3 , adjacent_5x5 ET adjacent_5x9
// Verifier si la case_depart (ligne,colonne) est joignable a la case_d'arrivee (ligne_libre,colonne_libre)
// Return 1 : si c'est le cas
// Return 0 : sinon
int adjacent_libre(int ligne,int colonne,int ligne_libre,int colonne_libre)
{
    if(colonne_max==3){
        return adjacent_3x3(ligne,colonne,ligne_libre,colonne_libre);
    }
    else if(colonne_max==5){
        return adjacent_5x5(ligne,colonne,ligne_libre,colonne_libre);
    }
    else{
        return adjacent_5x9(ligne,colonne,ligne_libre,colonne_libre);
    }
}

// Les trois fonctions suivants font les memes traitement, mais chacune sur des matrices de dimension differentes
// Pour modeliser les intersections entre les cases :
// On stocke dans chaque case les coordonnes des cases qui lui sont joignable, sous forme d'un nombre compose d'une concatenation de ((ligne*10)+colonne) des cases joignables
int adjacent_3x3(int ligne,int colonne,int ligne_libre,int colonne_libre)
{
    // J'ai cree deux matrice pour parvenir a stocker les nombres que leur size depasse la size(int)
    int Graphe1[3][3]={
                    {111001,110002,110112},
                    {110020,12020100,110222},
                    {111021,112022,112112},
                    };
    int Graphe2[3][3]={
                    {0,0,0},
                    {0,10202122,0},
                    {0,0,0},
                    };
    int T[20]={};
    int k=0,i,j=0;
    int a;
    a=Graphe1[ligne][colonne];
    do{
        T[k]=a%100;
        a=a/100;
        k++;
    }while(a!=0);
    a=Graphe2[ligne][colonne];
    if(a!=0){
        do{
            T[k]=a%100;
            a=a/100;
            k++;
        }while(a!=0);
    }

    for( i=0; i<k; i++){
	    if (T[i]==((ligne_libre*10)+colonne_libre)){
                j++;
                break;
	    }
	}
	if (j!=0)
        return 1;
    else
        return 0;
}


int adjacent_5x5(int ligne,int colonne,int ligne_libre,int colonne_libre)
{
    // J'ai cree deux matrice pour parvenir a stocker les nombres que leur size depasse la size(int)
    int Graphe1[5][5]={
                        {111001,110002,130301,130402,141303},
                        {110020,10020100,22131102,12040302,241304},
                        {211110,31222011,21131211,33242213,231413},
                        {403120,30222120,42333122,32242322,443324},
                        {413130,424031,333231,444233,433433},
                        };
        int Graphe2[5][5]={
                        {0,0,1112,0,0},
                        {0,22212012,0,24232214,0},
                        {3031,0,33323123,0,3433},
                        {0,42414032,0,44434234,0},
                        {0,0,4341,0,0},
                        };
        int T[20]={};
    int k=0,i,j=0;
    int a;
    a=Graphe1[ligne][colonne];
    do{
        T[k]=a%100;
        a=a/100;
        k++;
    }while(a!=0);
    a=Graphe2[ligne][colonne];
    if(a!=0){
        do{
            T[k]=a%100;
            a=a/100;
            k++;
        }while(a!=0);
    }

    for( i=0; i<k; i++){
	    if (T[i]==((ligne_libre*10)+colonne_libre)){
                j++;
                break;
	    }
	}
	if (j!=0)
        return 1;
    else
        return 0;
}


int adjacent_5x9(int ligne,int colonne,int ligne_libre,int colonne_libre)
{
    // J'ai cree deux matrice pour parvenir a stocker les nombres que leur size depasse la size(int)
    int Graphe1[5][9]={
                    {111001,110002,130301,130402,150503,150406,170705,170608,181707},
                    {110020,10020100,22131102,12040302,24151304,14060504,26171506,16080706,281708},
                    {211110,31222011,21131211,33242213,23151413,35262415,25171615,37282617,271817},
                    {403120,30222120,42333122,32242322,44353324,34262524,46373526,36282726,483728},
                    {413130,424031,333231,444233,353433,464435,373635,484637,473837},
                    };
    int Graphe2[5][9]={
                    {0,0,1112,0,1314,0,1516,0,0},
                    {0,22212012,0,24232214,0,26252416,0,28272618,0},
                    {3031,0,33323123,0,35343325,0,37363527,0,3837},
                    {0,42414032,0,44434234,0,46454436,0,48474638,0},
                    {0,0,4341,0,4543,0,4745,0,0},
                    };
    int T[20]={};
    int k=0,i,j=0;
    int a;
    a=Graphe1[ligne][colonne];
    do{
        T[k]=a%100;
        a=a/100;
        k++;
    }while(a!=0);
    a=Graphe2[ligne][colonne];
    if(a!=0){
        do{
            T[k]=a%100;
            a=a/100;
            k++;
        }while(a!=0);
    }

    for( i=0; i<k; i++){
	    if (T[i]==((ligne_libre*10)+colonne_libre)){
                j++;
                break;
	    }
	}
	if (j!=0)
        return 1;
    else
        return 0;
}


//shema dessine sur la feuille
// Verifier s'il existe une capture par éloignement ou par approche a partir une position (ligne,colonne) d'un pion vers un pion adverse
// return 1 s'il existe une capture, 0 sinon
int existe_manger(char pion_adverse,int ligne,int colonne,char Tableau[ligne_max][colonne_max])
{
    int k,i,j;
    int T[16]={0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
    for(k=0;k<16;k+=2)
    {
        i=T[k];
        j=T[k+1]; // le coupe (i,j) represante un variant qui depend du sens de la direction d'une prise parmis les 8 cas possibles du prise
        if (existe_pion(pion_adverse,ligne+i,colonne+j,Tableau)!=0 && existe_libre(ligne,colonne,ligne-i,colonne-j,Tableau)!=0) // Capture par éloignement
            return 1;
        if (existe_pion(pion_adverse,ligne+2*i,colonne+2*j,Tableau)!=0 && existe_libre(ligne,colonne,ligne+i,colonne+j,Tableau)!=0) // Capture par approche
            return 1;
    }
    return 0;
}

// Savoir si les coordonnes du deplacement saisie par le joueur (ligne_libre,colonne_libre), permet au pion de faire une prise
// Return 1: si les coordonnes du mouvement permet de faire une prise
// Return 0 : sinon
int joueur_permet_manger(char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max])
{
    int a,b;
    a=ligne_libre-ligne;
    b=colonne_libre-colonne;
    if(existe_pion(pion_adverse,ligne_libre+a,colonne_libre+b,Tableau)!=0)
        return 1;
    else if(existe_pion(pion_adverse,ligne-a,colonne-b,Tableau)!=0)
        return 1;
    else
        return 0;
}


//On execute le deplacement du pion :
// On remplace les pions adverses prises par des '*' a travers la fonction Deplacer_manger()
//+ On donne le choix au joueur entre prise gauche/droit ou haut/bas
void Deplacer_pion(char pion,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2])
{
    int x,y;

    //chaque deplacement se caracterise par un sens
    // on conserve ce sens dans une matrice Tab2, qui sera utile pour check la possibilite de plusieurs prise

    if(ligne==ligne_libre){ // deplacement suivant la direction horizontale
            // sens: Horizontale + gauche
            Tab2[0][0]=0;
            Tab2[1][0]=1;
            // sens: Horizontale + droite
            Tab2[0][1]=0;
            Tab2[1][1]=-1;
            if(colonne>colonne_libre){// sens: Horizontale + gauche
                x=1;
                y=0;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{// sens: Horizontale + droite
                x=-1;
                y=0;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else if(colonne==colonne_libre){ // deplacement suivant la direction verticale
            // sens: verticale + Haut
            Tab2[0][0]=1;
            Tab2[1][0]=0;
            // sens: verticale + Bas
            Tab2[0][1]=-1;
            Tab2[1][1]=0;
            if(ligne>ligne_libre){// sens: verticale + Haut
                x=0;
                y=1;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{// sens: verticale + Bas
                x=0;
                y=-1;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else if(ligne_libre-ligne==colonne_libre-colonne){// deplacement suivant la direction de la droite y=-x
            // sens: Haut + gauche
            Tab2[0][0]=1;
            Tab2[1][0]=1;
            // sens: Bas + droite
            Tab2[0][1]=-1;
            Tab2[1][1]=-1;
            if(ligne>ligne_libre){// sens: Haut + gauche
                x=1;
                y=1;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{// sens: Bas + droite
                x=-1;
                y=-1;
                Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else{// deplacement suivant la direction de la droite y=x
        // sens: Haut + droite
        Tab2[0][0]=1;
        Tab2[1][0]=-1;
        // sens: Bas + gauche
        Tab2[0][1]=-1;
        Tab2[1][1]=1;
        if(ligne>ligne_libre){// sens: Haut + droite
            x=-1;
            y=1;
            Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
        }
        else{// sens: Bas + Gauche
            x=1;
            y=-1;
            Deplacer_manger(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
        }
    }


    Tableau[ligne][colonne]='*'; // on remplace l'ancienne case du pion par le vide = '*'
    Tableau[ligne_libre][colonne_libre]=pion; // on place le pion dans la nouvelle position

}


//C'est la fonction qui traitement le deplacement d'un pion ET donne la possiblite au joueur de choisir entre une prise Gauche/Droite ou Haut/Bas si c'est le cas de choisir
void Deplacer_manger(int x,int y,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2])
{
    int i=0,j=0;
    char c;
    while(existe_pion(pion_adverse,ligne+y*(i+1),colonne+x*(i+1),Tableau)!=0){
        i++;
    }
    while(existe_pion(pion_adverse,ligne-y*(j+2),colonne-x*(j+2),Tableau)!=0){
        j++;
    }

    if(i!=0 && j!=0){
        if(ligne==ligne_libre){
            do{
                printf("Prise Gauche ou Droite ? (G/D) : ");
                scanf("%c",&c);
            }while(c!='G' && c!='D');
        }
        else{
            do{
                printf("Prise Haut ou Bas ? (H/B) : ");
                scanf("%c",&c);
            }while(c!='H' && c!='B');
        }
        if((y==-1)||(x==-1 && y==0)){
            if(c=='G'||c=='H'){
                for(j=1;j<=i;j++){
                    Tableau[ligne+y*j][colonne+x*j]='*';
                }
            }
            else{
                for(i=0;i<j;i++){
                    Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
                }
            }
        }
        else{
            if(c=='G'||c=='H'){
                for(i=0;i<j;i++){
                    Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
                }
            }
            else{
                for(j=1;j<=i;j++){
                    Tableau[ligne+y*j][colonne+x*j]='*';
                }
            }
        }
    }
    else if(i!=0){
        for(j=1;j<=i;j++){
            Tableau[ligne+y*j][colonne+x*j]='*';
        }
    }
    else if(j!=0){
        for(i=0;i<j;i++){
            Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
        }
    }
    else{
        //Si le deplacement est sans prise, on change les valeurs de Tab2 par des valeurs max 100
        Tab2[0][0]=100;
        Tab2[1][0]=100;
        Tab2[0][1]=100;
        Tab2[1][1]=100;
        printf("AUCUNE PRISE ! %c\n",1);
    }
}

// Stocker la direction et le postion du dernier deplacement
void deja_prise(int k,int ligne,int colonne,int Tab1[2][100],int Tab2[2][2])
{
    Tab1[0][0]=Tab2[0][0];
    Tab1[1][0]=Tab2[1][0];
    Tab1[0][1]=Tab2[0][1];
    Tab1[1][1]=Tab2[1][1];
    Tab1[0][k+2]=ligne;
    Tab1[1][k+2]=colonne;
}


// Savoir si il existe au moins un pion qui peut faire une prise :
// On parcoure le plateau case par case pour verifier s'il exisite une prise possible
// Return 1 : exite au moins une prise pour le joueur du pion
// Return 0 : N'existe aucune prise possible dans tout le plateau pour le joueur du pion
int existe_autre_manger(char pion,char pion_adverse,char Tableau[ligne_max][colonne_max])
{
    int i,j;

    for(i=0;i<ligne_max;i++){
        for(j=0;j<colonne_max;j++){
            if(Tableau[i][j]==pion){
                if(existe_manger(pion_adverse,i,j,Tableau)!=0){
                    return 1;
                }
            }
        }
    }
    return 0;
}


//return 1 si le prochaine movement verifier les 2 conditions : Ne pas repasser deux fois sur la meme case + Changer de direction entre les deux prises
int existe_prise_prochaine(char pion_adverse,int ligne,int colonne,char Tableau[ligne_max][colonne_max],int Tab1[2][100],int k)
{
    int Tcase1[2][50]={};
    int Tcase2[2][50]={};
    int r,i,j,c;
    int m=0,n=0;
    int T[16]={0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
    for(r=0;r<16;r+=2)
    {
        i=T[r];
        j=T[r+1];
        if (existe_pion(pion_adverse,ligne+i,colonne+j,Tableau)!=0 && existe_libre(ligne,colonne,ligne-i,colonne-j,Tableau)!=0){
            Tcase1[0][n]=i;
            Tcase1[1][n]=j;
            Tcase1[0][n+1]=ligne-i;
            Tcase1[1][n+1]=colonne-j;
            n+=2;
        }
        if (existe_pion(pion_adverse,ligne+2*i,colonne+2*j,Tableau)!=0 && existe_libre(ligne,colonne,ligne+i,colonne+j,Tableau)!=0){
            Tcase2[0][m]=-i;
            Tcase2[1][m]=-j;
            Tcase2[0][m+1]=ligne+i;
            Tcase2[1][m+1]=colonne+j;
            m+=2;
        }
    }
    for(i=0;i<n;i+=2){
        if((Tab1[0][0]!=Tcase1[0][i] || Tab1[1][0]!=Tcase1[1][i]) && (Tab1[0][1]!=Tcase1[0][i] || Tab1[1][1]!=Tcase1[1][i]) ){
            c=0;
            for(r=0;r<k;r++){
                if(Tab1[0][r+2]==Tcase1[0][i+1] && Tab1[1][r+2]==Tcase1[1][i+1])
                    c++;
            }
            if(c==0)
                return 1;
        }
    }
    for(i=0;i<m;i+=2){
        if((Tab1[0][0]!=Tcase2[0][i] || Tab1[1][0]!=Tcase2[1][i]) && (Tab1[0][1]!=Tcase2[0][i] || Tab1[1][1]!=Tcase2[1][i]) ){
            c=0;
            for(r=0;r<k;r++){
                if(Tab1[0][r+2]==Tcase2[0][i+1] && Tab1[1][r+2]==Tcase2[1][i+1])
                    c++;
            }
            if(c==0)
                return 1;
        }
    }
    return 0;
}


// Savoir si le deplacement saisie a permis au joueur de faire une prise + et si le mouvement ne se repete pas
// Return 1: le deplacement permet une prise parmi les prises possibles
// Return 0: sinon
int prise_parmis_exist(int ligne,int colonne,int ligne_libre,int colonne_libre,int Tab1[2][100],int k)
{
    int r,c=0;
    if(k==0){
        return 1;
    }
    else{
        if((Tab1[0][0]!=ligne-ligne_libre || Tab1[1][0]!=colonne-colonne_libre)&& (Tab1[0][1]!=ligne-ligne_libre || Tab1[1][1]!=colonne-colonne_libre)){
            c=1;
        }
        for(r=0;r<k;r++){
            if(Tab1[0][r+2]==ligne_libre && Tab1[1][r+2]==colonne_libre)
                c=2;
        }
        if(c==1)
            return 1;
        else
            return 0;
    }
}






 ///*****************************************     Joueur ---- Machine     ******************************************************** ///




//Pour Initialiser le plateau + traitement de toutes les instructions qui concernent un match joueur VS machine
void Joueur_Machine_facile(int k)
{
    int a;
    int Premier;
    char Tableau[ligne_max][colonne_max];

    if(colonne_max==3){
        Tableau[0][0]='N',Tableau[0][1]='*',Tableau[0][2]='B';
        Tableau[1][0]='B',Tableau[1][1]='N',Tableau[1][2]='*';
        Tableau[2][0]='N',Tableau[2][1]='B',Tableau[2][2]='*';
    }
    else{
        a=(colonne_max-1)/2;
        for(int i=0;i<ligne_max;i++){
            for(int j=0;j<colonne_max && i<2;j++){
                Tableau[i][j]='N';
            }
            for(int j=0;j<colonne_max && i==2;j++){
                if(j==a){
                    Tableau[i][j]='*';
                }
                else if(j%2==0 && j<a){
                    Tableau[i][j]='N';
                }
                else if(j%2!=0 && j<a){
                    Tableau[i][j]='B';
                }
                else if(j%2==0 && j>a){
                    Tableau[i][j]='B';
                }
                else{
                    Tableau[i][j]='N';
                }
            }
            for(int j=0;j<colonne_max && i>2;j++){
                Tableau[i][j]='B';
            }
        }
    }

    if(k==1)
        Premier=0;
    else
        Premier=1;

    PlateauTest(Tableau);

    logique_jouer_machine(Premier,Tableau);
}



// Combiner les tours entre le joueur et la machine, et verifier a chaque tour s'il n'existe pas de pion adverse ou si les pion  adverse ne peut pas se deplacer
void logique_jouer_machine(int i,char Tableau[ligne_max][colonne_max])
{
    char pion,pion_adverse;
    int tour=0;

    do{
        if (i==0){ // Joueur qui commence
            pion='B';
            pion_adverse='N';
            printf("\nHomme (B) : \n");
            Tour_joueur(pion,pion_adverse,tour,Tableau);// Verification, traitement et execution du tour du joueur
     //
     //
            if (Nb_pion('N',Tableau)!=0){// verifier s'il existe au moins pion a jouer
                pion='N';
                pion_adverse='B';
                sleep(2);
                printf("\nMachine (N) : \n");
                sleep(2);
                Tour_machine(pion,pion_adverse,tour,Tableau);// Verification, traitement et execution du tour du machine
            }
        }

        else{ // Machine qui commence
            pion='N';
            pion_adverse='B';
            sleep(2);
            printf("\nMachine (N) : \n");
            sleep(2);
            Tour_machine(pion,pion_adverse,tour,Tableau);// Verification, traitement et execution du tour du joueur
  //
  //
            if (Nb_pion('B',Tableau)!=0){// verifier s'il existe au moins pion a jouer
                pion='B';
                pion_adverse='N';
                printf("\nHomme (B) : \n");
                Tour_joueur(pion,pion_adverse,tour,Tableau);// Verification, traitement et execution du tour du machine
            }
        }
        tour++;
    }while(Nb_pion('B',Tableau)!=0 && Nb_pion('N',Tableau)!=0 && un_pion_libre('B',Tableau)!=0 && un_pion_libre('N',Tableau)!=0);
// A la fin de chaque tour on verifie s'il n'existe pas du pion ou s'il ne peut pas se deplacer

    //Annoncer le Vainqueur
    if (Nb_pion('B',Tableau)==0 || un_pion_libre('B',Tableau)==0) // verifier s'il n'existe pas de pion ou si le pion ne peut pas se deplacer
        printf("Le gagnant est : Machine !\n");
    else
        printf("Le gagnant est : Homme !\n");

}


// Tour machine:
//On stock les pions qui permettent de se deplacer ou bien de faire une prise (si c'est le cas)
//On choisit aleatoirement un parmi ces pions
//Etape traitement de deplacement:
//On stock les positions du deplacement soit qui assurent un mouvement sans prises, Soit qui permettent de faire une prise (si c'est le cas)
//On choisit aleatoirement un parmi ces positions
//On deplace le pion du machine
//On affiche le Plateau
//On stocke la direction et le postion du dernier deplacement pour verifier la possiblite d'avoir des prises multiples
void Tour_machine(char pion,char pion_adverse,int tour,char Tableau[ligne_max][colonne_max])
{
    if(un_pion_libre(pion,Tableau)!=0){

        int ligne,colonne,ligne_libre,colonne_libre;
        int choix;
        int k=0,r=-1,z=0;
        int Tab2[2][2]={};
        int Tab11[2][100]={};
        int T_dep_machine[2][20]={};
        int T_machine[2][45]={};

        position_pion(&z,pion,pion_adverse,T_machine,Tableau);
        choix=Machine_choix(z);
        ligne=T_machine[0][choix];
        colonne=T_machine[1][choix];

        do{
            z=0;
            case_possible(pion_adverse,&z,k,ligne,colonne,T_dep_machine,Tab11,Tableau);
            choix=Machine_choix(z);
            ligne_libre=T_dep_machine[0][choix];
            colonne_libre=T_dep_machine[1][choix];

            Deplacer_pion_machine(pion,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            PlateauTest(Tableau);
            deja_prise(k,ligne,colonne,Tab11,Tab2);
            ligne=ligne_libre;
            colonne=colonne_libre;
            r=existe_prise_prochaine(pion_adverse,ligne,colonne,Tableau,Tab11,k);
            k++;
        }while(r==1 && Tab2[0][0]!=100 && tour!=0);
    }
}

// Socker les positions des pions de la machine, qui permettent de se deplacer.
//S'il existe au moins un pion qui peut faire une prise, on stock juste les positions qui assurent une prise :
void position_pion(int *z,char pion,char pion_adverse,int T_machine[2][45],char Tableau[ligne_max][colonne_max])
{
    int a,b,i,j;
    b=existe_autre_manger(pion,pion_adverse,Tableau);
    for( i=0; i<ligne_max; i++){
		for( j=0; j<colonne_max; j++){
			 if(Tableau[i][j]==pion){
                a=b+existe_manger(pion_adverse,i,j,Tableau);
                if(a!=1 && existe_libre_position(i,j,Tableau)!=0){
                    T_machine[0][*z]=i;
                    T_machine[1][*z]=j;
                    (*z)++;
                }
			 }
		}
	}
}

// Le choix de la machine parmi les pions stocker a travers de la fonction position_pion()
int Machine_choix(int n)
{
    srand(time(NULL));
    return rand()%n;
}


// Socker les positions du deplacement possible d'un pion (ligne,colonne) de la machine, Soit qui permettent de faire une prise si c'est possible,
//soit juste qui permettent de se deplacer
void case_possible(char pion_adverse,int *z,int k,int ligne,int colonne,int T_dep_machine[2][20],int Tab1[2][100],char Tableau[ligne_max][colonne_max])
{

    int r,p,q,j;
    int T[16]={0,1,0,-1,1,0,-1,0,1,1,1,-1,-1,1,-1,-1};
    for(r=0;r<16;r+=2)
    {
        p=T[r];
        q=T[r+1];
        j=prise_parmis_exist(ligne,colonne,ligne+p,colonne+q,Tab1,k);
        if(existe_libre(ligne,colonne,ligne+p,colonne+q,Tableau)!=0 && j!=0 && (existe_manger(pion_adverse,ligne,colonne,Tableau)+joueur_permet_manger(pion_adverse,ligne,colonne,ligne+p,colonne+q,Tableau)!=1)){
            T_dep_machine[0][*z]=ligne+p;
            T_dep_machine[1][*z]=colonne+q;
            (*z)++;
        }
    }
}

//On execute le deplacement du pion :
// On remplace les pions adverses prises par des '*' a travers la fonction Deplacer_manger_machine()
void Deplacer_pion_machine(char pion,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2])
{
    int x,y;

    if(ligne==ligne_libre){
            Tab2[0][0]=0;
            Tab2[1][0]=1;
            Tab2[0][1]=0;
            Tab2[1][1]=-1;
            if(colonne>colonne_libre){
                x=1;
                y=0;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{
                x=-1;
                y=0;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else if(colonne==colonne_libre){
            Tab2[0][0]=1;
            Tab2[1][0]=0;
            Tab2[0][1]=-1;
            Tab2[1][1]=0;
            if(ligne>ligne_libre){
                x=0;
                y=1;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{
                x=0;
                y=-1;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else if(ligne_libre-ligne==colonne_libre-colonne){
            Tab2[0][0]=1;
            Tab2[1][0]=1;
            Tab2[0][1]=-1;
            Tab2[1][1]=-1;
            if(ligne>ligne_libre){
                x=1;
                y=1;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
            else{
                x=-1;
                y=-1;
                Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
            }
    }
    else{
        Tab2[0][0]=1;
        Tab2[1][0]=-1;
        Tab2[0][1]=-1;
        Tab2[1][1]=1;
        if(ligne>ligne_libre){
            x=-1;
            y=1;
            Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
        }
        else{
            x=1;
            y=-1;
            Deplacer_manger_machine(x,y,pion_adverse,ligne,colonne,ligne_libre,colonne_libre,Tableau,Tab2);
        }
    }

    Tableau[ligne][colonne]='*';
    Tableau[ligne_libre][colonne_libre]=pion;

}

//C'est la fonction qui traitement le deplacement d'un pion
//On choisit aleatoirement un parmi les sens : Haut/Bas ou Gauche/Droite , contrairement a la fonction Deplacer_manger()qui donne le choix au joueur de choisir
void Deplacer_manger_machine(int x,int y,char pion_adverse,int ligne,int colonne,int ligne_libre,int colonne_libre,char Tableau[ligne_max][colonne_max],int Tab2[2][2])
{
    int i=0,j=0;
    char c;
    while(existe_pion(pion_adverse,ligne+y*(i+1),colonne+x*(i+1),Tableau)!=0){
        i++;
    }
    while(existe_pion(pion_adverse,ligne-y*(j+2),colonne-x*(j+2),Tableau)!=0){
        j++;
    }

    if(i!=0 && j!=0){
        if(ligne==ligne_libre){
            if(Machine_choix(2)==0)
                c='G';
            else
                c='D';
        }
        else{
            if(Machine_choix(2)==0)
                c='H';
            else
                c='B';
        }
        if((y==-1)||(x==-1 && y==0)){
            if(c=='G'||c=='H'){
                for(j=1;j<=i;j++){
                    Tableau[ligne+y*j][colonne+x*j]='*';
                }
            }
            else{
                for(i=0;i<j;i++){
                    Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
                }
            }
        }
        else{
            if(c=='G'||c=='H'){
                for(i=0;i<j;i++){
                    Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
                }
            }
            else{
                for(j=1;j<=i;j++){
                    Tableau[ligne+y*j][colonne+x*j]='*';
                }
            }
        }
    }
    else if(i!=0){
        for(j=1;j<=i;j++){
            Tableau[ligne+y*j][colonne+x*j]='*';
        }
    }
    else if(j!=0){
        for(i=0;i<j;i++){
            Tableau[ligne-y*(i+2)][colonne-x*(i+2)]='*';
        }
    }
    else{
        Tab2[0][0]=100;
        Tab2[1][0]=100;
        Tab2[0][1]=100;
        Tab2[1][1]=100;
        printf("Slime : %c\n",1);
    }
}







///*****************************************     Patrie ---- Setting     ******************************************************** ///






void Joueur_Joueur(int Premier)
{
    int a;
    char Tableau[ligne_max][colonne_max];

    //Fonction pour initialiser la grille
    if(colonne_max==3){ // Remplir le tableau 3x3
        Tableau[0][0]='N',Tableau[0][1]='*',Tableau[0][2]='B';
        Tableau[1][0]='B',Tableau[1][1]='N',Tableau[1][2]='*';
        Tableau[2][0]='N',Tableau[2][1]='B',Tableau[2][2]='*';
    }
    else{ // Remplir le tableau 5x5 ou 5x9
        a=(colonne_max-1)/2;
        for(int i=0;i<ligne_max;i++){
            for(int j=0;j<colonne_max && i<2;j++){
                Tableau[i][j]='N';
            }
            for(int j=0;j<colonne_max && i==2;j++){
                if(j==a){
                    Tableau[i][j]='*';
                }
                else if(j%2==0 && j<a){
                    Tableau[i][j]='N';
                }
                else if(j%2!=0 && j<a){
                    Tableau[i][j]='B';
                }
                else if(j%2==0 && j>a){
                    Tableau[i][j]='B';
                }
                else{
                    Tableau[i][j]='N';
                }
            }
            for(int j=0;j<colonne_max && i>2;j++){
                Tableau[i][j]='B';
            }
        }
    }
    PlateauTest(Tableau);

    logique_jouer(Premier-1,Tableau);
    //Partie LE VELA
     ///***************************************      PARTIE LE VELA      ***************************************************** ///
}

void Jouer()
{
    int c,a,b;

    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  MENU   +--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
    printf("\t |                                                                                    |\n");
    printf("\t +                                                                                    +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 1- Fanoron-telo (3x3)                              +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 2- Fanoron-dimy (5x5)                              +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 3- Fanoron-tsivy (5x9)                             +\n");
    printf("\t |                                                                                    |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");

    do{
        printf("Entrez un choix : ");
        scanf("%d",&c);
    }while(c!=1 && c!=2 && c!=3);
    switch(c){
            case 1: *(&ligne_max)=3,*(&colonne_max)=3;
                    break;
            case 2: *(&ligne_max)=5,*(&colonne_max)=5;
                    break;
            case 3: *(&ligne_max)=5,*(&colonne_max)=9;
                    break;
    }

    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  MODE   +--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
    printf("\t |                                                                                    |\n");
    printf("\t +                                                                                    +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 1- Joueur vs Joueur                                +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 2- Joueur vs Machine                               +\n");
    printf("\t |                                                                                    |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");

    do{
        printf("Entrez un choix : ");
        scanf("%d",&c);
    }while(c!=1 && c!=2);

    a=Premier_qui_joue();
    if (c==1){
        printf("\t  ____________________________________________________________________________________     \n\n\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+  Qui va commencer   +--+--+--+--+--+--+--+--+--+--+--+\n");
        printf("\t |                                                                                    |\n");
        printf("\t +                                                                                    +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 1- Joueur 1 (Blanc)                                +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 2- Joueur 2 (Noir)                                 +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 3- Aleatoirement                                   +\n");
        printf("\t |                                                                                    |\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");
        do{
            printf("Entrez un choix : ");
            scanf("%d",&c);
        }while (c!=1 && c!=2 && c!=3);
        switch(c){
                case 1: printf("le joueur qui va commencer est : Joueur 1 (Blanc)\n");
                        Joueur_Joueur(1);
                        break;
                case 2: printf("le joueur qui va commencer est : Joueur 2 (Noir)\n");
                        Joueur_Joueur(2);
                        break;
                case 3:
                        printf("le joueur qui va commencer est : Joueur %d (1=Blanc / 2=Noir)\n",a+1);
                        Joueur_Joueur(a+1);
                        break;
        }
    }
    else {
        printf("\t  _____________________________________________________________________________________   \n\n\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  NIVEAU  +--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
        printf("\t |                                                                                     |\n");
        printf("\t +                                                                                     +\n");
        printf("\t |                                 ----------------                                    |\n");
        printf("\t +                                 1- Facile                                           +\n");
        printf("\t |                                 ----------------                                    |\n");
        printf("\t +                                 2- Moyen                                            +\n");
        printf("\t |                                 ----------------                                    |\n");
        printf("\t +                                 3- Difficile                                        +\n");
        printf("\t |                                                                                     |\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");
        do{
            printf("Entrez un choix : ");
            scanf("%d",&b);
        }while ( b!=1 && b!=2 && b!=3);
        switch(b){
                case 1: printf("Le niveau sera Facile (Random)\n");
                        break;
                case 2: printf("Le niveau sera Moyen (Random + Coup remportant le plus)\n");
                        break;
                case 3: printf("Le niveau sera Difficile (Intelligence evoluee)\n");
                        break;
        }

        printf("\t  ____________________________________________________________________________________     \n\n\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+  Qui va commencer   +--+--+--+--+--+--+--+--+--+--+--+\n");
        printf("\t |                                                                                    |\n");
        printf("\t +                                                                                    +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 1- Homme (Blanc)                                   +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 2- Machine (Noir)                                  +\n");
        printf("\t |                                 ----------------                                   |\n");
        printf("\t +                                 3- Aleatoirement                                   +\n");
        printf("\t |                                                                                    |\n");
        printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");
        do{
            printf("Entrez un choix : ");
            scanf("%d",&c);
        }while ((c!=1)&&(c!=2)&&(c!=3));
        switch(c){
                case 1: printf("le joueur qui va commencer est : Homme  (Blanc)\n");
                        Joueur_Machine_facile(1);
                        break;
                case 2: printf("le joueur qui va commencer est : Machine (Noir)\n");
                        Joueur_Machine_facile(2);
                        break;
                case 3: if (a==0){
                            printf("le joueur qui va commencer est : Homme (Blanc)\n");
                            Joueur_Machine_facile(1);
                        }
                        else{
                            printf("le joueur qui va commencer est : Machine (Noir)\n");
                            Joueur_Machine_facile(2);
                        }
                        break;
        }
    }
}

void Regles()
{
    int c;

    // regles du jeu :
    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  %c Regles    +--+--+--+--+--+--+--+--+--+--+--+-+\n",15);
    printf("\t |                                                                                      |\n");
    printf("\t +    %c 1 Plateau de jeu.                                                               +\n",16);
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c 44 Pions, 22 de chaque couleur.                                                 +\n",16);
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c Il existe deux facons de capturer des pions:                                    +\n",16);
    printf("\t |       %c Par approche: un joueur deplace l un de ses pions vers un ou plusieurs       |\n",4);
    printf("\t +   pions adverses alignes. Le joueur capture tous les pions de l alignement.          +\n");
    printf("\t |       %c Par eloignement: un joueur deplace l un de ses pions en s eloignant d un ou  |\n",4);
    printf("\t +   plusieurs pions adverses aligne. Le joueur capture tous les pions de l alignement. +\n");
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c Realiser des prises multiples avec un seul pion, sous condition :               +\n",16);
    printf("\t |       %c Ne pas repasser deux fois sur la meme case                                   |\n",4);
    printf("\t +       %c Changer de direction entre les deux prises.                                  +\n",4);
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c Toute prise possible doit etre realisee.                                        +\n",16);
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c Les prises multiples sont interdites sur le premier coup de chaque joueur.      +\n",16);
    printf("\t |    ---------------------------------------------                                     |\n");
    printf("\t +    %c Le but du jeu est de prendre toutes les pieces de l adversaire.                 +\n",16);
    printf("\t |                                                                                      |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");


    // Retour au Menu
    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  RETOUR ?   +--+--+--+--+--+--+--+--+--+--+--+-+\n");
    printf("\t |                                                                                    |\n");
    printf("\t +                                                                                    +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 1- OUI                                             +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 2- NON                                             +\n");
    printf("\t |                                                                                    |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");
    do{
        printf("Entrez un choix : ");
        scanf("%d",&c);
    }while ((c!=1)&&(c!=2));
    if(c==1)
        depart_choix();
    else
        printf("\n Au revoir ! %c \n",3);
}

void Quitter()
{
    int c;
    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  RETOUR ?   +--+--+--+--+--+--+--+--+--+--+--+-+\n");
    printf("\t |                                                                                    |\n");
    printf("\t +                                                                                    +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 1- NON                                             +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 2- OUI                                             +\n");
    printf("\t |                                                                                    |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");
    do{
        printf("Entrez un choix : ");
        scanf("%d",&c);
    }while ((c!=1)&&(c!=2));
    if(c==2)
        depart_choix();
    else
        printf("\n Au revoir ! ");
        color(12,14);printf("%c \n",3);color(0,14);
}


void depart_choix()
{
    int choix;

    printf("\t  ____________________________________________________________________________________     \n\n\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+  MENU   +--+--+--+--+--+--+--+--+--+--+--+--+--+\n");
    printf("\t |                                                                                    |\n");
    printf("\t +                                                                                    +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 1- Jouer                                           +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 2- Regles                                          +\n");
    printf("\t |                                 ----------------                                   |\n");
    printf("\t +                                 3- Quitter                                         +\n");
    printf("\t |                                                                                    |\n");
    printf("\t +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+---+--+--+--+--+--+--+--+--+--+\n");

    do{
            printf("Entrez un choix (1 , 2 , 3) :\n");
            scanf("%d",&choix);
    }while((choix!=1)&&(choix!=2)&&(choix!=3));
    if (choix==1)
        Jouer();
    if (choix==2)
        Regles();
    if (choix==3)
        Quitter();
}


int main()
{
    printf("\t  FFFFFFF      A       N      N   OOOOOO   R R R     OOOOOO   N      N       A       \n");
    printf("\t  F           A A      N N    N  O      O  R    R   O      O  N N    N      A A      \n");
    printf("\t  FFFFFFF    A   A     N  N   N  O      O  R R R    O      O  N  N   N     A   A     \n");
    printf("\t  F         A A A A    N   N  N  O      O  R R      O      O  N   N  N    A A A A    \n");
    printf("\t  F        A       A   N    N N  O      O  R   R    O      O  N    N N   A       A   \n");
    printf("\t  F       A         A  N      N   OOOOOO   R     R   OOOOOO   N      N  A         A  \n");


    depart_choix();
    depart_choix();

    return 0;
}

