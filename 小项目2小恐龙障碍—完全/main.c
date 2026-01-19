
//																							小恐龙障碍赛抽象版
//																							小恐龙障碍赛抽象版
//																							小恐龙障碍赛抽象版
//																							小恐龙障碍赛抽象版
//																							小恐龙障碍赛抽象版


#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"
#include "delay.h"

unsigned char point;
unsigned char keynum;
unsigned char dragonspace=1;//龙状态（1在地0在天）
unsigned char obstruction=16;//障碍物
unsigned char counter=0;//陷阱计数
unsigned char speed=3;//陷阱速度计数
unsigned char cut=5;//关卡分界限度

void main()
{
	home:point=0;cut=5;speed=3;//分归零，界限回归标准，速度回归标准
	
	LCD_Init();
	LCD_ShowString(1,1,"                ");
	LCD_ShowString(2,1,"                ");
	LCD_ShowString(2,1,"i_______________");
	LCD_ShowString(1,10,"point");
	while(1)
	{
		keynum=MatrixKey();//矩阵数给
		
		if(keynum==1&&dragonspace==1)
		{
			dragonspace=0;//龙在天
			LCD_ShowChar(2,1,'_');
			LCD_ShowChar(1,1,'i');
			LCD_ShowString(1,4,"jump!");//! is 7
			
			counter=0;
		}	
		
		counter++;
		
		if(counter>=speed)//陷阱速度计数
		{
				counter=0;//回收counter
				if(obstruction<16)//清理前面的障碍
				{
				LCD_ShowString(2,obstruction,"_");
				}
				obstruction--;//移动
				if(obstruction==0)//重新出现
				{
				obstruction=16;
				}
				if(obstruction<16)//显示陷阱
				{
				LCD_ShowChar(2,obstruction,'#');
				}	
				
				if(dragonspace==0)
				{
					static unsigned char jumpcount=0;//跳跃计数器防delay
					jumpcount++;
					if(jumpcount>=2)
					{
						jumpcount=0;
						dragonspace=1;
						LCD_ShowChar(1,1,' ');//清地龙
						LCD_ShowChar(2,1,'i');//显龙
						LCD_ShowString(1,4,"     ");//清jump
					}
				}
		 }
		if(dragonspace==1&&obstruction==1)//失败部分
		{
			LCD_Init();
			LCD_ShowString(1, 1,"game over");
			while(1)
			{
				Delay(1);
				keynum=MatrixKey();
				if(keynum==2)
				{
					goto home;
				}
			 Delay(1);
			}	
		}
		if(dragonspace==0&&obstruction==1)//过后加分
		{
			point++;
			LCD_ShowNum(1,15,point,2);
		}
		if(point>=cut)
		{
			speed--;
			cut+=5;
		}
		if(point==20)
		{
			LCD_Init();
			LCD_ShowString(1, 1,"you win");//胜利部分
			while(1)
			{
				Delay(1);
				keynum=MatrixKey();
				if(keynum==2)
				{
					goto home;
				}
			 Delay(1);
			}
		}
		 
		Delay(150);		
	  }
}
