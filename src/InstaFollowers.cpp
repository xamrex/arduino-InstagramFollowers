#include "Arduino.h"
#include "InstaFollowers.h"
#if defined (ARDUINO_ARCH_ESP8266)
	#include <ESP8266WiFi.h>
	#include <ESP8266HTTPClient.h>
  #elif defined(ESP32)
	#include <WiFi.h>
	#include <HTTPClient.h>
#endif
#include <WiFiClientSecure.h>

char txtbufor[bufferSize]; // Bufor for actual data
int indexx = 0;
int found = 0;
char actualData[20]; //array for our data
int incractualData = 0; //incremental
String SearchFor = "follower_count"; //can be follower_count or sth elese

InstaFollowers::InstaFollowers(String host, String ApiKey) {
  m_host = host;
  m_ApiKey = ApiKey;
}

int InstaFollowers::GetUserFollowersCount(String username) {
  const char * apiEndpoint = "/v1/info?username_or_id_or_url=";
  SearchFor = "follower_count"; //seatch for follower_count
  int result = processRequest(username, apiEndpoint, SearchFor );
   return result;
}

int InstaFollowers::GetUserFollowingCount(String username) {
  const char * apiEndpoint = "/v1/info?username_or_id_or_url=";
  SearchFor = "following_count"; //seatch for follower_count
  int result = processRequest(username, apiEndpoint, SearchFor );
   return result;
}

void InstaFollowers::addToBuffer(char c) {
  if (indexx < bufferSize - 1) {
    txtbufor[indexx++] = c;
  } else {
    //  if (_debug) Serial.println("Buffor is full.");   /* it might happends sometimes its OK */
  }
}

void InstaFollowers::processBuffer() {
  txtbufor[indexx] = '\0'; // Add  null char to end
  String str = String(txtbufor);
  if (str.indexOf(SearchFor) != -1) {
    if (_debug) Serial.print("found tekst" + SearchFor);
    found = 1;
  }
  indexx = 0; // clear
}

int InstaFollowers::processRequest(String username, String ApiEndpoint, String SearchFor){

  HTTPClient http;
  WiFiClientSecure client;

  String url = String("https://") + m_host + ApiEndpoint + username;

  client.setInsecure();
  if (_debug) Serial.print("[HTTP] Connecting to URL: ");
  if (_debug) Serial.println(url);

  memset(actualData, '\0', sizeof(actualData)); //clear table

 if (http.begin(client, url)) {
    // Add headers
    http.addHeader("X-Rapidapi-Key", m_ApiKey);
    http.addHeader("X-Rapidapi-Host", m_host);
    int httpCode = http.GET(); // Send HTTP GET Request

    ////////////////////
    if (httpCode == HTTP_CODE_OK) {
      int cnt = 0;
      WiFiClient * stream = http.getStreamPtr();
      while (stream -> available()) {
        //74,"follower_count":137,"following_count":192,"ful
        char c = stream -> read();
        if (_debug) Serial.print(c);
        /************** Add to buffor until ':' is found *****************************/

        if (!found) {
          if (c != ':') { //add data to bufer every : found
            addToBuffer(c); //add char to buffer
          } else {
            processBuffer(); //process buffer after receiving :
          }
        } else { //Our data is found
          if (c != ',') {
            actualData[incractualData++] = c;
          } else {
            if (_debug) Serial.println("\r\nOur value is:" + String(actualData) + "END of our value");

            incractualData = 0;
            found = 0;
            return atoi(actualData);
          }
        }
      }
    } else {
      if (_debug)  Serial.printf("Error! [HTTP] Code is not 200");
    }
  }
  return 0; //shoudnt happend
}