#pragma once


#include "Copieur.h"
#include "Convertisseur.h"
#include "Horloge.h"
#include <string>
#include <sstream>
using namespace std;




namespace CopieurReseauLocal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	
	


	/// <summary>
	/// Description résumée de Form1
	///
	/// AVERTISSEMENT : si vous modifiez le nom de cette classe, vous devrez modifier la
	///          propriété 'Nom du fichier de ressources' de l'outil de compilation de ressource managée
	///          pour tous les fichiers .resx dont dépend cette classe. Dans le cas contraire,
	///          les concepteurs ne pourront pas interagir correctement avec les ressources
	///          localisées associées à ce formulaire.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			char szthis[300];
			char* c = szthis + GetModuleFileName(0, szthis, 300);
			while(*c != '\\') c--; *c = 0;
			SetCurrentDirectory(szthis);

			Horloge::getInstance();

			copieur=GestionnaireTelechargement::getInstance();

			InitializeComponent();
			//
			//TODO : ajoutez ici le code du constructeur
			//
			backgroundWorkerTelechargements->RunWorkerAsync();
			//this->Hide();
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~Form1()
		{
			isBGRunning=false;
			//backgroundWorkerTelechargements->CancelAsync();
			while(backgroundWorkerTelechargements->IsBusy)
				Application::DoEvents();

			copieur=GestionnaireTelechargement::destruction();
			Horloge::destruction();

			

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TabControl^  tabs;
	private: System::Windows::Forms::TabPage^  tabTelechargement;
	private: System::Windows::Forms::TabPage^  tabConfiguration;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ListView^  listViewTelechargements;
	private: System::Windows::Forms::ColumnHeader^  ColonneLien;
	private: System::Windows::Forms::ColumnHeader^  ColonneTaille;
	private: System::Windows::Forms::NotifyIcon^  notifyIcon;

	private: System::Windows::Forms::ColumnHeader^  colonneVitesse;
	private: System::Windows::Forms::ColumnHeader^  colonneProgression;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripAjouterTelechargement;
	private: System::Windows::Forms::ToolStripMenuItem^  ajouterUnTéléchargementToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialogSelectionTelechargement;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorkerTelechargements;
	private: System::Windows::Forms::Timer^  timerRaffraichissement;
	private: System::Windows::Forms::ColumnHeader^  colonneTempsRestant;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		bool isBGRunning;
	private: System::Windows::Forms::MenuStrip^  menuStripPrincipal;

	private: System::Windows::Forms::ToolStripMenuItem^  menuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aideToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aProposToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  réduireToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  quitterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  quitterToolStripMenuItem1;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStripNotifyIcon;
	private: System::Windows::Forms::ToolStripMenuItem^  ouvrirToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  réduireToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  quitterToolStripMenuItem2;
			 GestionnaireTelechargement* copieur;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->tabs = (gcnew System::Windows::Forms::TabControl());
			this->tabTelechargement = (gcnew System::Windows::Forms::TabPage());
			this->listViewTelechargements = (gcnew System::Windows::Forms::ListView());
			this->ColonneLien = (gcnew System::Windows::Forms::ColumnHeader());
			this->ColonneTaille = (gcnew System::Windows::Forms::ColumnHeader());
			this->colonneVitesse = (gcnew System::Windows::Forms::ColumnHeader());
			this->colonneProgression = (gcnew System::Windows::Forms::ColumnHeader());
			this->colonneTempsRestant = (gcnew System::Windows::Forms::ColumnHeader());
			this->contextMenuStripAjouterTelechargement = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ajouterUnTéléchargementToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabConfiguration = (gcnew System::Windows::Forms::TabPage());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->menuStripPrincipal = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->réduireToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitterToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aideToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aProposToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuStripNotifyIcon = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ouvrirToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->réduireToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitterToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialogSelectionTelechargement = (gcnew System::Windows::Forms::OpenFileDialog());
			this->backgroundWorkerTelechargements = (gcnew System::ComponentModel::BackgroundWorker());
			this->timerRaffraichissement = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->tabs->SuspendLayout();
			this->tabTelechargement->SuspendLayout();
			this->contextMenuStripAjouterTelechargement->SuspendLayout();
			this->menuStripPrincipal->SuspendLayout();
			this->contextMenuStripNotifyIcon->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->AutoScroll = true;
			this->panel1->AutoSize = true;
			this->panel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panel1->Controls->Add(this->tabs);
			this->panel1->Controls->Add(this->statusStrip1);
			this->panel1->Controls->Add(this->menuStripPrincipal);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1181, 621);
			this->panel1->TabIndex = 0;
			// 
			// tabs
			// 
			this->tabs->Controls->Add(this->tabTelechargement);
			this->tabs->Controls->Add(this->tabConfiguration);
			this->tabs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabs->Location = System::Drawing::Point(0, 24);
			this->tabs->Name = L"tabs";
			this->tabs->SelectedIndex = 0;
			this->tabs->Size = System::Drawing::Size(1181, 575);
			this->tabs->TabIndex = 1;
			// 
			// tabTelechargement
			// 
			this->tabTelechargement->Controls->Add(this->listViewTelechargements);
			this->tabTelechargement->Location = System::Drawing::Point(4, 22);
			this->tabTelechargement->Name = L"tabTelechargement";
			this->tabTelechargement->Padding = System::Windows::Forms::Padding(3);
			this->tabTelechargement->Size = System::Drawing::Size(1173, 549);
			this->tabTelechargement->TabIndex = 0;
			this->tabTelechargement->Text = L"Téléchargements";
			this->tabTelechargement->UseVisualStyleBackColor = true;
			// 
			// listViewTelechargements
			// 
			this->listViewTelechargements->AutoArrange = false;
			this->listViewTelechargements->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {this->ColonneLien, 
				this->ColonneTaille, this->colonneVitesse, this->colonneProgression, this->colonneTempsRestant});
			this->listViewTelechargements->ContextMenuStrip = this->contextMenuStripAjouterTelechargement;
			this->listViewTelechargements->Dock = System::Windows::Forms::DockStyle::Fill;
			this->listViewTelechargements->GridLines = true;
			this->listViewTelechargements->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->listViewTelechargements->HideSelection = false;
			this->listViewTelechargements->LabelWrap = false;
			this->listViewTelechargements->Location = System::Drawing::Point(3, 3);
			this->listViewTelechargements->MultiSelect = false;
			this->listViewTelechargements->Name = L"listViewTelechargements";
			this->listViewTelechargements->ShowGroups = false;
			this->listViewTelechargements->Size = System::Drawing::Size(1167, 543);
			this->listViewTelechargements->TabIndex = 0;
			this->listViewTelechargements->TabStop = false;
			this->listViewTelechargements->UseCompatibleStateImageBehavior = false;
			this->listViewTelechargements->View = System::Windows::Forms::View::Details;
			// 
			// ColonneLien
			// 
			this->ColonneLien->Text = L"Lien";
			this->ColonneLien->Width = 700;
			// 
			// ColonneTaille
			// 
			this->ColonneTaille->Text = L"courant/Total (ko)";
			this->ColonneTaille->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->ColonneTaille->Width = 100;
			// 
			// colonneVitesse
			// 
			this->colonneVitesse->Text = L"ko/s";
			this->colonneVitesse->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// colonneProgression
			// 
			this->colonneProgression->Text = L"Progression %";
			this->colonneProgression->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->colonneProgression->Width = 100;
			// 
			// colonneTempsRestant
			// 
			this->colonneTempsRestant->Text = L"Temps restant";
			this->colonneTempsRestant->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->colonneTempsRestant->Width = 184;
			// 
			// contextMenuStripAjouterTelechargement
			// 
			this->contextMenuStripAjouterTelechargement->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ajouterUnTéléchargementToolStripMenuItem});
			this->contextMenuStripAjouterTelechargement->Name = L"contextMenuStripAjouterTelechargement";
			this->contextMenuStripAjouterTelechargement->Size = System::Drawing::Size(204, 26);
			// 
			// ajouterUnTéléchargementToolStripMenuItem
			// 
			this->ajouterUnTéléchargementToolStripMenuItem->Name = L"ajouterUnTéléchargementToolStripMenuItem";
			this->ajouterUnTéléchargementToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->ajouterUnTéléchargementToolStripMenuItem->Text = L"Ajouter un téléchargement";
			this->ajouterUnTéléchargementToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ajouterUnTéléchargementToolStripMenuItem_Click);
			// 
			// tabConfiguration
			// 
			this->tabConfiguration->Location = System::Drawing::Point(4, 22);
			this->tabConfiguration->Name = L"tabConfiguration";
			this->tabConfiguration->Padding = System::Windows::Forms::Padding(3);
			this->tabConfiguration->Size = System::Drawing::Size(1173, 549);
			this->tabConfiguration->TabIndex = 1;
			this->tabConfiguration->Text = L"Configuration";
			this->tabConfiguration->UseVisualStyleBackColor = true;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Location = System::Drawing::Point(0, 599);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1181, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// menuStripPrincipal
			// 
			this->menuStripPrincipal->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->menuStripPrincipal->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->menuToolStripMenuItem, 
				this->aideToolStripMenuItem, this->aProposToolStripMenuItem});
			this->menuStripPrincipal->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->menuStripPrincipal->Location = System::Drawing::Point(0, 0);
			this->menuStripPrincipal->Name = L"menuStripPrincipal";
			this->menuStripPrincipal->Size = System::Drawing::Size(1181, 24);
			this->menuStripPrincipal->TabIndex = 2;
			this->menuStripPrincipal->TabStop = true;
			this->menuStripPrincipal->Text = L"menuStrip1";
			// 
			// menuToolStripMenuItem
			// 
			this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->réduireToolStripMenuItem, 
				this->quitterToolStripMenuItem, this->quitterToolStripMenuItem1});
			this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
			this->menuToolStripMenuItem->Size = System::Drawing::Size(45, 20);
			this->menuToolStripMenuItem->Text = L"Menu";
			// 
			// réduireToolStripMenuItem
			// 
			this->réduireToolStripMenuItem->Name = L"réduireToolStripMenuItem";
			this->réduireToolStripMenuItem->Size = System::Drawing::Size(228, 22);
			this->réduireToolStripMenuItem->Text = L"Sélectionner un Téléchargement";
			this->réduireToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::réduireToolStripMenuItem_Click);
			// 
			// quitterToolStripMenuItem
			// 
			this->quitterToolStripMenuItem->Name = L"quitterToolStripMenuItem";
			this->quitterToolStripMenuItem->Size = System::Drawing::Size(228, 22);
			this->quitterToolStripMenuItem->Text = L"Réduire";
			this->quitterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::quitterToolStripMenuItem_Click);
			// 
			// quitterToolStripMenuItem1
			// 
			this->quitterToolStripMenuItem1->Name = L"quitterToolStripMenuItem1";
			this->quitterToolStripMenuItem1->Size = System::Drawing::Size(228, 22);
			this->quitterToolStripMenuItem1->Text = L"Quitter";
			this->quitterToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::quitterToolStripMenuItem1_Click);
			// 
			// aideToolStripMenuItem
			// 
			this->aideToolStripMenuItem->Name = L"aideToolStripMenuItem";
			this->aideToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->aideToolStripMenuItem->Text = L"Aide";
			// 
			// aProposToolStripMenuItem
			// 
			this->aProposToolStripMenuItem->Name = L"aProposToolStripMenuItem";
			this->aProposToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->aProposToolStripMenuItem->Text = L"A propos";
			// 
			// notifyIcon
			// 
			this->notifyIcon->ContextMenuStrip = this->contextMenuStripNotifyIcon;
			this->notifyIcon->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"notifyIcon.Icon")));
			this->notifyIcon->Text = L"Copieur";
			this->notifyIcon->Visible = true;
			this->notifyIcon->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::notifyIcon_MouseDoubleClick);
			// 
			// contextMenuStripNotifyIcon
			// 
			this->contextMenuStripNotifyIcon->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->ouvrirToolStripMenuItem, 
				this->réduireToolStripMenuItem1, this->quitterToolStripMenuItem2});
			this->contextMenuStripNotifyIcon->Name = L"contextMenuStripNotifyIcon";
			this->contextMenuStripNotifyIcon->Size = System::Drawing::Size(112, 70);
			// 
			// ouvrirToolStripMenuItem
			// 
			this->ouvrirToolStripMenuItem->Name = L"ouvrirToolStripMenuItem";
			this->ouvrirToolStripMenuItem->Size = System::Drawing::Size(111, 22);
			this->ouvrirToolStripMenuItem->Text = L"Ouvrir";
			this->ouvrirToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::ouvrirToolStripMenuItem_Click);
			// 
			// réduireToolStripMenuItem1
			// 
			this->réduireToolStripMenuItem1->Name = L"réduireToolStripMenuItem1";
			this->réduireToolStripMenuItem1->Size = System::Drawing::Size(111, 22);
			this->réduireToolStripMenuItem1->Text = L"Réduire";
			this->réduireToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::réduireToolStripMenuItem1_Click);
			// 
			// quitterToolStripMenuItem2
			// 
			this->quitterToolStripMenuItem2->Name = L"quitterToolStripMenuItem2";
			this->quitterToolStripMenuItem2->Size = System::Drawing::Size(111, 22);
			this->quitterToolStripMenuItem2->Text = L"Quitter";
			this->quitterToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::quitterToolStripMenuItem2_Click);
			// 
			// openFileDialogSelectionTelechargement
			// 
			this->openFileDialogSelectionTelechargement->Multiselect = true;
			this->openFileDialogSelectionTelechargement->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialogSelectionTelechargement_FileOk);
			// 
			// backgroundWorkerTelechargements
			// 
			this->backgroundWorkerTelechargements->WorkerSupportsCancellation = true;
			this->backgroundWorkerTelechargements->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorkerTelechargements_DoWork);
			// 
			// timerRaffraichissement
			// 
			this->timerRaffraichissement->Enabled = true;
			this->timerRaffraichissement->Interval = 1000;
			this->timerRaffraichissement->Tick += gcnew System::EventHandler(this, &Form1::timerRaffraichissement_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1181, 621);
			this->Controls->Add(this->panel1);
			this->MainMenuStrip = this->menuStripPrincipal;
			this->Name = L"Form1";
			this->Text = L"Copieur réseau";
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabs->ResumeLayout(false);
			this->tabTelechargement->ResumeLayout(false);
			this->contextMenuStripAjouterTelechargement->ResumeLayout(false);
			this->menuStripPrincipal->ResumeLayout(false);
			this->menuStripPrincipal->PerformLayout();
			this->contextMenuStripNotifyIcon->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void ajouterUnTéléchargementToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 openFileDialogSelectionTelechargement->ShowDialog();
		 }

