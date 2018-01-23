#ifndef __DEBUGGER_H__
#define __DEBUGGER_H__

#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class Debugger
{
public:
	Debugger();

	void AddClass(string name, DWORD baseAddress);
	void Update();
	string Text() { return this->buff; }

private:
	char buff[1024];
	vector<DWORD>offsets;

	void Navigation();
	void ClassChanger();

	struct DebugInfo { int num; int index; DWORD address; } debugInfo;
	struct ClassInfo { string name; DWORD address; }; vector<ClassInfo>classes;

	// class atual
	ClassInfo CurrentClass() { return classes[debugInfo.index]; }
	string BaseName() { return CurrentClass().name; }
	DWORD BaseAddress() { return CurrentClass().address; }

	// endereço
	DWORD Offset() { return offsets[offsets.size() - 1]; }
	DWORD Address() { return (DWORD)&debugInfo.address; }

	// ponteiro
	DWORD Pointer() { return *(DWORD*)Address(); }
	bool IsValidPointer() { return !IsBadReadPtr((LPVOID)Pointer(), 4); }

	// valores
	bool Boolean() { return *(BYTE*)Address() == 1; }
	__int8 Int8() { return *(__int8*)Address(); }
	__int16 Int16() { return *(__int16*)Address(); }
	__int32 Int32() { return *(__int32*)Address(); }
	float Float() { return *(float*)Address(); }
};

extern Debugger debugger;

#endif	//__DEBUGGER_H__