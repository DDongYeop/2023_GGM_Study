//// PlaySound()
//#include<Windows.h>
//#include<mmsystem.h>
//#include<Digitalv.h>
//#pragma comment(lib, "winmm.lib")
//// Bgm, efffect ���ÿ� ����ϰ� �����ž�.
//MCI_OPEN_PARMS openBgm; // ���¿뵵
//MCI_PLAY_PARMS playBgm; // ����뵵
//MCI_OPEN_PARMS openEffect; // ���¿뵵
//MCI_PLAY_PARMS playEffect; // ����뵵
//UINT Bgmid, Effectid;
//
//void PlayBgm()
//{
//	openBgm.lpstrDeviceType = TEXT("mpegvideo");
//	openBgm.lpstrElementName = TEXT("Sound\\creativeminds.mp3");
//	// 1: ����̽����̵�, 2: ������? 3,4: �÷���
//	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)& openBgm);
//	Bgmid = openBgm.wDeviceID;
//	mciSendCommand(Bgmid, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&playBgm);
//}
//
//void PlayEfffect()
//{
//	openEffect.lpstrDeviceType = TEXT("waveaudio");
//	openEffect.lpstrElementName = TEXT("Sound\\explosion.wav");
//	// 1: ����̽����̵�, 2: ������? 3,4: �÷���
//	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openEffect);
//	Effectid = openEffect.wDeviceID;
//	mciSendCommand(Effectid, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playEffect);
//	Sleep(100)
//	mciSendCommand(Effectid, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&playEffect);
//}
//
//int main()
//{
//	PlayBgm();
//	while (true)
//	{
//		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
//		{
//			PlayEfffect();
//		}
//	}
//
//}