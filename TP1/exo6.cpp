#include <iostream>

using namespace std;

struct Noeud{
    int donnee;
    Noeud* suivant;
};

struct Liste{
    Noeud* premier;
};

struct DynaTableau{
    int* donnees;
    int maxSize;
    int size;
};


// --- LISTE ---
void initialise(Liste* liste)
{
    liste->premier = nullptr;
}

bool est_vide(const Liste* liste)
{
    return (liste->premier == nullptr);
}

void ajoute(Liste* liste, int valeur)
{
    Noeud* newNoeud = new Noeud;
    newNoeud->donnee = valeur;

    if(liste->premier == nullptr){
        liste->premier = newNoeud;
    }
    else{
        Noeud* tmpNoeud = liste->premier;
        while(tmpNoeud->suivant != nullptr){
            tmpNoeud = tmpNoeud->suivant;
        }
        tmpNoeud->suivant = newNoeud;
    }
}

void affiche(const Liste* liste)
{
    Noeud* tmpNoeud = liste->premier;
    while (tmpNoeud != nullptr) {
        cout << tmpNoeud -> donnee << "\n";
        tmpNoeud = tmpNoeud -> suivant;
    }
}

int recupere(const Liste* liste, int n)
{
    Noeud* tmpNoeud = liste->premier;
    for(int i=0; i < n; i++){
        if(tmpNoeud == nullptr){
            return -1;
        }
        tmpNoeud = tmpNoeud->suivant;
    }

    return tmpNoeud->donnee;
}

int cherche(const Liste* liste, int valeur)
{
    Noeud* tmpNoeud = liste->premier;
    int result = 0;
    while (tmpNoeud != nullptr) {
        if(tmpNoeud->donnee == valeur){
            return result;
        }
        tmpNoeud = tmpNoeud -> suivant;
        result ++;
    }

    return -1;
}

void stocke(Liste* liste, int n, int valeur)
{
    Noeud* tmpNoeud = liste->premier;
    for(int i=0; i < n; i++){
        if(tmpNoeud == nullptr){
            return;
        }
        tmpNoeud = tmpNoeud->suivant;
    }
    tmpNoeud->donnee = valeur;
}


// --- TABLEAU ---
void ajoute(DynaTableau* tableau, int valeur)
{
    if(tableau->size >= tableau->maxSize){
        tableau->maxSize *= 2;

        int* newDonnees = new int[tableau->maxSize];
        for(int i=0; i<tableau->size; i++){
            newDonnees[i] = tableau->donnees[i];
        }
        delete[] tableau->donnees;
        tableau->donnees = newDonnees;
    }
    tableau->donnees[tableau->size] = valeur;
    tableau->size ++;
}

void initialise(DynaTableau* tableau, int capacite)
{
    tableau->maxSize = capacite;
    tableau->size = 0;
    tableau->donnees = new int[capacite];
}

bool est_vide(const DynaTableau* liste)
{
    return (liste->size == 0);
}

void affiche(const DynaTableau* tableau)
{
    for(int i = 0; i < tableau->size; i++){
        cout << tableau->donnees[i] << endl;
    }
}

int recupere(const DynaTableau* tableau, int n)
{
    if(tableau->size > n){
        return tableau->donnees[n];
    }
    return -1;
}

int cherche(const DynaTableau* tableau, int valeur)
{
    for(int i=0; i<tableau->size; i++){
        if(tableau->donnees[i] == valeur){
            return i;
        }
    }
    return -1;
}

void stocke(DynaTableau* tableau, int n, int valeur)
{
    if(tableau->size >= n){
        tableau->donnees[n] = valeur;
    }
}

//void pousse_file(DynaTableau* liste, int valeur)
void pousse_file(Liste* liste, int valeur)
{

}

//int retire_file(Liste* liste)
int retire_file(Liste* liste)
{
    return 0;
}

//void pousse_pile(DynaTableau* liste, int valeur)
void pousse_pile(Liste* liste, int valeur)
{

}

//int retire_pile(DynaTableau* liste)
int retire_pile(Liste* liste)
{
    return 0;
}


int main()
{
    Liste liste;
    initialise(&liste);
    DynaTableau tableau;
    initialise(&tableau, 5);

    if (!est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (!est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    for (int i=1; i<=7; i++) {
        ajoute(&liste, i*7);
        ajoute(&tableau, i*5);
    }

    if (est_vide(&liste))
    {
        std::cout << "Oups y a une anguille dans ma liste" << std::endl;
    }

    if (est_vide(&tableau))
    {
        std::cout << "Oups y a une anguille dans mon tableau" << std::endl;
    }

    std::cout << "Elements initiaux:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    std::cout << "5e valeur de la liste " << recupere(&liste, 4) << std::endl;
    std::cout << "5e valeur du tableau " << recupere(&tableau, 4) << std::endl;

    std::cout << "21 se trouve dans la liste à " << cherche(&liste, 21) << std::endl;
    std::cout << "15 se trouve dans la liste à " << cherche(&tableau, 15) << std::endl;

    stocke(&liste, 4, 7);
    stocke(&tableau, 4, 7);

    std::cout << "Elements après stockage de 7:" << std::endl;
    affiche(&liste);
    affiche(&tableau);
    std::cout << std::endl;

    Liste pile; // DynaTableau pile;
    Liste file; // DynaTableau file;

    initialise(&pile);
    initialise(&file);

    for (int i=1; i<=7; i++) {
        pousse_file(&file, i);
        pousse_pile(&pile, i);
    }

    int compteur = 10;
    while(!est_vide(&file) && compteur > 0)
    {
        std::cout << retire_file(&file) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    compteur = 10;
    while(!est_vide(&pile) && compteur > 0)
    {
        std::cout << retire_pile(&pile) << std::endl;
        compteur--;
    }

    if (compteur == 0)
    {
        std::cout << "Ah y a un soucis là..." << std::endl;
    }

    return 0;
}
