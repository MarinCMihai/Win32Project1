#define _CRT_SECURE_NO_WARNINGS
// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include "stdafx.h"
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <string>
#include <cstdio>
#include<conio.h>
#define EDITCONTROL_01 1
#define MAX_LOADSTRING 100
#define BUTTONI 2
#define BUTTONCN 3
#define BUTTONCNR 4
#define BUTTONSN 5
#define BUTTONSNR 6
#define BUTTONA 7
#define BUTTONE 8
#define SKIPLIST_MAX_LEVEL 6




typedef struct snode {
	wchar_t key[3];
	wchar_t value[30];
	wchar_t nr[30];
	struct snode **forward;
} snode;

typedef struct skiplist {
	int level;
	int size;
	struct snode *header;
} skiplist;

skiplist *skiplist_init(skiplist *list)
{
	int i;
	snode *header = (snode *)malloc(sizeof(struct snode));
	list->header = header;
	header->forward = (snode **)malloc(sizeof(snode*) * (SKIPLIST_MAX_LEVEL + 1));
	for (i = 0; i <= SKIPLIST_MAX_LEVEL; i++) {
		header->forward[i] = list->header;
	}

	list->level = 1;
	list->size = 0;

	return list;
}
static int rand_level()
{
	int level = 1;
	while (rand() < RAND_MAX / 2 && level < SKIPLIST_MAX_LEVEL)
		level++;
	return level;
}


