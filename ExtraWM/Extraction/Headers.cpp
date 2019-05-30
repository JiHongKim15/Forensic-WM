#pragma once
#include "stdafx.h"
#include "Headers.h"


void calculate_SVD(Mat& src, Mat& U, Mat& S, Mat& V)
{
	Mat S_zero = Mat(src.rows, src.cols, src.type());
	S_zero = Scalar(0);
	V = V.t();
	SVD::compute(src, S, U, V, 4);  // full SVD
	for (int i = 0; i < src.rows; i++)
		S_zero.at<float>(i, i) = S.at<float>(i, 0);

	//adjoint(V, src.rows, src.cols);

	S = S_zero;
	//V = V.t();
}
