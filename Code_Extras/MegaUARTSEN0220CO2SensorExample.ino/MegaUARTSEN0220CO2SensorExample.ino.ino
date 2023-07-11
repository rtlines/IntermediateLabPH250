/***************************************************
* Infrared CO2 Sensor 0-50000ppm(Wide Range)
* ****************************************************
* The follow example is used to detect CO2 concentration.

* @author lg.gang(lg.gang@qq.com)
* @version  V1.0
* @date  2016-6-6

* GNU Lesser General Public License.
* See <http://www.gnu.org/licenses/> for details.
* All above must be included in any redistribution
* ****************************************************/
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX, TX
unsigned char hexdata[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; //Read the gas density command /Don't change the order
void setup() {

  Serial.begin(9600);
  while (!Serial) {

  }
  mySerial.begin(9600);

}

void loop() {
   mySerial.write(hexdata,9);
   delay(500);

   for(int i=0,j=0;i<9;i++) {
      if (mySerial.available()>0) {
         long hi,lo,CO2;
         int ch=mySerial.read();

         if(i==2){     hi=ch;   }   //High concentration
         if(i==3){     lo=ch;   }   //Low concentration
         if(i==8) {
               CO2=hi*256+lo;  //CO2 concentration
               Serial.print("CO2 concentration: ");
               Serial.print(CO2);
               Serial.println("ppm");
               }

         }

   }

 }
