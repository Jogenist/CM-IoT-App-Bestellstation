/*
Type:    HTML Index Page
Date:   14.08.2019
Author:   Tim Schanz
Description:  This header file stores the static HTML content of the ordering main page.
*/

#include <Arduino.h>
#include <string>
using namespace std;

string dynamic_content_CustomCocktails();

/*
const char HTML_Head[] PROGMEM{ R"=====(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="utf-8">
    <meta name="Cocktail orderingpage" content="This site provides all purchaseable cocktails">
    <meta name="cocktail" content="example, html, head, meta">
    
    <link rel="shortcut icon" href="image/favico.ico" type="image/x-icon">
  <link rel="icon" href="image/favico.ico" type="image/x-icon">
    <title>MixHit Order</title>
  <!-- Bootstrap core CSS -->
  <link rel="stylesheet" href="css/bootstrap.min.css">
  
  <!-- Custom styles for this template -->
    <link rel="stylesheet" href="css/design.css">
  <?php
   header("refresh: 0;");
  ?>
  </head>

)=====" };*/
const char CUSTOM_page_Begin[] PROGMEM{ R"=====(

<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="utf-8">
    <meta name="Cocktail orderingpage" content="This site provides all purchaseable cocktails">
    <meta name="cocktail" content="example, html, head, meta">
    
    <link rel="shortcut icon" href="image/favico.ico" type="image/x-icon">
  <link rel="icon" href="image/favico.ico" type="image/x-icon">
    <title>MixHit Order</title>
  <!-- Bootstrap core CSS -->
  <link rel="stylesheet" href="css/bootstrap.min.css">
  
  <!-- Custom styles for this template -->
    <link rel="stylesheet" href="css/design.css">
  <?php
   header("refresh: 3;");
  ?>
  </head>
  <body id="page-top">
        <!-- Navigation -->
        <nav class="navbar navbar-expand-lg navbar-dark fixed-top" id="mainNav">    
        <div class="container">
        <img class="logo_image" src="image/hska_logo.png">
                <a class="navbar-brand" href="/">Hochschule Karlsruhe - MixHit</a>
                <button
                    class="navbar-toggler"
                    type="button"
                    data-toggle="collapse"
                    data-target="#navbarResponsive"
                    aria-controls="navbarResponsive"
                    aria-expanded="false"
                    aria-label="Toggle navigation"
                    >
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarResponsive">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a
                                class="nav-link js-scroll-trigger"
                                href="/"
                                >Bestellübersicht</a
                            >
                        </li>
                    </ul>
                </div>
        </div>
        </nav>

        <header class="text-white">
            <div class="container text-center">
                <h1>CocktailMaker Ordering Terminal</h1>
                <p class="lead">
                    Get your freshening gulp!!!
                </p>
            </div>
        </header>

        <section id="CustomCocktails">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 mx-auto">
                        <h2>Alkoholische Cocktails</h2>
                        <p class="lead">Choose your drink!!!</p>
                  <div>
                  Wodka
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka-" value="-" onclick="myFunctionDec(0)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Wodka_insert" name="Wodka" value=Wodka_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka+" value="+" onclick="myFunctionInc(0)"/>


                  
                  <div>
                  Zitrone
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka-" value="-" onclick="myFunctionDec(1)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Zitrone_insert" name="Zitrone" value=Zitrone_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka+" value="+" onclick="myFunctionInc(1)"/>


                  <div>
                  Maracuja
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka-" value="-" onclick="myFunctionDec(2)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Maracuja_insert" name="Maracuja" value=Maracuja_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonWodka+" value="+" onclick="myFunctionInc(2)"/>



                  <div>
                  Banane
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonBanane-" value="-" onclick="myFunctionDec(3)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Banane_insert" name="Banane" value=Banane_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonBanane+" value="+" onclick="myFunctionInc(3)"/>



                  <div>
                  Ananas
                  </div> 
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonAnanas-" value="-" onclick="myFunctionDec(4)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Ananas_insert" name="Ananas" value=Ananas_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonAnanas+" value="+" onclick="myFunctionInc(4)"/>



                  <div>
                  Malibu
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonMalibu-" value="-" onclick="myFunctionDec(5)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Malibu_insert" name="Malibu" value=Malibu_ml></p>
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonMalibu+" value="+" onclick="myFunctionInc(5)"/>



                  <div>
                  Orange
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonOrange-" value="-" onclick="myFunctionDec(6)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Orange_insert" name="Malibu" value=Orange_ml></p>
                  </div>
                  <input type="button" style="padding:20px; background-color: #990b24" name="ButtonOrange+" value="+" onclick="myFunctionInc(6)"/>
                  

                  <div>
                  Grenadine
                  </div>
                  <input type="button" style="padding:20px;background-color: #990b24" name="ButtonGrenadine-" value="-" onclick="myFunctionDec(7)"/>
                  <div style="padding: 12px; background-color: #ffffff; display: inline-block;">
                  <input type="text" id="Grenadine_insert" name="Grenadine" value=Grenadine_ml></p>
                  </div>
                  <input type="button" style="padding:20px; background-color: #990b24" name="ButtonGrenadine+" value="+" onclick="myFunctionInc(7)"/>
                
                  

                  <br>
                  Gesamtfüllmenge (220ml) = <p id="All_insert"></p>
                  
                  <script>
                  var Wodka_ml = 0;
                  var Zitrone_ml = 0;
                  var Maracuja_ml = 0;
                  var Banane_ml = 0;
                  var Ananas_ml=0;
                  var Malibu_ml = 0;
                  var Orange_ml =0;
                  var Grenadine_ml =0;
                  var Gesamtfuell_ml =0;
                  

                  var Wodka_string = "000";
                  var Zitrone_string = "000";
                  var Maracuja_string = "000";
                  var Banane_string = "000";
                  var Ananas_string = "000";
                  var Malibu_string = "000";
                  var Orange_string = "000";
                  var Grenadine_string = "000";
                  
                  document.getElementById("Wodka_insert").value = Wodka_ml;
                  document.getElementById("Zitrone_insert").value = Zitrone_ml;
                  document.getElementById("Maracuja_insert").value = Maracuja_ml;
                  document.getElementById("Banane_insert").value = Banane_ml;
                  document.getElementById("Ananas_insert").value = Ananas_ml;
                  document.getElementById("Malibu_insert").value = Malibu_ml;
                  document.getElementById("Orange_insert").value = Orange_ml;
                  document.getElementById("Grenadine_insert").value = Grenadine_ml;
                  document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                  document.getElementsByClassName("btn btn-danger")[0].name = String(Wodka_ml) + String(Zitrone_ml) + String(Maracuja_ml) + String(Banane_ml) + String(Ananas_ml) + String(Malibu_ml) + String(Orange_ml) + String(Grenadine_ml);
                  //var x = document.getElementsByClassName("btn btn-danger")[0].name;
                  //document.getElementById("All_insert").innerHTML = x;
                   function ClearCustomValues()
                   {
                      Wodka_ml = 0;
                      Zitrone_ml = 0;
                      Maracuja_ml = 0;
                      Banane_ml = 0;
                      Ananas_ml=0;
                      Malibu_ml = 0;
                      Orange_ml =0;
                      Grenadine_ml =0;
                      Gesamtfuell_ml =0;
                  document.getElementById("Wodka_insert").value = Wodka_ml;
                  document.getElementById("Zitrone_insert").value = Zitrone_ml;
                  document.getElementById("Maracuja_insert").value = Maracuja_ml;
                  document.getElementById("Banane_insert").value = Banane_ml;
                  document.getElementById("Ananas_insert").value = Ananas_ml;
                  document.getElementById("Malibu_insert").value = Malibu_ml;
                  document.getElementById("Orange_insert").value = Orange_ml;
                  document.getElementById("Grenadine_insert").value = Grenadine_ml;
                  document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                  document.getElementsByClassName("btn btn-danger")[0].name = Wodka_string + Zitrone_string + Maracuja_string + Banane_string + Ananas_string + Malibu_string + Orange_string + Grenadine_string;
                  //var x = document.getElementsByClassName("btn btn-danger")[0].name;
                  //document.getElementById("All_insert").innerHTML = x;
                   }
                  
                  function myFunctionInc(p1) 
                  {
                      if (Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml == 220)
                        {
                          return 0;
                        }
                        
                        if (p1 == 0)
                        {
                          if(Wodka_ml >= 40)
                          {
                            return 0;
                          }
                        
                          Wodka_ml = Wodka_ml +5 ; 
                          Wodka_string = generateString(Wodka_ml,Wodka_string);
                          document.getElementById("Wodka_insert").value = Wodka_ml;
                          
                          //document.getElementById("Wodka_string").innerHTML = Wodka_string; //Test
                        }
                        
                        if (p1 == 1)
                        {
                         Zitrone_ml = Zitrone_ml + 5;
                         Zitrone_string = generateString(Zitrone_ml,Zitrone_string);
                         document.getElementById("Zitrone_insert").value = Zitrone_ml;
                        }
                        
                        if (p1 == 2)
                        {
                         Maracuja_ml = Maracuja_ml + 5;
                         Maracuja_string = generateString(Maracuja_ml,Maracuja_string);
                         document.getElementById("Maracuja_insert").value = Maracuja_ml;
                        }
                        if (p1 == 3)
                        {
                         Banane_ml = Banane_ml + 5;
                         Banane_string = generateString(Banane_ml,Banane_string);
                         document.getElementById("Banane_insert").value = Banane_ml;
                        }
                        if (p1 == 4)
                        {
                         Ananas_ml = Ananas_ml + 5;
                         Ananas_string = generateString(Ananas_ml,Ananas_string);
                         document.getElementById("Ananas_insert").value = Ananas_ml;
                        }
                        if (p1 == 5)
                        {
                        if(Malibu_ml >= 40)
                          {
                            return 0;
                          }
                         Malibu_ml = Malibu_ml + 5;
                         Malibu_string = generateString(Malibu_ml,Malibu_string);
                         document.getElementById("Malibu_insert").value = Malibu_ml;
                        }
                        if (p1 == 6)
                        {
                         Orange_ml = Orange_ml + 5;
                         Orange_string = generateString(Orange_ml,Orange_string);
                         document.getElementById("Orange_insert").value = Orange_ml;
                        }
                        if (p1 == 7)
                        {
                         Grenadine_ml = Grenadine_ml + 5;
                         Grendine_string = generateString(Grenadine_ml,Grenadine_string);
                         document.getElementById("Grenadine_insert").value = Grenadine_ml;
                        }
                        
                        document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                        document.getElementsByClassName("btn btn-danger")[0].name = Wodka_string + Zitrone_string + Maracuja_string + Banane_string + Ananas_string + Malibu_string + Orange_string + Grenadine_string;
                        //var x = document.getElementsByClassName("btn btn-danger")[0].name;
                        //document.getElementById("All_insert").innerHTML = x;
                  }
                  
                  function myFunctionDec(p1) {
                      if (p1 == 0)
                        {
                        if (Wodka_ml == 0)
                        {
                          return 0;
                        }
                         Wodka_ml = Wodka_ml - 5;
                         Wodka_string = generateString(Wodka_ml,Wodka_string);
                         document.getElementById("Wodka_insert").value = Wodka_ml;
                         //document.getElementById("Wodka_string").innerHTML = Wodka_string; //Test
                        }
                        if (p1 == 1)
                        {
                         if (Zitrone_ml == 0)
                        {
                          return 0;
                        }
                         Zitrone_ml = Zitrone_ml - 5;
                         Zitrone_string = generateString(Zitrone_ml,Zitrone_string);
                         document.getElementById("Zitrone_insert").value = Zitrone_ml;
                        }
                        
                        if (p1 == 2)
                        {
                         if (Maracuja_ml == 0)
                        {
                          return 0;
                        }
                         Maracuja_ml = Maracuja_ml - 5;
                         Maracuja_string = generateString(Maracuja_ml,Maracuja_string);
                         document.getElementById("Maracuja_insert").value = Maracuja_ml;                        }
                        if (p1 == 3)
                        {
                         if (Banane_ml == 0)
                        {
                          return 0;
                        }
                         Banane_ml = Banane_ml - 5;
                         Banane_string = generateString(Banane_ml,Banane_string);
                         document.getElementById("Banane_insert").value = Banane_ml;
                        }
                        if (p1 == 4)
                        {
                         if (Ananas_ml == 0)
                        {
                          return 0;
                        }
                         Ananas_ml = Ananas_ml - 5;
                         Ananas_string = generateString(Ananas_ml,Ananas_string);
                         document.getElementById("Ananas_insert").value = Ananas_ml;
                        }
                        if (p1 == 5)
                        {
                         if (Malibu_ml == 0)
                        {
                          return 0;
                        }
                         Malibu_ml = Malibu_ml - 5;
                         Malibu_string = generateString(Malibu_ml,Malibu_string);
                         document.getElementById("Malibu_insert").value = Malibu_ml;
                        }
                        if (p1 == 6)
                        {
                         if (Orange_ml == 0)
                        {
                          return 0;
                        }
                         Orange_ml = Orange_ml - 5;
                         Orange_string = generateString(Orange_ml,Orange_string);
                         document.getElementById("Orange_insert").value = Orange_ml;
                        }
                        if (p1 == 7)
                        {
                         if (Grenadine_ml == 0)
                        {
                          return 0;
                        }
                         Grenadine_ml = Grenadine_ml - 5;
                         Grendine_string = generateString(Grenadine_ml,Grenadine_string);
                         document.getElementById("Grenadine_insert").value = Grenadine_ml;
                        }
                        
                        document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                        document.getElementsByClassName("btn btn-danger")[0].name = Wodka_string + Zitrone_string + Maracuja_string + Banane_string + Ananas_string + Malibu_string + Orange_string + Grenadine_string;
                        //var x = document.getElementsByClassName("btn btn-danger")[0].name;
                        //document.getElementById("All_insert").innerHTML = x;
                        
                         }
                         
                         function generateString(i1,i2)
                         {
                         if (i1 <=5)
                          i2 = "00" + String(i1);
                         if (i1 > 5)
                          i2 = "0" + String(i1);
                         if (i1 > 95)
                          i2 = String(i1);
                         return i2;
                         }
                  </script>
             
              <div>
              <button name = "000000000000000000000000" id ="OrderButton" class="btn btn-danger" data-modal-target=#modalalc>Order</button>
              </div>
              <input type="button" name="ButtonClear" value="SAUWA" onclick="ClearCustomValues()"/>
            <!--/form-->
              <tbody>
)=====" };
            

