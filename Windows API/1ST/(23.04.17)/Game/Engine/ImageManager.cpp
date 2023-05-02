#include "pch.h"
#include "ImageManager.h"
#include "Image.h"

shared_ptr<Image> ImageManager::AddImage(wstring strKey, wstring fileName, COLORREF transColor)
{
	shared_ptr<Image> image = FindImage(strKey);

	if (image)
		return image;

	image = make_shared<Image>();
	if (image == nullptr || image->Load(fileName) == false)
		return image = nullptr;

	image->SetTransColor(transColor);
	m_imageContainer.insert(m_imageContainer.end(), pair<wstring, shared_ptr<Image>>(strKey, image));

	return image;
}

shared_ptr<Image> ImageManager::FindImage(wstring strKey)
{
	auto iter = m_imageContainer.find(strKey);

	if (iter != m_imageContainer.end())
		return iter->second;

	return nullptr;
}

bool ImageManager::DeleteImage(wstring strKey)
{
	m_imageContainer.erase(strKey);
	return true;
}

bool ImageManager::DeleteAll()
{
	m_imageContainer.erase(m_imageContainer.begin(), m_imageContainer.end());
	m_imageContainer.clear();
	return true;
}