private: System::Void openFileDialogSelectionTelechargement_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 
			 array<String^>^ fichiers = openFileDialogSelectionTelechargement->FileNames;
			 for(int i=0;i<fichiers->Length;i++) {
				 //String^ nouveauFichierSStr = openFileDialogSelectionTelechargement->FileName;
				 string nouveauFichierStr = netStr2CppStr(fichiers[i]);
				 copieur->nouveauTelechargement(nouveauFichierStr);
			 }
			 if(backgroundWorkerTelechargements->IsBusy==false) {
				backgroundWorkerTelechargements->RunWorkerAsync();
			 }
		 }
private: System::Void backgroundWorkerTelechargements_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			isBGRunning=true;
			while((isBGRunning)&&(backgroundWorkerTelechargements->CancellationPending==false)) {
				Horloge::getInstance()->raffraichissement();
				if(copieur->update()==false)
					break;
				//Application::DoEvents();
			}
			isBGRunning=false;
		 }

private: 
	System::Void raffraichissementListeTelechargements()
	{
		this->listViewTelechargements->Items->Clear();

		String^ fileNameS = gcnew String(fichierTelechargements);
		string fileName(fichierTelechargements);
		if(File::Exists(fileNameS)) {

			ifstream is(fileName.c_str());
			string lien, taille, vitesseStr, progression , position, nomDestination;
			string ligne;
			
			while (getline(is,ligne)) {
				stringstream bufSS(ligne);
				getline(bufSS,lien,';');
				getline(bufSS,taille,';');
				getline(bufSS,vitesseStr,';');
				getline(bufSS,progression,';');
				getline(bufSS,nomDestination,';');
				getline(bufSS,position,';');
				
				string tailleMessage = toString((stringToLong(position)/1024))+"/"+toString((stringToLong(taille)/1024)); 

				stringstream tempsRestant;
				int vitesse = stringToInt(vitesseStr);
				if(vitesse*1024!=0) {
					int sec = (stringToInt(taille)-stringToInt(position))/(vitesse*1024);
					int tempsH = sec/(60*60);
					int tempsM = (sec-tempsH*60*60)/60;
					int tempsS = sec - tempsH*60*60 - tempsM*60;
					tempsRestant << tempsH << ":" << tempsM << ":" << tempsS; 				 
				}

				ListViewItem^ LVI = listViewTelechargements->Items->Add(gcnew String(lien.c_str()));
				LVI->SubItems->Add(gcnew String(tailleMessage.c_str()));
				LVI->SubItems->Add(gcnew String(vitesseStr.c_str()));
				LVI->SubItems->Add(gcnew String(progression.c_str()));
				LVI->SubItems->Add(gcnew String(tempsRestant.str().c_str()));
			}
		}
		else {
			ofstream fichier (fichierTelechargements);
			fichier.close();
		}
	}


private: System::Void timerRaffraichissement_Tick(System::Object^  sender, System::EventArgs^  e) {
			raffraichissementListeTelechargements();
		 }
private: System::Void notifyIcon_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(this->Visible==true) {
				Hide();
			 }
			 else {
				 Show();
				 this->WindowState = System::Windows::Forms::FormWindowState::Normal; // not minimize
			 }
		 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			Hide();
		 }
private: System::Void réduireToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			openFileDialogSelectionTelechargement->ShowDialog();
		 }
private: System::Void quitterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Hide();
		 }
private: System::Void quitterToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
private: System::Void ouvrirToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Show();
			 this->WindowState = System::Windows::Forms::FormWindowState::Normal; // not minimize
		 }
private: System::Void réduireToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 Hide();
		 }
private: System::Void quitterToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }
};
}

