/*
Type:		HTML Index Page
Date:		14.08.2019
Author:		Tim Schanz
Description:	This file stores the dynamic javascript content of the ordering main page.
*/

#include "JS.h"

std::string dynamic_content_javascript()
{
	String JavaScript;
	String price_alc;
	String price_nonalc;
	File filec = SPIFFS.open("/config.json", FILE_READ);
	if (!filec) {
		Serial.println("There was an error opening the file /config.json for reading");
		return string("JAVASCRIPT VARIABLE ERROR IN CONFIG FILE READ!\n");
	}

	StaticJsonDocument<512> doc;
	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, filec);
	if (error)
	{
		Serial.println(F("Failed to read file, using default configuration"));
		price_alc = "4";
		price_nonalc = "3";

		JavaScript = "var with_deposit = true;\n";
		price_alc = "4";
		JavaScript += "var price_alc = " + price_alc;
		JavaScript += ";\n";
		price_nonalc = "3";
		JavaScript += "var price_nonalc = " + price_nonalc;
		JavaScript += ";\n";
	}
	else
	{
		String deposit = doc["deposit_radios"];
		if (deposit.equals("nodeposit"))
		{
			JavaScript = "var with_deposit = false;\n";
		}
		else
		{
			JavaScript = "var with_deposit = true;\n";
		}
		price_alc = doc["price_alc"].as<const char*>();
		JavaScript += "var price_alc = " + price_alc;
		JavaScript += ";\n";
		price_nonalc = doc["price_nonalc"].as<const char*>();
		JavaScript += "var price_nonalc = " + price_nonalc;
		JavaScript += ";\n";
	}
	return string(JavaScript.c_str());
}
