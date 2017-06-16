Little Calendars
===================
A Drupal 7 input filter that sets up one or more cleanly formatted calendars. Each day of the month can have it's own link and background color to denote certain events. Core logic adapted from https://github.com/Goatella/PHP-Calendar/blob/master/cal.php. I, in turn, converted to a class, allowed input of a current date function, added other embelishments as needed such as date highlighting, and made for use as a Drupal 7 Module.

How to use
----------
Always start on a development or test server. Never test a new module on a public-facing production server.

1. Clone repo to sites/all/modules
2. Enable module
3. Turn on input filter in settings (Text Formats inside of Full HTML, etc)

In a Body field, enter the following example.

[minical:2015|2|none,#336699,1,2,3|http://github.com,#445566,12,13,15]
[minical:2016|2|none,#336699,1,2,3|http://google.com,#445566,12,13,15]

As seen below, reading from left to right, it takes in the
- year
- month
- optional url (url or the word none)
- optional hex color for the background of the date (#hexcolor or the word none)
- and a remainder of comma deliniated series of days of the month that will take on this link and background color values

[minical:YYYY|M|url,#hex_color,d,a,t,e,s|url,#hex_color,d,a,t,e,s]


How to configure:
-----------------
The permissions and configuration are linked from the same place where you'll enable the module.

Disclaimer
----------
Use at your own risk. Test on a development or testing server, never on live code.

Other caveat:
-------------
You may have to turn off the "Convert URLs into links" filter.




