#pragma once

class Image;
class ImageManager
{
	DECLARE_SINGLE(ImageManager);

public:
	shared_ptr<Image>	AddImage(wstring strKey, wstring fileName, COLORREF transColor = RGB(255, 0, 255));
	shared_ptr<Image>	FindImage(wstring strKey);
	bool				DeleteImage(wstring strKey);
	bool				DeleteAll();

private:
	map<wstring, shared_ptr<Image>> m_imageContainer;
};

