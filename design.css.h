const char Design[] PROGMEM{ R"=====(
/*!
 * Start Bootstrap - Scrolling Nav (https://startbootstrap.com/template-overviews/scrolling-nav)
 * Copyright 2013-2019 Start Bootstrap
 * Licensed under MIT (https://github.com/BlackrockDigital/startbootstrap-scrolling-nav/blob/master/LICENSE)
 */
* {
  box-sizing: border-box;
}

body {
  margin: 0px;
  font-family: 'segoe ui';
}

.logo_image
{
	height: 70px;
	width: auto;
	background-color: white;
	box-shadow: 10px 10px 15px silver;
	border-radius: 10px;
}

.nav {
  height: 50px;
  width: 100%;
  background-color: red;
  position: fixed;
z-index: 5;
}

.nav > .nav-header {
  display: inline;
}

.nav > .nav-header > .nav-title {
  display: inline-block;
  font-size: 22px;
  color: #fff;
  padding: 10px 10px 10px 10px;
}

.nav > .nav-btn {
  display: none;
}

.nav > .nav-links {
  display: inline;
  float: right;
  font-size: 18px;
}

.nav > .nav-links > a {
  display: inline-block;
  padding: 10px 10px 13px 10px;
  text-decoration: none;
  color: #efefef;
}

.nav > .nav-links > a:hover {
  background-color: rgba(0, 0, 0, 0.3);
}

.nav > #nav-check {
  display: none;
}

@media (max-width:600px) {
  .nav > .nav-btn {
    display: inline-block;
    position: absolute;
    right: 0px;
    top: 0px;
  }
  .nav > .nav-btn > label {
    display: inline-block;
    width: 50px;
    height: 50px;
    padding: 13px;
  }
  .nav > .nav-btn > label:hover,.nav  #nav-check:checked ~ .nav-btn > label {
    background-color: rgba(0, 0, 0, 0.3);
  }
  .nav > .nav-btn > label > span {
    display: block;
    width: 25px;
    height: 10px;
    border-top: 2px solid #eee;
  }
  .nav > .nav-links {
    position: absolute;
    display: block;
    width: 100%;
    background-color: #333;
    height: 0px;
    transition: all 0.3s ease-in;
    overflow-y: hidden;
    top: 50px;
    left: 0px;
  }
  .nav > .nav-links > a {
    display: block;
    width: 100%;
  }
  .nav > #nav-check:not(:checked) ~ .nav-links {
    height: 0px;
  }
  .nav > #nav-check:checked ~ .nav-links {
    height: calc(100vh - 50px);
    overflow-y: auto;
  }
}

nav{
    background-color: red;
    color:white;
}

header {
    padding: 90px 0 0px;
    background-color: red;
}

section {
    padding-top: 0px;
    padding-right: 20px;
    padding-bottom: 50px;
    padding-left: 20px;
}

footer {
    
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    background-color: red;
    color: white;
    
}

#left {
    float:left;
    width:70%;
}

#center {
    display: inline-block;
    margin:0 auto;
    width:10%;
}

#right {
    float:right;
    width:20%;
}


*,
*::after,
*::before {
    box-sizing: border-box;
}

.modalalc, .modalnonalc, .modalcustom {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%) scale(0);
    transition: 200ms ease-in-out;
    border: 1px solid black;
    border-radius: 10px;
    z-index: 10;
    background-color: white;
    width: 500px;
    max-width: 80%;
}

//cs:0402 -> .modalcustom
.modalalc.active,  .modalnonalc.active,  .modalcustom.active{
    transform: translate(-50%, -50%) scale(1);
}

//cs:0402 -> .modalcustom
.modalalc-header, .modalnonalc-header {
    padding: 10px 15px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid black;
}

//cs:0402 -> .modalcustom
.modalalc-header .title, .modalnonalc-header .title, .modalcustom-header .title {
    font-size: 1.25rem;
    font-weight: bold;
}

//cs:0402 -> .modalcustom
.modalalc-header .close-button,  .modalnonalc-header .close-button,  .modalcustom-header .close-button{
    cursor: pointer;
    border: none;
    outline: none;
    background: none;
    font-size: 1.25rem;
    font-weight: bold;
}

//cs:0402 -> .modalcustom-body
.modalalc-body, .modalnonalc-body, .modalcustom-body {
    padding: 10px 15px;
}






.total1 {
    position: fixed;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%) scale(0);
    transition: 200ms ease-in-out;
    border: 1px solid black;
    border-radius: 10px;
    z-index: 10;
    background-color: white;
    width: 500px;
    max-width: 80%;
}

.total1.active {
    transform: translate(-50%, -50%) scale(1);
}

.total-header1 {
    padding: 10px 15px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid black;
}

.total-header1 .title {
    font-size: 1.25rem;
    font-weight: bold;
}

.total-header1 .close-button {
    cursor: pointer;
    border: none;
    outline: none;
    background: none;
    font-size: 1.25rem;
    font-weight: bold;
}

.total-body1 {
    padding: 10px 15px;
}



#overlay {
    position: fixed;
    opacity: 0;
    transition: 200ms ease-in-out;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: rgba(0, 0, 0, 0.5);
    pointer-events: none;
}

#overlay.active {
    opacity: 1;
    pointer-events: all;
}

input[type="number"]
{
    font-size:24px;
    color: red;
    margin-right: 10px;
    width:80%;
    padding-bottom: 10px;
}

.btn-calc
{
    width: 20%;
    height: inherit;
    position: absolute;    
}


)=====" };
