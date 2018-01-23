#include "debugger.h"

Debugger debugger;

Debugger::Debugger()
{
	// debugger
	this->debugInfo.num		= 0;	// número de classes
	this->debugInfo.index	= 0;	// índice atual
}

void Debugger::AddClass(string name, DWORD baseAddress)
{
	this->classes.push_back(ClassInfo());
	this->classes[this->debugInfo.num].name = name;
	this->classes[this->debugInfo.num].address = baseAddress;
	this->debugInfo.num++;
}

void Debugger::Update()
{
	if (this->debugInfo.num == 0)
		return;

	// navegação
	Navigation();
	ClassChanger();

	if (this->BaseAddress() != 0)
	{
		// cabeçalho
		sprintf(this->buff, "[%s]\nFrom: 0x%X + ", this->BaseName().c_str(), this->BaseAddress());

		// endereço base
		this->debugInfo.address = this->BaseAddress();

		// breadcrumb - offsets
		for (DWORD i = 0; i < this->offsets.size(); i++)
		{
			if (i != this->offsets.size() - 1)
				sprintf(this->buff + strlen(this->buff), "0x%X > ", this->offsets[i]);
			else
				sprintf(this->buff + strlen(this->buff), "0x%X ", this->offsets[i]);

			// endereço dinâmico
			this->debugInfo.address = *(DWORD*)((DWORD)this->debugInfo.address + this->offsets[i]);
		}

		// ponteiro
		sprintf(this->buff + strlen(this->buff), "\nTo: 0x%X\n\n", this->IsValidPointer() ? this->Pointer() : NULL);

		// informações
		sprintf(this->buff + strlen(this->buff), "bool: %s\n", this->Boolean() ? "true" : "false");
		sprintf(this->buff + strlen(this->buff), "int8: %d\n", this->Int8());
		sprintf(this->buff + strlen(this->buff), "int16: %d\n", this->Int16());
		sprintf(this->buff + strlen(this->buff), "int32: %d\n", this->Int32());
		sprintf(this->buff + strlen(this->buff), "float: %6.5f", this->Float());
	}
}

void Debugger::Navigation()
{
	if (this->offsets.size() == 0)
		this->offsets.push_back(0);

	if (GetAsyncKeyState(VK_ADD) &1)
		this->offsets[this->offsets.size() - 1] += 4;

	if (GetAsyncKeyState(VK_SUBTRACT) &1 && this->offsets[this->offsets.size() - 1] > 0)
		this->offsets[this->offsets.size() - 1] -= 4;

	if (GetAsyncKeyState(VK_MULTIPLY) &1 && this->IsValidPointer())
		this->offsets.push_back(0);

	if (GetAsyncKeyState(VK_DIVIDE) &1)
	{
		if (this->offsets.size() > 1)
			this->offsets.pop_back();
		else
			this->offsets[0] = 0;
	}
}

void Debugger::ClassChanger()
{
	for (int i = 0; i < this->classes.size(); i++)
	{
		if (GetAsyncKeyState(VK_NUMPAD0 + i) &1)
		{
			this->debugInfo.index = i;
			this->offsets.clear();
			this->offsets.push_back(0);
		}
	}
}