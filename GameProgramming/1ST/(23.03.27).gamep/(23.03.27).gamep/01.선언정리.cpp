#include<iostream>
#include<io.h>
#include<fcntl.h>
#include<Windows.h>
//#include "add.h"
//#include "Admul.h"
using namespace std;

// 소리 -> Beep(), Playsound, mcisendcommand()

int main()
{
	/*cout << add(10, 20) << endl;
	cout << PlusandMul() << endl << endl;*/

	Beep(523.25, 50000);
	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	wcout << L"	██████╗   █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ ██╗ \n";
	wcout << L"	██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║ \n";
	wcout << L"	██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝██║ \n";
	wcout << L"	██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝ \n";
	wcout << L"	╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗ \n";
	wcout << L"	 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝ \n";
	int b = _setmode(_fileno(stdout), _O_TEXT);
	cout << "Hello World";


}