const char CUSTOM_page_AfterFooter_BeforeScript[] PROGMEM{ R"=====(
                      </tbody>
                  </div>
                </div>
              </div>
            </section>
            <div class="modalalc" id="modalalc">
              <div class="modalalc-header h4">
                <div class="title">Ihre Bestellung</div>
                  <button data-close-button class="close-button">&times;</button>
              </div>
              <div class="modalalc-body h5">
                <strong>Ihre Bestellung wird gebucht.</strong><br />
                <em>Stellen Sie das Glas auf das Terminal.</em>
              </div>
            </div>

            <div class="modalnonalc" id="modalnonalc">
              <div class="modalnonalc-header h4">
                <div class="title">Ihre Bestellung</div>
                <button data-close-button class="close-button">&times;</button>
              </div>
              <div class="modalnonalc-body h5">
                <strong>Ihre Bestellung wird gebucht.</strong><br />
                <em>Stellen Sie das Glas auf das Terminal.</em>
              </div>
            </div>

            <div class="total1" id="total1">
              <div class="total-header1 h4">
                <div class="title">Kasse</div>
                <button total-close-button class="close-button">&times;</button>
              </div>
              <div class="total-body1 h5">
                <strong>Ihre Bestellung wird berechnet.</strong><br />
                <p class="h4">
                  Zu zahlender Betrag:
                  <strong><em onload="calculatePrice()" id="cost"></em>
                  <em>&euro;</em></strong>
                </p>
                <div class="form-group mx-sm-3 mb-2">
                <input
                class="form-control float-left"
                type="number"
                name="paid"
                id="paid" data-decimals="2" min="0" max="999.99" step="0.1"
                placeholder="0.0"
                onkeypress="return isNumberKey(event)" onkeydown="isEnterKey(event)"
                /><button class="btn btn-info float-right btn-calc"
                onclick="calculateReturn()">
                Calculate
                </button>
              </div>
            <div class="h4"> <p id="return"></p></div>
          </div>
        </div>
      <div id="overlay"></div>
      <!-- Footer -->
      <footer class="py-2">
        <div class="container">
          <div id="left">Copyright &copy; Your Website 2019</div>
          <div id="center">
            Price:
            <strong><em id="display"></em><em>&euro;</em></strong>
          </div>
          <div id="right">
            <button class="btn btn-success" data-modal-target="#total1">
              Total
            </button>
          </div>
        </div>
        <!-- /.container -->
      </footer>
      <script>
)=====" };


const char CUSTOM_page_AfterFooter_AfterScript[] PROGMEM{ R"=====(
      </script>     
    </body>
</html>
)=====" };
