/*
Type:    HTML Index Page
Date:   14.08.2019
Author:   Tim Schanz
Description:  This header file stores the static HTML content of the ordering main page.
*/

#include <Arduino.h>
#include <string>
using namespace std;

string dynamic_content_alc();
string dynamic_content_nonalc();
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
const char MAIN_page_Begin[] PROGMEM{ R"=====(

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
                <a class="navbar-brand" href="#page-top">Hochschule Karlsruhe - MixHit</a>
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
                <div class="collapse navbar-collapse" id="Settings">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a
                                class="nav-link js-scroll-trigger"
                                href="/settings"
                                >Settings</a                             
                            >

                <div class="collapse navbar-collapse" id="empty_drink_mode">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a
                                class="nav-link js-scroll-trigger"
                                href="/empty_drink_mode"
                                >empty_drink_mode</a
                            >
                            
                <div class="collapse navbar-collapse" id="navbarResponsive">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a
                                class="nav-link js-scroll-trigger"
                                href="/custom"
                                >Custom Cocktails</a
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

        <section id="Alc">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 mx-auto">
                        <h2>Alcoholic Cocktails</h2>
                        <p class="lead">Choose your drink!!!</p>
  
            <table class="table">
              <thead>
                <tr>  
                  <th style="text-align:center;">#</th>
                  <th style="text-align:center;">Cocktail</th>
                  <th style="text-align:center;">Ingriedients</th>
                  <th style="text-align:center;">Size</th>
                </tr>
              </thead>
              <tbody>
)=====" };


const char MAIN_page_Between[] PROGMEM{ R"=====(
              </tbody>
              </table>
            </div>
          </div>
        </div>
        </section>
        <section id="Alc">
              <div class="container">
                <div class="row">
                  <div class="col-lg-8 mx-auto">
                    <h2>Non-alcoholic Cocktails</h2>
                    <p class="lead">Choose your drink!!!</p>
  
                    <table class="table">
                      <thead>
                        <tr>
                          <th style="text-align:center;">#</th>
                          <th style="text-align:center;">Cocktail</th>
                          <th style="text-align:center;">Zutaten</th>
                          <th style="text-align:center;">Gr&ouml;&szlig;e</th>
                        </tr>
                      </thead>
                      <tbody>



)=====" };

/*const char MAIN_page_Dynamic[] PROGMEM{
  "<div class="card">
  <h4>The ESP32 Update web page without refresh</h4><br>
  <h1>Sensor Value:<span id="ADCValue">0</span></h1><br>
  <br><a href="https://circuits4you.com">Circuits4you.com</a>
  <button class="btn btn-primary" data-modal-target="#modal1">Open Modal</button>
    <div class="modal1" id="modal1">
    <div class="modal-header1">
      <div class="title">Example Modal</div>
      <button data-close-button class="close-button">&times;</button>
    </div>
    <div class="modal-body1">
      Lorem ipsum dolor sit amet consectetur adipisicing elit. Esse quod alias ut illo doloremque eum ipsum obcaecati distinctio debitis reiciendis quae quia soluta totam doloribus quos nesciunt necessitatibus, consectetur quisquam accusamus ex, dolorum, dicta vel? Nostrum voluptatem totam, molestiae rem at ad autem dolor ex aperiam. Amet assumenda eos architecto, dolor placeat deserunt voluptatibus tenetur sint officiis perferendis atque! Voluptatem maxime eius eum dolorem dolor exercitationem quis iusto totam! Repudiandae nobis nesciunt sequi iure! Eligendi, eius libero. Ex, repellat sapiente!
    </div>
    </div>
    <div id="overlay"></div>
</div>
)=====" };
*/
const char MAIN_page_AfterFooter_BeforeScript[] PROGMEM{ R"=====(
                      </tbody>
                    </table>
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


const char MAIN_page_AfterFooter_AfterScript[] PROGMEM{ R"=====(
      </script>     
    </body>
</html>
)=====" };
