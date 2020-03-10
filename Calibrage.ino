

#include "HX711.h"
#include <SoftwareSerial.h>
#include <EEPROM.h>


// HX711 Choix des broches 
const int Horloge_SCK=6;
const int Donnee_DT_AVG =2;
const int Donnee_DT_AVD =3;
const int Donnee_DT_ARG =4;
const int Donnee_DT_ARD =5;


//Variables globales
float   Roue_AVG=0;
float   Roue_AVD=0;
float   Roue_ARG=0;
float   Roue_ARD=0;
float   Total;
String Choix_pesons;



//  Les varaiables suivantes seront gavées dans l'EEPROM
float  SCALE_AVG;
float  SCALE_AVD;
float  SCALE_ARG;
float  SCALE_ARD;
float MASSE_ETALON=17.8;




//Variables qui me permettent de de faire des calculs intermédiaire ,des vérifications
float MASSE_BRUTE;
int adresse=0;
int Action;
int choix_pesons;
bool flag1=0;
bool flag2=0;


HX711 PesantAVG;
HX711 PesantAVD;
HX711 PesantARG;
HX711 PesantARD;


void setup() 

{
  Serial.begin(9600);
  Serial.println("");

    //EEPROM.put(adresse,MASSE_BRUTE);
   // adresse += sizeof(MASSE_BRUTE);
   
  
  
 PesantAVG.begin(Donnee_DT_AVG,Horloge_SCK);
 PesantAVD.begin(Donnee_DT_AVD,Horloge_SCK);
 PesantARG.begin(Donnee_DT_ARG,Horloge_SCK);
 PesantARD.begin(Donnee_DT_ARD,Horloge_SCK);
 
  Serial.println("________________________________Bienvenue dans l'interface de calibrage de la balance 4 plateaux du Kart de l'IUT GEII de POITIERS___________________________________________________________________________");
  
 
 }
     
  
   
   
   
  




