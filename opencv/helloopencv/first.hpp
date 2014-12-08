/*
 * first.hpp
 *
 *  Created on: 2014年12月7日
 *      Author: yf
 */
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>


#ifndef HELLOOPENCV_FIRST_HPP_
#define HELLOOPENCV_FIRST_HPP_





#endif /* HELLOOPENCV_FIRST_HPP_ */

using namespace cv;

void first(){
	Mat girl=imread("D:\\opecvimg\\ur.jpg"); //载入图像到Mat
	    namedWindow("动漫图"); //创建一个名为 "【1】动漫图"的窗口
	    imshow("动漫图",girl);//显示名为 "【1】动漫图"的窗口

	    waitKey();
}
