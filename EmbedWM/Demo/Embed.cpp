#pragma once
#include "Headers.h"

//////////////////////////////////////////////////////////////////////////////////////////
//// 삽입
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
	Mat Qr_Pixel = Mat(QrImg.rows, QrImg.cols, QrImg.type()); // 32x32 QRcode 각 픽셀 값을 255, 0으로 저장할 행렬 변수 생성

	// barcodePixel 데이터 0과 255로 설정
	for (int y = 0; y < QrImg.rows; y++)
		for (int x = 0; x < QrImg.cols; x++)
			Qr_Pixel.at<uchar>(y, x) = ((int)QrImg.at<uchar>(y, x) > 125) ? 255 : 0;

	cvtColor(HostImg, yuv, COLOR_RGB2YCrCb);    // RGV to YCrCb
	split(yuv, yuv_arr);						// 채널 분리
	WT(yuv_arr[0], WT_result, 1);               // Cb채널을 대상으로 2단계 DWT 진행

	// 부대역의 계수를 저장할 행렬 변수    
	Mat HH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat HL_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat LH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());

	HH_subband = WT_result(Rect(WT_result.cols / 2, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));
	HL_subband = WT_result(Rect(WT_result.cols / 2, 0, WT_result.cols / 2, WT_result.rows / 2));
	LH_subband = WT_result(Rect(0, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));

	// DCT를 진행할 8x8 크기의 블럭들
	Size blockSize(8, 8);
	vector<Mat> HH_blocks;	// 각 부대역의 블럭들
	vector<Mat> HL_blocks;
	vector<Mat> LH_blocks;
	int value[1024];		// QR의 삽입 값을 저장할 배열
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


	// 최신화된 부대역들을 기존의 DWT 결과에 갱신
	IWT(WT_result, IWT_result, 1);

	// 호스트 이미지의 Cb 채널을 워터마크 삽입된 Cb채널로 변경
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