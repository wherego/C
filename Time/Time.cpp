    #include <iostream>  
    #include <windows.h>  
    #include "Calculator.h"
    using namespace std;  
      
    int main()  
    {  
        LARGE_INTEGER Frequency;//������Ƶ��  
        LARGE_INTEGER start_PerformanceCount;//��ʼ������  
        LARGE_INTEGER end_PerformanceCount;//����������  
        double run_time; //����ʱ��  
        QueryPerformanceFrequency(&Frequency);   
           Calculator *calculator=new Calculator();
        for (int i = 0 ; i < 10 ; ++i )  
        {  
              
            QueryPerformanceCounter(&start_PerformanceCount);   
              
            //���в��ԵĴ���  
            Sleep(10);  
           
            calculator->cal();
              
            QueryPerformanceCounter(&end_PerformanceCount);   
            run_time = ( end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart ) / (double)Frequency.QuadPart;  
            cout<<run_time<<endl;  
        }  
          
        return 0;  
    }  
