
    MAN ANDREI VLAD 311CD TEMA 2 - README

    0. Functia <task0> apeleaza functia  < print_board > pentru a afisa
    tabla de joc;
    
    1. Functia <task1> scrie cuvantul dat la pozitia data si pe directia
    data. Se scrie pana la intalnirea caracterului '\0' care marcheaza
    sfarsitul string ului;

    2. Functia <task2> calculeaza scorul cuvantului dat, bazandu-se doar
    pe litere (fara bonus);

    3.1. Functia <task3A> verifica daca string ul dat contine cele 2 litere
    din bonus; Daca da, se intoarce 1, daca nu 0;

    3.2. Functia <task3> cauta pe directia data, incepand de la pozitiile
    X si Y date, valorile de 1 si 2 de pe tabla. Pentru valorile de 1 gasite,
    multiplier ul se inmulteste cu 2 daca se indeplineste conditia. Pt 
    valorile de 2 sunt 2 conditii. La gasirea valorii 2, prima oara verificam
    daca acest cuvant contine cele 2 caractere. Avem un multiplier temporar
    <temp> pe care il inmultim cu 3. La final, verificam daca acest cuvant
    are strict la finalul cuvantului string-ul YY, daca da <multi> se 
    inmulteste cu <temp> pt multiplier ul final.

    4.1 Functia <task4find> cauta incepand de la pozitiile posy si posx date,
    daca pe tabla se regaseste prima litera din string-ul dat. Daca da se
    intoarce o valoare formata din <100*y+x> (coordonatele respective),
    daca nu, se va intoarce -1;

    4.2 Functia <task4check> va verifica daca string-ul dat poate fi introdus
    pe verticala sau/si orizontala in tabla de joc. Acesta este verificat
    litera cu litera si trebuie sa nu intalneasca alte litere in drum ( = '.' )
    si in acelasi timp sa nu depaseasca tabla de joc. Daca nu incape,
    se intoarce valoarea -1. Daca incape pe verticala se intoarce 1. 
    Daca incape pe orizontala /si pe verticala se intoarce 0. 

    In cod veti gasi mai multe comentarii la fiecare pas al acestuia, este
    mai usor sa urmariti explicatiile acolo. Fiecare comentariu se afla
    deasupra portiunii explicate (in principiu). 
    Codul este facut astfel incat mai multe task-uri sa foloseasca aceeasi
    portiune de cod daca este nevoie.