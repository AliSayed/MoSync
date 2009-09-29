/* Copyright (C) 2009 Mobile Sorcery AB

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/

#include "maapi.h"
#include "ttsdemo.png.h"
#include "ttsdemo_splash.png.h"

int main() {
	Handle splash = 0;
	CreateImage(splash, splash_png, sizeof(splash_png));
	DrawImage(splash, 0, 0);
	UpdateScreen();
	do {
		Wait(WAIT_KEY);
		if(GetKeys() & MAK_FIRE)
			break;
	} while(1);
	DestroyObject(splash);

	Handle backg = 0;
	CreateImage(backg, ttsdemo_png, sizeof(ttsdemo_png));
	DrawImage(backg, 0, 0);
	UpdateScreen();

	int oldKeys = GetKeys();
	while(1) {
		Wait(WAIT_KEY);
		int newKeys = GetKeys();
		int downedKeys = newKeys & (~oldKeys);
		oldKeys = newKeys;

		if(downedKeys)
			StopSpeaking();

		if(downedKeys & MAK_FIRE) {
			StartSpeaking("Du st�r i korsningen G�tgatan �s�gatan riktning Slussen. En meter till "
				"v�nster om dig �r ett �verg�ngst�lle, f�r passage �ver G�tgatan med "
				"tryckknapp f�r g�ngtrafikanter. Vid trottoarkanten l�per en cykelv�g.");
		}
		if(downedKeys & MAK_DOWN) {
			StartSpeaking("Tre meter bakom dig i riktning Skanstull �r ett �verg�ngst�lle f�r "
				"passage �ver �s�gatan.");
		}
		if(downedKeys & MAK_UP) {
			StartSpeaking("Trottoaren rakt framforts�tter 50 meter till n�sta korsning Folkungagatan. "
				"P� andra sidan av �verg�ngst�llet finns ing�ngar till tunnelbanestation "
				"medborgarplatsen.");
		}
		/*if(downedKeys & MAK_RIGHT) {
		StartSpeaking("Am I right? Of course I'm right.");
		}
		if(downedKeys & MAK_LEFT) {
		StartSpeaking("No one is left behind.");
		}*/
	}
	return 0;
}

