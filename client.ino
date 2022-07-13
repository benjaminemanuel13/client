
void setup() {
  // initialize serial:
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  char command[8];
  int count = 0;
  while (Serial.available() > 0) {
    char dat = Serial.read();

    for(int i = 0; i < 8; i++)
    {
      command[count++] = dat;
    }

    //Got Command
    int check = strcmp(command, "GETWIFIX");

    if(check == 0)
    {
      //Send Wifi Details
      WriteWifiList();

      //Get SSID and Password - format 000 Length of SSID - SSID - format 000 Length of Password - Password
      Serial.println("Please enter the Length of the SSID you with to Connect to (in format 0000)");

      char len[4];
      for(int i = 0; i < 4; i++)
      {
        len[i] = Serial.read();
      }

      Serial.println("Please enter the SSID you wish to connect to");

      int actlen = strtol(len, NULL, 10);
      
      char* ssid = malloc(sizeof(char) * actlen);

      for(int i = 0; i < actlen; i++)
      {
        ssid[i] = Serial.read();
      }

      Serial.println("Please enter the Length of the Password you with to use (in format 0000)");

      for(int i = 0; i < 4; i++)
      {
        len[i] = Serial.read();
      }

      actlen = strtol(len, NULL, 10);

      char pwd = malloc(sizeof(char) * actlen);

      for(int i = 0; i < actlen; i++)
      {
        pwd[i] = Serial.read();
      }

      //Save details to EEPROM then release everything;
      //Connect to Wifi
      
      free(ssid);
      free(pwd);
    }
  }
}

void WriteWifiList()
{
  Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
