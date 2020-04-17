/*
Type:		HTML Index Page
Date:		14.08.2019
Author:		Tim Schanz
Description:	This header file stores the javascript content of the ordering main page.
*/

#include <Arduino.h>
#include <string>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <FS.h>

using namespace std;

std::string dynamic_content_javascript();

const char JAVASCRIPT_static[] PROGMEM{ R"=====(
			
			var with_deposit = %PLACEHOLDER_DEPOSIT%;
			var price_alc = %PLACEHOLDER_PRICE_ALC%;
			var price_nonalc = %PLACEHOLDER_PRICE_NONALC%;
			
			var count_alc = 0;
            var count_nonalc = 0;
            var paid = "";
			var total_price = 0;

            let Cocktail;
            let IsAlc;
            //Javascript Popup f�r Bestellungen mit Alkohol
            const openModalButtons = document.querySelectorAll(
                "[data-modal-target]"
            );
            const closeModalButtons = document.querySelectorAll(
                "[data-close-button]"
            );
            const overlay = document.getElementById("overlay");

            openModalButtons.forEach(button => {
                button.addEventListener("click", () => {
                    Cocktail = button.name; //scch -> weil custom die Drinks in ml dynamisch gespeichert werdne müssen
                    const modal = document.querySelector(
                        button.dataset.modalTarget
                    );
                    openModal(modal);
                });
            });

            overlay.addEventListener("click", () => {
                const modals = document.querySelectorAll(".modalalc.active");
                modals.forEach(modal => {
                    closeModal(modal);
                });
            });

            overlay.addEventListener("click", () => {
                //cs20200320-APP
                const modals = document.querySelectorAll(".modalcust.active");
                modals.forEach(modal => {
                    closeModal(modal);
                });
            });

            overlay.addEventListener("click", () => {
                const modals = document.querySelectorAll(".modalnonalc.active");
                modals.forEach(modal => {
                    closeModal(modal);
                });
            });

            closeModalButtons.forEach(button => {
                button.addEventListener("click", () => {
                    const modal = button.closest(".modalalc");
                    closeModal(modal);
                });
            });

            closeModalButtons.forEach(button => {
                button.addEventListener("click", () => {
                    //cs20200320-APP
                    const modal = button.closest(".modalcust");
                    closeModal(modal);
                });
            })

            closeModalButtons.forEach(button => {
                button.addEventListener("click", () => {
                    const modal = button.closest(".modalnonalc");
                    closeModal(modal);
                });
            });

            function closeModal(modal) {
                if (modal == null) return;
                modal.classList.remove("active");
                overlay.classList.remove("active");
            }

            function openModal(modal) 
            {
                if (modal == null) return;

                console.log(modal.className);
                modal.classList.add("active");
                overlay.classList.add("active");
                if (modal.classList.contains("modalalc")) {
                    IsAlc = true;
                    let response = fetch ('/Bestellung',{
                        method:  'POST',
                        headers:  {
                        'Content-Type': 'text/plain'
                         },
                        body:  Cocktail
                        });
                    count_alc++;
					if ( with_deposit == true)
					{
                    total_price =
                        count_alc * price_alc +
                        count_alc * 5 +
                        count_nonalc * price_nonalc +
                        count_nonalc * 5;
					}
					else
					{
						total_price =
                        count_alc * price_alc +
                        count_nonalc * price_nonalc;
					}
					document.getElementById("display").innerHTML = total_price;

                    setTimeout(function() {
                        closeModal(modal);
                    }, 3000);
                } else if (modal.classList.contains("modalnonalc")) {
                    IsAlc = false;
                    let response = fetch ('/Bestellung',{
                        method:  'POST',
                        headers:  {
                        'Content-Type': 'text/plain'
                        },
                        body:  Cocktail
                        });
                    count_nonalc++;
					if ( with_deposit == true)
					{
                    total_price =
                        count_alc * price_alc +
                        count_alc * 5 +
                        count_nonalc * price_nonalc +
                        count_nonalc * 5;
					}
					else
					{
						total_price =
                        count_alc * price_alc +
                        count_nonalc * price_nonalc;
					}
					document.getElementById("display").innerHTML = total_price;
                    setTimeout(function() {
                        closeModal(modal);
                    }, 3000);
                } else {
                    calculatePrice();
                    paid = document.querySelector("#paid").value;
                }
            }

            function calculatePrice() {
				if ( with_deposit == true)
				{
                total_price =
                    count_alc * price_alc +
                    count_alc * 5 +
                    count_nonalc * price_nonalc +
                    count_nonalc * 5;
				}
				else
				{
					total_price =
                    count_alc * price_alc +
                    count_nonalc * price_nonalc;
				}
                document.getElementById("cost").innerHTML = total_price;
            }
            function calculateReturn() {
				
                var paid_local =  parseFloat(document.getElementById("paid").value);
				if ( with_deposit == true)
				{
                total_price =
                    count_alc * price_alc +
                    count_alc * 5 +
                    count_nonalc * price_nonalc +
                    count_nonalc * 5;
				}
				else
				{
					total_price =
                    count_alc * price_alc +
                    count_nonalc * price_nonalc;
				}				



                var price = parseFloat(total_price);
                if (paid_local>=price)
                {
                    document.getElementById("return").innerHTML = "R&uuml;ckgeld: <strong>" + (paid_local - price).toString()+ "&euro;</strong>";
                }
                else
                {
                    document.getElementById("return").innerHTML = "Noch zu zahlen: <strong>" + (price - paid_local).toString() + "&euro;</strong>";
                }
            }

            function isNumberKey(evt) {
                var charCode = evt.which ? evt.which : event.keyCode;
                if (
                    charCode > 31 &&
                    (charCode != 46 && (charCode < 48 || charCode > 57))
                )
                    return false;
                return true;
            }
            
            function isEnterKey(evt) {
                
                if (evt.keyCode == 13)
                    calculateReturn();
            }

            //Javascript Popup f�r Total
            const openTotalButton = document.querySelectorAll(
                "[total-modal-target]"
            );
            const closeTotalButton = document.querySelectorAll(
                "[total-close-button]"
            );
            //const overlay = document.getElementById("overlay");

            /* openTotalButton.forEach(button => {
                            button.addEventListener("click", () => {
                                const total = document.querySelector(
                                    button.dataset.totalTarget
                                );
                                openTotal(total);
                            });
                        });
            */
            overlay.addEventListener("click", () => {
                const total = document.querySelectorAll(".total1.active");
                total.forEach(total => {
                    closeTotal(total);
                });
            });

            closeTotalButton.forEach(button => {
                button.addEventListener("click", () => {
                    const total = button.closest(".total1");
                    closeTotal(total);
                });
            });

            function closeTotal(total) {
                if (total == null) return;
                total.classList.remove("active");
                overlay.classList.remove("active");
                if (total.classList.contains("total1")) {
                    count_alc = 0;
                    count_nonalc = 0;
                    document.getElementById("display").innerHTML = 0;
                    document.getElementById("paid").value = 0;
                    document.getElementById("return").innerHTML = "";
                }
            }

            function openTotal(total) {
                if (total == null) return;
                total.classList.add("active");
                overlay.classList.add("active");
            }



)=====" };
