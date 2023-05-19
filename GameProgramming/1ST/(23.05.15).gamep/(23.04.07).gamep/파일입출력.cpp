#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{
	//파일 쓰기
	std::ofstream writeFile;
	/*writeFile.open("test.txt");
	char arr[9] = "Dongyeop";
	if (writeFile.is_open())
	{
		writeFile.write(arr, 8);
		writeFile << "GameP" << endl;
	}*/
	/*ostream writeFile("test3.txt");
	string str;
	for (int i = 0; i < 5; ++i)
	{
		cin >> str;
		writeFile << str << endl;
	}
	writeFile.close();*/

	//file read
	/*ifstream readFile("test2.txt");

	char buf[1024];
	while (!readFile.eof())
	{
		readFile.getline(buf, 12);
		cout << buf << endl;
	}*/

	/*string str;
	while(getline(readFile, str))
		cout << str << endl;*/

	/*int num, sum = 0;
	for (int i = 0; i < 5; ++i)
	{
		readFile >> num;
		sum += num;
	}*/
	/*while (!readFile.eof())
		cout << readFile.get(); */
}
