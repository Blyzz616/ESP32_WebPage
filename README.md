<b><h2><center>The code that I'm using to display temperatures and the status of my  garage as well as a button to activeate the garage door</center></h1></b>

Using this [awesome code](https://github.com/KrisKasprzak/ESP32_WebPage) from [KrisKasprzak](https://github.com/KrisKasprzak), I've creadted a static web page that displays the current temperatures of the freezer in my garage, the ambient temerature in my garage and the outside temerature. I've also set up 2 hall effect sensors to show me whether the  garage door is fully open, fully  closed or somewhere in between.

The best part is that I've added a optocoupler relay to activate the garage door. As I've got a personal VPN sut up, All I need to do to  connec to that with my phone, and I can close my garage door (or open it to give someone access), frmo anywhere in the world with ineternet access.
<br>
The garage door status will slowly flash orange when it is travelling (not open and not closed) and it will flash red if it is open. The freezer temerature indicator will also start flashing red when the temperature is above -10 C°.
<br>

<strong>To do:</strong><br>
1:    Add a notification system to notify me when the garage door is open.<br>
1.1:  I might also include a way to check to see if my cellphone is connected to the network first. (If I'm connected to the network, then ifgnore, else, send notification to me)
<br><br>
2:    I'm  also busy recording all the temperatures to another server and generating a graph for the last 90 minutes, 36 hours, 10 days, 45 days and 9 months. I'm probably going to host that image on that server and then put in static \<img\> tag to load that up from the server.
<br><br>


![garage](https://user-images.githubusercontent.com/19424317/221385717-bb6a6d08-2603-41ee-95e0-7aa49f3024cb.png)
