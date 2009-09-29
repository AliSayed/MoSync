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

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RGB(r, g, b) (((r) << 16) | ((g) << 8) | (b))

Extent DrawTextLine(int line, char* text);

int main() {
	int line = 0;

	DrawTextLine(line++, "Press any key");
	Wait(WAIT_KEY);

	DrawTextLine(line++, "Hello World!");
	StartSpeaking("G� i riktning mot Stockholm, sv�ng v�nster vid Sickla Industriv�g. F�lj trappan som ligger till h�ger om Atlas Copco huset. Ta v�nster vid Skr�dderifirman in till Marcusplatsen. Dieselverkstaden ligger till v�nster, g� in genom huvudentr�n, ta trappan upp s� finns vi innanf�r d�rren till h�ger."
		"Saltsj�banan fr�n Slussen till Sickla station."
		"F�lj trappan som ligger till h�ger om Atlas Copco huset. Ta v�nster vid Skr�dderifirman in till Marcusplatsen. Dieselverkstaden ligger till v�nster, g� in genom huvudentr�n, ta trappan upp och d�rren till h�ger."
		"Det finns �ven skyltar mot Dieselverkstaden som man kan f�lja.");
	DrawTextLine(line++, "started");
	if(!IsSpeaking()) {
		DrawTextLine(line++, "Not speaking!");
		goto end;
	}
	Wait(WAIT_TTS);
	DrawTextLine(line++, "done");
	if(IsSpeaking()) {
		DrawTextLine(line++, "Still speaking!");
		goto end;
	}

end:
	//wait for keypress, then exit
	DrawTextLine(line++, "PAK to quit");
	Wait(WAIT_KEY);
	DrawTextLine(line++, "Quitting...");
	Exit(0);
	DrawTextLine(line++, "Exit returned!");
	return 0;
}

Extent DrawTextLine(int line, char* text) {
	Extent res = DrawText(10, line*10+20, text);
	UpdateScreen();
	return res;
}

