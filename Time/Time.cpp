    #include <iostream>  
    #include <windows.h>  
    #include "Calculator.h"
    using namespace std;  
      
    int main()  
    {  
        LARGE_INTEGER Frequency;//计数器频率  
        LARGE_INTEGER start_PerformanceCount;//起始计数器  
        LARGE_INTEGER end_PerformanceCount;//结束计数器  
        double run_time; //运行时间  
        QueryPerformanceFrequency(&Frequency);   
           Calculator *calculator=new Calculator();
        for (int i = 0 ; i < 10 ; ++i )  
        {  
              
            QueryPerformanceCounter(&start_PerformanceCount);   
              
            //运行测试的代码  
            Sleep(10);  
           
            calculator->cal();
              
            QueryPerformanceCounter(&end_PerformanceCount);   
            run_time = ( end_PerformanceCount.QuadPart - start_PerformanceCount.QuadPart ) / (double)Frequency.QuadPart;  
            cout<<run_time<<endl;  
        }  
          
        return 0;  
    }  
