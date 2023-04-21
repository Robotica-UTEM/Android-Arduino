/* Comunicacion Android-Arduino en donde al mandar un dato desde el android enciende un LED, de modo contrario si se manda otro mensaje desde el computador 
el LED que estaba encendido ahora se apaga
*/

#include <SoftwareSerial.h>

SoftwareSerial BT1(3,2); // Habilita mediante la libreria SoftwareSerial dos pines cualquieras a RX, TX, para de este modo no ocupar la comunicacion
                         // serial que existe en los pines 1 y 2 con el computador
char lectura1;

void setup()
   {
       Serial.begin(9600);                    //Incia el serial PC-Arduino
       BT1.begin(9600);                       //Inicia serial Android-Arduino
       Serial.println("Enter AT commands:");  //Mensaje de inicio
       pinMode(13,OUTPUT);
   }

void loop()
   {
       if (BT1.available()){                  // Si existen datos desde el Android
           lectura1=(BT1.read());             // Guarda en la variable "lectura1" lo que manda el android
           Serial.write(lectura1);            // Escribe en el serial el dato mandado
           digitalWrite(13,1);                // Enciende el LED13
         }
       
       if (Serial.available())               // Si el serial del PC recive datos
          {  String S = GetLine();           // guarda lo escrito en una cadena llamada S
             BT1.print(S);                   // y se imprime en el Android S
             Serial.println("---> " + S);    // y ademas se imprime en el Serial del PC el valor ingresado
             digitalWrite(13,0);             // apaga el LED13
          }
}

String GetLine()
   {   String S = "" ;
       if (Serial.available())
          {    char c = Serial.read(); ;
                while ( c != '\n')            //Hasta que el caracter sea intro
                  {     S = S + c ;
                        delay(25) ;
                        c = Serial.read();
                  }
                return( S + '\n') ;
          }
   }
