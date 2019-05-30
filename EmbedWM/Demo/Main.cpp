#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "Socket.h"
#include "QRmain.h"
#include "Headers.h"


int main()
{
	int count = 0;
	Mat QrImg;
	BOOL imageErr = TRUE;
	serverMain();

	while (1)
	{
		HostImage();

		char* key;
		key = serverKey();

		char k[100] = { 0, };

		for (int i = 0; i < strlen(key); i++) {
			k[i] = key[i];
		}


		//iKey = (LPSTR)key;
		QrImg = doBasicDemo(k);
		BOOL imageErr = TRUE;
		if (imageErr == FALSE)
		{
			cout << "이미지 통신 실패" << endl;
			break;
		}
		
		cv::Mat HostImg = cv::imread("test.png");

		if (HostImg.empty())
		{
			cout << "이미지 에러" << endl;
			system("pause");
			break;
		}

		cout << "Embed Count: " << count << endl << endl;
		EmbedWatermark(HostImg, QrImg);

		count++;
		
	}

	serverEnd();
}