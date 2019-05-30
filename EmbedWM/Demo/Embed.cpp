#pragma once
#include "Headers.h"

//////////////////////////////////////////////////////////////////////////////////////////
//// ����
//////////////////////////////////////////////////////////////////////////////////////////
Mat EmbedWatermark(Mat& HostImg, Mat& QrImg)
{
	return Embed(HostImg, QrImg);
}

Mat Embed(Mat& HostImg, Mat& QrImg)
{
	Mat yuv;
	Mat yuv_arr[3];
	Mat WT_result;
	Mat IWT_result;
	Mat Qr_Pixel = Mat(QrImg.rows, QrImg.cols, QrImg.type()); // 32x32 QRcode �� �ȼ� ���� 255, 0���� ������ ��� ���� ����

	// barcodePixel ������ 0�� 255�� ����
	for (int y = 0; y < QrImg.rows; y++)
		for (int x = 0; x < QrImg.cols; x++)
			Qr_Pixel.at<uchar>(y, x) = ((int)QrImg.at<uchar>(y, x) > 125) ? 255 : 0;

	cvtColor(HostImg, yuv, COLOR_RGB2YCrCb);    // RGV to YCrCb
	split(yuv, yuv_arr);						// ä�� �и�
	WT(yuv_arr[0], WT_result, 1);               // Cbä���� ������� 2�ܰ� DWT ����

	// �δ뿪�� ����� ������ ��� ����    
	Mat HH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat HL_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat LH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());

	HH_subband = WT_result(Rect(WT_result.cols / 2, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));
	HL_subband = WT_result(Rect(WT_result.cols / 2, 0, WT_result.cols / 2, WT_result.rows / 2));
	LH_subband = WT_result(Rect(0, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));

	// DCT�� ������ 8x8 ũ���� ����
	Size blockSize(8, 8);
	vector<Mat> HH_blocks;	// �� �δ뿪�� ����
	vector<Mat> HL_blocks;
	vector<Mat> LH_blocks;
	int value[1024];		// QR�� ���� ���� ������ �迭
	int i = 0;

	for (int y = 0; y < 256; y += blockSize.height)
	{
		for (int x = 0; x < 256; x += blockSize.width)
		{
			Rect rect = Rect(x, y, blockSize.width, blockSize.height);
			HH_blocks.push_back(Mat(HH_subband, rect));
			HL_blocks.push_back(Mat(HL_subband, rect));
			LH_blocks.push_back(Mat(LH_subband, rect));
			value[i++] = ((int)Qr_Pixel.at<uchar>((int)(y / 8), (int)(x / 8)) > 125 ? 3 : -3);
		}
	}


	int x = 0, y = 0;
	for (int i = 0; i < 1024; i++)
	{
		dct(HH_blocks[i], HH_blocks[i]);
		dct(HL_blocks[i], HL_blocks[i]);
		dct(LH_blocks[i], LH_blocks[i]);

		HH_blocks[i].at<float>(0, 0) += 23 * value[i];

		HL_blocks[i].at<float>(0, 0) += 23 * value[i];

		LH_blocks[i].at<float>(0, 0) += 23 * value[i];

		idct(HH_blocks[i], HH_blocks[i]);
		idct(HL_blocks[i], HL_blocks[i]);
		idct(LH_blocks[i], LH_blocks[i]);

		x += 8;
		if (x == 256)
		{
			x = 0;
			y += 8;
		}
	}


	// �ֽ�ȭ�� �δ뿪���� ������ DWT ����� ����
	IWT(WT_result, IWT_result, 1);

	// ȣ��Ʈ �̹����� Cb ä���� ���͸�ũ ���Ե� Cbä�η� ����
	for (int i = 0; i < HostImg.rows; i++) {
		for (int j = 0; j < HostImg.cols; j++) {
			yuv.at<Vec3b>(i, j)[0] = (int)IWT_result.at<float>(i, j);
		}
	}

	cvtColor(yuv, yuv, COLOR_YCrCb2RGB); // RGB to YCrCb

	imwrite("C:/Users/JH/Desktop/pngMarked_Image.png", yuv);
	
	imwrite("C:/Users/JH/Desktop/jpgMarked_Image.jpg", yuv);

	return yuv;
}