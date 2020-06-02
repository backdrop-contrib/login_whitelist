Login whitelist
===============

Restrict login to your site for whitelisted users only, protect against "lazy"   
brute force attack and harmful malformed login requests.

Features 
--------

You may want to restrict access to login to your site for a few registered   
users only by creating your whitelist.

"Lazy" brute force attack can use large number non-repeated IPs with relatively   
rare requests (one or two in few minutes) and cannot be prevented by using   
IP-based blacklisting.

This module reacts to such behavior by returning error 404 or 403 (you can   
select which) to an attacker for any user login related activity:
- in case username or email is not in whitelist;
- if login request is harmfully malformed, for example, executable code   
injection attempt.

By enabling logging all unwanted login attempts you can have an idea which pairs   
of usernames and passwords have been used for brute force, IP and User-Agent   
string used by attacker script.

Additionally, User-Agent strings used by known attackers (also collected from   
the module log) can be placed to block-list to reject further login requests.

**Please note:** when this module enabled, only administrators can manage accounts   
for users, like new user registration or password reset.

Installation
------------

Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration
-------------

Configuration page is available via menu *Administration > Configuration > 
User accounts > Login whitelist* (admin/config/people/login_whitelist).

Under the tab "Main settings":

- allow login to all registered active users (enabled by default);
- or create a whitelist for some users as described under a corresponding field;
- change type of HTTP status code returning to an unwanted visitor.

Under the tab "Blocked User-Agents":

- block a User-Agent string:
    - enter unwanted User-Agent string (wildcarded part of the string can be used);

- unblock previously blocked User-Agent:
    - beside a User-Agent string, click "Unblock", then confirm unblocking.

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

