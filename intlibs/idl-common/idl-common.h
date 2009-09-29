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

#ifndef IDL_COMMON_H
#define IDL_COMMON_H

#include <vector>
#include <exception>
#include <string>

using namespace std;

struct Typedef {
	string type, name;
	string comment;
	int ix;
};

struct Define {
	string value;
	string comment;
	int ix;
};

struct Constant {
	string name, value;
	string comment;
	int ix;
};

struct ConstSet {
	string name;
	vector<Constant> constants;
};

struct Argument {
	bool in;
	string type;
	string name;
};

struct Function {
	string returnType;
	string name;
	vector<Argument> args;
	string comment;
	int number;
};

struct IoctlFunction {
	Function f;
	int ix;
};

struct Ioctl {
	string name;
	vector<IoctlFunction> functions;
};

struct PlainOldData {
	string type, name;
	string comment;
};

//enum MemberType { PLAIN_OLD_DATA, ANONYMOUS_UNION };

struct Member {
	//MemberType type;
	vector<PlainOldData> pod;	//if size() == 1, then type == POD, else AU.
};

struct Struct {
	string type, name;
	vector<Member> members;
	string comment;
	int ix;	//internal extension
};

struct Interface {
	string path;	//used by extensions
	string name;
	vector<Typedef> typedefs;
	vector<Define> defines;
	vector<ConstSet> constSets;
	vector<Function> functions;
	vector<Struct> structs;
	vector<Ioctl> ioctls;	//internal IDL only
	string comment;
};

typedef unsigned int uint32;
typedef unsigned short uint16;

#define MAIN_INTERFACE (-1)

#if defined(__GNUC__) || defined(__SYMBIAN32__)
#define ATTRIBUTE(a, func)  func __attribute__ ((a))
#elif defined(_MSC_VER)
#define ATTRIBUTE(a, func)  __declspec (a) func
#else
#error Unsupported compiler!
#endif

//doesn't set Interface.path
Interface parseInterface(const vector<string>& ixs, const string& filename);

void dumpInterfaces(const vector<Interface>& infs);
uint32 calculateChecksum(const vector<Interface>& infs);
uint32 calculateChecksum(const Interface& inf);

void streamHash(ostream& stream, const Interface& inf);

void streamHeaderFile(ostream& stream, const Interface& inf, const vector<string>& ixs, int ix);
void streamCppDefsFile(ostream& stream, const Interface& inf, const vector<string>& ixs, int ix);

void streamConstants(ostream& stream, const vector<ConstSet>& constSets, int ix);
void streamIoctlDefines(ostream& stream, const vector<Ioctl>& ioctls, int ix);
//void streamIoctlFunction(ostream& stream, const Interface& inf, const Function& f,
//	const string& ioctlName);

//implemented by the user
void streamHeaderFunctions(ostream& stream, const Interface& inf, bool syscall);

void ATTRIBUTE(noreturn, throwException(const string& msg));
void runCommand(const string& cmd);
const string& getJdkDir();
const string& getJ2meDir();

inline const char *validateString(const char *str) {
	if(!str) throwException("No MOSYNCDIR exists");
	return str;
}
#define MOSYNCDIR string(validateString(getenv("MOSYNCDIR")))

#endif	//IDL_COMMON_H
