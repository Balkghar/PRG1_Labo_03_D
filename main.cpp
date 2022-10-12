/*
-----------------------------------------------------------------------------------
Nom du fichier :  labo_02_taxi_groupe_g.cpp
Auteur(s) :       Bianchet Stefano, Léon Surbeck
Classe :          PRG1B
Date creation :   06.10.2022
Description :     Un programme qui calcule le prix d'un taxi en fonction de la distance parcourue,
                  du nombre de bagages et de l'heure du trajet.
Remarque(s) :     -
Compilateur :     Mingw-w64 g++ 12.1.0
-----------------------------------------------------------------------------------
*/
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(),'\n')

using namespace std;

int main() {

   // Déclaration des identificateurs
   const double TAXE_BASE        = 5.00;
   const double TAXE_BAGAGE      = 2.60;
   const double TARIF_JOUR       = 1.00;
   const double TARIF_NUIT       = 1.60;
   const int    LARGEUR          = 6;
   const int    DECIMALES        = 2;
   const int    HEURE_MIN        = 0;
   const int    HEURE_MAX        = 23;
   const int    V_MAX            = 120;
   const int    V_MIN            = 50;
   const int    DISTANCE_MIN     = 0;
   const int    DISTANCE_MAX     = 500;
   const int    BAGAGE_MIN       = 0;
   const int    BAGAGE_MAX       = 4;
   const int    HEURE_JOUR_MIN   = 8;
   const int    HEURE_JOUR_MAX   = 20;

   int          nbr_bagage;
   int          nbr_km;
   int          h_depart;
   double       prix_tot_bagages;
   double       prix_km;
   double       prix_total;
   double       vitesse_moyenne;

   // Affichage de 2 décimales après la virgule
   cout << fixed << setprecision(DECIMALES);

   // Présentation du programme à l'utilisateur

   cout << "Ce programme calcule le prix d'un taxi en fonction de la distance parcourue,"
           " du nombre de bagages et de l'heure du trajet." << endl;
   cout << endl;

   // Présentation des conditions
   cout << "Les conditions sont les suivantes" << endl;
   cout << "=================================" << endl;
   cout << "Tarif de base     : "    << setw(LARGEUR) << TAXE_BASE      << " Euros" << endl;
   cout << "Taxe par bagage   : "    << setw(LARGEUR) << TAXE_BAGAGE    << " Euros" << endl;
   cout << "Tarif jour        : "    << setw(LARGEUR) << TARIF_JOUR     << " Euros" << endl;
   cout << "Tarif nuit        : "    << setw(LARGEUR) << TARIF_NUIT     << " Euros" << endl;
   cout << "Heure du jour     :   [" << HEURE_MIN << " - " << HEURE_MAX << "]" << endl << endl;


   // Entrées utilisateur et vérification des valeurs
   cout << "Votre commande" << endl;
   cout << "==============" << endl;
   cout << "Veuillez entrer le nombre de bagages           ["
        << BAGAGE_MIN << " - " << BAGAGE_MAX << "]:";
   cin  >> nbr_bagage;
   VIDER_BUFFER;

   if (nbr_bagage < BAGAGE_MIN or nbr_bagage > BAGAGE_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer la distance en KM              ["
        << DISTANCE_MIN << " - " << DISTANCE_MAX << "]:";
   cin  >> nbr_km;
   VIDER_BUFFER;

   if (nbr_km < DISTANCE_MIN or nbr_km > DISTANCE_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer la vitesse moyenne en KM/H     ["
        << V_MIN << "-" << V_MAX <<"]: ";
   cin  >> vitesse_moyenne;
   VIDER_BUFFER;

   if (vitesse_moyenne < V_MIN or vitesse_moyenne > V_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer l'heure de depart              ["
        << HEURE_MIN << "-" << HEURE_MAX << "]: ";
   cin  >> h_depart;
   VIDER_BUFFER;

   if (h_depart < HEURE_MIN or h_depart > HEURE_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   // Calculs des sous-totaux
   prix_tot_bagages    = nbr_bagage * TAXE_BAGAGE;

   // Si l'heure de départ est entre 8h et 20h le tarif de jour est appliqué.
   // Dans le cas contraire, le tarif de nuit est appliqué.
   if (h_depart >= HEURE_JOUR_MIN and h_depart <= HEURE_JOUR_MAX){
      prix_km = nbr_km * TARIF_JOUR;
   } else {
      prix_km = nbr_km * TARIF_NUIT;
   }

   // Calcul du prix total
   prix_total = TAXE_BASE + prix_tot_bagages + prix_km;



   // Affichage du ticket
   cout << endl;
   cout << "Votre ticket" << endl;
   cout << "============" << endl;
   cout << "Prise en charge      : " << setw(LARGEUR) << TAXE_BASE         << " Euros" << endl;
   cout << "Supplements bagages  : " << setw(LARGEUR) << prix_tot_bagages  << " Euros" << endl;
   cout << "Prix du trajet       : " << setw(LARGEUR) << prix_km           << " Euros" << endl;
   cout << "Prix TOTAL           : " << setw(LARGEUR) << prix_total        << " Euros" << endl;


   // Confirmation de l'utilisateur pour quitter le programme
   cout << endl;
   cout << "Presser ENTER pour quitter" << endl;
   VIDER_BUFFER;

   return EXIT_SUCCESS;
   
}