#include <Ethernet.h>
/*
 * SDWebBrowse.ino
 *
 * This sketch uses the microSD card slot on the a WIZ5500 Ethernet shield
 * to serve up files over a very minimal browsing interface
 *
 * Some code is from Bill Greiman's SdFatLib examples, some is from the
 * Arduino Ethernet WebServer example and the rest is from Limor Fried
 * (Adafruit) so its probably under GPL
 *
 * Tutorial is at https://learn.adafruit.com/arduino-ethernet-sd-card/serving-files-over-ethernet
 * 
 */
 

/************ ETHERNET STUFF ************/
#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  // change if necessary
IPAddress ip(192, 168, 10, 177);
IPAddress gateway(192, 168, 10, 1);
IPAddress dns(192, 168, 10, 1);
EthernetServer server(80);

/************ SDCARD STUFF ************/
#define SDCARD_CS 4
#define W5500_SS 10
// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;

#if defined(ESP8266)
  // default for ESPressif
  #define WIZ_CS 15
#elif defined(ESP32)
  #define WIZ_CS 33
#elif defined(ARDUINO_STM32_FEATHER)
  // default for WICED
  #define WIZ_CS PB4
#elif defined(TEENSYDUINO)
  #define WIZ_CS 10
#elif defined(ARDUINO_FEATHER52)
  #define WIZ_CS 11
#elif defined(ARDUINO_AVR_MEGA2560)
  #define WIZ_CS 53
#else   // default for 328p, 32u4 and m0
  #define WIZ_CS 10
#endif

// store error strings in flash to save RAM
#define error(s) error_P(PSTR(s))

void error_P(const char* str) {
  Serial.print(F("error: "));
  Serial.println(str);

  while(1);
}

