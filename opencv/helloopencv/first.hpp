/*
 * first.hpp
 *
 *  Created on: 2014��12��7��
 *      Author: yf
 */
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>


#ifndef HELLOOPENCV_FIRST_HPP_
#define HELLOOPENCV_FIRST_HPP_





#endif /* HELLOOPENCV_FIRST_HPP_ */

using namespace cv;

void first(){
	Mat girl=imread("D:\\opecvimg\\ur.jpg"); //����ͼ��Mat
	    namedWindow("����ͼ"); //����һ����Ϊ "��1������ͼ"�Ĵ���
	    imshow("����ͼ",girl);//��ʾ��Ϊ "��1������ͼ"�Ĵ���

	    waitKey();
}
