
Debian
====================
This directory contains files used to package MTNCd/MTNC-qt
for Debian-based Linux systems. If you compile MTNCd/MTNC-qt yourself, there are some useful files here.

## MTNC: URI support ##


MTNC-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install MTNC-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your MTNC-qt binary to `/usr/bin`
and the `../../share/pixmaps/MTNC128.png` to `/usr/share/pixmaps`

MTNC-qt.protocol (KDE)

