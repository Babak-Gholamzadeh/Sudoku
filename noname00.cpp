#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

void display(void);
int custom(void);
int sodoko(int);
void satr(int);
void soton(int);
void s(int);
void eachk(void);
int a[9][9];
char chk[3][10];
void gotoxy(int x,int y)
{

    COORD pos;
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

    if (INVALID_HANDLE_VALUE != hConsole)
    {
        pos.X = x;
        pos.Y = y;

        SetConsoleCursorPosition( hConsole, pos );
    }
}
int main()
{
	char ch;
NewSodoko:
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
			a[i][j]=0;
	// clrscr();
    system("cls");
	cout << "1.Automatic Sudoku" << endl
		  << "2.Customize Sudoku" << endl
		  << "Any else character = Exit" << endl
		  << "\nSelect Number:";
	ch=getch();
	if (ch=='1' || ch=='2')
	{
		if (ch=='2')
			custom();
	}
	else
		return 0;
	sodoko(0);
	display();
	cout << "New?(Y/N)";
	ch=getch();
	if (ch=='y'||ch=='Y')
		goto NewSodoko;
	return 0;
}
int custom()
{
	int i,j,num;
	char ca[10];
	// clrscr();
    system("cls");
	gotoxy(20,10);
	cout << "Info: To exit from customize sudoku, \n\n\t\t   enter the zero(0) number in the selected cell.";
	gotoxy(49,25);
	cout << "Press any key to continue . . .";
	getch();
	for (int k=0;k<81;k++)
	{
	NewIJ:
		display();
		cout << "\nSelect Cell= " << "\n\nExample= 3 5";
		gotoxy(14,22);
		cin >> i >> j;
		if (i<1 || i>9 || j<1 || j>9)
		{
			cout << "Not Valid Number ( 1<=Number=<9 )";
			getch();
			goto NewIJ;
		}
		display();
		gotoxy(58,4);
		cout << "Enter a number:";
		gotoxy(60,6);
		cout << "1<=Number=<9";
		gotoxy(58,8);
		cout << "If number=0 then";
		gotoxy(60,10);
		cout << "Exit customize sudoku";
		gotoxy(62,12);
		cout << "AND";
		gotoxy(60,14);
		cout << "Start sudoku again";
		gotoxy(58,16);
		cout << "Any else number";
		gotoxy(60,18);
		cout << "NOT VALID";

		for (int z=1;z<=9;z++)
			ca[z]='0';
		eachk();
		satr((i-1)*9+(j-1));
		soton((i-1)*9+(j-1));
		s((i-1)*9+(j-1));
		gotoxy(0,23);
		cout << "Valid number for this cell: ";
		for (int z=1;z<=9;z++)
			if (chk[0][z]=='1' && chk[1][z]=='1' && chk[2][z]=='1')
			{
				ca[z]='1';
				cout << z << ", ";
			}

	NewNum:
		gotoxy(j*6,i*2+1);
		num=getch();
		num-=48;
		if (num==0)
			return 0;
		if (ca[num]!='1')
			goto NewNum;
		a[i-1][j-1]=num;
	}
}
int sodoko(int n)
{
CheckN:
	if (n==81)
		return 1;
	if (a[n/9][n%9]!=0)
	{
		n++;
		goto CheckN;
	}
	char st[10];
	int r,c1=0,c2=0,i;
	for (i=1;i<=9;i++)
		st[i]='0';
	eachk();
	satr(n);
	soton(n);
	s(n);
	for (i=1;i<=9;i++)
		if (chk[0][i]=='1' && chk[1][i]=='1' && chk[2][i]=='1')
		{
			st[i]='1';
			c1++;
		}
	c2=c1;
	for (int k=0;k<c2;k++)
	{
		r=1+rand()%c1;
		for (int i=1;i<=9;i++)
			if (st[i]=='1')
			{
				r--;
				if (r==0)
				{
					a[n/9][n-((n/9)*9)]=i;
					if (sodoko(n+1)==1)
						return 1;
					a[n/9][n-((n/9)*9)]=0;
					st[i]='0';
					c1--;
					break;
				}
			}
	}
	return 0;
}
void eachk()
{
	for (int i=0;i<3;i++)
		for (int j=1;j<=9;j++)
			chk[i][j]='1';
}
void satr(int n)
{
	for (int i=0;i<9;i++)
		chk[0][a[n/9][i]]='0';
}
void soton(int n)
{
	for (int i=0;i<9;i++)
		chk[1][a[i][n%9]]='0';
}
void s(int n)
{
	for (int i=((n/9)/3)*3;i<(((n/9)/3)*3)+3;i++)
		for (int j=((n%9)/3)*3;j<(((n%9)/3)*3)+3;j++)
			chk[2][a[i][j]]='0';
}
void display()
{
	// clrscr();
    system("cls");
	int i,j;
	for (i=1;i<=9;i++)
		cout << "     " << i;
	cout << endl << "   ";
	for (i=0;i<9;i++)
		cout << "_____ ";
	cout << endl;
	for (i=0;i<9;i++){
		cout << (i+1) << " |  ";
		for (j=0;j<9;j++)
			if (a[i][j]==0)
				cout << "   |  ";
			else
				cout << a[i][j] << "  |  ";
		cout << endl << "  ";
		for (j=0;j<9;j++)
			cout << "|_____";
		cout << "|" << endl;
	}
}
