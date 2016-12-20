Login whitelist
===============

Restrict login to the site for whitelisted users only.
Provides protection against "lazy" brute force attack and harmfully malformed login requests.

Goals 
-----
IP-based blacklisting is not effective protection against "lazy" brute force attack, 
which use large number non-repeated IPs and relatively rare requests - one or two in few minutes.

For any of such requests Backdrop returned HTTP status code "200 OK" 
and attacker's script still to try same usernames or emails again and again.

This module prevents such behavior by returning 403 or 404 to any login attempt, 
where username or email is not whitelisted.

Same reaction will be performed for harmfully malformed login requests, 
e.g. using array within POST, and preventing useful for attacker PHP errors 
generating (and displaying on some setups).

For some reason you may want to restrict access to the site 
for few of registered users only, so you can do it by creating a short (or long) whitelist.

Additionally, *User-Agent strings known as used by bad robots* can be added to reject 
even for their GET login request. 

Installation
------------
Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
Administration page is available via menu *Administration > Configuration > 
User accounts > Login whitelist* (admin/config/people/login_whitelist) 
and may be used for:

- allow login to all registered active users (enabled by default);
- create whitelist for login as described under corresponding field;
- change type of HTTP status code which should be returned to unwanted visitor,
- create list of User-Agent strings known as used by bad robots.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module 
issue queue at https://github.com/backdrop-contrib/login_whitelist/issues.

