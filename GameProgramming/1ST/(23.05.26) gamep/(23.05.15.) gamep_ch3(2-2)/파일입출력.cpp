//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	// ���� ���� open, is_open(), close(), write()
////	std::ofstream writeFile("test2.txt");
//////	writeFile.open("test.txt");
////	char arr[8] = "JunYong";
////	if (writeFile.is_open())
////	{
////		writeFile.write(arr, 7);
////		writeFile << "����" << endl;
////		writeFile << "�޷�";
////	}
//	//ofstream writeFile("test3.txt");
//	//string str;
//	//for (int i = 0; i < 5; i++)
//	//{
//	//	cin >> str;
//	//	writeFile << str << endl;
//	//}
//	//writeFile.close();
//	
//	// ���� �б� open(), is_open(), close(), eof(), get()
//	ifstream readFile("test2.txt");
//	// getline 2���� ���� - string, ifstream
//	//string str;
//	//
//	//while (getline(readFile, str))
//	//	cout << str << endl;
//	char buf[1024];
//	while (!readFile.eof())
//	{
//		readFile.getline(buf, 12);
//		cout << buf << endl;
//	}
//	
//	//int num, sum = 0;
//	//for (int i = 0; i < 5; i++)
//	//{
//	//	readFile >> num;
//	//	sum += num;
//	//}
//	//cout << "�հ�: " << sum << endl;
//	//while (!readFile.eof())
//	//	cout << readFile.get() << endl;
//}