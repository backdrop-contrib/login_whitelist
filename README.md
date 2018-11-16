Login whitelist
===============

Restrict login to your site for whitelisted users only, protect against "lazy" brute force 
attack and harmful malformed login requests.

Features 
--------

You may want to restrict access to login to your site for few of registered users only, 
so you can do it by creating a short (or long) whitelist.

IP-based blacklisting is not effective protection against "lazy" brute force attack, 
which can use large number non-repeated IPs and relatively rare requests - one or two in few minutes.

This module react to such behavior by returning 403 or 404 (by your choice) to any login attempt, 
where username or email is not whitelisted.

Same reaction will be performed for harmfully malformed login requests, 
e.g. using array within POST, and preventing useful for attacker PHP errors 
generating (and displaying on some setups).

By enabling logging for all unwanted login attempts you can have an idea which pairs 
of usernames and passwords have been used for brute force, IP and User-Agent used by attackers script.

Additionally, User-Agent strings of known attackers (also collected from log, described above) 
can be used in block-list to reject their requests even for `GET user/login` requests.

Installation
------------

Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration
-------------

Administration page is available via menu *Administration > Configuration > 
User accounts > Login whitelist* (admin/config/people/login_whitelist).

Under tab "Main settings":

- allow login to all registered active users (enabled by default);
- create whitelist for login as described under corresponding field;
- change type of HTTP status code which should be returned to unwanted visitor.

Under tab "Blocked User-Agents":

- create and manage block-list of User-Agent strings known as used by bad robots.

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------

Vladimir (https://github.com/findlabnet/)

Issues
------
For bug reports, feature or support requests, please use the module 
issue queue at https://github.com/backdrop-contrib/login_whitelist/issues.

