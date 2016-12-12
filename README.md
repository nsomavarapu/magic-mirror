**Magic Mirror**
============================================
A magic mirror system written in C/C++ using GTK+3.

**Build Instructions**

This is will build with any *nix system.

**Steps:**

* ./configure
* make

This is will produce an executable magic_mirror which can be run with ./magic_mirror

**Setup Calender**

* Use this [wizard](https://console.developers.google.com/flows/enableapi?apiid=calendar&pli=1) to create or select a project in the Google Developers Console and automatically turn on the API. Click **Continue**, then Go to **credentials**.
* On the **Add credentials to your project** page, click the **Cancel** button.
* At the top of the page, select the **OAuth consent screen** tab. Select an **Email address**, enter a **Product name** if not already set, and click the **Save** button.
* Select the **Credentials** tab, click the **Create credentials** button and select **OAuth client ID**.
* Select the application type **Other**, enter the name "Google Calendar API Quickstart", and click the **Create** button.
* Click **OK** to dismiss the resulting dialog.
* Click the **download** button to the right of the client ID.
* Move this file to your /src/calender/ directory and rename it client_secret.json.

**Setup Weather**
* Register at [this](https://darksky.net/dev/register) link
* You will recieve an API key
* In */src/weather/* in *weather.cpp*, line 11, change the the API key to the one you recieved like so: https://api.darksky.net/forecast/YOUR_API_KEY_HERE/

*Optional*
* If you do not live in Atlanta, in *main.cpp*, line 27, you will have to update your latitude and longitude to your current location, respectively.


**Voice Recognition**
* Voice recognition has been setup to parse speech 
* Requires an external USB Microphone
* Currently does not act upon parsed speech
