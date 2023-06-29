//MAN ANDREI VLAD 311 CD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"


/* Adauga un angajat nou in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL, 
           atunci employee_name e primul om din ierarhie.
 */
Tree hire(Tree tree, char *employee_name, char *manager_name) {
    
    if((tree == NULL)&&(manager_name == NULL)) {
        Tree employee = malloc(sizeof(TreeNode));
        employee->direct_employees_no = 0;
        employee->name = malloc(10*sizeof(char));
        strcpy(employee->name,employee_name);
        employee->team = (TreeNode**)malloc(100*sizeof(TreeNode));
        employee->manager = NULL;
        
        return employee;
    } else if (strcmp(tree->name,manager_name)==0) {
        
        Tree employee = malloc(sizeof(TreeNode));
        employee->direct_employees_no = 0;
        employee->name = malloc(10*sizeof(char));
        strcpy(employee->name,employee_name);
        employee->team = (TreeNode**)malloc(100*sizeof(TreeNode));

        employee->manager = tree;
        if(tree->direct_employees_no == 0) {
            tree->team[tree->direct_employees_no] = employee;
            tree->direct_employees_no ++;
        } else {

            // char *aux1 = calloc(10,sizeof(char));
            // aux1 = strtok(employee_name,"a");
            // int aux_nr1 = atoi(aux1);

            int ok = 1;
            for(int i = 0; i < tree->direct_employees_no; i++) {

                // char *aux2 = calloc(10,sizeof(char));
                // aux2 = strtok(tree->team[i]->name,"a");
                // int aux_nr2 = atoi(aux2);

                if(strcmp(employee_name,tree->team[i]->name)<0) {
                    
                    //int x = i;
                    //Tree aux_struct = tree->team[tree->direct_employees_no];
                    for(int j = tree->direct_employees_no; j > i; j--) {
                        tree->team[j] = tree->team[j-1];
                    }
                    tree->team[i] = employee;
                    tree->direct_employees_no ++;
                    ok=0;
                    //tree->team[tree->direct_employees_no] = aux_struct;
                    break;
                }
            }
            if(ok) {
                tree->team[tree->direct_employees_no] = employee;
                tree->direct_employees_no ++;
            }

            
        }
        return tree;
    } else {
        for(int i = 0; i < tree->direct_employees_no; i ++) {
            tree->team[i] = hire(tree->team[i],employee_name,manager_name);
        }
    }
    return tree;
}

/* Sterge un angajat din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */

Tree find_by_name(Tree tree, char *employee_name) {
    if(tree == NULL) {
        return NULL;
    }
    if(strcmp(tree->name,employee_name)==0) {
        return tree;
    }
    for(int i = 0; i < tree->direct_employees_no; i ++) {
        Tree aux = find_by_name(tree->team[i],employee_name);
        if(aux) {
            return aux;
        }
    }
    return NULL;
}

Tree fire(Tree tree, char *employee_name) {

    Tree toFire = find_by_name(tree,employee_name);

    if((toFire == NULL)||(toFire == tree)) {
        return tree;
    }

    for(int i = 0; i < toFire->manager->direct_employees_no; i ++) {
        if(strcmp(toFire->name,toFire->manager->team[i]->name)==0) {
            for(int j = i; j < toFire->manager->direct_employees_no - 1; j++) {
                toFire->manager->team[j] = toFire->manager->team[j+1];
            }
            toFire->manager->direct_employees_no --;
            break;
        }
    }
    for(int i = 0; i < toFire->direct_employees_no; i++) {    

        int ok = 1;

        for(int x = 0; x < toFire->manager->direct_employees_no; x++) {

            if(strcmp(toFire->team[i]->name,toFire->manager->team[x]->name)<0) {

                for(int j = toFire->manager->direct_employees_no; j > x; j--) {
                    toFire->manager->team[j] = toFire->manager->team[j-1];
                }

                toFire->manager->team[x] = toFire->team[i];
                toFire->team[i]->manager = toFire->manager;
                toFire->manager->direct_employees_no ++;
                ok=0;                    
                break;
            }
        }
        if(ok) {
            toFire->manager->team[toFire->manager->direct_employees_no] = toFire->team[i];
            toFire->team[i]->manager = toFire->manager;
            toFire->manager->direct_employees_no ++;
        }
        
    }
    free(toFire->team);
    free(toFire->name);
    free(toFire);
    return tree;
    
}

