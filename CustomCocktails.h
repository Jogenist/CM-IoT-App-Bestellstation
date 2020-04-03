/*
Type:		HTML Index Page
Date:		14.08.2019
Author:		Tim Schanz
Description:	This header file stores the static HTML content of the configuration page.
*/

#include <Arduino.h>
#include <string>
using namespace std;

string dynamic_content_CustomCocktails();
//string Customstring = "0001020304050607";  //cs:0402

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
                    Customize your own Cocktail!
                </p>
            </div>
        </header>
		<section id="CustomCocktails" class="bg-light">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 mx-auto">
                        <h2>Custom Cocktails</h2>
                        <p class="lead">Define the parameters and click save</p>
						<form action="/" method="post" enctype="multipart/form-data">
							<!--div class="form-check">
								<input
									class="form-check-input"
									type="radio"
									name="deposit_radios"
									id="deposit"
									value="deposit"
									checked
								>
								<label class="form-check-label" for="deposit">
									Pfand
								</label>
							</div-->
							<!--div class="form-check">
								<input
									class="form-check-input"
									type="radio"
									name="deposit_radios"
									id="nodeposit"
									value="nodeposit"
								>
								<label class="form-check-label" for="nodeposit">
									Kein Pfand
								</label>
							</div-->

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
                  
                  document.getElementById("Wodka_insert").value = Wodka_ml;
                  document.getElementById("Zitrone_insert").value = Zitrone_ml;
                  document.getElementById("Maracuja_insert").value = Maracuja_ml;
                  document.getElementById("Banane_insert").value = Banane_ml;
                  document.getElementById("Ananas_insert").value = Ananas_ml;
                  document.getElementById("Malibu_insert").value = Malibu_ml;
                  document.getElementById("Orange_insert").value = Orange_ml;
                  document.getElementById("Grenadine_insert").value = Grenadine_ml;
                  document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;

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
                          document.getElementById("Wodka_insert").value = Wodka_ml;
                        }

                        
                        if (p1 == 1)
                        {
                         Zitrone_ml = Zitrone_ml + 5;
                         document.getElementById("Zitrone_insert").value = Zitrone_ml;
                        }
                        
                        if (p1 == 2)
                        {
                         Maracuja_ml = Maracuja_ml + 5;
                         document.getElementById("Maracuja_insert").value = Maracuja_ml;
                        }

                        if (p1 == 3)
                        {
                         Banane_ml = Banane_ml + 5;
                         document.getElementById("Banane_insert").value = Banane_ml;
                        }

                        if (p1 == 4)
                        {
                         Ananas_ml = Ananas_ml + 5;
                         document.getElementById("Ananas_insert").value = Ananas_ml;
                        }

                        if (p1 == 5)
                        {

                        if(Malibu_ml >= 40)
                          {
                            return 0;
                          }
                         Malibu_ml = Malibu_ml + 5;
                         document.getElementById("Malibu_insert").value = Malibu_ml;
                        }

                        if (p1 == 6)
                        {
                         Orange_ml = Orange_ml + 5;
                         document.getElementById("Orange_insert").value = Orange_ml;
                        }

                        if (p1 == 7)
                        {
                         Grenadine_ml = Grenadine_ml + 5;
                         document.getElementById("Grenadine_insert").value = Grenadine_ml;
                        }
                        
                        document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                  }
                  
                  function myFunctionDec(p1) {
                      if (p1 == 0)
                        {
                        if (Wodka_ml == 0)
                        {
                          return 0;
                        }
                         Wodka_ml = Wodka_ml - 5;
                         document.getElementById("Wodka_insert").value = Wodka_ml;
                        }
                        if (p1 == 1)
                        {
                         if (Zitrone_ml == 0)
                        {
                          return 0;
                        }
                         Zitrone_ml = Zitrone_ml - 5;
                         document.getElementById("Zitrone_insert").value = Zitrone_ml;
                        }
                        
                        if (p1 == 2)
                        {
                         if (Maracuja_ml == 0)
                        {
                          return 0;
                        }
                         Maracuja_ml = Maracuja_ml - 5;
                         document.getElementById("Maracuja_insert").value = Maracuja_ml;                        }

                        if (p1 == 3)
                        {
                         if (Banane_ml == 0)
                        {
                          return 0;
                        }
                         Banane_ml = Banane_ml - 5;
                         document.getElementById("Banane_insert").value = Banane_ml;
                        }

                        if (p1 == 4)
                        {
                         if (Ananas_ml == 0)
                        {
                          return 0;
                        }
                         Ananas_ml = Ananas_ml - 5;
                         document.getElementById("Ananas_insert").value = Ananas_ml;
                        }

                        if (p1 == 5)
                        {
                         if (Malibu_ml == 0)
                        {
                          return 0;
                        }
                         Malibu_ml = Malibu_ml - 5;
                         document.getElementById("Malibu_insert").value = Malibu_ml;
                        }

                        if (p1 == 6)
                        {
                         if (Orange_ml == 0)
                        {
                          return 0;
                        }
                         Orange_ml = Orange_ml - 5;
                         document.getElementById("Orange_insert").value = Orange_ml;
                        }

                        if (p1 == 7)
                        {
                         if (Grenadine_ml == 0)
                        {
                          return 0;
                        }
                         Grenadine_ml = Grenadine_ml - 5;
                         document.getElementById("Grenadine_insert").value = Grenadine_ml;
                        }
                        
                        document.getElementById("All_insert").innerHTML = Wodka_ml + Zitrone_ml + Maracuja_ml + Banane_ml + Ananas_ml + Malibu_ml + Orange_ml+ Grenadine_ml;
                         }
                                  
                  </script>
             

							<div>
              <button id ="0001020304050607" class="btn btn-danger" data-modal-target=#modalcustom> 220 ml</button>
              </div>
              
              <!--button onclick="ClearCustomValues()">SAUWA</button-->
              <input type="button" name="ButtonClear" value="SAUWA" onclick="ClearCustomValues()"/>
              <input type="submit" value="Save" name="save">
						</form>



)=====" };






const char CUSTOM_page_After[] PROGMEM{ R"=====(
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

             //cs:0402 -> modalcustom
            <div class="modalcustom" id="modalcustom">
              <div class="modalcustom-header h4">
                <div class="title">Ihre Bestellung</div>
                <button data-close-button class="close-button">&times;</button>
              </div>
              <div class="modalcustom-body h5">
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
		<!-- Footer -->
        <footer class="py-2">
            <div class="container">
                <div id="left">Copyright &copy; Your Website 2019</div>
                <div id="right">
                    <!--button class="btn btn-success" data-modal-target="#save">
                        Save Settings
                    </button-->
                </div>
            </div>
            <!-- /.container -->
        </footer>
		<script>
		</script>
	</body>
</html>
)=====" };
