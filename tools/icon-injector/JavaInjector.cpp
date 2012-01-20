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

#include "JavaInjector.h"
#include  "Icon.h"
#include <fstream>
#include <sstream>
#include "Shared.h"
#include <stdio.h>

using namespace std;

namespace MoSync {

static int j_inject(const char *jarFile, const char *pngFile) {
	int res;

	//extract manifest
	char buf[1024];
	sprintf(buf, "unzip -o \"%s\" \"%s\"", jarFile, "META-INF/MANIFEST.MF");
	res = run(buf);
	if(res != 0)
		return res;
	char icon[1024];

	//parse / modify
	{
		ifstream mfIn("META-INF/MANIFEST.MF");
		ostringstream mfStrOut;
		while(1) {
			mfIn.getline(buf, sizeof(buf));
			if(!mfIn.good())
				break;
			char name[1024], midlet[1024];
			if(sscanf(buf, "MIDlet-1: %[^,], %[^,], %s", name, icon, midlet) == 3) {
				// Modifying the manifest will lead to deployment problems,
				// hence this fix
				//mfStrOut << "MIDlet-1: " << name << ", " << pngFile << ", " << midlet << "\n";
			}
			mfStrOut << buf << "\n";
		}
		mfIn.close();
		ofstream mfFileOut("META-INF/MANIFEST.MF");
		mfFileOut << mfStrOut.str();
	}

	// Rename our png file
	rename(pngFile, icon);

	//insert modified manifest & icon
	sprintf(buf, "zip \"%s\" \"%s\" \"%s\"", jarFile, "META-INF/MANIFEST.MF", icon);
	res = run(buf);
	if(res != 0)
		return res;

	//done
	return 0;
}


void JavaInjector::inject(const Icon* icon, const std::map<std::string, std::string>& params) {
	string size = verifyParameter(params, "size");
	string dst = verifyParameter(params, "dst");
	const IconInstance* iconInst = icon->findBestInstance(size);
	if(!iconInst) errorExit("Couldn't find any icon instance.");

	if(!convertInstanceToImageFormat(iconInst, "temp.png", size, "png"))
		errorExit("Java icon conversion failed.");
	if(j_inject(dst.c_str(), "temp.png") != 0)
		errorExit("Java injector failed.");
}

}
