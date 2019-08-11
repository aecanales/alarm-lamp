# alarm-lamp

Simple Arduino project that switches on a lamp at a specified hour. Made for fun (and to help me wake up in the morning) but hope it's useful to someone else!

Requires the [DS3231 library](http://www.rinkydinkelectronics.com/library.php?id=73) by Rinky Dink Electronics. If you're using a ZS-042 DS3231 with a CR2032, please remove the resistor marked as '201' as shown in the attached image [in this post.](https://forum.arduino.cc/index.php?topic=278270.msg2916047#msg2916047) If you do not, you risk the CR2032 swelling and poping out!

## Components
* Arduino UNO
* 16x2 LCD Shield
* 1 channel relay
* DS3231 RTC module
