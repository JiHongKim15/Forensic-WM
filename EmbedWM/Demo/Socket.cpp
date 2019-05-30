#include "Socket.h"

void showError(const char * msg)
{
	std::cout << "에러 : " << msg << std::endl;
	exit(-1);
}

SOCKET server;
SOCKET client;
int flag = 1;

void serverMain()
{
	WSADATA data;
	::WSAStartup(MAKEWORD(2, 2), &data);

	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server == INVALID_SOCKET)
		showError("ServerCreateFailed");

	sockaddr_in addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);

	if (bind(server, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
		showError("BindingFailed");

	if (listen(server, SOMAXCONN) == SOCKET_ERROR)
		showError("ListeningFailed");

	std::cout << "Waiting for client" << std::endl;

	client = accept(server, NULL, NULL);

	flag = 0;

	return;
}
int dataReceive(SOCKET c, char* buf, int len, int flags) {

	// 통신에 필요한 변수 선언
	int received;
	char *ptr = buf;
	int left = len;

	// 남아있는 데이터가 있는 경우 반복적으로 시행
	while (left > 0) {
		received = recv(c, ptr, left, flags);

		// 더이상 데이터를 받아오지 못하는 경우
		if (received == 0)
			break;

		// 받아온 데이터가 존재하는 경우
		left -= received;
		ptr += received;
	}

	// 더 받을 수 있는 데이터 길이를 반환(데이터를 한 번이라도 받았으면 0이 아닌 수를 반환하게 됨)
	return (len - left);
}
void HostImage()
{
	if (flag == 1) {

		std::cout << "Waiting for client" << std::endl;

		client = accept(server, NULL, NULL);
	}
	int nbyte;
	size_t filesize = 0, bufsize = 0;
	FILE *file = NULL;
	char buf[256];
	char temp[100] = { 0, };
	recv(client, temp, sizeof(temp), 0);
	filesize = atoi(temp);
	bufsize = 256;
	file = fopen("test.png", "w+");
	while (filesize != 0) {
		if (filesize < 256) {
			bufsize = filesize;
			nbyte = recv(client, buf, bufsize, 0);
			filesize = filesize - nbyte;
			if (filesize != 0) {
				std::cout << "이미지 에러" << std::endl;
				break;
			}
			fwrite(buf, sizeof(char), nbyte, file);
			nbyte = 0;
			//cv::Mat HostImg = cv::imread("test.png");
			//imshow("aa", HostImg);
			//cv::waitKey(0);
		}
		nbyte = recv(client, buf, bufsize, 0);
		filesize = filesize - nbyte;
		fwrite(buf, sizeof(char), nbyte, file);
		nbyte = 0;
	}
	fclose(file);
	closesocket(client);


	//cv::Mat HostImg = cv::imread("test.png");
	//imshow("aa", HostImg);
	flag = 1;
	return;
}
/*
void HostImage()
{
   char buff[1024];
   cv::Mat  img = cv::Mat::zeros(512, 512, CV_8UC3);

   while (1) {
	  if (client < 0)
		 std::cout << "ERROR on accept" << std::endl;

	  memset(buff, NULL, sizeof(buff));

	  int  imgSize = img.total()*img.elemSize();
	  char* sockData = new char[imgSize];
	  int bytes = 0;

	  for (int i = 0; i < imgSize; i += bytes) {
		 if ((bytes = recv(client, sockData + i, imgSize - i, 0)) == -1) {
			std::cout << "recv failed";
			return;
		 }
	  }

	  int ptr = 0;
	  for (int i = 0; i < img.rows; i++) {
		 for (int j = 0; j < img.cols; j++) {
			img.at<cv::Vec3b>(i, j) = cv::Vec3b(sockData[ptr + 0], sockData[ptr + 1], sockData[ptr + 2]);
			ptr = ptr + 3;
		 }
	  }

	  imshow("Server", img);
	  cv::waitKey(10);
   }
}
void HostImage()
{
   char *buff = (char*)malloc(sizeof(char) * (512 * 512));
   FILE *output;
   output = fopen("test.jpg", "wb");
   unsigned int readBytes = 0;
   while (true)
   {
	  int ret = recv(client, buff, (512 * 512) - readBytes, 0);
	  if (ret <= 0)
	  {
		 break;
	  }
	  readBytes += ret;
   }


   fwrite(buff, sizeof(char), readBytes, output);
   fclose(output);

   cv::Mat img_2 = cv::imread("test.jpg");
   int n;
   n = recv(client, buff, 512*512, 0);
   if (n < 0) std::cout << "ERROR reading from socket" << std::endl;

   cv::Mat image(512, 512, CV_8UC3, *buff);
   cv::imshow("bb", image);

   cv::waitKey(0);
   return;
}*/
char* serverKey()
{
	char iKey[100];

	memset(iKey, NULL, sizeof(iKey));
	if (flag == 1) {

		client = accept(server, NULL, NULL);
	}
	recv(client, iKey, sizeof(iKey), 0);
	std::cout << "iKey: " << iKey << std::endl;

	closesocket(client);

	flag = 1;
	return iKey;
}

void serverEnd()
{
	closesocket(server);
	::WSACleanup();
}
char* clientMain()
{
	//client
	WSADATA data;
	::WSAStartup(MAKEWORD(2, 2), &data);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client == INVALID_SOCKET)
		std::cout << "클라이언트 생성 실패" << std::endl;

	sockaddr_in addr = { 0 };

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(9000);


	while (1) {
		if (connect(client, (sockaddr *)&addr, sizeof(addr)) != SOCKET_ERROR)
			break;//AfxMessageBox(_T("연결 실패"));
	}
	char iKey[100];

	recv(client, iKey, sizeof(iKey), 0);

	std::cout << iKey << std::endl;


	closesocket(client);
	::WSACleanup();
	return iKey;
}