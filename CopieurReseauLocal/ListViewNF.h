#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


public ref class ListViewNF : System::Windows::Forms::ListView
{
	public: ListViewNF(System::Windows::Forms::ListView^ list)
    {
		this->AutoArrange = list->AutoArrange;
		this->ContextMenuStrip = list->ContextMenuStrip;
		this->Dock = list->Dock;
		this->GridLines = list->GridLines;
		this->HeaderStyle = list->HeaderStyle;
		this->HideSelection = list->HideSelection;
		this->LabelWrap = list->LabelWrap;
		this->Location = list->Location;
		this->MultiSelect = list->MultiSelect;
		this->Name = list->Name;
		this->ShowGroups = list->ShowGroups;
		this->Size = list->Size;
		this->TabIndex = list->TabIndex;
		this->TabStop = list->TabStop;
		this->UseCompatibleStateImageBehavior = list->UseCompatibleStateImageBehavior;
		this->View = list->View;
		

		//Activate double buffering
		this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);

		//Enable the OnNotifyMessage event so we get a chance to filter out 
		// Windows messages before they get to the form's WndProc
		//this->SetStyle(ControlStyles::EnableNotifyMessage, true);
	}

	ListViewNF()
	{
		//Activate double buffering
		this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);

		//Enable the OnNotifyMessage event so we get a chance to filter out 
		// Windows messages before they get to the form's WndProc
		//this->SetStyle(ControlStyles::EnableNotifyMessage, true);
	}
};