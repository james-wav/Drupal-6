$Id: README.txt,v 1.5.6.1.2.2 2009/01/23 15:05:07 paulbooker Exp $

DESCRIPTION
--------------------------
* provides a recently added block for your del.icio.us bookmarks
* provides "smart tagging" of node body and teaser contents based on
  del.icio.us user tags
* allows each user to have their own del.icio.us links
* allows customized blocks based upon combinations of users and tags

INSTALLATION
---------------
1. Upload the del.icio.us module to your modules directory @ site/all/modules
2. Enable the del.icio.us module @ admin/build/modules
3. Configure permissions for the del.icio.us module @ admin/user/permissions#module-delicious 
4. Configure the del.icio.us module @ admin/settings/delicious
5. Configure del.icio.us blocks @ admin/build/block/delicious
6. Enable del.icio.us for your account at user/<UID>/delicious and enter your del.icio.us account details


NOTES
----------------
* The link and tag lists are updated by drupal's cron service.
* Because del.icio.us requests that updates not be done more than every 30 minutes, there is no provision to force an update other than by hitting cron.php. Hence there is a lag between the time you add a link and it appears in the sidebar block this module generates.

DEVELOPERS & SITE BUILDERS
------------------

THEMES
------------------

INTEGRATION
---------------------

UNIT TESTING
----------------------
This module does not come with unit tests. Please consider helping to build some of these.  See http://drupal.org/simpletest

TODO/BUGS/FEATURE REQUESTS
----------------
- See http://drupal.org/project/issues/delicious. Please search before filing issues in order to prevent duplicates.

* Tag clouds
* Look at the actuator code

UPGRADING FROM 5.0 TO 6.x
-----------------

CREDITS
----------------------------
Authored and maintained by Paul Booker <paul AT glaxstar DOT com>