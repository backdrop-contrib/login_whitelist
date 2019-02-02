Login whitelist
===============

Restrict login to your site for whitelisted users only, protect against "lazy" brute force 
attack and harmful malformed login requests.

Features 
--------

You may want to restrict access to login to your site for few of registered users only  
by creating your own whitelist.

"Lazy" brute force attack can use large number non-repeated IPs with relatively rare requests 
(one or two in few minutes) and cannot be prevented by using IP-based blacklisting.

This module react to such behavior by returning to attacker error 403 or 404 (you choice) 
to any user login related activity attempt in case username or email is not whitelisted or 
if login request is harmfully malformed, for example: executable code injection attempt.

By enabling logging all unwanted login attempts you can have an idea which pairs 
of usernames and passwords have been used for brute force, IP and User-Agent string used by attacker script.

Additionally, User-Agent strings used by known attackers (collected from module log) 
can be placed to block-list for reject their further login requests.

Please note: when this module enabled, only administrators can manage users accounts, 
like new user registration or password reset.

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
- or create whitelist for some users as described under corresponding field;
- change type of HTTP status code returning to unwanted visitor.

Under tab "Blocked User-Agents":

- create and manage block-list of User-Agent strings (or wildcarded parts of strings) known as used by bad robots 
or just not intended for user login to your site.

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

