//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	// 파일 쓰기 open, is_open(), close(), write()
////	std::ofstream writeFile("test2.txt");
//////	writeFile.open("test.txt");
////	char arr[8] = "JunYong";
////	if (writeFile.is_open())
////	{
////		writeFile.write(arr, 7);
////		writeFile << "겜프" << endl;
////		writeFile << "메롱";
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
//	// 파일 읽기 open(), is_open(), close(), eof(), get()
//	ifstream readFile("test2.txt");
//	// getline 2가지 버전 - string, ifstream
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
//	//cout << "합계: " << sum << endl;
//	//while (!readFile.eof())
//	//	cout << readFile.get() << endl;
//}