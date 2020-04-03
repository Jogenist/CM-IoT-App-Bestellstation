/*
Type:		HTML Index Page
Date:		14.08.2019
Author:		Tim Schanz
Description:	This file stores the dynamic HTML content of the ordering main page.
*/

#include "index.h"
extern const char* Cocktails[];
extern const char* Zutaten_alk_statisch[];
extern const char* Zutaten_antialk_statisch[];
extern const char* Lutscher[];  //cs:0402; also du
//string leerzeichen="     ";
std::string dynamic_content_alc()
{
	String HTML_AlcoholicList = "";
	for (int i = 0; i < 13; i++)
	{
    
		HTML_AlcoholicList += "<tr>\n";
		HTML_AlcoholicList += "<td scope=\"row\" style=\"text-align:center;\" >" + String(i + 1) + "</td>\n";
    HTML_AlcoholicList += "<td style=\"text-align:center;\"><strong> " + String(Cocktails[i]) + "</strong></td>\n";
		String lIngredients = "";
   
    lIngredients+= Zutaten_alk_statisch[i];
		HTML_AlcoholicList += "<td><em>" + lIngredients + "</em></td>\n";
    HTML_AlcoholicList += "<td style=\"text-align:center;\"><button id =\""+String(Cocktails[i])+ "\" class=\"btn btn-danger btn-block\" data-modal-target=#modalcustom>" + String(220) + "ml</button></td>\n";
		HTML_AlcoholicList += "</tr>\n";

	}
	return string(HTML_AlcoholicList.c_str());
}

std::string dynamic_content_nonalc()
{
	String HTML_NonAlcoholicList = "";
	for (int i = 0; i < 18; i++)
	{
		HTML_NonAlcoholicList += "<tr>\n";
		HTML_NonAlcoholicList += "<td scope=\"row\" style=\"text-align:center;\" >" + String(i + 1) + "</td>\n";
    HTML_NonAlcoholicList += "<td style=\"text-align:center;\"><strong> " + String(Cocktails[12+i]) + "</strong></td>\n";
		String lIngredients = "";
   
    lIngredients += Zutaten_antialk_statisch[i]; 
		HTML_NonAlcoholicList += "<td><em>" + lIngredients + "</em></td>\n";
    HTML_NonAlcoholicList += "<td style=\"text-align:center;\"><button id =\""+String(Cocktails[12+i])+ "\" class=\"btn btn-danger btn-block\" data-modal-target=#modalnonalc>" + String(220) + "ml</button></td>\n";
		//HTML_AlcoholicList += "<td><a href='/Bestellung_Alkoholisch_Gross/" + String(i) + "' class='btn btn-primary btn-block'><" + fontSizeText + ">" + String(gCocktailMixer.mGlasses.getBigAmount()) + "ml</font></a></td>";
		HTML_NonAlcoholicList += "</tr>\n";

	}
	return string(HTML_NonAlcoholicList.c_str());
}
