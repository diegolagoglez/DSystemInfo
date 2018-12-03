# DSystemInfo

This is an app that shows general information about your computer and system
resources like memory available, used and max sems, ports, threads and teams.
Theese are showed on a status bars. This app also shows file system
information for mounted file systems. Shows disk space and used disk space.
This is showed on a status bar too.

# Information

 - Platform: __BeOS (x86)__
 - Programming language: __C++__
 - Creation date: __2000-12-15__
 - Modification times: __2001-02-03__/__2018-12-03__
 - License: __GPLv2__
 - Original download page: [DSytemInfo at BeBits](http://bebits.com/app/1831)

# Screenshot

![D System Info Screenshot](https://raw.github.com/diegolagoglez/DSystemInfo/master/art/dsysteminfo.jpg "D System Info Screenshot")

# Changelog

Release 0.2.6:
 - Version reset.
 - Added Makefile.

Release 2.5:
 - Added a menu bar with a new option that shows more info about the volume.
 - Added an "About" menu that shows credits.

Release 2.0:
 - The used space status bar is updated when used space change (dynamically).
 - When a file system is mounted, is its added to the menu field without restarting the app.
 - Font is always the same, even if you are using a different font of the standard BeOS font.
 - On start app, the boot volume is showed on used space status bar.
 - Some code have been optimized.

 - Error: If you keep expanded the menu field when you mount a volume, the app will crash.

Release 1.0:
 - Only support one processor.
 - Cannot update the menu field when an item is mounted.
 - Cannot update used space status bar dynamically.

> NOTE: Choosing version numbers at that time was not one of my skills (maybe not today either). DSystemInfo version should be 0.3 ;)