int skiplist_insert(skiplist *list, wchar_t value[], wchar_t nr[])
{
	snode *update[SKIPLIST_MAX_LEVEL + 1];
	snode *x = list->header;
	int i, level;
	int aux;
	for (i = list->level; i >= 1; i--) {
		while (wcscmp(x->forward[i]->value, value) < 0)
		{
			x = x->forward[i];
		}
		update[i] = x;
	}
	x = x->forward[1];
	if (wcscmp(value, x->value) == 0) {
		wcscpy(x->value, value);
		wcscpy(x->nr, nr);
		return 0;
	}
	else {
		level = rand_level();
		if (level > list->level) {
			for (i = list->level + 1; i <= level; i++) {
				update[i] = list->header;
			}
			list->level = level;
		}

		x = (snode *)malloc(sizeof(snode));
		wcscpy(x->value, value);
		wcscpy(x->nr, nr);
		x->forward = (snode **)malloc(sizeof(snode*) * (level + 1));
		for (i = 1; i <= level; i++) {


			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
	}
	return 0;
}

snode *skiplist_search(skiplist *list, wchar_t value[])
{
	snode *x = list->header;
	while (x && x->forward[1] != list->header) {
		if (wcscmp(x->forward[1]->value, value) == 0) {
			return x->forward[1];
		}
		x = x->forward[1];
	}

	return NULL;
}

snode *skiplist_search_nr(skiplist *list, wchar_t value[])
{
	snode *x = list->header;
	while (x && x->forward[1] != list->header) {
		if (wcscmp(x->forward[1]->nr, value) == 0) {
			return x->forward[1];
		}
		x = x->forward[1];
	}

	return NULL;
}

snode *skiplist_search_nr_ord(skiplist *list, wchar_t key[])
{
	snode *x = list->header;
	while (x && x->forward[1] != list->header) {
		if (wcscmp(x->forward[1]->key, key)==0) {
			return x->forward[1];
		}
		x = x->forward[1];
	}

	return NULL;
}

static void skiplist_node_free(snode *x)
{
	if (x) {
		free(x->forward);
		free(x);
	}
}

int skiplist_delete(skiplist *list, wchar_t value[])
{

	int i;
	snode *update[SKIPLIST_MAX_LEVEL + 1];
	snode *x = list->header;
	for (i = list->level; i >= 1; i--) {
		while (wcscmp(x->forward[i]->value, value) < 0)
			x = x->forward[i];
		update[i] = x;
	}
	wchar_t r[20];
	x = x->forward[1];

			for (i = 1; i <= list->level; i++) {
				if (update[i]->forward[i] != x)
					break;
				update[i]->forward[i] = x->forward[i];
			}
			skiplist_node_free(x);

			while (list->level > 1 && list->header->forward[list->level] == list->header)
				list->level--;
			return 0;

	return 1;
}

static void skiplist_dump(skiplist *list)
{
	snode *x = list->header;
	int i = 0;
	while (x && x->forward[1] != list->header) {
		printf("%-3ls%-20ls%ls\n", x->forward[1]->key, x->forward[1]->value, x->forward[1]->nr);
		i++;
		x = x->forward[1];
	}
}

static void ord(skiplist *list)
{
	snode *x = list->header;
	int i = 49;
	int cont = 0;
	while (x && x->forward[1] != list->header) {
		if (i > 57)
		{
			i = 48;
			cont++;
		}
		else {
			x->forward[1]->key[cont] = i;
			i++;
		}

		x = x->forward[1];
	}
}

void inlocuire(skiplist *list)
{
	snode *x = list->header;
	char i = 49;
	FILE *f;
	int cont = 0;

	f = fopen("agenda.txt", "w");
	while (x && x->forward[1] != list->header) {
		if (i > 57)
		{
			i = 48;
			cont++;
		}
		else {
			x->forward[1]->key[cont] = i;
			x->forward[1]->key[cont+1] = '\0';
			i++;
		}
		fprintf(f, "%-5ls%-20ls%ls\n", x->forward[1]->key, x->forward[1]->value, x->forward[1]->nr);
		x = x->forward[1];
	}
	fclose(f);
}




// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND STATIC01;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
	   L"Agenda",
	  WS_EX_PALETTEWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HWND TextBox02;
HWND TextBox01;
HWND TextBox03;
HWND TextBox04;
HWND BUTTONI01;

HWND BUTTONCN01;

HWND BUTTONCNR01;

HWND BUTTONSN01;

HWND BUTTONSNR01;

HWND BUTTONA01;

wchar_t c = 1;
wchar_t nume[100];
wchar_t numar[20];
wchar_t key[3];
int pas = 1;
skiplist list;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	if (pas == 1)
	{
	
	skiplist_init(&list);
	

	FILE *f;
	f = fopen("agenda.txt", "r");
	int semafor = 1;
	if (f == NULL)
	{
		f = fopen("agenda.txt", "w");
		semafor = 0;
		fclose(f);
		f = fopen("agenda.txt", "r");
	}
	while (!feof(f))
	{
		fwscanf(f, L"%ls", key);
		fwscanf(f, L"%ls", nume);
		fwscanf(f, L"%ls", numar);
		if(semafor)
		skiplist_insert(&list, nume, numar);
	}

		ord(&list);
		fclose(f);
		inlocuire(&list);

	pas++;
}


    switch (message)
    {
	case WM_CREATE:
	{
		//TextBox1nsert
		LPCWSTR TextBox_ID = L"EDIT";
		LPCWSTR TextBox_text = L"";
		TextBox01 = CreateWindowEx(NULL, TextBox_ID, TextBox_text, WS_BORDER | WS_VISIBLE | WS_CHILD, 100, 20, 100, 25, hWnd, (HMENU)EDITCONTROL_01, NULL, NULL);
		//EndTextbox


		//TextBox21nsert
		LPCWSTR TextBox_ID2 = L"EDIT";
		//LPCWSTR TextBox_text = L"";
		TextBox02 = CreateWindowEx(NULL, TextBox_ID, TextBox_text, WS_BORDER | WS_VISIBLE | WS_CHILD, 300, 20, 100, 25, hWnd, (HMENU)EDITCONTROL_01, NULL, NULL);
		//EndTextbox

		//TextBoxCautareNume
		LPCWSTR TextBox_ID3 = L"EDIT";
		//LPCWSTR TextBox_text = L"";
		TextBox03 = CreateWindowEx(NULL, TextBox_ID3, TextBox_text, WS_BORDER | WS_VISIBLE | WS_CHILD, 100, 70, 100, 25, hWnd, (HMENU)EDITCONTROL_01, NULL, NULL);
		//EndTextbox


		//TextBoxCautare numar
		LPCWSTR TextBox_ID4 = L"EDIT";
		//LPCWSTR TextBox_text = L"";
		TextBox04 = CreateWindowEx(NULL, TextBox_ID4, TextBox_text, WS_BORDER | WS_VISIBLE | WS_CHILD, 160, 120, 40, 25, hWnd, (HMENU)EDITCONTROL_01, NULL, NULL);
		//EndTextbox

		//BUTTON 1nserare
		LPCWSTR BUTTONI_ID = L"BUTTON";
		LPCWSTR BUTTONI_text = L"Adaugare";
		BUTTONI01 = CreateWindowEx(NULL, BUTTONI_ID, BUTTONI_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 450, 20, 100, 25, hWnd, (HMENU)BUTTONI, NULL, NULL);
		//BUTTON 1nserare END

		//BUTTON Cautare Nume
		LPCWSTR BUTTONCN_ID = L"BUTTON";
		LPCWSTR BUTTONCN_text = L"Cautare nume";
		BUTTONCN01 = CreateWindowEx(NULL, BUTTONCN_ID, BUTTONCN_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 300, 70, 100, 25, hWnd, (HMENU)BUTTONCN, NULL, NULL);
		//BUTTON Cautare Nume END

		//BUTTON Sterge Nume
		LPCWSTR BUTTONSN_ID = L"BUTTON";
		LPCWSTR BUTTONSN_text = L"Sterge nume";
		BUTTONSN01 = CreateWindowEx(NULL, BUTTONSN_ID, BUTTONSN_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 450, 70, 100, 25, hWnd, (HMENU)BUTTONSN, NULL, NULL);
		//BUTTON Sterge Nume END

		//BUTTON Cautare numar
		LPCWSTR BUTTONCNR_ID = L"BUTTON";
		LPCWSTR BUTTONCNR_text = L"Cautare numar";
		BUTTONCNR01 = CreateWindowEx(NULL, BUTTONCNR_ID, BUTTONCNR_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 300, 120, 100, 25, hWnd, (HMENU)BUTTONCNR, NULL, NULL);
		//BUTTON Cautare numar END

		//BUTTON sterge numar
		LPCWSTR BUTTONSNR_ID = L"BUTTON";
		LPCWSTR BUTTONSNR_text = L"Sterge numar";
		BUTTONSNR01 = CreateWindowEx(NULL, BUTTONSNR_ID, BUTTONSNR_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 450, 120, 100, 25, hWnd, (HMENU)BUTTONSNR, NULL, NULL);
		//BUTTON sterge numar END

		//BUTTON Afisare agenda
		LPCWSTR BUTTONA_ID = L"BUTTON";
		LPCWSTR BUTTONA_text = L"AFISARE AGENDA!";
		BUTTONA01 = CreateWindowEx(NULL, BUTTONA_ID, BUTTONA_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 100, 170, 400, 50, hWnd, (HMENU)BUTTONA, NULL, NULL);
		//BUTTON afisare agenda END

		//BUTTON Afisare EXIT
		LPCWSTR BUTTONE_ID = L"BUTTON";
		LPCWSTR BUTTONE_text = L"EXIT";
		BUTTONA01 = CreateWindowEx(NULL, BUTTONE_ID, BUTTONE_text, BS_DEFPUSHBUTTON | WS_BORDER | WS_VISIBLE | WS_CHILD, 200, 250, 200, 30, hWnd, (HMENU)BUTTONE, NULL, NULL);
		//BUTTON afisare agenda END
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {	
			case BUTTONI:
			{
				
				int caractnumbers = 0;//numarul de caractere al cuvantului introdus
				caractnumbers = GetWindowText(TextBox01, nume, 100);
				caractnumbers = GetWindowText(TextBox02, numar,100);
				if (wcscmp(nume,L"\0")==0 || wcscmp(numar, L"\0") == 0)
				{
					MessageBox(NULL, L"Nu ati introdus date valide", L"Adaugare contact", MB_OK); break;
				}
				skiplist_insert(&list, nume, numar);
				inlocuire(&list);
				snode *x = skiplist_search(&list, nume);
				wchar_t cheie[5], nrr[20];
				wcscpy(nrr, x->nr);
				wcscpy(cheie, x->key);
				wcscpy(nume, x->value);
				wchar_t s[100] = L"A fost adaugat contactul:\n Pozitia:";
				wcscat_s(s, cheie); wcscat(s, L"  Nume: ");
				wcscat_s(s, nume); wcscpy_s(nume, s);
				wcscat_s(nume, L"   Numar: ");
				wcscat_s(nume, nrr);
				MessageBox(NULL, nume, L"Adaugare contact", MB_OK);
				//wchar_t s[100] = L"Nume: ";
				//wcscat_s(s, nume); wcscpy_s(nume,s);
				//wcscat_s(nume, L"   Numar:");
				//wcscat_s(nume,numar);
				break;
			}
			case BUTTONCN:
			{
				int caractnumbers = 0;//numarul de caractere al cuvantului introdus
				caractnumbers = GetWindowText(TextBox03, nume, 100);
					if (wcscmp(nume, L"\0") == 0)
					{
						MessageBox(NULL, L"Nu ati introdus date valide", L"Cautare nume", MB_OK); break;
					}
				snode *x = skiplist_search(&list, nume);
				if (x) {
					wchar_t s[100] = L"Pozitia: ";
					wcscat(s, x->key); wcscat(s,L"  Nume: ");
					wcscat_s(s, nume); wcscpy_s(nume,s);
					wcscat_s(nume, L"   Numar: ");
					wcscat_s(nume,x->nr);
					MessageBox(NULL, nume, L"Cautare Nume", MB_OK);
				}
				else {
					MessageBox(NULL, L"Acest nume nu exista in agenda", L"Cautare Nume", MB_OK);
				}
				inlocuire(&list);
				
				break;
			}
			case BUTTONSN:
			{
				int caractnumbers = 0;//numarul de caractere al cuvantului introdus
				caractnumbers = GetWindowText(TextBox03, nume, 100);
				if (wcscmp(nume, L"\0") == 0)
				{
					MessageBox(NULL, L"Nu ati introdus date valide", L"Stergere contact", MB_OK); break;
				}
				snode *x = skiplist_search(&list, nume);
				if (x) {
					wchar_t cheie[5],nrr[20];
					wcscpy(nrr, x->nr);
					wcscpy(cheie,x->key);
					wcscpy(nume, x->value);
					skiplist_delete(&list, nume);
					wchar_t s[100] = L"A fost sters contactul:\n Pozitia:";
					wcscat_s(s, cheie); wcscat(s, L"  Nume: ");
					wcscat_s(s, nume); wcscpy_s(nume, s);
					wcscat_s(nume, L"   Numar: ");
					wcscat_s(nume, nrr);
					MessageBox(NULL, nume, L"Stergere contact", MB_OK);
				}
				else {
					MessageBox(NULL, L"Acest nume nu exista in agenda", L"Stergere contact", MB_OK);
				}
				inlocuire(&list);

				break;
			}
			case BUTTONCNR:
			{
				int caractnumbers = 0;//numarul de caractere al cuvantului introdus
				caractnumbers = GetWindowText(TextBox04, key, 100);
				if (wcscmp(key, L"\0") == 0)
				{
					MessageBox(NULL, L"Nu ati introdus date valide", L"Cautare numar", MB_OK); break;
				}
				snode *x = skiplist_search_nr_ord(&list, key);
				if (x) {
					wcscpy(nume, x->value);
					wchar_t s[100] = L"Pozitia: ";
					wcscat(s, x->key); wcscat(s, L"  Nume: ");
					wcscat_s(s, nume); wcscpy_s(nume, s);
					wcscat_s(nume, L"   Numar: ");
					wcscat_s(nume, x->nr);
					MessageBox(NULL, nume, L"Cautare numar", MB_OK);
				}
				else {
					MessageBox(NULL, L"Acest numar nu exista in agenda", L"Cautare numar", MB_OK);
				}
				inlocuire(&list);
				break;
			}
			case BUTTONSNR:
			{
				int caractnumbers = 0;//numarul de caractere al cuvantului introdus
				caractnumbers = GetWindowText(TextBox04, key, 100);
				if (wcscmp(key, L"\0") == 0)
				{
					MessageBox(NULL, L"Nu ati introdus date valide", L"Stergere contact", MB_OK); break;
				}
				snode *y = skiplist_search_nr_ord(&list, key);
				snode *x = skiplist_search(&list, y->value);

				if (x) {
					wchar_t cheie[5], nrr[20];
					wcscpy(nrr, x->nr);
					wcscpy(cheie, x->key);
					wcscpy(nume, x->value);
					skiplist_delete(&list, nume);
					wchar_t s[100] = L" A fost sters contactul:\n Pozitia:";
					wcscat_s(s, cheie); wcscat(s, L"  Nume: ");
					wcscat_s(s, nume); wcscpy_s(nume, s);
					wcscat_s(nume, L"   Numar: ");
					wcscat_s(nume, nrr); 
					MessageBox(NULL, nume, L"Stergere contact", MB_OK);
				}
				else {
					MessageBox(NULL, L"Acest numar nu exista in agenda", L"Stergere contact", MB_OK);
				}
				inlocuire(&list);
				break;
			}
			case BUTTONE: {
				DestroyWindow(hWnd);
				break;
			}
			
            case  BUTTONA:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);

                break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			TextOut(hdc, 35, 22, L"Nume:", 5);
			TextOut(hdc, 235, 22, L"Numar:", 6);
			TextOut(hdc, 33, 72, L"Nume:", 6);
			TextOut(hdc, 30, 123, L"Numar de ordine:", 16);
			ReleaseDC(hWnd,hdc);
            EndPaint(hWnd, &ps);
			
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
wchar_t string2[100];
wchar_t deafisat[100]=L"";

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
		
	case WM_INITDIALOG: {
		FILE *fin = fopen("agenda.txt", "r");
		while (!feof(fin)) {
			
			wcscpy(deafisat, L" ");
			fwscanf(fin, L"%ls", string2);
			wcscat(deafisat, string2); wcscat(deafisat,L". ");
			fwscanf(fin, L"%ls", string2);
			wcscat(deafisat, string2); wcscat(deafisat, L"       ");
			fwscanf(fin, L"%ls", string2);
			wcscat(deafisat, string2);
			if(!feof(fin))
			SendMessage(GetDlgItem(hDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)deafisat);

		}
		fclose(fin);
		return (INT_PTR)TRUE;
	}break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}