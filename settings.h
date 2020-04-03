/*
Type:		HTML Index Page
Date:		14.08.2019
Author:		Tim Schanz
Description:	This header file stores the static HTML content of the configuration page.
*/

#include <Arduino.h>
#include <string>
using namespace std;

string dynamic_content_settings();

const char SETTINGS_page_Begin[] PROGMEM{ R"=====(

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
                <div class="collapse navbar-collapse" id="navbarResponsive">
                    <ul class="navbar-nav ml-auto">
                        <li class="nav-item">
                            <a
                                class="nav-link js-scroll-trigger"
                                href="#services"
                                >Settings</a
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
                    This is the settingspage
                </p>
            </div>
        </header>
		<section id="settings" class="bg-light">
            <div class="container">
                <div class="row">
                    <div class="col-lg-8 mx-auto">
                        <h2>Settings</h2>
                        <p class="lead">Define the parameters and click save</p>
						<form action="/" method="post" enctype="multipart/form-data">
							<div class="form-check">
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
							</div>
							<div class="form-check">
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
							</div>
							Preis alkoholisch<br>
							<input type="text" name="price_alc" value="5">
							<br>
              Preis custom<br>
              <input type="text" name="price_custom" value="30">
              <br>
							Preis nicht alkoholisch<br>
							<input type="text" name="price_nonalc" value="4">
							<br><br>

							<input type="submit" value="Save" name="save">
						</form>


)=====" };


const char SETTINGS_page_After[] PROGMEM{ R"=====(
		</div>
                </div>
            </div>
        </section>
		<!-- Footer -->
        <footer class="py-2">
            <div class="container">
                <div id="left">Copyright &copy; Your Website 2019</div>
                <div id="right">
                    <button class="btn btn-success" data-modal-target="#save">
                        Save Settings
                    </button>
                </div>
            </div>
            <!-- /.container -->
        </footer>
		<script>
			  
		</script>
	</body>
</html>
)=====" };