//Quelques mesures pour vérifier que le tarage et l'étalonnage ont été faits.
void loop() 
{
 
 if (Serial.available() > 0) 
 {
    //lecture de action
    Action = Serial.read();


    if(Action=='1')
    {
      Serial.println("Bienvenue dans la zone de tarage");
      Serial.println("Veuillez choisir le pesons a tarer grace a un chiffre:");
      
      Serial.println("5-Pesons AVG");
      Serial.println("6-Pesons AVD");
      Serial.println("7-Pesons ARG");
      Serial.println("8-Pesons ARD");
       flag1=0;
       while(Serial.available() <5 and flag1==0)
       {
        
         if (Serial.available() > 0) 
        {
          
          //lecture de choixpesons
          choix_pesons = Serial.read();
          
          if(choix_pesons=='5')
          {
            PesantAVG.tare();
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons AVG TARé");
            Serial.println("**********************************************************************************\n\n");
            flag1=1;
          }
          if(choix_pesons=='6')
          {
            PesantAVD.tare();
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons AVD TARé");
            Serial.println("**********************************************************************************\n\n");
            flag1=1;
          }
          if(choix_pesons=='7')
          {
            PesantARG.tare();
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons ARG TARé");
            Serial.println("**********************************************************************************\n\n");
            flag1=1;
          }
          if(choix_pesons=='8')
          {
            PesantARD.tare();
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons ARD TARé");
            Serial.println("**********************************************************************************\n\n");
            flag1=1;
          }
          
      
        }
       
       }
       
      }
    
    if(Action=='2')
    {
      Serial.println("Bienvenue dans la zone d'étalonnage");
      Serial.println("Veuillez choisir le pesons a étalonner grace a un chiffre:");
      Serial.println("9-Pesons AVG");
      Serial.println("A-Pesons AVD");
      Serial.println("B-Pesons ARG");
      Serial.println("C-Pesons ARD");

      flag2=0;
      while(Serial.available() <9 and flag2==0)
       {
        
         if (Serial.available() > 0) 
        {
          
          //lecture de choixpesons
          choix_pesons = Serial.read();
          
          if(choix_pesons=='9')
          {
            MASSE_BRUTE=PesantAVG.get_units(10);
            SCALE_AVG=MASSE_BRUTE/MASSE_ETALON;
            PesantAVG.set_scale(SCALE_AVG);
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons AVG étalonné");
            Serial.println("**********************************************************************************\n\n");
            flag2=1;
        
          }
          if(choix_pesons=='A')
          {
            MASSE_BRUTE=PesantAVD.get_units(10);
            SCALE_AVD=MASSE_BRUTE/MASSE_ETALON;
            PesantAVD.set_scale(SCALE_AVD);
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons AVD étalonné");
            Serial.println("**********************************************************************************\n\n");
            
            flag2=1;
          }
          if(choix_pesons=='B')
          {
            MASSE_BRUTE=PesantARG.get_units(10);
            SCALE_ARG=MASSE_BRUTE/MASSE_ETALON;
            PesantARG.set_scale(SCALE_ARG);
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons ARG étalonné");
            Serial.println("**********************************************************************************\n\n");
            flag2=1;
          }
          if(choix_pesons=='C')
          {
            MASSE_BRUTE=PesantARD.get_units(10);
            SCALE_ARD=MASSE_BRUTE/MASSE_ETALON;
            PesantARD.set_scale(SCALE_ARD);
            Serial.println("\n\n**********************************************************************************");
            Serial.println("Pesons ARD étalonné");
            Serial.println("**********************************************************************************\n\n");
            flag2=1;
          }
          
      
        }
       
       }
    }
    
  

 if(Action=='D')
 {
    EEPROM.put(adresse,SCALE_AVG);
    adresse += sizeof(SCALE_AVG);
    Serial.println("\n\n**********************************************************************************");
    Serial.println("Coefficient de mesure pour le pesons AVG a été enrégistré dans l'EEPROM");
 
    EEPROM.put(adresse,SCALE_AVD);
    adresse += sizeof(SCALE_AVD);
    Serial.println("Coefficient de mesure pour le pesons AVD a été enrégistré dans l'EEPROM");
    
    EEPROM.put(adresse,SCALE_ARG);
    adresse += sizeof(SCALE_ARG);
    Serial.println("Coefficient de mesure pour le pesons ARG a été enrégistré dans l'EEPROM");
   
    EEPROM.put(adresse,SCALE_ARD);
    adresse += sizeof(SCALE_ARD);
    Serial.println("Coefficient de mesure pour le pesons ARD a été enrégistré dans l'EEPROM");
    Serial.println("**********************************************************************************\n\n");
    adresse=0;
 }
   

    
    if(Action=='E')
    { 
      Roue_AVG=PesantAVG.get_units(10),2;
      Serial.println("\n\n**********************************************************************************");
      Serial.println("Roue_AVG");
      Serial.println(Roue_AVG);
      delay(500);
      
    
      Roue_AVD=PesantAVD.get_units(10),2;
      Serial.println("Roue_AVD");
      Serial.println(Roue_AVD);
      delay(500);
   
      Roue_ARG=PesantARG.get_units(10),2;
      Serial.println("Roue_ARG");
      Serial.println(Roue_ARG);
      delay(500);

      Roue_ARD=PesantARD.get_units(10),2;
      Serial.println("Roue_ARD");
      Serial.println(Roue_ARD);
      delay(500);

      float Total=Roue_AVG+Roue_AVD+Roue_ARG+Roue_ARD;
      Serial.println("TOTAL");
      Serial.println(Total);
      delay(5000);
    }
 }
 
  Serial.println("________________________________________________________________________________________________________________________________________________________________");
  Serial.println("appuyez sur une touche puis patientez 5 secondes :");
  Serial.println("Touche 1 - tarage");
  Serial.println("Touche 2 - etalonnage");
  Serial.println("Touche - D -Pour enregistrer les coefficients de mesure dans l'EEPROM a la fin de l'etalonnage");
  Serial.println("Touche - E -Pour éffectuer une mesure de vérification");
  Serial.println("__________________________________________________________________________________________________________________________________________________________________\n\n\n"); 
  delay(5000);
 
 }


