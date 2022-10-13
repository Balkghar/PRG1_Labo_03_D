/*
-----------------------------------------------------------------------------------
Nom du fichier :  main.cpp
Auteur(s)      :  Bianchet Stefano, Léon Surbeck, Hugo Germano
Classe         :  PRG1B
Date creation  :  06.10.2022
Description    :  Un programme qui calcule le prix d'un taxi en fonction de la distance parcourue,
                  du nombre de bagages et de l'heure du trajet.
Remarque(s)    :  -
Modification(s):
Compilateur    :  gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
-----------------------------------------------------------------------------------
*/
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

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
   const int    V_MAX            = 120;
   const int    V_MIN            = 30;
   const int    DISTANCE_MIN     = 0;
   const int    DISTANCE_MAX     = 500;
   const int    BAGAGE_MIN       = 0;
   const int    BAGAGE_MAX       = 4;
   const int    HEURE_JOUR_MIN   = 8;
   const int    MINUTE_JOUR_MIN  = 0;
   const int    HEURE_JOUR_MAX   = 20;
   const int    MINUTE_JOUR_MAX  = 0;


   //déclaration des variables
   int          nbr_bagage;
   int          nbr_km;
   int          h_depart;        //l'heure de départ
   int          min_depart;      //la minute de départ
   int          h_arrivee;       //l'heure d'arrivée
   int          min_arrivee;     //la minute d'arrivée
   int          temps_h;         //l'heure du temps de trajet
   int          temps_min;       //minute du temps de trajets
   int          temp_total_min;  //temps du trajet en minutes
   int          min_jour;        //total minutes de jour du trajet
   int          min_nuit;        //total minutes de nuit du trajet
   int          temps_journee;   //total minutes pour la journéee
   int          temps_nuit;      //total minutes pour la nuit
   double       prix_tot_bagages;
   double       prix_trajet_jour;
   double       prix_trajet_nuit;
   double       prix_trajet;
   double       prix_total;
   double       vitesse_moyenne;
   double       temps_trajets;
   string       hour_depart;     //pour stocker en string l'entrée utilisateur
   string       minute_depart;   //pour stocker en string l'entrée utilisateur minute
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
   //adaptation de l'affichage par rapport  l'heure/minute
   if(MINUTE_JOUR_MAX < 10 && MINUTE_JOUR_MIN < 10){
      cout << "Tarif jour        :   " << HEURE_JOUR_MIN << "h0" << MINUTE_JOUR_MIN <<" - " << HEURE_JOUR_MAX << "h0" << MINUTE_JOUR_MAX<< "" << endl << endl;
   }
   else if(MINUTE_JOUR_MAX < 10){
      cout << "Tarif jour        :   " << HEURE_JOUR_MIN << "h" << MINUTE_JOUR_MIN <<" - " << HEURE_JOUR_MAX << "h0" << MINUTE_JOUR_MAX<< "" << endl << endl;
   }
   else if(MINUTE_JOUR_MIN < 10){
      cout << "Tarif jour        :   " << HEURE_JOUR_MIN << "h0" << MINUTE_JOUR_MIN <<" - " << HEURE_JOUR_MAX << "h" << MINUTE_JOUR_MAX<< "" << endl << endl;
   }
   else{
      cout << "Tarif jour        :   " << HEURE_JOUR_MIN << "h" << MINUTE_JOUR_MIN <<" - " << HEURE_JOUR_MAX << "h" << MINUTE_JOUR_MAX<< "" << endl << endl;
   }


   // Entrées utilisateur et vérification des valeurs
   cout << "Votre commande" << endl;
   cout << "==============" << endl;
   cout << "Veuillez entrer le nombre de bagages           ["
        << BAGAGE_MIN << " - " << BAGAGE_MAX << "]  : ";
   cin  >> nbr_bagage;
   VIDER_BUFFER;

   if (nbr_bagage < BAGAGE_MIN or nbr_bagage > BAGAGE_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer la distance en KM              ["
        << DISTANCE_MIN << " - " << DISTANCE_MAX << "]: ";
   cin  >> nbr_km;
   VIDER_BUFFER;

   if (nbr_km < DISTANCE_MIN or nbr_km > DISTANCE_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer la vitesse moyenne en KM/H     ["
        << V_MIN << "-" << V_MAX <<"] : ";
   cin  >> vitesse_moyenne;
   VIDER_BUFFER;

   if (vitesse_moyenne < V_MIN or vitesse_moyenne > V_MAX){
      cout << "Valeur incorrecte. Presser ENTER pour quitter" << endl;
      VIDER_BUFFER;
      return EXIT_SUCCESS;
   }

   cout << "Veuillez entrer l'heure de départ              [hh:mm]  : ";

   getline(cin, hour_depart, ':');                 //prend les valeurs avant ':' ref : https://stackoverflow.com/questions/19036186/time-format-hhmmss-input
   getline(cin, minute_depart);
   h_depart = stoi(hour_depart);                   //convertit string en int ref : https://www.freecodecamp.org/news/string-to-int-in-c-how-to-convert-a-string-to-an-integer-example/
   min_depart = stoi(minute_depart);
   
   // Calculs des sous-totaux
   prix_tot_bagages = nbr_bagage * TAXE_BAGAGE;


   //calcul le temps de trajet total en minutes
   temps_trajets = double(nbr_km/vitesse_moyenne);
   temps_h = trunc(temps_trajets);
   temps_min = round(double(temps_trajets - temps_h)*60);
   temp_total_min = (temps_h)*60 + temps_min;
   //calcul du temps minute en journée
   temps_journee = (HEURE_JOUR_MAX-HEURE_JOUR_MIN)*60;
   temps_journee += MINUTE_JOUR_MAX-MINUTE_JOUR_MIN;
   //calcul du temps minute la nuit
   temps_nuit = (24 - HEURE_JOUR_MAX +HEURE_JOUR_MIN)*60;
   temps_nuit += MINUTE_JOUR_MIN-MINUTE_JOUR_MAX;

   //vérifie et calcul si le départ est en journée
   if (h_depart >= HEURE_JOUR_MIN and h_depart <= HEURE_JOUR_MAX){
      //verifications si le temps de trajet dépasse sur le temps de nuit
      if(((h_depart - HEURE_JOUR_MIN)*60 + min_depart +  temp_total_min) > temps_journee){
        //minute pour la première journée
        min_jour = (HEURE_JOUR_MAX-HEURE_JOUR_MIN)*60 - (h_depart - HEURE_JOUR_MIN)*60;
        //vérifie si le trajet dépasse le temps de nuit et si oui calcul en conséquence
        if(temp_total_min - min_jour > temps_nuit){
            min_nuit = temps_nuit;
            min_jour += temp_total_min - min_jour - temps_nuit;
        }
        //si il ne dépasse passe pas, ajoute les minute à la nuit
        else{
         min_nuit = temp_total_min - min_jour;
        }
      }
      //calcul le trajet si c'est uniquemnt en journée
      else{
        min_jour = temp_total_min;
      }
   }
   //si le départ est de nuit
   else {
      //vérifie si le trajet dépasse l'heure de nuit
      if((24 - h_depart)*60 + min_depart +  temp_total_min > temps_nuit){
         min_nuit = temps_nuit - ((24 - h_depart)*60 + min_depart);
         //check s'il dépasse sur une autre journée et calcul en conséquence
         if(temp_total_min - min_nuit > temps_journee){
            min_jour = temps_journee;
            min_nuit += temp_total_min - min_nuit - temps_journee;
         }
         //calcul s'il ne dépasse pas
         else{
            min_jour = temp_total_min -min_nuit;
         }
      }
      //calcul si c'est uniquement de nuit
      else{
         min_nuit = temp_total_min;
      }
   }

   // Calcul du prix total du trajet de jour, nuit et total
   prix_trajet_jour = min_jour*TARIF_JOUR;
   prix_trajet_nuit = min_nuit*TARIF_NUIT;
   prix_trajet = prix_trajet_jour + prix_trajet_nuit; 
   prix_total = TAXE_BASE + prix_tot_bagages + prix_trajet;



   // Affichage du ticket
   cout << endl;
   cout << "Votre ticket" << endl;
   cout << "============" << endl;
   cout << "Prise en charge      : " << setw(LARGEUR) << TAXE_BASE         << " Euros" << endl;
   cout << "Supplements bagages  : " << setw(LARGEUR) << prix_tot_bagages  << " Euros" << endl;
   cout << "Temps de course      : " << endl;
   cout << " - " << min_jour << " @ " << TARIF_JOUR << "        : " << prix_trajet_jour << " Euros"<< endl;
   cout << " - " << min_nuit << " @ " << TARIF_NUIT << "        : " << prix_trajet_nuit << " Euros" << endl;
   cout << "-----------------------------------" << endl;
   cout << "               TOTAL : " << setw(LARGEUR) << prix_total        << " Euros" << endl;


   // Confirmation de l'utilisateur pour quitter le programme
   cout << endl;
   cout << "Presser ENTER pour quitter" << endl;
   VIDER_BUFFER;

   return EXIT_SUCCESS;
   
}