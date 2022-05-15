# My build of **suckless's dwm**

This build includes some patches (Mentioned below)

## Original README

Bellow are the contents of the original README file from **suckless** with some
minor edits.

### dwm - dynamic window manager

dwm is an extremely fast, small, and dynamic window manager for X.

### Requirements

In order to build dwm you need the Xlib header files.

### Installation

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

`make clean install`

### Running dwm

Add the following line to your _.xinitrc_ file to start dwm using `startx`:

`exec dwm`

In order to connect dwm to a specific display, make sure that
the **DISPLAY** environment variable is set correctly, e.g.:

`DISPLAY=foo.bar:1 exec dwm`

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your _.xinitrc_ file:

```sh
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"; do
  sleep 1
done &
exec dwm
```

### Configuration

The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Patches credits

- [attachaside patch](https://dwm.suckless.org/patches/attachaside/):
  - Jerome Andrieux - jerome@gcu.info
  - Chris Down - chris@chrisdown.name (6.1 port and fixes)
  - Laslo Hunhold - dev@frign.de (git port)
- [ru gaps patches](https://dwm.suckless.org/patches/ru_gaps/)
  - Aaron Duxler - aaron@duxler.xyz
  - Rob Livesey - rlives6789@gmail.com
-	[hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/):
	- Adrian Amaglio
	- Ondřej Grover - ondrej.grover@gmail.com
	- Matthew Boswell
	- Jochen Sprickerhof - project@firstname.lastname.de
- [status2d](https://dwm.suckless.org/patches/status2d/)
	- sipi - https://github.com/sipi
	- lhark - lhark@ntymail.com
