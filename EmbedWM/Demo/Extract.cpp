#pragma once
#include "stdafx.h"
#include "Headers.h"

//////////////////////////////////////////////////////////////////////////////////////////
//// 추출
//////////////////////////////////////////////////////////////////////////////////////////

void ExtractWatermark(Mat& marked_img)
{
	Extract(marked_img);
}

void Extract(Mat& Marked_Image)
{
	imshow("Marked_Image", Marked_Image);
	////////////////////////////////
	//getPSNR(Marked_Image);
	////////////////////////////////
	Mat yuv_arr[3];
	cvtColor(Marked_Image, Marked_Image, COLOR_RGB2YCrCb);   // RGB to YCrCb
	split(Marked_Image, yuv_arr);                     // 채널 분리
	Mat Marked_Y_channel = Mat(Marked_Image.cols, Marked_Image.rows, Marked_Image.type());
	int QRcodeSize;

	yuv_arr[0].copyTo(Marked_Y_channel);               // Cb 채널 분리

	// 추출한 QRcode 계수들을 저장할 행렬 변수
	Mat HH_recoverd_barcode_Pixel = Mat(32, 32, CV_8UC1);
	Mat LH_recoverd_barcode_Pixel = Mat(32, 32, CV_8UC1);
	Mat HL_recoverd_barcode_Pixel = Mat(32, 32, CV_8UC1);

	Mat WT_result;
	WT(Marked_Y_channel, WT_result, 1);               // 분리한 Cb 채널을 DWT 진행
	imshow("Extracted_Image_WT", WT_result);

	// 대역의 계수를 저장할 행렬 변수
	Mat HH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat HL_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());
	Mat LH_subband = Mat(WT_result.cols / 2, WT_result.rows / 2, WT_result.type());

	HH_subband = WT_result(Rect(WT_result.cols / 2, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));
	HL_subband = WT_result(Rect(WT_result.cols / 2, 0, WT_result.cols / 2, WT_result.rows / 2));
	LH_subband = WT_result(Rect(0, WT_result.rows / 2, WT_result.cols / 2, WT_result.rows / 2));

	Size blockSize(8, 8);
	vector<Mat> HH_blocks;
	vector<Mat> HL_blocks;
	vector<Mat> LH_blocks;
	int sigma[1024];
	int i = 0;
	for (int y = 0; y < 256; y += blockSize.height)
	{
		for (int x = 0; x < 256; x += blockSize.width)
		{
			Rect rect = Rect(x, y, blockSize.width, blockSize.height);
			HH_blocks.push_back(Mat(HH_subband, rect));
			HL_blocks.push_back(Mat(HL_subband, rect));
			LH_blocks.push_back(Mat(LH_subband, rect));
		}
	}


	int x = 0, y = 0;
	for (int i = 0; i < 1024; i++)
	{
		dct(HH_blocks[i], HH_blocks[i]);
		dct(HL_blocks[i], HL_blocks[i]);
		dct(LH_blocks[i], LH_blocks[i]);

		float HH_sum = HH_blocks[i].at<float>(0, 0);
		float HL_sum = HL_blocks[i].at<float>(0, 0);
		float LH_sum = LH_blocks[i].at<float>(0, 0);
		
		//cout << i << " HH_sum : " << HH_sum << endl;
		HH_recoverd_barcode_Pixel.at<uchar>((int)(y), (int)(x)) = ((HH_sum > 0) ? 255 : 0);
		HL_recoverd_barcode_Pixel.at<uchar>((int)(y), (int)(x)) = ((HL_sum > 0) ? 255 : 0);
		LH_recoverd_barcode_Pixel.at<uchar>((int)(y), (int)(x++)) = ((LH_sum > 0) ? 255 : 0);
		
		if (x == 32)
		{
			y++;
			x = 0;
		}
	}

	// QRcode를 생성할 행렬 변수 설정
	QRcodeSize = HL_recoverd_barcode_Pixel.rows;
	Mat QR_2(QRcodeSize + 2, QRcodeSize + 2, HH_recoverd_barcode_Pixel.type(), Scalar(255));
	Mat QR_3(QRcodeSize + 2, QRcodeSize + 2, HL_recoverd_barcode_Pixel.type(), Scalar(255));
	Mat QR_4(QRcodeSize + 2, QRcodeSize + 2, LH_recoverd_barcode_Pixel.type(), Scalar(255));

	// 결정된 QRcode의 픽셀 값을 위치에 맞게 저장
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			QR_2.at<uchar>(i + 1, j + 1) = HH_recoverd_barcode_Pixel.at<uchar>(i, j);
			QR_3.at<uchar>(i + 1, j + 1) = HL_recoverd_barcode_Pixel.at<uchar>(i, j);
			QR_4.at<uchar>(i + 1, j + 1) = LH_recoverd_barcode_Pixel.at<uchar>(i, j);
		}
	}

	Mat BIG_QR_2(100, 100, HH_recoverd_barcode_Pixel.type(), Scalar(255));
	Mat BIG_QR_3(100, 100, HL_recoverd_barcode_Pixel.type(), Scalar(255));
	Mat BIG_QR_4(100, 100, LH_recoverd_barcode_Pixel.type(), Scalar(255));

	int n = 0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			BIG_QR_2.at<uchar>(n, 3 * j) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n, 3 * j + 1) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n, 3 * j + 2) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 1, 3 * j) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 1, 3 * j + 1) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 1, 3 * j + 2) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 2, 3 * j) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 2, 3 * j + 1) = QR_2.at<uchar>(i, j);
			BIG_QR_2.at<uchar>(n + 2, 3 * j + 2) = QR_2.at<uchar>(i, j);

			BIG_QR_3.at<uchar>(n, 3 * j) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n, 3 * j + 1) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n, 3 * j + 2) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 1, 3 * j) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 1, 3 * j + 1) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 1, 3 * j + 2) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 2, 3 * j) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 2, 3 * j + 1) = QR_3.at<uchar>(i, j);
			BIG_QR_3.at<uchar>(n + 2, 3 * j + 2) = QR_3.at<uchar>(i, j);

			BIG_QR_4.at<uchar>(n, 3 * j) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n, 3 * j + 1) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n, 3 * j + 2) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 1, 3 * j) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 1, 3 * j + 1) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 1, 3 * j + 2) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 2, 3 * j) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 2, 3 * j + 1) = QR_4.at<uchar>(i, j);
			BIG_QR_4.at<uchar>(n + 2, 3 * j + 2) = QR_4.at<uchar>(i, j);
		}
		n += 3;
	}

	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/HH_QRcode.png", BIG_QR_2);
	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/HL_QRcode.png", BIG_QR_3);
	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/LH_QRcode.png", BIG_QR_4);
	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/HH_recoverd_QRcode.png", HH_recoverd_barcode_Pixel);
	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/HL_recoverd_QRcode.png", HL_recoverd_barcode_Pixel);
	imwrite("C:/Users/fnzld/Desktop/Test_WM/result/LH_recoverd_QRcode.png", LH_recoverd_barcode_Pixel);


	//getNCC();
}