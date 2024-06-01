/*******************************************************************
 *  An example of usisng the InstagramFollowers library to get
 *  info (followers, following) on a given user.
 *
 *  Written by XamreX
 *******************************************************************/

#include "InstaFollowers.h"
// ----------------------------
// Standard Libraries - Already Installed
// ----------------------------
#if defined (ARDUINO_ARCH_ESP8266)
	#include <ESP8266WiFi.h>
	#include <ESP8266HTTPClient.h>
  #elif defined(ESP32)
	#include <WiFi.h>
	#include <HTTPClient.h>
#endif
//------- Replace the following! ------
const char * ssid = "Internet Janusza";       // your network SSID (name)
const char * password = "Ch0re0gr4f14";      // your network password

/***********************************************Setup procedure ************************************************
/1.Go to https://rapidapi.com/ and create account
/2.Search for: Instagram Scraper API    //https://rapidapi.com/social-api1-instagram/api/instagram-scraper-api2
/3.Save X-RapidAPI-Key, and X-RapidAPI-Host
/4.Fulfill InstaFollowers class with X-RapidAPI-Key and X-RapidAPI-Host
/LIMITATIONS: Regarding to this API, you can have only 500 requests/month
*****************************************************************************************************************/
void setup()
{
  Serial.begin(115200);
  delay(100);

  Serial.print("Connectiwng with ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  /***** Insta Stats******/
  InstaFollowers instaStats("instagram-scraper-api2.p.rapidapi.com","cefb4a1bfamshe0e5f1325007c0ap19a395jsnb06781e3d470");
  //1.Followers:
  int FollowersCount= instaStats.GetUserFollowersCount("arduino.cc");
  Serial.print("Follower count:"+String(FollowersCount));
  //2.Following:
  int FollowingCount= instaStats.GetUserFollowingCount("arduino.cc");
  Serial.print("Following count:"+String(FollowingCount));

}

void loop()
{
delay(100);
}