/* Promoveaza un angajat in ierarhie. Verifica faptul ca angajatul e cel putin 
 * pe nivelul 2 pentru a putea efectua operatia.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 *
 * return: intoarce ierarhia modificata.
 */
Tree promote(Tree tree, char *employee_name) {

    Tree aux = find_by_name(tree,employee_name);
    if((aux != NULL)&&(aux->manager != tree)&&(aux != tree)) {
        char* new_manager = malloc(10*sizeof(char));
        strcpy(new_manager,aux->manager->manager->name);
        tree = fire(tree,employee_name);
        tree = hire(tree,employee_name,new_manager);
        free(new_manager);
    }
    return tree;
}

/* Muta un angajat in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_employee(Tree tree, char *employee_name, char *new_manager_name) {
    Tree aux = find_by_name(tree,employee_name);
    if((aux != NULL)&&(aux != tree)&&(strcmp(aux->manager->name,new_manager_name))) {
        tree = fire(tree,employee_name);
        tree = hire(tree,employee_name,new_manager_name);
    }
    return tree;
}

/* Muta o echipa in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei mutate
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_team(Tree tree, char *employee_name, char *new_manager_name) {
    Tree toMove = find_by_name(tree,employee_name);
    Tree newManager = find_by_name(tree,new_manager_name);

    if((toMove == tree)||(toMove == NULL)) {
        return tree;
    }

    for(int i = 0; i < toMove->manager->direct_employees_no; i ++) {
        if(strcmp(toMove->name,toMove->manager->team[i]->name)==0) {
            for(int j = i; j < toMove->manager->direct_employees_no - 1; j++) {
                toMove->manager->team[j] = toMove->manager->team[j+1];
            }
            toMove->manager->direct_employees_no --;
            break;
        }
    }
    int ok = 1;
    for(int x = 0; x < newManager->direct_employees_no; x++) {
        if(strcmp(toMove->name,newManager->team[x]->name)<0) {

            for(int j = newManager->direct_employees_no; j > x; j--) {
                newManager->team[j] = newManager->team[j-1];
            }

            newManager->team[x] = toMove;
            toMove->manager = newManager;
            newManager->direct_employees_no ++;
            ok=0;                    
            break;
        }
    }
    if(ok) {
        newManager->team[newManager->direct_employees_no] = toMove;
        toMove->manager = newManager;
        newManager->direct_employees_no ++;
    }

    return tree;
}

/* Concediaza o echipa din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire_team(Tree tree, char *employee_name) {

    Tree toFire = find_by_name(tree,employee_name);
    if((toFire == NULL)||(toFire == tree)) {
        return tree;
    }

    for(int i = 0; i < toFire->manager->direct_employees_no; i ++) {
        if(strcmp(toFire->name,toFire->manager->team[i]->name)==0) {
            for(int j = i; j < toFire->manager->direct_employees_no - 1; j++) {
                toFire->manager->team[j] = toFire->manager->team[j+1];
            }
            toFire->manager->direct_employees_no --;
            break;
        }
    }
    destroy_tree(toFire);
    return tree;
}

/* Afiseaza toti angajatii sub conducerea unui angajat.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei
 */

void aux_gebm(Tree tree, Tree team) {
    if(tree == NULL) {
        return;
    } else {

        if(team->direct_employees_no == 0) {
            team->team[team->direct_employees_no] = tree;
            team->direct_employees_no ++;
        } else {

            int ok = 1;
            for(int i = 0; i < team->direct_employees_no; i++) {

                if(strcmp(tree->name,team->team[i]->name)<0) {
                    
                    for(int j = team->direct_employees_no; j > i; j--) {
                        team->team[j] = team->team[j-1];
                    }
                    team->team[i] = tree;
                    team->direct_employees_no ++;
                    ok=0;

                    break;
                }
            }
            if(ok) {
                team->team[team->direct_employees_no] = tree;
                team->direct_employees_no ++;
            }
            
        }

        for(int i = 0; i < tree->direct_employees_no; i++) {
            aux_gebm(tree->team[i],team);
        }

    }
    return;
}