void CheckSD(String message = "No message"){
	digitalWrite(W5500_SS, HIGH);  //  turn off the W5500 chip for now  
	digitalWrite(SDCARD_CS, LOW);  //  turn on the SD chip for now  
    Serial.println("Starting Check SD");
  if (!card.init(SPI_HALF_SPEED, SDCARD_CS)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {if (!SD.begin(SDCARD_CS)) {
		Serial.println(F("card.init failed"));
	  error("card.init failed!");
	 
	}else{

		SDFile root;
		Serial.println("SDTest: " + message);
		root = SD.open("/");
		printDirectory(root, 0);
  
		// Recursive list of all directories
		Serial.println(F("Files found in all dirs:"));
		printDirectory(root, 0);
  
		Serial.println();
		Serial.println(F("Done"));
		SD.end();
	}
  }
		digitalWrite(SDCARD_CS, HIGH);  //  turn on the SD chip for now  
		digitalWrite(W5500_SS, LOW);  // turn on the W5500 chip for now  
}

void setup() {
  Serial.begin(115200);
  while (!Serial);      // For 32u4 based microcontrollers like 32u4 Adalogger Feather
 
  Serial.print(F("Free RAM: ")); Serial.println(FreeRam());  

  pinMode(W5500_SS, OUTPUT);     // set the Ethernet SS pin as an output W5500_SS = 10/53
  pinMode(SDCARD_CS, OUTPUT);     // set the SD SS pin as an output usually 4
  
  CheckSD("Inital Test");
  
  // Debugging complete, we start the server!
  Serial.println(F("Initializing WizNet"));
  digitalWrite(W5500_SS, LOW);  // turn on the W5500 chip for now  
  Ethernet.init(WIZ_CS);
  // give the ethernet module time to boot up
  delay(1000);
  // start the Ethernet connection
  // Use the fixed IP specified. If you want to use DHCP first
  //   then switch the Ethernet.begin statements
  Ethernet.begin(mac, ip, dns, gateway);
  // try to congifure using DHCP address instead of IP:
  //  Ethernet.begin(mac);
  //int dmac = Ethernet.MACAddress;
  Serial.println("Ethernet Has Begun");
  // print the Ethernet board/shield's IP address to Serial monitor
  Serial.print(F("My IP address: "));
  Serial.println(Ethernet.localIP());

  server.begin();
  Serial.println(F("Server Began"));
    
  //CheckSD("After server start");
}

void ListFiles(EthernetClient client, uint8_t flags, SDFile dir) {
  client.println("<ul>");
  while (true) {
    SDFile entry = dir.openNextFile();
   
    // done if past last used entry
     if (! entry) {
       // no more files
       break;
     }

    // print any indent spaces
    client.print("<li><a href=\"");
    client.print(entry.name());
    if (entry.isDirectory()) {
       client.println("/");
    }
    client.print("\">");
    
    // print file name with possible blank fill
    client.print(entry.name());
    if (entry.isDirectory()) {
       client.println("/");
    }
        
    client.print("</a>");
/*
    // print modify date/time if requested
    if (flags & LS_DATE) {
       dir.printFatDate(p.lastWriteDate);
       client.print(' ');
       dir.printFatTime(p.lastWriteTime);
    }
    // print size if requested
    if (!DIR_IS_SUBDIR(&p) && (flags & LS_SIZE)) {
      client.print(' ');
      client.print(p.fileSize);
    }
    */
    client.println("</li>");
    entry.close();
  }
  client.println("</ul>");
}

// How big our line buffer should be. 100 is plenty!
#define BUFSIZ 100

void loop()
{
  char clientline[BUFSIZ];
  char name[17];
  int index = 0;
  int sdTestLoop = 0;
  
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean current_line_is_blank = true;
    
    // reset the input buffer
    index = 0;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        // If it isn't a new line, add the character to the buffer
        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          // are we too big for the buffer? start tossing out data
          if (index >= BUFSIZ) 
            index = BUFSIZ -1;
          
          // continue to read more data!
          continue;
        }
        
        // got a \n or \r new line, which means the string is done
        clientline[index] = 0;
        
        // Print it out for debugging
        Serial.println(clientline);
        
        // Look for substring such as a request to get the file
        if (strstr(clientline, "GET /") != 0) {
          // this time no space after the /, so a sub-file!
          char *filename;
          
          filename = clientline + 5; // look after the "GET /" (5 chars)  *******
          // a little trick, look for the " HTTP/1.1" string and 
          // turn the first character of the substring into a 0 to clear it out.
          (strstr(clientline, " HTTP"))[0] = 0;
 
          if(filename[strlen(filename)-1] == '/') {  // Trim a directory filename
            filename[strlen(filename)-1] = 0;        //  as Open throws error with trailing /
          }
          
          Serial.print(F("Web request for: ")); Serial.println(filename);  // print the file we want

          SDFile file = SD.open(filename, O_READ);
          if ( file == 0 ) {  // Opening the file with return code of 0 is an error in SDFile.open
            client.println("HTTP/1.1 404 Not Found");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<h2>File Not Found!</h2>");
            client.println("<br><h3>Couldn't open the File!</h3>");
            break; 
          }
          
          Serial.println("File Opened!");
                    
          client.println("HTTP/1.1 200 OK");
          if (file.isDirectory()) {
            Serial.println("is a directory");
            //file.close();
            client.println("Content-Type: text/html");
            client.println();
            client.print("<h2>Files in /");
            client.print(filename); 
            client.println(":</h2>");
            ListFiles(client,LS_SIZE,file);  
            file.close();                   
          } else { // Any non-directory clicked, server will send file to client for download
            client.println("Content-Type: application/octet-stream");
            client.println();
          
            char file_buffer[16];
            int avail;
            while (avail = file.available()) {
              int to_read = min(avail, 16);
              if (to_read != file.read(file_buffer, to_read)) {
                break;
              }
              // uncomment the serial to debug (slow!)
              //Serial.write((char)c);
              client.write(file_buffer, to_read);
            }
            file.close();
          }
        } else {
          // everything else is a 404
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h2>File Not Found!</h2>");
        }
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
  else{
	if(sdTestLoop++ > 1000) {
		sdTestLoop = 0;
		CheckSD("In WIZ Loop");
	}
	}
} 


void printDirectory(SDFile dir, int numTabs) {
   while(true) {
     SDFile entry =  dir.openNextFile();
	 //Serial.println("start directory loop");
     if (! entry) {
		 // Serial.println("no files found");
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
   // Serial.println("No More Entries");
}
