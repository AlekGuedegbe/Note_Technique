
  
/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/


#include <HX711.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <math.h>
#include <Nextion.h>

SoftwareSerial nextionBroche(16,17);// RX,TX

float  Roue_AVG=0;
float  Roue_AVD=0;
float  Roue_ARG=0;
float  Roue_ARD=0;
float  Total;

float  SCALE_AVG;//  Les varaiables SCALE_.... seront gavés dans l'EEPROM
float  SCALE_AVD;
float  SCALE_ARG;
float  SCALE_ARD;



// HX711 Choix des broches 
const int Horloge_SCK=6;

const int Donnee_DT_AVG =2;

const int Donnee_DT_AVD =3;

const int Donnee_DT_ARG =4;

const int Donnee_DT_ARD =5;


// l'ajout des variables restantes 




HX711 PesantAVG;
HX711 PesantAVD;
HX711 PesantARG;
HX711 PesantARD;


//AFFICHAGE MESURES MASSES
NexText t4 = NexText(0,6,"t4");// aff AVG
NexText t5 = NexText(0,7,"t5");// aff AVD
NexText t7 = NexText(0,9,"t7");// aff ARG
NexText t8 = NexText(0,10,"t8");// aff ARD
NexText t6 = NexText(0,8,"t6");// aff Total

 
 





void setup() 
{

 
  Serial.begin(9600);
  Serial.println("OK on entre dans le void setup");
  
  PesantAVG.begin(Donnee_DT_AVG,Horloge_SCK);
  PesantAVD.begin(Donnee_DT_AVD,Horloge_SCK);
  PesantARG.begin(Donnee_DT_ARG,Horloge_SCK);
  PesantARD.begin(Donnee_DT_ARD,Horloge_SCK);

  int adresse = 0;
  EEPROM.get(adresse,SCALE_AVG);
  adresse += sizeof(SCALE_AVG);

  EEPROM.get(adresse,SCALE_AVD);
  adresse += sizeof(SCALE_AVD);

  EEPROM.get(adresse,SCALE_ARG);
  adresse += sizeof(SCALE_ARG);

  EEPROM.get(adresse,SCALE_ARD);
  adresse += sizeof(SCALE_ARD);

 



   if(nexInit()) 
  {
    Serial.println("setup ok");
  }
  else
  {
    Serial.println("Setup error !!! ");
    while(1){;}
  }
  
  
 
  dbSerialPrintln("setup done"); 

  Serial.print("Lecture Brute: \t\t\n\n"); // Mesure unique sans aucun parametrage , mesure brute 
  
  Serial.print("ROUE AVANT GAUCHE: \t\t");
  Serial.println( PesantAVG.read());  // afficher la sortie brute 
  Serial.print("\n");

  Serial.print("ROUE AVANT DROITE: \t\t");
  Serial.println( PesantAVD.read());  // afficher la sortie brute 
  Serial.print("\n");

  Serial.print("ROUE ARRIERE GAUCHE: \t\t");
  Serial.println( PesantARG.read());  // afficher la sortie brute 
  Serial.print("\n");

  Serial.print("ROUE ARRIERE DROITE: \t\t");
  Serial.println( PesantARD.read());  // afficher la sortie brute 
  Serial.print("\n\n");
 
 
  
  //Verification du bon fonctionnement de l'ecran

  

  PesantAVG.set_scale(SCALE_AVG); 
  PesantAVG.tare();

  PesantAVD.set_scale(SCALE_AVD); 
  PesantAVD.tare();
  
  PesantARG.set_scale(SCALE_ARG); 
  PesantARG.tare();
  
  PesantARD.set_scale(SCALE_ARD); 
  PesantARD.tare();

  

  
  

  //Autorisation pour démarrer la pesée 
  

  
  }




void loop() 

{
   
    Roue_AVG=PesantAVG.get_units(5),2;
    Serial.println(" Roue AVG");          
    Serial.println(Roue_AVG); 
    float AffAVG=fabs(Roue_AVG);
    char s1[16];
    dtostrf(AffAVG, 2, 2,s1); 
    t4.setText(s1);
    //delay(500);
    
    Roue_AVD=PesantAVD.get_units(5),2;
    Serial.println("Roue_AVD");
    Serial.println(Roue_AVD);
    float AffAVD=fabs(Roue_AVD);
    char s2[16];
    dtostrf(AffAVD, 2, 2, s2); 
    t5.setText(s2);
    //delay(500);
   
    Roue_ARG=PesantARG.get_units(5),2;
    Serial.println("Roue_ARG");
    Serial.println(Roue_ARG);
    float AffARG=fabs(Roue_ARG);
    char s3[16];
    dtostrf(AffARG, 2, 2, s3); 
    t7.setText(s3);
    //delay(500);

    Roue_ARD=PesantARD.get_units(5),2;
    Serial.println("Roue_ARD");
    Serial.println(Roue_ARD);
    float AffARD=fabs(Roue_ARD);
    char s4[16];
    dtostrf(AffARD, 2, 2, s4); 
    Serial.println(s4);
     t8.setText(s4);
    //delay(500);

    Total=AffAVG+AffAVD+AffARG+AffARD;
    Serial.println("TOTAL");
    Serial.println(Total);
    float AffTot=Total;
    char s5[16];
    dtostrf(AffTot, 2, 2, s5);  
    t6.setText(s5);
    
    //delay(500);
  
  
}

