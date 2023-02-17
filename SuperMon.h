const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<head>
<meta http-equiv="refresh" content="120">
<title>Garage Status</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
      margin: 20px auto;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #FFFFFF;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
      text-align:center;
    }
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
    .blink-red{
      text-align:center;
      animation: flashred 1s infinite;
    }
    @keyframes flashred{
      0%    { background-color: #C8C8C8;}
      50%   { background-color: #FF0000;}
      100%  { background-color: #C8C8C8;}
    }
    .blink-org{
    animation: flashorange 3s infinite;
    text-align:center;
    }
    @keyframes flashorange{
      0%    { background-color: #C8C8C8;}
      50%   { background-color: #FF8000;}
      100%  { background-color: #C8C8C8;}
    }
    .btn {
      background-color: #4444CC;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 24px;
      margin: 30px auto;
      cursor: pointer;
      border-radius: 5px;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>
</head>
  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Garage Status</div>
            <div class="navdata" id = "date">dd/mm/yyyy</div>
            <div class="navheading">DATE</div><br/>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div style="border-radius: 10px !important;">
        <table style="width:75%">
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 10%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
        </colgroup>
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <tr>
          <th colspan="1"><div class="heading">Sensor</div></th>
          <th colspan="1"><div class="heading">Status</div></th>
        </tr>
          <tr>
          <td><div class="bodytext">Freezer temp</div></td>
          <td><div class="tabledata" id = "tempF"></div></td>
        </tr>
        </tr>
          <tr>
          <td><div class="bodytext">Garage temp</div></td>
          <td><div class="tabledata" id = "tempG"></div></td>
        </tr>
        </tr>
          <tr>
          <td><div class="bodytext">Outside temp</div></td>
          <td><div class="tabledata" id = "tempO"></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Door Status</div></td>
          <td><div id = "garage"></div></td>
        </tr>
        <tr>
          <td colspan="2" align ="center">
            <button type="button" class = "btn" id = "btn1" onclick="ButtonPress()">Activate Garage Door</button>
          </td>
        </tr
        </table>
    </div>
  </main>
  
  </body>


  <script type = "text/javascript">
  
    // global variable visible to all java functions
    var xmlHttp=createXmlHttpObject();

    // function to create XML object
    function createXmlHttpObject(){
      if(window.XMLHttpRequest){
        xmlHttp=new XMLHttpRequest();
      }
      else{
        xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
      }
      return xmlHttp;
    }

    // function ButtonPress0() {
    //   var xhttp = new XMLHttpRequest(); 
    //   var message;
    //   // if you want to handle an immediate reply (like status from the ESP
    //   // handling of the button press use this code
    //   // since this button status from the ESP is in the main XML code
    //   // we don't need this
    //   // remember that if you want immediate processing feedbac you must send it
    //   // in the ESP handling function and here
    //   /*
    //   xhttp.onreadystatechange = function() {
    //     if (this.readyState == 4 && this.status == 200) {
    //       message = this.responseText;
    //       // update some HTML data
    //     }
    //   }
    //   */
    //  
    //   xhttp.open("PUT", "BUTTON_0", false);
    //   xhttp.send();
    // }

    function ButtonPress() {
      var xhttp = new XMLHttpRequest();
      xhttp.open("PUT", "BUTTON", false);
      xhttp.send(); 
    }
    
 // function to handle the response from the ESP
    function response(){
       var message;
       var xmlResponse;
       var xmldoc;
       var dt = new Date();
     
      // get the xml stream
      xmlResponse=xmlHttp.responseXML;
  
      // get host date and time
      document.getElementById("time").innerHTML = dt.toLocaleTimeString('en-US', {hour12: false});
      //document.getElementById("time").innerHTML = dt.toLocaleTimeString();
      document.getElementById("date").innerHTML = dt.toLocaleDateString('en-GB', {day: 'numeric', month: 'short', year: 'numeric'});
      //document.getElementById("date").innerHTML = dt.toLocaleDateString();
  
      //Temp
      xmldoc = xmlResponse.getElementsByTagName("TF"); // Freezer Temp
      message = xmldoc[0].firstChild.nodeValue;
      if (message == "-127.0")  {
        document.getElementById("tempF").className="blink-red";
        message = "Sensor Error"
      }
      else if (message >= -10){
        document.getElementById("tempF").className="blink-red";
      } 
      else {
        document.getElementById("tempF").className="tabledata";
      }
      document.getElementById("tempF").innerHTML=message;
      
      xmldoc = xmlResponse.getElementsByTagName("TG"); // Garage Temp
      message = xmldoc[0].firstChild.nodeValue;
      if (message == "-127.0") {
        document.getElementById("tempG").className="blink-red";
        message = "Sensor Error"
      }
      document.getElementById("tempG").innerHTML=message;
      
      xmldoc = xmlResponse.getElementsByTagName("TO"); // Outside Temp
      message = xmldoc[0].firstChild.nodeValue;
      if (message ==  "-127.0" ) {
        document.getElementById("tempO").className="blink-red";
        message = "Sensor Error"
      }
      document.getElementById("tempO").innerHTML=message;

      //Garage
      xmldoc = xmlResponse.getElementsByTagName("G0");
      message = xmldoc[0].firstChild.nodeValue;
      if (message == "Closed"){
        document.getElementById("garage").className="tabledata";
        document.getElementById("garage").innerHTML=message;
      } else if (message == "Open") {
        document.getElementById("garage").className="blink-red";
        document.getElementById("garage").innerHTML=message;
      } else {
        document.getElementById("garage").className="blink-org";
        document.getElementById("garage").innerHTML=message;
      }

      // update the text in the table
      
      xmldoc = xmlResponse.getElementsByTagName("RELAY");
      message = xmldoc[0].firstChild.nodeValue;
      document.getElementById("relay").style.backgroundColor="rgb(200,200,200)";

      if (message == 0){
        document.getElementById("relay").innerHTML="---";
        document.getElementById("btn1").innerHTML="Activate Garage Door";
        document.getElementById("relay").style.color="#0000AA"; 
      }
      else {
        document.getElementById("relay").innerHTML="Switch is ON";
        document.getElementById("btn1").innerHTML="Activate Garage Door";
        document.getElementById("relay").style.color="#00AA00";
      }
     }


    function process(){
     
     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
        xmlHttp.open("PUT","xml",true);
        xmlHttp.onreadystatechange=response;
        xmlHttp.send(null);
      }       
        // you may have to play with this value, big pages need more porcessing time, and hence
        // a longer timeout
        setTimeout("process()",300);
    }
  
  
  </script>

</html>



)=====";
