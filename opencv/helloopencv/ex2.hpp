/*
 * ex2.hpp
 *
 *  Created on: 2014��12��8��
 *      Author: yf
 */

#ifndef HELLOOPENCV_EX2_HPP_
#define HELLOOPENCV_EX2_HPP_





#endif
/* HELLOOPENCV_EX2_HPP_ */
    //-----------------------------------������˵����----------------------------------------------
    //  ��������:����OpenCV���Ž̳�֮�ġ� ROI����ͼ�����&����ͼ���� ȫ����   ����Դ��
    // VS2010��   OpenCV�汾��2.4.8
    //     2014��3��10�� Create by ǳī
    //    ͼƬ�زĳ�����dota2ԭ�� dota2logo
    //     ǳī��΢����@ǳī_ë����
    //------------------------------------------------------------------------------------------------

    //-----------------------------------��ͷ�ļ��������֡�---------------------------------------
    //     ����������������������ͷ�ļ�
    //----------------------------------------------------------------------------------------------
    #include <cv.h>
    #include <highgui.h>
    #include <iostream>

    //-----------------------------------�������ռ��������֡�---------------------------------------
    //     ����������������ʹ�õ������ռ�
    //-----------------------------------------------------------------------------------------------



    //-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
    //     ������ȫ�ֺ�������
    //-----------------------------------------------------------------------------------------------
    bool ROI_AddImage();
    bool LinearBlending();
    bool ROI_LinearBlending();

    //-----------------------------------��main( )������--------------------------------------------
    //     ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
    //-----------------------------------------------------------------------------------------------

    //----------------------------------��ROI_AddImage( )������----------------------------------
    // ��������ROI_AddImage����
    //     ���������ø���Ȥ����ROIʵ��ͼ�����
    //----------------------------------------------------------------------------------------------
    //----------------------------------��ROI_AddImage( )������----------------------------------
    // ��������ROI_AddImage����
    //     ���������ø���Ȥ����ROIʵ��ͼ�����
    //----------------------------------------------------------------------------------------------
    bool ROI_AddImage()
    {

           //��1������ͼ��
           Mat srcImage1= imread("D:\\opecvimg\\dota_pa.jpg");
           Mat logoImage= imread("D:\\opecvimg\\dota_logo.jpg");
           if(!srcImage1.data ) { printf("���ã���ȡsrcImage1����~�� \n"); return false; }
           if(!logoImage.data ) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

           //��2������һ��Mat���Ͳ������趨ROI����
           Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));

           //��3��������ģ�������ǻҶ�ͼ��
           Mat mask= imread("D:\\opecvimg\\dota_logo.jpg",0);

           //��4������Ĥ������ROI
           logoImage.copyTo(imageROI,mask);

           //��5����ʾ���
           namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
           imshow("<1>����ROIʵ��ͼ�����ʾ������",srcImage1);

           return true;
    }


    //---------------------------------��LinearBlending����������-------------------------------------
    // ��������LinearBlending����
    // ����������cv::addWeighted��������ʵ��ͼ�����Ի��
    //--------------------------------------------------------------------------------------------
    bool LinearBlending()
    {
           //��0������һЩ�ֲ�����
           double alphaValue = 0.5;
           double betaValue;
           Mat srcImage2, srcImage3, dstImage;

           //��1����ȡͼ�� ( ����ͼƬ��Ϊͬ�������ͺͳߴ� )
           srcImage2= imread("D:\\opecvimg\\mogu.jpg");
           srcImage3= imread("D:\\opecvimg\\rain.jpg");

           if(!srcImage2.data ) { printf("���ã���ȡsrcImage2����~�� \n"); return false; }
           if(!srcImage3.data ) { printf("���ã���ȡsrcImage3����~�� \n"); return false; }

           //��2������ͼ���ϼ�Ȩ����
           betaValue= ( 1.0 - alphaValue );
           addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

           //��3����������ʾԭͼ����
           namedWindow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", 1);
           imshow("<2>���Ի��ʾ�����ڡ�ԭͼ�� byǳī", srcImage2 );

           namedWindow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", 1);
           imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ�� byǳī", dstImage );

           return true;

    }

    //---------------------------------��ROI_LinearBlending������-------------------------------------
    // ��������ROI_LinearBlending����
    // ���������Ի��ʵ�ֺ���,ָ����������ͼ����.����cv::addWeighted����������϶���
    //                     ����Ȥ����ROI��ʵ���Զ�����������Ի��
    //--------------------------------------------------------------------------------------------
    bool ROI_LinearBlending()
    {

           //��1����ȡͼ��
           Mat srcImage4= imread("D:\\opecvimg\\dota_pa.jpg",1);
           Mat logoImage= imread("D:\\opecvimg\\dota_logo.jpg");

           if(!srcImage4.data ) { printf("���ã���ȡsrcImage4����~�� \n"); return false; }
           if(!logoImage.data ) { printf("���ã���ȡlogoImage����~�� \n"); return false; }

           //��2������һ��Mat���Ͳ������趨ROI����
           Mat imageROI;
                  //����һ
           imageROI=srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));
           //������
           //imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

           //��3����logo�ӵ�ԭͼ��
           addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);

           //��4����ʾ���
           namedWindow("<4>��������ͼ����ʾ������ byǳī");
           imshow("<4>��������ͼ����ʾ������ byǳī",srcImage4);

           return true;
    }
