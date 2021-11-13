#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Servo_ESP32.h>


char ssid[] = "GITJ Wedarijaksa";
char pass[] = "terangdunia1975";

#define FIREBASE_HOST "https://miniproject-8ace4-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "gwyOsHyNDXUGu7i5QD7ISGaacXLogoV1d9d2MLGH"

int servoPin= 12;
#define ldrPin 39

FirebaseData Fbdo;
int cahaya;

Servo_ESP32 serv;

void setup(){
  
  Serial.begin(9600);
  //Fungsi Koneksi
  
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Fungsi Menghubungkan Firebase ke Adruino
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(Fbdo, 1000 * 60);
  Firebase.setwriteSizeLimit(Fbdo, "tiny");

  serv.attach(servoPin);
}

void loop() {
  cahaya = (0.009768*analogRead(ldrPin))+10;
  Serial.println(cahaya);
  int servalue = 0; 
  int tombol;
  Firebase.getInt(Fbdo, "/projectiot4/tombol");
  tombol = Fbdo.intData();
  
   if(tombol == 1 ){
        //Gorden terbuka
        if(cahaya >= 20){
          serv.write(180);
          servalue=180;
        }else if (cahaya <20){
        //Gorden tertutup
          serv.write(0);
          servalue=0;
        }
  }else if(tombol ==0){
      serv.write(0);
      servalue = 0; 
      cahaya = 0;
  }
  
  Firebase.setInt(Fbdo, "/projectiot4/cahaya", cahaya);
  Firebase.setInt(Fbdo, "/projectiot4/servo", servalue);
}
