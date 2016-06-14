
// strings.cpp : Defines the entry point for the application.
//
//#define _CRT_NON_CONFORMING_SWPRINTFS.

//#define _CRT_SECURE_NO_WARNINGS
//#include "atlwin.h"
#include "stdafx.h"
#include "strings.h"
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include <cstdio>



//#define IDD_DIALOG1  //afiseaza raspunsurile
#define LoadImage LoadImageW
#define MAX_LOADSTRING 100
//Definim
#define EDITCONTROL_01 1
#define BUTTONGO 2
#define STATIC 3
#define BUTTONSTART 4
#define IMAGE_VIEW 5 //poza de background
#define HEART1 6 //vietile
#define HEART2 7 //vietile
#define HEART3 8 //vietile
#define HEART4 9 //vietile
#define HEART5 10 //vietile
#define SUITCASE 11 //poza cu valiza
#define BUTTONTUTORIAL 12 //buton tutorial
#define SCROLL 13 //messagebox cu scroll 
#define BUTTON_TEST 15

//Definim_end

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Raspuns(HWND, UINT, WPARAM, LPARAM);




int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_STRINGS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STRINGS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STRINGS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_STRINGS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   
   hInst = hInstance; // Store instance handle in our global variable


   hWnd = CreateWindowEx(
	   WS_EX_CLIENTEDGE,
	   szWindowClass,
	   L"Ce incape intr-o valiza?",
	   WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, 1155, 585,
	   NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//

HWND BUTTONGO01;
HWND BUTTONSTART01;
HWND TextBox01;
HWND STATIC01;
//declarare variabile
wchar_t string[20];
//declarare variabile_end


//lista care tine minte alfabetul (radacinile fiecarui arbore)
typedef struct nod{
	wchar_t string[20];
	nod *next;
};
nod *prim;
nod *ultim;
void adaugare(wchar_t cuvant[]){
	nod *p = (nod*)malloc(sizeof(nod));
	p->next = NULL;
	wcsncpy(p->string, cuvant, 20);
	if (prim == NULL){//lista este goala
		prim = p;
		ultim = p;
	}
	else{//sunt elemente in lista
		ultim->next = p;
		ultim = p;
	}
}

void alfabet(){
	adaugare(L" A");
	adaugare(L" B");
	adaugare(L" C");
	adaugare(L" D");
	adaugare(L" E");
	adaugare(L" F");
	adaugare(L" G");
	adaugare(L" H");
	adaugare(L" I");
	adaugare(L" J");
	adaugare(L" K");
	adaugare(L" L");
	adaugare(L" M");
	adaugare(L" N");
	adaugare(L" O");
	adaugare(L" P");
	adaugare(L" Q");
	adaugare(L" R");
	adaugare(L" S");
	adaugare(L" T");
	adaugare(L" U");
	adaugare(L" V");
	adaugare(L" W");
	adaugare(L" X");
	adaugare(L" Y");
	adaugare(L" Z");
}
//lista alfabet_end
int count = 0;
nod *aux;

// ARBORE DE SUFIX GENERALIZAT
typedef struct litera{
	wchar_t c;
	litera *next;
	litera *treerad;
};
litera *rad;
void adaugaretree(wchar_t *cuvant){
	int exista = 0;//tine minte daca exista radacina
	litera *p = (litera*)malloc(sizeof(litera));
	p->c = cuvant[0];
	p->next = NULL;
	p->treerad = NULL;
	litera *cautare = rad;//cautam daca exista litera
	litera* prev = NULL;//precedentul pointerului care cauta;
	if (rad == NULL){//daca nu exista elemente in prima lista
		rad = p;
		cautare = rad;
		//	printf("radacina devine:%c\n ", p->c);
	}
	else{//daca exista elemente in lista

		while (cautare != NULL){//pana se ajunge la ultimul element(NULL)

			if (cautare->c == p->c){//daca mai exista nu se intampla nimic
				exista = 1;
				//printf("%c exista-> mergem in jos   \n", p->c);
				break;
			}
			else if ((cautare->c) > (p->c)){//daca gasim o litera mai mare alfabetic atunci adaugam inaintea ei
				if (cautare == rad){//daca primul element este mai mare ca cel care vrem sa l adaugam
					p->next = rad;
					rad = p;
					cautare = rad;
					//printf("inlocuim primul element cu %c\n ", p->c);
				}
				else{//este un element oarecare
					p->next = cautare;
					prev->next = p;
					cautare = p;
					//printf("inlocuim elementul cu %c \n", p->c);
				}
				break;
			}
			else if (cautare->next == NULL){//inseamna ca suntem la ultimul element
				cautare->next = p;
				cautare = p;
				//printf("inlocuim ultimul element cu:%c\n ", p->c);
				break;
			}
			else{
				prev = cautare;
				cautare = cautare->next;
			}


		}
	}//am adaugat prima litera
	if (!exista){//daca prima litera nu exista =>nu exista tot cuvantul
		litera *sus = cautare;//tine minte elementul dinainte
		//printf("scriem cuvantul asa cum e in jos\n ");
		for (int i = 1; i < wcslen(cuvant); i++){
			litera *q = (litera*)malloc(sizeof(litera));
			q->c = cuvant[i];
			q->treerad = NULL;
			q->next = NULL;

			sus->treerad = q;
			sus = sus->treerad;
		}
	}
	else{//daca primul element exista->>>>>>>>>>>>>>>>al doilea pas
		litera *q = (litera *)malloc(sizeof(litera));
		litera *sus = cautare;//tine minte elementul dinainte
		//printf("radacina de sus: %c -->problema\n", sus->c);
		litera *cautare2 = sus->treerad;//radacina devine prima litera de sub
		for (int i = 1; i < wcslen(cuvant); i++){//cautam pentru fiecare litera si nivelul creste

			exista = 0;
			q->c = cuvant[i];
			q->treerad = NULL;
			q->next = NULL;

			//	printf("noua radacina din lista :%c\n ", cautare2->c);
			litera* prev = NULL;//precedentul pointerului care cauta;
			if (cautare2 == NULL){//daca nu exista elemente in prima lista
				sus->treerad = q;//!!!!!!!s ar putea sa fie greseala ca cautare 2 sa devina noul sus->treerad!!!!!!!!
				cautare2 = sus->treerad;
			}
			else{//daca exista elemente in lista
				while (cautare2 != NULL){//pana se ajunge la ultimul element(NULL)
					if (cautare2->c == q->c){//daca mai exista nu se intampla nimic
						exista = 1;
						break;
					}
					else if ((cautare2->c) > (q->c)){//daca gasim o litera mai mare alfabetic atunci adaugam inaintea ei
						if (cautare2 == sus->treerad){//daca primul element este mai mare ca cel care vrem sa l adaugam
							q->next = sus->treerad;
							sus->treerad = q;
							cautare2 = sus->treerad;
						}
						else{//este un element oarecare
							q->next = cautare2;
							prev->next = q;
							cautare2 = q;
						}
						break;
					}
					else if (cautare2->next == NULL){//inseamna ca suntem la ultimul element
						cautare2->next = q;
						cautare2 = q;
						break;
					}
					else{
						prev = cautare2;
						cautare2 = cautare2->next;
					}
				}
			}//am adaugat prima litera
			if (!exista){//daca prima litera nu exista =>nu exista tot cuvantul
				litera *sus = cautare2;//tine minte elementul dinainte
				//	printf("radacina de sus: %c -->problema2\n ", sus->c);
				for (int j = i + 1; j < wcslen(cuvant); j++){
					litera *k = (litera*)malloc(sizeof(litera));
					k->c = cuvant[j];
					k->treerad = NULL;
					k->next = NULL;

					sus->treerad = k;
					sus = sus->treerad;
				}
				break;
			}
			sus = cautare2;//coboara //inainte era =sus->treerad ( posibila greseala)
			cautare2 = sus->treerad;
		}//-------------->se termina cazul 2
	}

	//
}
bool cautare(wchar_t *cuvant){
	int sem;
	litera *cautare = rad;
	for (int i = 0; i < wcslen(cuvant); i++){
		sem = 0;
		while (cautare != NULL){
			if (cautare->c == cuvant[i]){
				//printf("%c ", cautare->c);
				sem = 1;//s a gasit
				break;
			}
			if (sem != 1)//daca s a gasit nu trece mai departe
				cautare = cautare->next;
		}
		if (sem == 0)
			break;
		cautare = cautare->treerad;//trece la urmatorul caracter
	}

	if (sem)
		return true;
	else
		return false;
}

wchar_t *obiecte = (wchar_t*)malloc(sizeof(wchar_t)* 20);
void adaugareCuvinte(){
	FILE *fin = fopen("date.txt", "r");
	while (!feof(fin)){
		fwscanf(fin, L"%ls", obiecte);
		adaugaretree(obiecte);
	}
	fclose(fin);
	
	
	
}
//ARBORE DE SUFIX GENERALIZAT_END
//matrice de cuvinte care sa tina minte cuvintele adaugate care sunt corecte ( ca sa nu se repete)
wchar_t corecte[5][20];
int ncorecte = 0;
void adaugareCorecte(wchar_t *cuvant){
	wcscpy(corecte[ncorecte], cuvant);
	ncorecte++;
}
bool valid(wchar_t *cuvant){
	for (int i = 0; i < ncorecte; i++){
		if (wcscmp(cuvant, corecte[i]) == 0)
			return false;//cuvantul a mai fost adaugat
	}
	return true;
}
//matrice de cuvinte _end
int gresite = 0;//daca se ajunge la 6 raspunsuri gresite jocul se termina (VALIZA)
int start = 0;//daca a fost apasat butonul de start

HWND BUTTONTUTORIAL01;
//vieti
HWND hImageView; //background
HWND HEARTView1;
HWND HEARTView2;
HWND HEARTView3;
HWND HEARTView4;
HWND HEARTView5;
HBITMAP hHEART1;
HBITMAP hHEART2;
HBITMAP hHEART3;
HBITMAP hHEART4;
HBITMAP hHEART5;
void validVieti(){
	switch (gresite) {
	case 1:{
			   SendMessage(HEARTView5, STM_SETIMAGE, IMAGE_BITMAP, NULL); 
	}break;
	case 2:{
			   SendMessage(HEARTView4, STM_SETIMAGE, IMAGE_BITMAP, NULL);
	}break;
	case 3:{
			   SendMessage(HEARTView3, STM_SETIMAGE, IMAGE_BITMAP, NULL);
	}break;
	case 4:{
			   SendMessage(HEARTView2, STM_SETIMAGE, IMAGE_BITMAP, NULL);
	}break;
	case 5:{
			   SendMessage(HEARTView1, STM_SETIMAGE, IMAGE_BITMAP, NULL);
	}break;
	}
}
//vieti_end

//incercare maximizare
RECT dim;
//incercare maximizare_end


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	validVieti();
	if (gresite == 6){//GAME OVER
		
		gresite = 0;
		start = 0;
		ncorecte = 0;
		//MessageBox(NULL, L"GAME OVER!", L"Ce incape intr-o valiza?", MB_OK);
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Raspuns);
		DestroyWindow(hWnd);
		//SetWindowText(STATIC01, L" ");
	}
	if (count == 0){//incarca alfabetul numai la primul pas si auxiliar devine primul
		alfabet();//incarca alfabetul
		aux = prim;
		count++;
		adaugareCuvinte();//adauga cuvintele in arborele de sufix generalizat
	}
	
	
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:{

					//background
					   HBITMAP hImage = (HBITMAP)LoadImage(NULL, L"image.bmp", IMAGE_BITMAP, 1140, 545, LR_LOADFROMFILE);
					   hImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, 500, 600, hWnd, (HMENU)IMAGE_VIEW, GetModuleHandle(NULL), NULL);
					   SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

					 /*  HBITMAP suitcaseImage = (HBITMAP)LoadImage(NULL, L"suitcase.bmp", IMAGE_BITMAP, 400, 400, LR_LOADFROMFILE);
					   HWND suitcaseImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 350, 130, 500, 600, hWnd, (HMENU)SUITCASE, GetModuleHandle(NULL), NULL);
					   SendMessage(suitcaseImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)suitcaseImage);*/


					   // vietile
					    hHEART1 = (HBITMAP)LoadImage(NULL, L"image2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
					   HEARTView1 = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 1110, 0, 500, 600, hWnd, (HMENU)HEART1, GetModuleHandle(NULL), NULL);
					   SendMessage(HEARTView1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHEART1);


					    hHEART2 = (HBITMAP)LoadImage(NULL, L"image2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
					   HEARTView2 = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 1085, 0, 500, 600, hWnd, (HMENU)HEART2, GetModuleHandle(NULL), NULL);
					   SendMessage(HEARTView2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHEART2);

					    hHEART3 = (HBITMAP)LoadImage(NULL, L"image2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
					   HEARTView3 = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 1060, 0, 500, 600, hWnd, (HMENU)HEART3, GetModuleHandle(NULL), NULL);
					   SendMessage(HEARTView3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHEART3);

					    hHEART4 = (HBITMAP)LoadImage(NULL, L"image2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
					   HEARTView4 = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 1035, 0, 500, 600, hWnd, (HMENU)HEART4, GetModuleHandle(NULL), NULL);
					   SendMessage(HEARTView4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHEART4);

					    hHEART5 = (HBITMAP)LoadImage(NULL, L"image2.bmp", IMAGE_BITMAP, 20, 20, LR_LOADFROMFILE);
					   HEARTView5 = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 1010, 0, 500, 600, hWnd, (HMENU)HEART5, GetModuleHandle(NULL), NULL);
					   SendMessage(HEARTView5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hHEART5);
					   //vietile_end

					 //background_end
					   //TextBox
					   LPCWSTR TextBox_ID = L"EDIT";
					   LPCWSTR TextBox_text = L"";
					   TextBox01 = CreateWindowEx(NULL, TextBox_ID, TextBox_text, WS_BORDER | WS_VISIBLE | WS_CHILD, 400, 400, 300, 20, hWnd, (HMENU)EDITCONTROL_01, NULL, NULL);
					   //TextBox_end
					   //BUTTON GO
					   LPCWSTR BUTTONGO_ID = L"BUTTON";
					   LPCWSTR BUTTONGO_text = L"GO!";
					   BUTTONGO01 = CreateWindowEx(NULL, BUTTONGO_ID, BUTTONGO_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 705, 400, 40, 20, hWnd, (HMENU)BUTTONGO, NULL, NULL);
					   //BUTTON GO END
					   //Static_Text
					   LPCWSTR Static_ID = L"STATIC";
					   STATIC01 = CreateWindowEx(NULL, Static_ID, L"", WS_BORDER | WS_VISIBLE | WS_CHILD, 510,285,100,100,hWnd,(HMENU)STATIC, NULL, NULL);  
					   HFONT hFont = CreateFont(100, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
					   SendMessage(STATIC01, WM_SETFONT, WPARAM(hFont), TRUE);
					   
					   //Static_Text_End
					   //Button Start ALfabet
					   BUTTONSTART01 = CreateWindowEx(NULL, L"BUTTON", L"START!", BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 630,305, 80, 35, hWnd, (HMENU)BUTTONSTART, NULL, NULL);
					   //BUTTON start alfabet end
					   //tutorial button
					   BUTTONTUTORIAL01 = CreateWindowEx(NULL, L"BUTTON", L"?", BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 120, 498, 20, 20, hWnd, (HMENU)BUTTONTUTORIAL, NULL, NULL);
					   //tutorial button_end

					   //incarcare icon
					    HANDLE hIcon = LoadImage(NULL, L"D:\\INFO ATM\\TEHNICI DE PROGRAMARE\\Proiect\\strings\\strings\\image.ico", IMAGE_ICON, 15, 15, LR_LOADFROMFILE);
					   if (hIcon)
						   SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
					   else
						   MessageBox(hWnd, L"Imagine prea mare, nu se poate incarca!", L"Eroare", MB_OK | MB_ICONERROR);

					 HANDLE  hIconSm = LoadImage(NULL, L"D:\\INFO ATM\\TEHNICI DE PROGRAMARE\\Proiect\\strings\\strings\\image.ico", IMAGE_ICON, 15, 15, LR_LOADFROMFILE);
					   if (hIconSm)
						   SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
					   else
						   MessageBox(hWnd,L"Imagine prea mica, nu se poate incarca", L"Erroare", MB_OK | MB_ICONERROR);
					   //incarcare icon_end
					   
	}break;

		
	case WM_KEYDOWN:{
						switch (wParam){
						case VK_RIGHT:{//daca apasam tasta -> apare o litera random din alfabet
										  start = 1;
										  aux = prim;
										  srand(time(NULL));
										  int r = rand() % 26;

										  for (int i = 0; i < r; i++)
											  aux = aux->next;
										  SetWindowText(STATIC01, aux->string); }

										  //									  SetWindowText(STATIC01, aux->string);
										  //									  aux = aux->next;
										  //									  Sleep(100);//_>>>>>>>>>>>aici
										  					

										  //					
										  //									   //SetFocus(BUTTONGO01);
										  //									  // NextDlgCtrl();
										  //									  //  GotoDlgCtrl(hWnd);
										  //									  // SetFocus(BUTTONGO01);
						}break;
						}

		//testare

		//testare_end
	case WM_SIZE:{//STATIC01 = CreateWindowEx(NULL, Static_ID, L"", WS_BORDER | WS_VISIBLE | WS_CHILD, 510,285,100,100,hWnd,(HMEN
					// GetClientRect(hWnd, &dim);
					 //MoveWindow(hImageView, dim.left, dim.top, abs(dim.right - dim.left), abs(dim.top - dim.bottom), TRUE);
					// MoveWindow(STATIC01, dim.left+510 , dim.top +285, 100 , 100 , TRUE);
					
	}break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		

		// Parse the menu selections:
		switch (wmId)
		{

		case BUTTONSTART:{
							 start = 1;
							 aux = prim;
							 srand(time(NULL));
							 int r = rand() % 26;

							 for (int i = 0; i < r; i++)
								 aux = aux->next; 
			SetWindowText(STATIC01, aux->string);
		}break;
		case BUTTONTUTORIAL:{
				//MessageBox(NULL, L"Prima litera nu corespunde!", L"Ce incape intr-o valiza?", MB_OK);
								 DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
								break;
		}break;
		case BUTTONGO:{
						  int caractnumbers = 0;//numarul de caractere al cuvantului introdus
						  caractnumbers = GetWindowText(TextBox01, string, 20);
						  if (start == 1){
							  if (string[0] == (aux->string)[1] || string[0] == (_wcslwr(aux->string))[1]){
								  if (cautare(string)){
									  if (valid(string)){//cautam daca a mai fost adaugat
										  MessageBox(NULL, L"Raspuns Corect!", L"Ce incape intr-o valiza?", MB_OK);
										  adaugareCorecte(string);//adaugam cuvantul corect in matrice ca sa nu se mai repete
									  }
									  else{
										  MessageBox(NULL, L"Cuvantul a mai fost adaugat!", L"Ce incape intr-o valiza?", MB_OK);
										  gresite++;
									  }
								  }
								  else{
									  MessageBox(NULL, L"Raspuns Gresit!", L"Ce incape intr-o valiza?", MB_OK);
									  gresite++;
								  }
							  }
							  else{
								  MessageBox(NULL, L"Prima litera nu corespunde!", L"Ce incape intr-o valiza?", MB_OK);
								  gresite++;
							  }
						  }else
							  MessageBox(NULL, L"Nu s-a generat litera de inceput!", L"Ce incape intr-o valiza?", MB_OK);
						  //
						  //if (wcscmp(string, L"mihai")==0)
							 //MessageBox(NULL, string, L"Rezultat", MB_OK);
						  //else
							 //MessageBox(NULL, L"NU",L"Rezultat", MB_OK);
						  //SetWindowText(STATIC01, prim->string);
		}	
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

		//
	case WM_PAINT:{
					  PAINTSTRUCT ps;
					  HDC hdc = BeginPaint(hWnd, &ps);

					  RECT rec;
					  //       SetRect(rect, x ,y ,width, height)
					  SetRect(&rec, 500,80,800, 100);
					  
					  //       DrawText(HDC, text, text length, drawing area, parameters "DT_XXX")
					  DrawText(hdc, TEXT("Ce Incape Intr-o Valiza?"), strlen("Ce Incape Intr-o Valiza?"), &rec, DT_TOP | DT_LEFT );

					  EndPaint(hWnd, &ps);
					  ReleaseDC(hWnd, hdc);
	}break;
		//
	//case WM_PAINT:
	//	hdc = BeginPaint(hWnd, &ps);
	//	// TODO: Add any drawing code here...
	//	EndPaint(hWnd, &ps);
	//	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HBITMAP bmp1;///////////
	//HBITMAP bmp2;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	
		
	case WM_INITDIALOG:{  
						   //GetDlgItem(hDlg, IDC_EDIT1)
						   //SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), L"MIHAI");
						   HBITMAP hImage = (HBITMAP)LoadImage(NULL, L"cumsejoaca.bmp", IMAGE_BITMAP, 500, 460, LR_LOADFROMFILE);
						   HWND hImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, 500, 600, hDlg, (HMENU)IMAGE_VIEW, GetModuleHandle(NULL), NULL);
						   SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);

						   return (INT_PTR)TRUE;
	
	}break; 

	

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL  )
		{
			//SetFocus(HWND(IDOK1))
			//SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), L"MIHAI");
			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
wchar_t *string2 = (wchar_t*)malloc(sizeof(wchar_t)* 20);

INT_PTR CALLBACK Raspuns(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HBITMAP bmp1;///////////
	//HBITMAP bmp2;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{


	case WM_INITDIALOG:{
						   ////GetDlgItem(hDlg, IDC_EDIT1)
						   
						   //HBITMAP hImage = (HBITMAP)LoadImage(NULL, L"cumsejoaca.bmp", IMAGE_BITMAP, 500, 460, LR_LOADFROMFILE);
						   //HWND hImageView = CreateWindowEx(NULL, L"STATIC", NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD, 0, 0, 500, 600, hDlg, (HMENU)IMAGE_VIEW, GetModuleHandle(NULL), NULL);
						   //SendMessage(hImageView, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hImage);
						  // SendMessage(GetDlgItem(hDlg, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)string2);
					//lista de cuvinte corecte
						   FILE *fin = fopen("date.txt", "r");
						   while (!feof(fin)){
							   fwscanf(fin, L"%ls", string2);
							   SendMessage(GetDlgItem(hDlg, IDC_LIST3), LB_ADDSTRING, 0, (LPARAM)string2);
						   }
						   fclose(fin);
					//lista de cuvinte corecte_end
						   return (INT_PTR)TRUE;

	}break;



	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//SetFocus(HWND(IDOK1))
			//SetWindowText(GetDlgItem(hDlg, IDC_EDIT1), L"MIHAI");
			//SetWindowText(GetDlgItem(hDlg, IDC_EDIT3), L"MIHAI noifacnonuac uiea u avuohouc houa \\n petre midhaifean ofieanoifnaoincofa oinceaonf ocuanuoeacwonu iu bciua icgeiag ieagiyb diya ydivayvdiyaw vdyiaw vyidva wyivdywie vyiawdv yiwv yid waviyvd ayis vyid vayid vweiy vyidav siydv aiywev aiywe v");
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}