#include <ESP8266WiFi.h>
#include <Servo.h>
 
#include <ESP8266WebServer.h>

#define PIN_SERVO D0
const char* ssid = "olleh_WiFi_E5E4";
const char* password = "0000009994";



const char* host = "172.30.1.15";
const int port = 8888;

Servo myservo;

ESP8266WebServer server(80);
String line = "";
String url = "";
int count=0;



void sendHtml(String url){

  String html = "";

  html += "<html><script src=\"http://www.w3schools.com/lib/w3data.js\"></script>";

  html += "<body><div w3-include-html=\"" + url + "\"></div>";

  html += "<script>w3IncludeHTML();</script></body></html>";

   server.send(200, "text/html", html);

}




void setup() {
  Serial.begin(115200);
  delay(10);

  
  myservo.attach(PIN_SERVO);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());



 

  server.begin();

  Serial.println("HTTP server started");

 

  myservo.attach(D0);   // Servo attached to D5 pin

  myservo.write(0);




}

void loop() {
  
  server.handleClient();
  delay(500);

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;



  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

  int timeout = millis() + 10000;
  
  // We now create a URI for the request

  server.on("/", [](){

   sendHtml("https://raw.githubusercontent.com/BogyeumKim/ESP8266-PANEL/master/index.html");
  });

 

  server.on("/s", [](){

    String sdegree = server.arg("degree");

    int degree = sdegree.toInt();

    Serial.print("degree: ");

    Serial.println(degree);

    myservo.write(degree);

    server.send(100, "text/plain", String(degree, DEC));
sendHtml("https://raw.githubusercontent.com/BogyeumKim/ESP8266-PANEL/master/index.html");
  });

 

  server.on("/on", [](){

    Serial.println("ON");

    myservo.write(90);


String get = "/on?";

   url= String(get);
   

  Serial.print("Requesting URL: ");
  Serial.println(url);

  
sendHtml("https://raw.githubusercontent.com/BogyeumKim/ESP8266-PANEL/master/index.html");
  });

 

  server.on("/off", [](){

    Serial.println("OFF");

    myservo.write(0);
 String get = "/off?";

  url= String(get);
  
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
 sendHtml("https://raw.githubusercontent.com/BogyeumKim/ESP8266-PANEL/master/index.html");
  });


  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n"
               + "Host: " + host + "\r\n"
               + "Connection: close\r\n\r\n");


     // client.stop(); 
  
    
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    line = client.readStringUntil('\r');
    Serial.print(line);

    
  int timeout = millis() + 10000;
  }
  
  //수신받은 line 데이터를 이용하여 GPIO 콘트롤


  
//  if (line == “go”) digitalWrite(7, HIGH);
//  else digitalWrite(7, LOW));
//  Serial.println("closing connection"); 
}
