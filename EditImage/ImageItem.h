#pragma once
class ImageItem
{
public:
	ImageItem();

	void Initialize();
	void Resize(CImage& image, int width, int height);
	void Load(CString path);
	void ChangeBrightness(float percent);
	void ChangeContrast(float percent);
	void Zoom(CImage& image, float percent_z);

	void EditImage();

	void SetSize(int width, int height);

	CImage* getImage();

private:
	CImage	m_image;
	CImage	m_originalImage;
	int		m_width;
	int		m_height;
	float	m_brightness;
	float	m_contrast;
	float	m_zoom;
	bool	m_isFlip;
};