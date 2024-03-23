#include "pch.h"
#include "ImageItem.h"

ImageItem::ImageItem() {
	Initialize();
}

void ImageItem::Initialize() {
	m_brightness = 0.0;
	m_contrast = 1.0;
	m_zoom = 1.0;
	m_isFlip = false;
	if (!m_originalImage.IsNull()) {
		m_image = m_originalImage;
	}
}

void ImageItem::SetSize(int width, int height) {
	m_width = width;
	m_height = height;
}

void ImageItem::Resize(CImage &image, int width, int height) {
	HBITMAP hBitmap = image.Detach();
	Gdiplus::Bitmap bitmap(hBitmap, NULL);
	Gdiplus::Bitmap newBitmap(width, height, bitmap.GetPixelFormat());
	Gdiplus::Graphics graphics(&newBitmap);
	graphics.DrawImage(&bitmap, Gdiplus::Rect(0, 0, width, height),
		0, 0, bitmap.GetWidth(), bitmap.GetHeight(), Gdiplus::UnitPixel);
	newBitmap.GetHBITMAP(NULL, &hBitmap);
	image.Attach(hBitmap);
}

void ImageItem::Load(CString path) {
	if (!m_originalImage.IsNull()) {
		m_image.Destroy();
		m_originalImage.Destroy();
		Initialize();
	}

	m_originalImage.Load(path);
	m_image = m_originalImage;
}

CImage* ImageItem::getImage() {
	return &m_image;
}

void ImageItem::ChangeBrightness(float percent) {
	m_brightness += percent;
	EditImage();
}
void ImageItem::ChangeContrast(float percent) {
	m_contrast += percent;
	EditImage();
}


void ImageItem::Zoom(CImage& image, float percent_z) {
	m_zoom += percent_z;
	if(m_zoom < 1.0) {
		m_zoom = 1.0;
	}

	HBITMAP hBitmap = image.Detach();
	Gdiplus::Bitmap bitmap(hBitmap, NULL);
	Gdiplus::Bitmap bitmap_bp1(bitmap.GetWidth()* m_zoom, bitmap.GetHeight()* m_zoom, bitmap.GetPixelFormat());
	Gdiplus::Graphics graphics_bp1(&bitmap_bp1);
	graphics_bp1.DrawImage(&bitmap, Gdiplus::Rect(0, 0, bitmap.GetWidth() * m_zoom, bitmap.GetHeight() * m_zoom),
		0, 0, bitmap.GetWidth(), bitmap.GetHeight(), Gdiplus::UnitPixel);

	//Gdiplus::Bitmap bitmap_bp2(bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetPixelFormat());
	Gdiplus::Graphics graphics_bp2(&bitmap);
	graphics_bp2.DrawImage(&bitmap, Gdiplus::Rect(0, 0, bitmap.GetWidth(), bitmap.GetHeight()),
		0, 0, bitmap_bp1.GetWidth(), bitmap_bp1.GetHeight(), Gdiplus::UnitPixel);

	bitmap.GetHBITMAP(NULL, &hBitmap);
	image.Attach(hBitmap);
}

void ImageItem::EditImage() {
	m_image = m_originalImage;
	//dx = 50 * (PanRightButtonClicked - PanLeftButtonClicked);
	//dy = 50 * (PanDownButtonClicked - PanUpButtonClicked);

	// Convert CImage to Gdiplus::Bitmap
	HBITMAP hBitmap = m_image.Detach();
	Gdiplus::Bitmap bitmap(hBitmap, NULL);

	// Flip the image
	if (m_isFlip) {
		bitmap.RotateFlip(Gdiplus::RotateNoneFlipX);
	}

	// Create a ColorMatrix object to adjust brightness and contrast
	Gdiplus::ColorMatrix colorMatrix = {
		m_contrast, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, m_contrast, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, m_contrast, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		m_brightness, m_brightness, m_brightness, 0.0f, 1.0f
	};

	// Draw the Bitmap object onto a new bitmap while applying the color matrix
	Gdiplus::Bitmap newBitmap(m_width, m_height, bitmap.GetPixelFormat());
	Gdiplus::Graphics graphics(&newBitmap);

	// Create an ImageAttributes object and set its color matrix
	Gdiplus::ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

	// Calculate new size
	//double scaleFactor = pow(1.2f, zoomButtonClicked);
	//int newWidth = static_cast<int>(bitmap.GetWidth() * scaleFactor);
	//int newHeight = static_cast<int>(bitmap.GetHeight() * scaleFactor);

	// Set the interpolation mode
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);

	// Draw the original image onto the new Bitmap
	graphics.DrawImage(&bitmap, Gdiplus::Rect(0, 0, m_width, m_height), 0, 0, bitmap.GetWidth(), bitmap.GetHeight(), Gdiplus::UnitPixel, &imageAttributes);

	// Convert the new Gdiplus::Bitmap back to CImage
	newBitmap.GetHBITMAP(NULL, &hBitmap);
	m_image.Attach(hBitmap);
}