void get_employees_by_manager(FILE *f, Tree tree, char *employee_name) {
    Tree manager = find_by_name(tree,employee_name);

    Tree team = malloc(sizeof(TreeNode));
    team->direct_employees_no = 0;
    team->name = malloc(10*sizeof(char));
    team->team = (TreeNode**)malloc(100*sizeof(TreeNode));
    team->manager = NULL;


    aux_gebm(manager,team);
    for(int i = 0; i < team->direct_employees_no; i++) {
        fprintf(f,"%s ",team->team[i]->name);
    }
    fprintf(f,"\n");

    free(team->team);
    free(team->name);
    free(team);
    return;
}

/* Afiseaza toti angajatii de pe un nivel din ierarhie.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * level: nivelul din ierarhie
 */
int node_level(Tree tree) {
    int x=0;
    while(tree->manager != NULL) {
        x++;
        tree = tree->manager;
    }
    return x;
}

void aux_gebl(Tree tree, Tree team, int level) {
    if(tree == NULL) {
        return;
    } else {
        int x = node_level(tree);
        if(x < level) {
            for(int i = 0; i < tree->direct_employees_no; i++) {
            aux_gebl(tree->team[i],team,level);
            }
        } else if ( x == level) {

            if(team->direct_employees_no == 0) {
            team->team[team->direct_employees_no] = tree;
            team->direct_employees_no ++;
            } else {

                int ok = 1;
                for(int i = 0; i < team->direct_employees_no; i++) {

                    if(strcmp(tree->name,team->team[i]->name)<0) {
                        
                        for(int j = team->direct_employees_no; j > i; j--) {
                            team->team[j] = team->team[j-1];
                        }
                        team->team[i] = tree;
                        team->direct_employees_no ++;
                        ok=0;

                        break;
                    }
                }
                if(ok) {
                    team->team[team->direct_employees_no] = tree;
                    team->direct_employees_no ++;
                }
            }
        }   
    }
}

void get_employees_by_level(FILE *f, Tree tree, int level) {

    Tree team = malloc(sizeof(TreeNode));
    team->direct_employees_no = 0;
    team->name = malloc(10*sizeof(char));
    team->team = (TreeNode**)malloc(100*sizeof(TreeNode));
    team->manager = NULL;

    aux_gebl(tree,team,level);
    for(int i = 0; i < team->direct_employees_no; i++) {
        fprintf(f,"%s ",team->team[i]->name);
    }
    fprintf(f,"\n");

    free(team->team);
    free(team->name);
    free(team);
    return;
}

/* Afiseaza angajatul cu cei mai multi oameni din echipa.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */

void aux_gbm(Tree tree, Tree team, int* max) {
    if(tree == NULL) {
        return;
    } else {
        if(tree->direct_employees_no == *max) {
            if(team->direct_employees_no == 0) {
            team->team[team->direct_employees_no] = tree;
            team->direct_employees_no ++;
            } else {

                int ok = 1;
                for(int i = 0; i < team->direct_employees_no; i++) {

                    if(strcmp(tree->name,team->team[i]->name)<0) {
                        
                        for(int j = team->direct_employees_no; j > i; j--) {
                            team->team[j] = team->team[j-1];
                        }
                        team->team[i] = tree;
                        team->direct_employees_no ++;
                        ok=0;

                        break;
                    }
                }
                if(ok) {
                    team->team[team->direct_employees_no] = tree;
                    team->direct_employees_no ++;
                }
            }
        } else if(tree->direct_employees_no > *max) {
            team->team[0] = tree;
            team->direct_employees_no = 1;
            *max = tree->direct_employees_no; 
        }
        for(int i = 0; i < tree->direct_employees_no; i++) {
            aux_gbm(tree->team[i],team,max);
        }
    }
}

