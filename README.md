# MQTT-Dashboard-Website-And-Client
This is a project where I made a Webbased Dashboard meant to be used as a way to controll and monitor microcontrollers around the home and send them instructions through an MQTT-Broker. The Provided Example will controll an LED.
In order to set this up you will need to do the following:

Step 1: Setup your own MQTT-Broker (I used my own raspberry pi 3B)

Step 2: Download the libraries used for the website through pip

Step 3: Enter the MQTT-Credentials in both the web and Client files

Step 4: Configure the IP and passwords for the WIFI you are using in the Client file (OBS: if it refuse to connect make sure your network is set to private and allow the connection through the Firewall)

Step 5: Upload the Client code to a MicroController and try controlling it through the website
