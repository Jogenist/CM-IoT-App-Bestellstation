#include "leertrinkbetrieb.h"
extern bool alcoholic_cocktails[];
extern bool non_alcoholic_cocktails[];

extern const char* Cocktails[];
extern const char* Zutaten_alk_statisch[];
extern const char* Zutaten_antialk_statisch[];

std::string dynamic_content_leertrinkbetrieb_alc()
{
  String HTML_Leertrinkbetrieb_alc = "";
  for (int i = 0; i < 12; i++)
  {

   if(alcoholic_cocktails[i] == true)
   {
    HTML_Leertrinkbetrieb_alc += "<tr>\n";
    HTML_Leertrinkbetrieb_alc += "<td scope=\"row\" style=\"text-align:center;\" >" + String(i + 1) + "</td>\n";
    HTML_Leertrinkbetrieb_alc += "<td style=\"text-align:center;\"><strong> " + String(Cocktails[i]) + "</strong></td>\n";
    String lIngredients = "";
    lIngredients+= Zutaten_alk_statisch[i];
    HTML_Leertrinkbetrieb_alc += "<td><em>" + lIngredients + "</em></td>\n";
    HTML_Leertrinkbetrieb_alc += "<td style=\"text-align:center;\"><button id =\"OrderButton\" name =\""+String(Cocktails[i])+ "\" class=\"btn btn-danger btn-block\" data-modal-target=#modalalc>" + String(220) + "ml</button></td>\n"; //gejo0407
    HTML_Leertrinkbetrieb_alc += "</tr>\n";
    //return string(HTML_Leertrinkbetrieb_alc.c_str());
    }
  }
return string(HTML_Leertrinkbetrieb_alc.c_str());
}

std::string dynamic_content_leertrinkbetrieb_nonalc()
{
  String HTML_Leerrinkbetrieb_nonalc = "";
  for (int i = 0; i < 18; i++)
  {

    if(non_alcoholic_cocktails[i]==true)
   {
    HTML_Leerrinkbetrieb_nonalc += "<tr>\n";
    HTML_Leerrinkbetrieb_nonalc += "<td scope=\"row\" style=\"text-align:center;\" >" + String(i + 1) + "</td>\n";
    HTML_Leerrinkbetrieb_nonalc += "<td style=\"text-align:center;\"><strong> " + String(Cocktails[12+i]) + "</strong></td>\n";
    String lIngredients = "";
    lIngredients += Zutaten_antialk_statisch[i]; 
    HTML_Leerrinkbetrieb_nonalc += "<td><em>" + lIngredients + "</em></td>\n";
    HTML_Leerrinkbetrieb_nonalc += "<td style=\"text-align:center;\"><button id =\"OrderButton\" name =\""+String(Cocktails[12+i])+ "\" class=\"btn btn-danger btn-block\" data-modal-target=#modalnonalc>" + String(220) + "ml</button></td>\n"; //jg0407
    HTML_Leerrinkbetrieb_nonalc += "</tr>\n";
    
   
   }

  }
   return string(HTML_Leerrinkbetrieb_nonalc.c_str());
}
