#include <Windows.h>
#include <mmsystem.h>
#include <Digitalv.h>
#pragma comment(lib, "winmm.lib")

MCI_OPEN_PARMS openBgm; //여는거
MCI_PLAY_PARMS playBgm; //재생용
MCI_OPEN_PARMS OoenEffect; //여는거
MCI_PLAY_PARMS playEffect; //재생용
UINT Bgmid, Effectid;

void PlayBgm()
{
	openBgm.lpstrDeviceType = TEXT("mpegvideo");
	openBgm.lpstrElementName = TEXT("Sound\\creativeminds.mp3");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openBgm);
	openBgm.wDeviceID;
	Bgmid = openBgm.wDeviceID;
	mciSendCommand(Bgmid, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD_PTR)&openBgm);
}

void PlayEffect()
{
	OoenEffect.lpstrDeviceType = TEXT("waveaudio");
	OoenEffect.lpstrElementName = TEXT("Sound\\pickupCoin.wav");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&OoenEffect);
	OoenEffect.wDeviceID;
	Effectid = OoenEffect.wDeviceID;
	mciSendCommand(Effectid, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&OoenEffect);
	Sleep(100); 
	mciSendCommand(Effectid, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&OoenEffect);
}

int main()
{
	PlayBgm();
	while (true)
	{
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
			PlayEffect();
	}
}