#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>

#include <sys/stat.h> 
// open 
#include <fcntl.h>	
// open
#include <errno.h>
#include <string.h>

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#pragma comment (lib , "ws2_32.lib")


void HostImage();
void showError(const char * msg);

void serverMain();

char* serverKey();

void serverEnd();

char* clientMain();