void get_best_manager(FILE *f, Tree tree) {

    Tree team = malloc(1*sizeof(TreeNode));
    team->direct_employees_no = 0;
    team->name = malloc(10*sizeof(char));
    team->team = (TreeNode**)malloc(100*sizeof(TreeNode));
    team->manager = NULL;

    int max=0;
    aux_gbm(tree,team,&max);
    for(int i = 0; i < team->direct_employees_no; i++) {
        fprintf(f,"%s ",team->team[i]->name);
    }
    fprintf(f,"\n");

    free(team->team);
    free(team->name);
    free(team);

    return;
}

/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */
Tree hire2(Tree manager, Tree employee){
    int nr;
        if(manager->direct_employees_no == 0){
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            //manager->team = (Tree *)malloc(nr*sizeof(Tree));
            manager->team[0]=employee;  
        }
        else{
            manager->direct_employees_no++;
            nr = manager->direct_employees_no;
            //manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
            manager->team[nr-1] = employee;
        }
        Tree temp;
            for (int i = 0; i < nr-1; i++)       
                for (int j = 0; j < nr-i-1; j++) 
                    if (strcmp(manager->team[j]->name, manager->team[j+1]->name) >0) {
                        temp = manager->team[j];
                        manager->team[j] = manager->team[j+1];
                        manager->team[j+1] = temp;
                    }
        employee->manager = manager;
    return manager;
}
Tree fire2( Tree manager, char* employee_name){
    if (manager->name == employee_name)
        return NULL;
    else{
        int i, j, nr, gasit = 0;
    for( i=0; i< manager->direct_employees_no; i++ ){
        if(strcmp(manager->team[i]->name,employee_name)==0){
            manager->team[i]->manager = NULL;
            for(j=i; j<manager->direct_employees_no-1; j++) {
                manager->team[j] = manager->team[j+1];
            }
            manager->direct_employees_no--;
            break;
        }
    }
    nr = manager->direct_employees_no;
    //manager->team = (Tree *)realloc( manager->team, nr*sizeof(Tree));
    return manager;
    }
}
Tree reorganize(Tree tree, char *employee_name) {
    Tree employee, manager, aux, aux2, aux3;

    Tree whereToHire,newToHire,nextManager;

    employee = find_by_name(tree, employee_name);

    if((employee == NULL)||(employee == tree)) {
        return tree;
    }
    
    manager = employee->manager;
    manager = fire2(manager, employee_name);
    employee->manager = NULL;
    
    whereToHire = employee;
    newToHire = manager;

    while(newToHire->manager != NULL) {

        nextManager = newToHire->manager;
        nextManager = fire2(nextManager,newToHire->name);
        whereToHire = hire2(whereToHire, newToHire);
        whereToHire = newToHire;
        newToHire = nextManager;

    }

    whereToHire = hire2(whereToHire,newToHire);

    return employee;
}

/* Parcurge ierarhia conform parcurgerii preordine.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void preorder_traversal(FILE *f, Tree tree) {
    if(tree != NULL) {
        if(tree->manager == NULL) {
            fprintf(f,"%s ",tree->name);
        } else {
            fprintf(f,"%s-%s ",tree->name,tree->manager->name);
        }
        for(int i = 0; i < tree->direct_employees_no; i++) {
            preorder_traversal(f,tree->team[i]);
        }
        if(tree->manager == NULL) {
            fprintf(f,"\n");
        }
	}
    return;
}
void preorder_traversal_console(Tree tree) {
    if(tree != NULL) {
        if(tree->manager == NULL) {
            printf("%s ",tree->name);
        } else {
            printf("%s-%s ",tree->name,tree->manager->name);
        }
        for(int i = 0; i < tree->direct_employees_no; i++) {
            preorder_traversal_console(tree->team[i]);
        }
        if(tree->manager == NULL) {
            printf("\n");
        }
	}
    return;
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */
void destroy_tree(Tree tree) {
    if(tree != NULL) {
        for(int i = 0; i < tree->direct_employees_no; i++) {
            destroy_tree(tree->team[i]);
        }
        free(tree->name);
        free(tree->team);
        free(tree);
    }
    return;
}

