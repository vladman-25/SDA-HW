///// MAN ANDREI VLAD 311 CD /////
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util/print_board.h"
#include "util/scrabble.h"

#define SIZE 15

char game_board[SIZE][SIZE] = {
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'}};

int score[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
/////////////////A B C D E F G H I J K L M N O P  Q R S T U V W X Y  Z

char *remove_white_spaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}
/////////////////////////////////////////////////////////////////////////////
void task0() {
    print_board(game_board);
}
//////////////////////////////////////////////////////////////////////////////
void task1(uint32_t Y, uint32_t X, uint32_t D, char *str) {
    int k = 0;
    if(D == 0) {
        while(str[k]!='\0') {
            game_board[Y][X+k] = str[k];
            k++;
        }
    } else {
        while(str[k]!='\0') {
            game_board[Y+k][X] = str[k];
            k++;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////
uint32_t task2(char *str) {
    int k = 0;
    int litera;
    int scor=0;
    while(str[k]!='\0') {
        litera = (int)str[k]-65;
        scor += score[litera];
        k++;
    }
    return scor;
}
///////////////////////////////////////////////////////////////////////////////
uint32_t task3A(char *str,char *AAstr) {
    int k = 0;
    uint32_t res = 0;
    while(str[k]!='\0') {
        if((str[k]==AAstr[0])&&(str[k+1]==AAstr[1])) {
            res = 1;
        }
        k++;
    }
    return res;
}

uint32_t task3(uint32_t Y, uint32_t X, uint32_t D, char *str, 
                                    char *XXstr,char *YYstr) {
    int k = 0;
    uint32_t multi = 1;
    uint32_t temp = 1;
    if(D == 0) {
        while(str[k]!='\0') {
            if(bonus_board[Y][X+k] == 1) {
                if(task3A(str, XXstr) == 1) {
                    multi *=2;
                }
            }   
            if(bonus_board[Y][X+k] == 2) {
                if(task3A(str, YYstr) == 1) {
                    temp *=3;
                }
            }
            k++;
        }
        if((str[k-2]==YYstr[0])&&(str[k-1]==YYstr[1])) {
            multi *= temp;
        }
    } else {
        while(str[k]!='\0') {
            if(bonus_board[Y+k][X] == 1) {
                if(task3A(str, XXstr) == 1) {
                    multi *=2;
                }
            }
            if(bonus_board[Y+k][X] == 2) {
                if(task3A(str, YYstr) == 1) {
                    temp *=3;
                }
            }
            k++;
        }
        if((str[k-2]==YYstr[0])&&(str[k-1]==YYstr[1])) {
            multi *= temp;
        }
        
    }
    return multi;
}
//////////////////////////////////////////////////////////////////////////
uint32_t task4find(char *word,int posy,int posx) {
    int i,j;
    int x=0,y=0;
    for(i = posy; i < SIZE; i++) {
        for(j = posx; j < SIZE; j++) {
            if(game_board[i][j]==word[0]) {
                y=i;
                x=j;
                return 100*y+x;
            }
        }
        posx = 0;
    }
    return -1;
}

uint32_t task4check(char *word, int posy, int posx) {
    int oriz=1,vert=1,k=1;

    while(word[k]!='\0') {
        if((game_board[posy][posx+k]!='.')||(posx + k >= SIZE)) {
            oriz = 0;
            break;
        }
        k++;
    }
    k=1;

    while(word[k]!='\0') {
        if((game_board[posy+k][posx]!='.')||(posy + k >= SIZE)) {
            vert = 0;
            break;
        }
        k++;
    }

    if((oriz == 1)&&(vert == 1)) {
        return 0;
    }

    if(oriz == 1) {
        return 0;
    }
    if(vert == 1) {
        return 1;
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
int main() {

    /* Se citeste numarul task-ului sub forma de string si este transformat
    in numar */
    char task_str[10];
    fgets(task_str,10,stdin);
    strtok(task_str, "\n");
    char *ptr;
    uint32_t task;
    task = strtol(task_str,&ptr,10);

    uint32_t i;
    char XX[10] = " ";
    char YY[10] = " ";

    if(task == 0) {
        task0();
    }

    if(task >= 1) {

        /* De la task-ul 3 se citesc si XX si YY */
        if(task >= 3) {
            fgets(XX,10,stdin);
            strtok(XX, "\n");

            fgets(YY,10,stdin);
            strtok(YY, "\n");
        }

        /* Este citit <N> sub forma de string, apoi este prelucrat
        in intreg */
        char N_str[10];
        fgets(N_str,10,stdin);
        strtok(N_str, "\n");
        uint32_t N;
        N = strtol(N_str,&ptr,10);

        char line[30] = " ";
        uint32_t Y,X,D;
        uint32_t W=0,T=0;

        /* Aceste variabile sunt folosite pt task 4 si 5 */
        char usedwords[2*N][SIZE];
        int count = 0;
        int Ytask6[N],Xtask6[N],Dtask6[N];

        for(i = 0; i < N; i++) {

            /* Pentru fiecare linie introdusa, aceasta este citita iar
            datele sunt prelucrate */
            fgets(line,30,stdin);
            strtok(line, "\n");
            Y = strtol(line,&ptr,10);
            X = strtol(ptr,&ptr,10);
            D = strtol(ptr,&ptr,10);
            remove_white_spaces(ptr);
            if(task != 6) {
               task1(Y,X,D,ptr); 
            } else {
                Ytask6[i] = Y;
                Xtask6[i] = X;
                Dtask6[i] = D;
            }

            if(task == 2) {
                /* Pt task 2, punctajul este calculat pentru fiecare jucator, 
                fara bonusuri, W ia cuvintele de pe pozitiile 2k, iar T 
                cuvintele de pe pozitiile 2k+1 */
                if(i%2 == 0) {
                    W += task2(ptr);
                } else {
                    T += task2(ptr);
                }
            }

            if((task == 3)||(task == 5)) {
                /* Pt task-urile 3 si 5 vom calcula punctajele jucatorilor
                cu tot cu bonusuri. Functia <task2> calculeaza punctajul
                iar functia <task3> calculeaza multiplier-ul. */
                if(i%2 == 0) {
                    W += task2(ptr)*task3(Y,X,D,ptr,XX,YY);
                } else {
                    T += task2(ptr)*task3(Y,X,D,ptr,XX,YY);
                }
            }
            
            /* Pt task 4 stocam cuvintele deja folosite. */
            if(task >= 4) {
                strcpy(usedwords[count],ptr);
                count++;
            }
        }
///////////////////////////////////////////////////////////////////////////////

        /* In functie de numarul task-ului se afiseaza ce trebuie */
        if(task == 1) {
            task0();
        }

        if((task == 2)||(task == 3)) {
            printf("Player 1: %d Points\n",W);
            printf("Player 2: %d Points\n",T);
        }

        if(task >= 4) {
            
            int countTask6,iTask6;
            if(task == 6) {
                countTask6 = N;
            } else {
                countTask6 = 1;
            }

            for(iTask6 = 0; iTask6 < countTask6; iTask6++) {

                int j, condition,condition2 = 1;
                int maxpoints = 0,points;
                char maxword[15];
                int maxwordy=0,maxwordx=0,maxwordd=0;

                if( task == 6) {
                    task1(Ytask6[iTask6],Xtask6[iTask6],Dtask6[iTask6],usedwords[iTask6]);
                    W += task2(usedwords[iTask6])*task3(Ytask6[iTask6],Xtask6[iTask6],Dtask6[iTask6],usedwords[iTask6],XX,YY);
                }

                condition2 = 1;
                maxpoints = 0;
                

                for(i = 0; i < NUM_WORDS; i++) {

                    /* La task-ul 4 trb gasit primul cuvant; astfel <condition2>
                    arata ca s-a gasit cuvantul, terminand iteratia de cuvinte */
                    if(task == 4) {
                        if(condition2 == 0) {
                            break;
                        }
                    }

                    /* Se verifica daca iteratia actuala, cuvantul selectat,  
                    se regaseste deja in valorile introduse din teste; in caz
                    ca acest cuvant a fost deja utilizat, <condition> nu va 
                    permite intrarea in urmatorul pas */
                    condition = 1;
                    for(j = 0; j < count + iTask6; j++) {
                        if(strcmp(words[i],usedwords[j])==0) {
                            condition = 0;
                            break;
                        }
                    }

                    /* Cuvantul ales nu se regaseste printre cele deja utilizate,
                    acesta trece la urmatorul pas */
                    if(condition == 1) {

                        int posx=0, posy=0,posyx,res;

                        while(1) {

                    /* Functia <task4find> verifica daca prima litera a cuvantului
                    se regasaeste sau nu pe tabla; daca nu se regaseste, intoarce
                    valoarea -1; daca se regaseste intoarce coordonatele acestuia
                    sub forma: <100*Y + X> ; stocate in <posyx> */        
                            posyx = task4find(words[i],posy,posx);
                    
                    /* Pt posyx = -1 inseamna ca avest cuvant nu are prima litera
                    pe tabla, deci nu respecta conditiile impuse; prin <break>
                    se va trece la urmatorul cuvant */
                            if(posyx == -1) {

                                break;

                            } else {

                    /* Coordonatele gasite sunt desfacute. Functia <task4check>
                    verifica daca la pozitia data, cuvantul poate fi scris pe
                    orizontala, verticala sau nu poate fi scris. Functia intoarce
                    prin <res> valoarea -1 daca nu poate fi scris, 0 daca poate
                    fi scris si pe orizontala si pe verticala, 1 daca poate fi
                    scris doar pe verticala */
                                posx = posyx%100;
                                posy = posyx/100;
                                res = task4check(words[i],posy,posx);

                    /* In cazul in care cuvantul nu poate fi scris, pozitia
                    este schimbata cu una succesiva, si se incearca iar procesul*/
                                if(res == -1) {

                                    if(posx < SIZE-1) {
                                        ++posx;
                                    } else {
                                        ++posy;
                                        posx=0;
                                    }

                                } else {

                    /* Pt task-ul 4 este de ajuns primul cuvant gasit, se scrie
                    cuvantul respectiv pe tabla, si se iese din bucla 
                    <condition2> este setat cu 0 pentru a opri tot procesul */
                                    if(task == 4) {
                                        task1(posy,posx,res,words[i]);
                                        task0();
                                        condition2=0;
                                        break;
                                    }


                                    if(task >= 5) {

                    /* Pt cuvantul din iteratia curenta, se calculeaza punctajul
                    potential pe care il ofera. Daca acest punctaj este mai mare
                    decat maximul precedent, cuvantul este tinut minte, alaturi de
                    punctaj, pozitie si directie. */
                                        points = task2(words[i]);
                                        points *= task3(posy,posx,res,words[i],XX,YY);

                                        if (points >= maxpoints) {

                                            if((points == maxpoints)&&(strcmp(words[i],maxword) != 0)) {
                                                if (posy < maxwordy) {
                                                        //printf("\n%s (%d;%d) %d\n",words[i],posy,posx,points);
                                                        maxpoints = points;
                                                        strcpy(maxword,words[i]);
                                                        maxwordx = posx;
                                                        maxwordy = posy;
                                                        maxwordd = res;                                                
                                                }
                                                if (posy == maxwordy) {
                                                    if(posx < maxwordx) {
                                                        maxpoints = points;
                                                        strcpy(maxword,words[i]);
                                                        maxwordx = posx;
                                                        maxwordy = posy;
                                                        maxwordd = res;  
                                                    }
                                                }

                                            } else if((points == maxpoints)&&(strcmp(words[i],maxword) == 0)) {
                                                

                                            } else {
                                                //printf("\n%s (%d;%d) %d\n",words[i],posy,posx,points);
                                                maxpoints = points;
                                                strcpy(maxword,words[i]);
                                                maxwordx = posx;
                                                maxwordy = posy;
                                                maxwordd = res;
                                            }
                                            
                                        }
                    /* Pt acelasi cuvant se verifica daca asezarea acestuia pe
                    alta pozitie va aduce un punctaj mai mare, astfel vom incepe
                    verificarea de la pozitia urmatoare. */
                                        if(posx < SIZE-1) {
                                            ++posx;
                                        } else {
                                            ++posy;
                                            posx=0;
                                        }

                                    }

                                }
                            }
                        }
                    }
                }
                /* Cuvantul cu punctaj maxim este gasit, se verifica daca 
                alaturi de punctajul curent va depasi punctajul adversarului
                iar apoi se executa cerinta */
                if(task == 5) {
                    if(T + maxpoints >= W) {
                        task1(maxwordy,maxwordx,maxwordd,maxword);
                        task0();
                    } else {
                        printf("Fail!");
                    }
                }
                if(task == 6) {
                    task1(maxwordy,maxwordx,maxwordd,maxword);
                    strcpy(usedwords[N + iTask6],maxword);
                    T += task2(maxword)*task3(maxwordy,maxwordx,maxwordd,maxword,XX,YY);
                    //printf("\nSe alege %s (%d;%d) %d\n",maxword,maxwordy,maxwordx,maxpoints);
                }
            }
            if(task == 6) {
                print_board(game_board);
                if(W > T) {
                    printf("Player 1 Won!");
                } else {
                    printf("Player 2 Won!");
                }
            }
            
        }
        ////////////////END OF TASK 4////////////////////////
    }
    

    return 0;    
}