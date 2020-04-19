#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_cg_sau.h"
#include "r_cg_wdt.h"
#include "r_cg_rtc.h"
#include "device.h"
#include "hum.h"
#include "lora.h"
#include "irc.h"
#include "24cxx.h"
#include "r_cg_adc.h"
#include "r_cg_tau.h"
#include "r_cg_rtc.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "cs123x.h"


  
			
/////////////////////////////////////////get temperature////////////////////////////////////
/////////////////////////////////////////get temperature////////////////////////////////////

static const long temp_tab[] = 
{

	583542,  554647, 526968,  500480, 475159, 450974, 427897, 405892, 384927,  364967, //-55...-46
	345975,  327915, 310751,  294448, 278969, 264279, 250344, 237130, 224603,  212733, //-45...-36
	201487,  190836, 180750,  171201, 162163, 153610, 145516, 137858, 130614,  123761,//-35....-26

	117280,  111149, 105351,  99867 , 94681,   89776,  85137,  80750,  76600,   72676,  // -25 .........-16
	68963 ,  65451 ,  62129,  58986 , 56012,   53198,  50539,  48013,  45627,   43368,   // -15.......... -6
	41229 ,  39204 ,  37285,  35468 , 33747,   32116,  30570,  29105,  27716,   26399,   // -5............4
	25150 ,  23965 ,  22842,  21776 , 20764,   19783,  18892,  18026,  17204,   16423,   //  5.......... 14
	15681 ,  14976 ,  14306,  13669 , 13063,   12487,  11939,  11418,  10921,   10449,    //  15...........24
	10000 ,  9571  ,   9164,  8775  ,  8405,   8052 ,  7716,    7396,   7090,    6798,     // 25...........34
	6520  ,   6255 ,   6002,  5760  ,  5529,    5309,  5098,    4897,   4704,    4521,     //  35..........44
	4345  ,   4177 ,   4016,  3863  ,  3716,    3588,  3440,    3311,   3188,    3069,    // 45...........54
	2956  ,   2848 ,   2744,  2644  ,  2548,    2457,  2369,    2284,   2204,    2126,2051, //  55..........65
	1980  ,    1911,   1845,  1782  ,  1721,    1663,  1606,    1552,   1500, 1450,  //66-75
	1402  ,    1356,   1312,  1269  ,  1228,    1188,  1150,    1113,   1078, 1044,  //76-85
	1011  ,     979,    948,  919   ,   891,     863,   837,     811,    787,  763,   //86-95
	740   ,     718,    697,  676   ,   657,     637,   619,     601,    584,  567,   //96-105
	551   ,     535,    520,  505   ,   491,     477,   464,     451,    439,  427,   //106-115
	415   ,     404,    393,  383   ,   373,     363,   353,     344,    335,  326   //116-125

};



static void delay_us(int t)
{
	while(t>0)
	{
		NOP();NOP();
		t--;
	}
}



int read_time_seg_data_param(void *buf,int len )
{
    return _24cxx_comps.read(MD_TIME_SEG_DATA_PARAM_START_ADDR,buf,len);
}

int save_time_seg_data_param(void const *buf,int len )
{
     return _24cxx_comps.write(MD_TIME_SEG_DATA_PARAM_START_ADDR,buf,len);
}

int read_system_time(void *buf,int len )
{
    return _24cxx_comps.read(MD_SYSTEM_TIME_START_ADDR,buf,len);
}

int save_system_time(void const *buf,int len )
{
     return _24cxx_comps.write(MD_SYSTEM_TIME_START_ADDR,buf,len);
}


int read_calibration_param(void *buf,int len )
{
    return _24cxx_comps.read(MD_CALIBRATION_PARAM_START_ADDR,buf,len);
}
int save_calibration_param(void const *buf,int len )
{
    return _24cxx_comps.write(MD_CALIBRATION_PARAM_START_ADDR,buf,len);
}

int read_res_calibration_param(void *buf,int len )
{
    return _24cxx_comps.read(MD_RES_CALIBRATION_PARAM_START_ADDR,buf,len);
}
int save_res_calibration_param(void const *buf,int len )
{
    return _24cxx_comps.write(MD_RES_CALIBRATION_PARAM_START_ADDR,buf,len);
}

static int read_device_coe(void *buf,int len )
{
    return _24cxx_comps.read(MD_DEVICE_COE_START_ADDR,buf,len);
}

int save_device_coe(void const *buf,int len )
{
    return _24cxx_comps.write(MD_DEVICE_COE_START_ADDR,buf,len);
}


int read_air_leak_param(void *buf,int len )
{
    return _24cxx_comps.read(MD_TIME_AIR_LEAK_PARAM_START_ADDR,buf,len);
}

int save_air_leak_param(void *buf,int len )
{
    return _24cxx_comps.write(MD_TIME_AIR_LEAK_PARAM_START_ADDR,buf,len);
}

int read_report_param(void *buf,int len)
{
     return _24cxx_comps.read(MD_REPORT_PARAM_START_ADDR,buf,len);
}
int save_report_param(void const *buf,int len)
{
    return _24cxx_comps.write(MD_REPORT_PARAM_START_ADDR,buf,len);
}

     
int read_access_param(void *buf,int len)
{
     return _24cxx_comps.read(MD_ACCESS_PARAM_START_ADDR,buf,len);
}
int save_access_param(void const *buf,int len)
{
     return _24cxx_comps.write(MD_ACCESS_PARAM_START_ADDR,buf,len);
}


int read_alarm_param(void *buf,int len)
{
    return _24cxx_comps.read(MD_ALARM_PARAM_START_ADDR,buf,len);
}
 
int save_alarm_param(void const *buf,int len)
{
    return _24cxx_comps.write(MD_ALARM_PARAM_START_ADDR,buf,len);
}

  
int read_device_addr(void *buf,int len)
 {
     return _24cxx_comps.read(MD_DEVICE_ADDR_START_ADDR,buf,len);
 }
 int save_device_addr(void const *buf,int len)
 {
    return _24cxx_comps.write(MD_DEVICE_ADDR_START_ADDR,buf,len);
 }


 static void get_batt()
 {
     unsigned int adc;
     MD_SET_BAT_CTL_ON;
     MD_SET_REF_3030C_OFF;
     delay_us(30);
     ADCE=0;
     delay_us(2);
     ADM2|=0x80;//switch internal vref
     ADM2&=~0x40;  //1.45V
     ADS = _01_AD_INPUT_CHANNEL_1;
     delay_us(10);
     ADCE=1;
     delay_us(2);
     
 
     device_comps.sw._bit.adc_busy=1;
     R_ADC_Start();
     while(device_comps.sw._bit.adc_busy);
     R_ADC_Get_Result(&adc);
     MD_SET_BAT_CTL_OFF;
     ADCE=0;
     
     ADCE=0;       //switch extern vref
     delay_us(2);
     ADM2&=~0x80;
     ADM2|=0x40;
     delay_us(2);
		       
     
     
   #if(MD_DEVICE_BATT ==MD_3_6V)
     device_comps.batt=(unsigned long)435*adc/10230;//0.1V  20k 10k
   #elif(MD_DEVICE_BATT ==MD_4_5V)
     device_comps.batt=(unsigned long)580*adc/10230;//0.1V  30k 10k
   #endif
   hum_comps.dis_oper_mark._bit.refresh_batt_symbol=1;
 }



/////start ntc temp

static  long calc_ad3_average(device_comps_t *const this)
{
    int   i=0;
    const int count=this->ad3_pos;
    unsigned long average=0;
	for(i=0;i<count;i++)
	{
		average+=this-> ad3_convert_result[i];
	}
    average=average*10/count;	
    //free (period);
	return average;
}

static long calc_ntc_valve(device_comps_t *const this)
{
	long  r_std=10000;
	long  ad3_average=this->ad3_average_result;
	long  ntc_valve=(r_std*ad3_average)/(10231-ad3_average);
	return ntc_valve;
}

static int calc_temp(device_comps_t  *const this)
{
    long Tem;
    long LowRValue;
    long HighRValue;        
    long   Tem0;
    int i;
    int  cBottom, cTop;
    int limit=sizeof(temp_tab)/sizeof(temp_tab[0])-1;
    

    if (this->ntc_valve >temp_tab[0])                // ����ֵС�ڱ�����ֵ�����������ޡ�
    {
         return -550;
    }
    if (this->ntc_valve < temp_tab[limit])        // ����ֵ���ڱ������ֵ�������������� ��
    {
        return 1250;
    }
    cBottom = 0; 
    cTop    = limit;
     for (i=limit/2; (cTop-cBottom)!=1; )        // 2�ַ������
    {

       if (this->ntc_valve > temp_tab[i])
        {
            cTop = i;
            i = (cTop + cBottom) / 2;
        }
        else if (this->ntc_valve < temp_tab[i])
        {
            cBottom = i;
            i = (cTop + cBottom) / 2;
        }
        else
        {
            Tem0 = i * 10 - 550;
            Tem = Tem0;
            goto ret;
        }
    }
    Tem0 = i * 10 - 550;
    LowRValue  =temp_tab[cBottom];
    HighRValue = temp_tab[cTop];
    Tem = ( ((this->ntc_valve - LowRValue)*10) / (HighRValue - LowRValue) ) + Tem0;        // ��������5��Ϊһ���ġ�
ret:
    Tem=Tem*this->coe.temp/10000;
    return Tem;
}


////////////////////////////////end get ntc temperature////////////////////////////////////
////////////////////////////////end get ntc temperature////////////////////////////////////



static long calc_temp_p_temp_n_average(device_comps_t *const this)
{
    int   i=0;
    int   j=0;
    const int count=this->temp_p_pos;
    long  temp_var;
    long average=0;
	long difference[32]={0};//=malloc(count*sizeof(float));
	for(i=0;i<count;i++)
	{
		difference[i]=this-> temp_p_convert_result[i]-this-> temp_n_convert_result[i];
	}
    /*
    for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-1-i;j++)
        {
        	if(difference[j]>difference[j+1])
        	{
        		temp_var=difference[j+1];
        		difference[j+1]=difference[j];
        		difference[j]=temp_var;
        	}
        }
    }
    */
    for(i=0;i<count;i++)
	{
		average+=difference[i];
	}	
	average=(average/(count));
	//free (period);
	return average;

}

static long calc_pt_valve(device_comps_t *const this)
{
    
	long delta_y=this->res_calibration_param.y[1]-this->res_calibration_param.y[0];
	long delta_x=this->res_calibration_param.x[1]-this->res_calibration_param.x[0];
    	long pt_valve=delta_y*(this->temp_p_temp_n_average_result-this->res_calibration_param.x[0])/delta_x+this->res_calibration_param.y[0];
	return pt_valve;

}

static int calc_pt_temp(device_comps_t  *const this)
{



}


/////////////////////////////////////////get press////////////////////////////////////





static long  calc_ad1_ad2_average(device_comps_t *const this)
{
    int   i=0;
    int   j=0;
    const int count=this->ad1_pos;
    long  temp_var;
    long average=0;
	long difference[32]={0};//=malloc(count*sizeof(float));
	for(i=0;i<count;i++)
	{
		difference[i]=this-> ad1_convert_result[i]-this-> ad2_convert_result[i];
	}
    /*for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-1-i;j++)
        {
        	if(difference[j]>difference[j+1])
        	{
        		temp_var=difference[j+1];
        		difference[j+1]=difference[j];
        		difference[j]=temp_var;
        	}
        }
    }
    */
    for(i=0;i<count;i++)
	{
		average+=difference[i];
	}	
	average=(average/(count));
	//free (period);
	return average;

}

static  long calc_current_press(device_comps_t *const this)
{
    long delta_v= this->ad1_ad2_average_result;
	long press=0;

    long  LowTValue;
    long  HighTValue;        
    int   i;
    int  Bottom=0;
    int  Top=4-1; //cal 4 points 0-3
    if (delta_v<=device_comps.calibration_param.x[Bottom])               
    {
       // Top=Bottom+1;
       // goto insert_calc;//jmp 2 points insert_calc code
        return press=device_comps.calibration_param.y[Bottom];
    }
    else if (delta_v>device_comps.calibration_param.x[Top])       
    {
        Bottom=Top-1;
        goto insert_calc;
    }
	i=Top/2;
	while(Top-Bottom>1)
	{
        if (delta_v<device_comps.calibration_param.x[i])
        {
            Top = i;
            i = (Top + Bottom) / 2;
        }
        else if (delta_v >device_comps.calibration_param.x[i])
        {
            Bottom = i;
            i = (Top + Bottom) / 2;
        }
        else
        {
            press = device_comps.calibration_param.y[i];
            goto  ret;
        }
    }
insert_calc:
{
    
    LowTValue  = device_comps.calibration_param.x[Bottom];
    HighTValue = device_comps.calibration_param.x[Top];
    press =(long)(
    ((double) (delta_v-LowTValue)*(device_comps.calibration_param.y[Top]-device_comps.calibration_param.y[Bottom]))
    /(HighTValue - LowTValue)
    )
    +device_comps.calibration_param.y[Bottom];
}
ret:
    press-=this->coe.press_clr_value;
	if(press>this->calibration_param.y[3]*1/100)//>fs*1/100.
	{
		press;
	}
	else
	{
		press=0;
	}
	return press*(this->coe.press/10000.);
}


//Algorithm: The actual measured value is less than 4% of full scale and can be cleared. 
//The actual value = current value + cleared value. 
//Because the current value = actual value-clear value

static int clr_press(void)
{
    long actual_value=device_comps.current_press+device_comps.coe.press_clr_value;
    int ret=0;
    if(actual_value>device_comps.calibration_param.y[3]*4/100)//
    {
        ret=1;
    }
    else
    {
        device_comps.coe.press_clr_value=actual_value;
        device_comps.coe.cs=Check_Sum_5A(&device_comps.coe, &device_comps.coe.cs-(unsigned char *)&device_comps.coe);
        device_comps.save_coe(&device_comps.coe,sizeof(device_comps.coe));
    }
    return ret;
}
////////////////////////////////end get press////////////////////////////////////



static void device_comps_output_debug_info(device_comps_t const *const this)
{
	static int line_num=0;
	int tx_num=0;
	memset(this->debug_info,0,sizeof(this->debug_info));
	if(line_num==0)
	{
		
		//start output attribute name(title)
		sprintf(this->debug_info+strlen(this->debug_info),"AD1-AD2\t\t");//
		sprintf(this->debug_info+strlen(this->debug_info),"ad2_pos\t\t");//
		sprintf(this->debug_info+strlen(this->debug_info),"AD3\t\t");//signal_ferq_from_timer_ch0 extern event counter 
		sprintf(this->debug_info+strlen(this->debug_info),"ad3_pos\r\n");//signal_freq
		//end output attribute name(title)
	}
	else
	{
		sprintf(this->debug_info+strlen(this->debug_info),"%05ld\t\t",this->ad1_ad2_average_result);
		sprintf(this->debug_info+strlen(this->debug_info),"%05ld\t\t",this->ad2_pos);
		sprintf(this->debug_info+strlen(this->debug_info),"%05ld\t\t",this->ad3_average_result);
		sprintf(this->debug_info+strlen(this->debug_info),"%05ld\r\n",this->ad3_pos);
		
	}
	line_num++;
	if(line_num>=10)//Output attribute name(title) every 50 lines
	{
		line_num=0; 
	}
	tx_num=strlen(this->debug_info);
	if(tx_num>=sizeof(this->debug_info))
	{
		memset(this->debug_info,0,sizeof(this->debug_info));
		sprintf(this->debug_info,"Write sensor debug output buffer overflow\r\n"); 
		tx_num=strlen(this->debug_info);
	}
	ircComps.write(this->debug_info,tx_num);
	
	
}




static unsigned char device_comps_init(device_comps_t *const this)
{
	/**************START E2PROM TEST********************/
	if(device_comps.sw._bit.e2prom_driver_err)	
	{
		char msg[32]="";// ep2rom low 48bytes use test
		_24cxx_comps.write(0,"this is a e2prom driver test",strlen("this is a e2prom driver test"));
		_24cxx_comps.read (0,msg,strlen("this is a e2prom driver test"));
		if(!strcmp(msg,"this is a e2prom driver test"))
		{
			device_comps.sw._bit.e2prom_driver_err=0;	
		}
		else
		{
			device_comps.sw._bit.e2prom_driver_err=1;
		}
	}
	if(device_comps.sw._bit.cs123x_driver_err)	
	{
		if(!cs123x_comps.Init(0x7c))
		{
            device_comps.sw._bit.cs123x_driver_err=0;
		}
		else
		{
            device_comps.sw._bit.cs123x_driver_err=1;
		}
	}
	/**************END E2PROM TEST********************/
	

	/***********************start other test******************************/
	//TODO
	/**************END other test ********************/
	 #if(MD_PRODUCT_NAME==MD_LORA)
		{
			  if(!(device_comps.sw.All&0x000f)&&loraComps.sw._bit.init_ok)
            	{
            		return 0;
            	}
            	else
            	{
            		return 1;
            	}
		  }
          #elif (MD_PRODUCT_NAME==MD_AIR_LEAK||MD_PRODUCT_NAME==MD_NORMAL)
          {
		if(!(device_comps.sw.All&0x000f))
            	{
            		return 0;
            	}
            	else
            	{
            		return 1;
            	}
	  }
	 #endif
}


static void check_air_param()
{
    if(device_comps.air_leak_param.unit>3)
    {
        device_comps.air_leak_param.unit=0;
    }
    if(device_comps.air_leak_param.Constant_pressure_value>99999)
    {
        device_comps.air_leak_param.Constant_pressure_value=0;
    }
     if(device_comps.air_leak_param.buck_delta_value>99999)
    {
        device_comps.air_leak_param.buck_delta_value=0;
    }
    if(device_comps.air_leak_param.buck_percent>999)
    {
        device_comps.air_leak_param.buck_percent=0;
    }
    if(device_comps.air_leak_param.work_mode>2)
    {
        device_comps.air_leak_param.work_mode=0;
    }
     if(device_comps.air_leak_param.count_direction>1)
    {
        device_comps.air_leak_param.count_direction=0;
    }
    if(device_comps.air_leak_param.delay_timer>9999)
    {
        device_comps.air_leak_param.delay_timer=0;
    }
    if(device_comps.air_leak_param.timer>9999)
    {
        device_comps.air_leak_param.timer=0;
    }
}
static void read_all_param(struct _DEVICE_COMPONENTS  *const this)
{
    if(!device_comps.sw._bit.e2prom_driver_err)
    {
        if(!read_system_time(&device_comps.system_time,sizeof(device_comps.system_time)))
        {
            if(device_comps.system_time.cs!=Check_Sum_5A(&device_comps.system_time, &device_comps.system_time.cs-(unsigned char *)&device_comps.system_time))
            {
                device_comps.system_time.year=0x20;
                device_comps.system_time.month=1;
                device_comps.system_time.day=1;
                device_comps.system_time.hour=0;
                device_comps.system_time.min=0;
                device_comps.system_time.sec=0;
	    }
	    
	    rtc_valve.year=device_comps.system_time.year;
            rtc_valve.month=device_comps.system_time.month;
            rtc_valve.day=device_comps.system_time.day;
            rtc_valve.hour=device_comps.system_time.hour;
            rtc_valve.min=device_comps.system_time.min;
            rtc_valve.sec=device_comps.system_time.sec;
            R_RTC_Set_CounterValue(rtc_valve);	
        }
        
        if(!read_time_seg_data_param(&device_comps.TimeSegData,sizeof(device_comps.TimeSegData)))
        {
            if(device_comps.TimeSegData.cs!=Check_Sum_5A(&device_comps.TimeSegData, &device_comps.TimeSegData.cs-(unsigned char *)&device_comps.TimeSegData))
            {
                device_comps.TimeSegData.store_addr=MD_TIME_SEG_DATA_START_ADDR;
            }
        }

        if(!read_calibration_param(&device_comps.calibration_param,sizeof(device_comps.calibration_param)))
        {
            if(device_comps.calibration_param.cs!=Check_Sum_5A(&device_comps.calibration_param, & device_comps.calibration_param.cs-(unsigned char *)&device_comps.calibration_param))
            {
                device_comps.calibration_param.is_calibrated=0;
                memset(&device_comps.calibration_param,0,sizeof(device_comps.calibration_param));
            }
        }
        if(!read_res_calibration_param(&device_comps.res_calibration_param,sizeof(device_comps.res_calibration_param)))
        {
            if(device_comps.res_calibration_param.cs!=Check_Sum_5A(&device_comps.res_calibration_param, & device_comps.res_calibration_param.cs-(unsigned char *)&device_comps.res_calibration_param))
            {
                device_comps.res_calibration_param.is_calibrated=0;
                memset(&device_comps.res_calibration_param,0,sizeof(device_comps.res_calibration_param));
            }
        }
        if(!read_air_leak_param(&device_comps.air_leak_param,sizeof(device_comps.air_leak_param)))
        {
            if(device_comps.air_leak_param.cs!=Check_Sum_5A(&device_comps.air_leak_param, & device_comps.air_leak_param.cs-(unsigned char *)&device_comps.air_leak_param))
            {
                memset(&device_comps.air_leak_param,0,sizeof(device_comps.air_leak_param));
            }
            check_air_param();
           
        }
        if(!device_comps.read_coe(&device_comps.coe,sizeof(device_comps.coe)))
        {
            if(device_comps.coe.cs!=Check_Sum_5A(&device_comps.coe, &device_comps.coe.cs-(unsigned char *)&device_comps.coe))
            {
                device_comps.coe.press=10000;
                device_comps.coe.temp=10000;
                device_comps.coe.press_clr_value=0;
            }
            if(device_comps.coe.press<7000||device_comps.coe.press>13000)
            {
                device_comps.coe.press=10000;
            }
             if(device_comps.coe.temp<7000||device_comps.coe.temp>13000)
            {
                device_comps.coe.temp=10000;
            }
            if(device_comps.coe.press_clr_value>device_comps.calibration_param.y[3]*4/100)
            {
                device_comps.coe.press_clr_value=0;
            }
        }
        if(!read_alarm_param(&device_comps.alarm_param,sizeof(device_comps.alarm_param)))
        {
            if(device_comps.alarm_param.cs!=Check_Sum_5A(&device_comps.alarm_param, & device_comps.alarm_param.cs-(unsigned char *)&device_comps.alarm_param))
            {
                memset(&device_comps.alarm_param,0,sizeof(device_comps.alarm_param));
            }
        }

        if(!read_report_param(&device_comps.report_param,sizeof(device_comps.report_param)))
        {
            if(device_comps.report_param.cs!=Check_Sum_5A(&device_comps.report_param, & device_comps.report_param.cs-(unsigned char *)&device_comps.report_param))
            {
                device_comps.report_param.min=0;
                device_comps.report_param.hour=3;
                device_comps.report_param.hour_Interval=25;
                device_comps.report_param.disFactor=60;
            }
        }

        if(!read_device_addr(&device_comps.device_addr,sizeof(device_comps.device_addr)))
        {
            if(device_comps.device_addr.cs!=Check_Sum_5A(&device_comps.device_addr, & device_comps.device_addr.cs-(unsigned char *)&device_comps.device_addr))
            {
                const unsigned char default_addr[7]={0x61,0x05,0x01,0x00,0x00,0x00,0x00};
                memcpy(&device_comps.device_addr.addr[0],default_addr,sizeof(device_comps.device_addr.addr));
            }
        }
        if(!read_access_param(&device_comps.access_param,sizeof(device_comps.access_param)))
        {
            if(device_comps.access_param.cs!=Check_Sum_5A(&device_comps.access_param, &device_comps.access_param.cs-(unsigned char *)&device_comps.access_param))
            {
                access_param_t default_access_param=
                {
                    //{180,101,147,115},
                    {117,60,157,137},
                    5683,
                    0
                };
                 memcpy(&device_comps.access_param,&default_access_param,sizeof(device_comps.access_param));
            }
         }
    }
    else
    {
        device_comps.calibration_param.is_calibrated=0;
        device_comps.res_calibration_param.is_calibrated=0;
    }
}

//only use the highlow and low_upper 
static void pressOverloadReport(struct _DEVICE_COMPONENTS  *const this )
{
    long temp=0;
    if((this->calibration_param.unit&0x0f)==this->alarm_param.unit)
    {
        if(this->alarm_param.press_high_lower>0)
        {
            temp=formatData4fixDot(this->current_press);
            if(temp>this->alarm_param.press_high_lower)
            {
                this->PHihgOverTimer++;
                this->PHihgRealseTimer=0;
                if( this->PHihgOverTimer>=40)
                {
                    if(!this->sw._bit.isPHighOverTriggered)
                    {
                        if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
            	        {
                            if(device_comps.batt>30)
                            {
//                                protocolComps.triggerIrq._bit.PHighOver=1;
                                this->sw._bit.isPHighRealseTriggered=0;
                                this->sw._bit.isPHighOverTriggered=1;
                            }
            	        }
                    }
                    this->PHihgOverTimer=0;
                }
            }
            else if((temp<this->alarm_param.press_high_lower-this->alarm_param.press_high_lower/10)&&(this->sw._bit.isPHighOverTriggered))//dealt 10%
            {
                this->PHihgOverTimer=0;
                this->PHihgRealseTimer++;
                if( this->PHihgRealseTimer>=40)
                {
                    if(!this->sw._bit.isPHighRealseTriggered)
                    {
                        if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
            	        {
                            if(device_comps.batt>30)
                            {
 //                               protocolComps.triggerIrq._bit.PHighRealse=1;
                                this->sw._bit.isPHighRealseTriggered=1;
                                this->sw._bit.isPHighOverTriggered=0;
                            }
            	        }
                    }
                    this->PHihgRealseTimer=0;
                }
            }
        }

       if(this->alarm_param.press_low_upper>0)
       {
           if(temp<this->alarm_param.press_low_upper)
           {
               this->PLowLessTimer++;
               this->PLowRealseTimer=0;
               if( this->PLowLessTimer>=40)
               {
                   if(!this->sw._bit.isPLowLessTriggered)
                   {
                       if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
                       {
                           if(device_comps.batt>30)
                           {
//                               protocolComps.triggerIrq._bit.PLowLess=1;
                               this->sw._bit.isPLowRealseTriggered=0;
                               this->sw._bit.isPLowLessTriggered=1;
                           }
                       }
                   }
                   this->PLowLessTimer=0;
               }
           }
           else if((temp>this->alarm_param.press_low_upper+this->alarm_param.press_low_upper/10)&&(this->sw._bit.isPLowLessTriggered))//dealt 10%
           {
               this->PLowLessTimer=0;
               this->PLowRealseTimer++;
               if(this->PLowRealseTimer>=40)
               {
                   if(!this->sw._bit.isPLowRealseTriggered)
                   {
                       if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
                       {
                           if(device_comps.batt>30)
                           {
    //                           protocolComps.triggerIrq._bit.PLowRealse=1;
                               this->sw._bit.isPLowRealseTriggered=1;
                               this->sw._bit.isPLowLessTriggered=0;
                           }
                       }
                   }
                   this->PLowRealseTimer=0;
               }
           }
       }
        
   }

}
static void device_comps_task_handle(void)//Execution interval is 200 ms
{
	int i=0;
	device_comps_t *this=device_comps.this;
	if(this->do_init==1)
	{
		if(this->count<40)
		{
			if(!this->init(this))
			{
				this->do_init=0;
			}
			else
			{
				this->count++;
				hum_comps.dis_oper_mark._bit.refresh_err_code=1;
			}
			
		}
		else
		{
		    #ifdef  MD_IGNORE_ALL_ERR
			    this->do_init=0;
			#else
			    WDTE='R';
			#endif
		}
		if(this->do_init==0)
		{
            cs123x_comps.power_down();
			this->count=0;
			get_batt();
		 
			this->read_all_param(this);
			//TODO
		}
	}
	if(this->do_init==0&&hum_comps.dis_oper_mark._bit.test_ok)
	{
	    static int init_once=1;
	    if(init_once)
	    {
             #if(MD_PRODUCT_NAME==MD_LORA)
    		  {
    			  enter_lora_mode();
    		  }
              #elif (MD_PRODUCT_NAME==MD_AIR_LEAK)
              {
    			  enter_air_leak_mode();
    		  }
    		  #elif (MD_PRODUCT_NAME==MD_NORMAL)
    		  {
                    enter_normal_mode();
    		  }
    		  #endif
    		  init_once=0;
		  }
    }
	
	//if((this->do_init==0)&&(!loraComps.sw._bit.runing))
	if(this->do_init==0)//&&(!loraComps.sw._bit.runing))
	{
		if(this->count==5)//every 1s calc press and temperature
		{
            long ad1_ad3_temp=0;
			this->count=0;
			get_batt();
			
			ad1_ad3_temp=this->ad3_average_result;
            this->ad3_average_result=this->calc_ad3_average(this);
            this->ntc_valve=this->calc_ntc_valve(this);
            this->current_temp_n_2=this->current_temp_n_1;
            this->current_temp_n_1=this->current_temp;
            this->current_temp=this->calc_temp(this);
            ad1_ad3_temp-=this->ad3_average_result;

           // ad1_ad3_temp=this->temp_p_temp_n_average_result;
			//this->ad3_average_result=this->temp_p_temp_n_average_result=this->calc_temp_p_temp_n_average(this);
			// //this->temp_p_temp_n_average_result=this->temp_p_convert_result[0];
			//this->pt_valve=this->calc_pt_valve(this);
			//this->current_temp_n_2=this->current_temp_n_1;
            //this->current_temp_n_1=this->current_temp;
			//this->current_temp=this->calc_pt_temp(this);
            //ad1_ad3_temp-=this->temp_p_temp_n_average_result;
			
			if(ad1_ad3_temp<0)
			{
                ad1_ad3_temp=-ad1_ad3_temp;
			}
			if(ad1_ad3_temp>2)
			{
                 device_comps.sw._bit.temp_adc_stb=0;
			}
			else
			{
                 device_comps.sw._bit.temp_adc_stb=1;
			}
			
	    
			hum_comps.dis_oper_mark._bit.refresh_temp=1;
			hum_comps.dis_oper_mark._bit.refresh_temp_adc=1;
			
			
        

            ad1_ad3_temp=this->ad1_ad2_average_result;
			this->ad1_ad2_average_result=this->calc_ad1_ad2_average(this);
			//this->ad1_ad2_average_result=this->ad1_convert_result[0];
			ad1_ad3_temp-=this->ad1_ad2_average_result;
			if(ad1_ad3_temp<0)
			{
                ad1_ad3_temp=-ad1_ad3_temp;
			}
			if(ad1_ad3_temp>2)
			{
                 device_comps.sw._bit.adc_stb=0;
			}
			else
			{
                 device_comps.sw._bit.adc_stb=1;
			}
			this->current_press_n_2=this->current_press_n_1;
			this->current_press_n_1=this->current_press;
			this->current_press=this->calc_current_press(this);
			pressOverloadReport(this);
			if(this->current_press>this->calibration_param.y[3])
			{
				device_comps.sw._bit.over_range=1;
			}
			else
			{
                device_comps.sw._bit.over_range=0;
			}
			
			hum_comps.dis_oper_mark._bit.refresh_press=1;
			hum_comps.dis_oper_mark._bit.refresh_press_adc=1;

			
			this->ad3_pos=0;
			this->ad1_pos=0;
			this->ad2_pos=0;
			this->temp_p_pos=0;
			this->temp_n_pos=0;
		 
		}
       
        MD_SET_REF_3030C_ON;
        


      
       delay_us(100);//400
       cs123x_comps.restart();
       NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
       while(MD_CS123X_DATA);
       //cs123x_comps.write_reg(&this->ad1_convert_result[this->ad1_pos++],0x7d);
         cs123x_comps.read_adc(&this->ad1_convert_result[this->ad1_pos++]);
//       NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
//       while(MD_CS123X_DATA);
//       cs123x_comps.write_reg(&this->temp_p_convert_result[this->temp_p_pos++],0x7c);
         cs123x_comps.power_down();
       
	       
//        	R_ADC_Set_OperationOff();
//	        delay_us(40);
//	        ADM2&=~0x80;
//	        ADM2|=0x40;
//	        delay_us(40);
		
                ADS = _01_AD_INPUT_CHANNEL_1;
	        R_ADC_Set_OperationOn();
	        delay_us(2);
		
		device_comps.sw._bit.adc_busy=1;
		R_ADC_Start();
		while(device_comps.sw._bit.adc_busy);
		R_ADC_Get_Result(&this->ad3_convert_result[this->ad3_pos++]);

		
	/*
		ADS = _10_AD_INPUT_CHANNEL_16;
		delay_us(2);
		device_comps.sw._bit.adc_busy=1;
		R_ADC_Start();
		while(device_comps.sw._bit.adc_busy);
		R_ADC_Get_Result(&this->ad1_convert_result[this->ad1_pos++]);

		
		
		ADS = _14_AD_INPUT_CHANNEL_20;
		delay_us(2);
		device_comps.sw._bit.adc_busy=1;
		R_ADC_Start();
		while(device_comps.sw._bit.adc_busy);
        	R_ADC_Get_Result(&this->ad2_convert_result[this->ad2_pos++]);


	        ADS = _10_AD_INPUT_CHANNEL_16;
		delay_us(2);
		device_comps.sw._bit.adc_busy=1;
		R_ADC_Start();
		while(device_comps.sw._bit.adc_busy);
		R_ADC_Get_Result(&this->temp_p_convert_result[this->temp_p_pos++]);

		
		
		ADS = _14_AD_INPUT_CHANNEL_20;
		delay_us(2);
		device_comps.sw._bit.adc_busy=1;
		R_ADC_Start();
		while(device_comps.sw._bit.adc_busy);
		R_ADC_Get_Result(&this->temp_n_convert_result[this->temp_n_pos++]);
        
      */ 
	R_ADC_Set_OperationOff();
        MD_SET_REF_3030C_OFF;
		
        this->count++;
	}
}

static void nop(void)
{
    NOP();
}


device_comps_t device_comps=
{
	"device comps",                //char *desc;
    &device_comps,     //struct _DEVICE_COMPONENTS  *const this;
    1,//   int   do_init;//Whether to initialize,1:init 0,no init
    device_comps_init,//    unsigned char (*const init)(struct _DEVICE_COMPONENTS *);
    0,//    unsigned long count;            //Called counter


    {3}, //union sw;  e2prom fault +cs123x err
    
   0, //int PHihgOverTimer;
   0,// int PHihgRealseTimer;
   0, //int PLowLessTimer;
   0,// int PLowRealseTimer;

    {0},//    unsigned int  ad1_convert_result[MD_ADC_MAX_POS];
    0,//   unsigned int  ad1_pos;
    {0},//   unsigned int  ad2_convert_result[MD_ADC_MAX_POS];
    0,//   unsigned int  ad2_pos;
    0,//long          ad1_ad2_average_result;//(ad1-ad2)/ad1_pos

   {0}, //unsigned int  temp_p_convert_result[MD_ADC_MAX_POS];
	0,//unsigned int  temp_p_pos;
	{0},//unsigned int  temp_n_convert_result[MD_ADC_MAX_POS];
	0,//unsigned int  temp_n_pos;
	0,//long          temp_p_temp_n_average_result;//(temp_p_convert_result-temp_n_convert_result)/temp_p_pos
	
    {0}, //  unsigned int  ad3_convert_result[MD_ADC_MAX_POS];
    0, // unsigned int  ad3_pos;
    0,//unsigned long ad3_average_result



    10000,//     float ntc_valve;
    calc_ad3_average,//unsigned long ( * const calc_ad3_average)(struct _DEVICE_COMPONENTS  *const);
    calc_ntc_valve,    //float ( * const calc_ntc_valve)(struct _DEVICE_COMPONENTS  *const);//point to function calc_pt1000( device_comps_t *const this) whith param adc_result[][] 
    calc_temp,//      long  ( * const calc_temp)  (struct _DEVICE_COMPONENTS     *const);//point to function calc_temp( sensor_comp_t *const this)with param pt1000_valve

   100,
    calc_temp_p_temp_n_average,
    calc_pt_valve,
    calc_pt_temp,
    0,//     long  current_temp;
    0,//     long  current_temp_n_1;
    0,//     long  current_temp_n_2;

   
	calc_ad1_ad2_average,//long ( *const calc_ad1_ad2_average)(struct _DEVICE_COMPONENTS *const ); //point to calc_signal_period(sensor_comp_t *const this)
	calc_current_press,//     unsigned long ( *const calc_current_press)(struct _DEVICE_COMPONENTS *const ); //point to calc_signal_period(sensor_comp_t *const this)
    0,//     long  current_press;  //Yn
    0,//     long  current_press_n_1;//Yn-1
    0,//     long  current_press_n_2;//Yn-2

    {           //struct 
        10000,  //{ int press;
        10000,   //  int temp;  
        0        //   long press_clr_value 
    },         //}coe;
    read_device_coe,
    save_device_coe,  
    clr_press,
    
    0,//     unsigned int batt;//batt voltage

    {{0},{0},{0},{0},0,0,0,0}, //struct calibration_param 
 	{{0},{0},{0},{0},0,0,0,0},//struct calibration_param_bak 
 	0,// cal_type
 	read_calibration_param,//     int (*read_calibration_param)(void *,int );
    save_calibration_param,//     int (*save_calibration_param)(void const *,int);


    {{0},{0},{0},{0},0,0,0,0}, //struct res_calibration_param 
    {{0},{0},{0},{0},0,0,0,0},//struct res_calibration_param_bak 
    read_res_calibration_param,//     int (*read_res_calibration_param)(void *,int );
    save_res_calibration_param,//     int (*save_res_calibration_param)(void const *,int);

    {0},   //struct report_parm;
    read_report_param,//  int (*read_report_param)(void *,int);
    save_report_param,//  int (*save_report_param)(void const *,int);

    {{0},0,0},   //struct access_parm;
    read_access_param,//   int (*read_access_param)(void *,int);
    save_access_param,//   int (*save_access_param)(void const *,int);


    {0},// struct alarm_param;
    read_alarm_param,// int (*read_alarm_param)(void *,int);
    save_alarm_param,//int (*save_alarm_param)(void const *,int);

    {{0},0},//unsigned char addr[7];
    read_device_addr,// int (*read_device_addr)(void *,int);
    save_device_addr,//int (*save_device_addr)(void const *,int);

    { MD_TIME_SEG_DATA_START_ADDR,"",0},//TimeSegData_t TimeSegData;
    read_time_seg_data_param,
    save_time_seg_data_param,

    {0},
    read_system_time,
    save_system_time,

    {0},
    read_air_leak_param,
    save_air_leak_param,

    { {0},
      0
    },
    0,//int report_interval_timer;
    0,//_1s_timr_acc

    read_all_param,//void (*read_all_param)(struct _DEVICE_COMPONENTS  *const);

	device_comps_output_debug_info,//void  ( *const output_debug_info)(struct _DEVICE_COMPONENTS   *const);//point to sensor_comps_output_debug_info(device_comps_t const *const this)
	"",                     //char debug_info[128];
	device_comps_task_handle,//void  ( *const task_handle)(void);//point to device_comps_task_handle
};



void GSMReturnTimeChk(unsigned char RHur,unsigned char RMin,unsigned char RSec)
{
	unsigned int cmp=device_comps.report_param.hour_Interval;//((unsigned int)GSM.ReturnCecle[0]<<8)+GSM.ReturnCecle[1];
    if(cmp==0)
	{
		cmp=1;
	}
	if(device_comps.report_interval_timer>=(unsigned long)cmp*60)
    {
		unsigned char reltSec=((RSec>>4)*10+(RSec&0x0f)) +60-((rtc_valve.sec>>4)*10+(rtc_valve.sec&0x0f));
		unsigned char reltMin=((RMin>>4)*10+(RMin&0x0f)) +60-1-((rtc_valve.min>>4)*10+(rtc_valve.min&0x0f));
		unsigned char reltHur=((RHur>>4)*10+(RHur&0x0f)) +24-1-((rtc_valve.hour>>4)*10+(rtc_valve.hour&0x0f));
		unsigned char equSec= reltSec%60;
		unsigned char equMin=(reltMin+(reltSec/60))%60;
		unsigned char equHur=(reltHur+((reltMin+(reltSec/60))/60))%24;
		unsigned long InterTimer=(unsigned long)equHur*3600+   (unsigned long)equMin*60    +(unsigned long)equSec;
	     if(InterTimer>(unsigned long)5*60) 
		{
			 if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
	        {
                if(device_comps.batt>30)
                {
   //                 protocolComps.triggerIrq._bit.intervalTime=1;
                }
	        }
	    }
	    device_comps.report_interval_timer=0;
	}
}
void CalcReportTime(unsigned char *hur,unsigned char *min,unsigned char *sec)
{
	unsigned long  DisPerTimeTotalSecond=(unsigned long)((device_comps.device_addr.addr[6]>>4)*10+(device_comps.device_addr.addr[6]&0x0f))* device_comps.report_param.disFactor;
	unsigned long  Min=DisPerTimeTotalSecond/60;
	unsigned long  DisPerTimehur=Min/60;
	unsigned long  DisPerTimeMin=Min%60;//min
	
	*sec=DisPerTimeTotalSecond%60;
	*min=(device_comps.report_param.min+DisPerTimeMin)%60;
	*hur=(device_comps.report_param.hour+DisPerTimehur+(device_comps.report_param.min+DisPerTimeMin)/60)%24;
	
	*sec=(*sec/10<<4)+(*sec%10);
	*min=(*min/10<<4)+(*min%10);
	*hur=(*hur/10<<4)+(*hur%10);
}

void  Timing_interval_report(void)
{
    unsigned char ReportHur;
	unsigned char ReportMin;
	unsigned char ReportSec;
	unsigned char ReportMin_30=ReportMin;
	unsigned char temp[7];
    CalcReportTime(&ReportHur,&ReportMin,&ReportSec);
    if(rtc_valve.sec == ReportSec)
	{	
		device_comps.report_interval_timer++;
        if((ReportHur==rtc_valve.hour)&&(ReportMin==rtc_valve.min))
        {
	        device_comps.report_interval_timer=0;
	        if((device_comps.device_addr.addr[4]!=0)&&(device_comps.device_addr.addr[3]!=0))
	        {
                if(device_comps.batt>30)
                {
   //                 protocolComps.triggerIrq._bit.timeAuto=1;
                }
	        }
	     }
		//GSMReturnTimeChk(ReportHur,ReportMin,ReportSec); //����ϱ�ʱ�䣬�������ָ���ϱ�ʱ�䣬��ϵͳ��ʼ�ϱ�����//	

        ReportMin_30+=0x30;
        if(ReportMin_30>=0x60)
        {
            ReportMin_30-=0x60;
        }
		if(rtc_valve.min == ReportMin  || rtc_valve.min == ReportMin_30)
		{
			if(1)
			{
				unsigned int StoreAddr=device_comps.TimeSegData.store_addr;
				
				if((StoreAddr>= MD_TIME_SEG_DATA_START_ADDR )&&(StoreAddr<=MD_TIME_SEG_DATA_END_ADDR-4))
				{
                    _24cxx_comps.write(StoreAddr,&device_comps.current_press,4);
					
					StoreAddr+=4;
					if(StoreAddr>=MD_TIME_SEG_DATA_END_ADDR)
					{
					        StoreAddr=MD_TIME_SEG_DATA_START_ADDR;
					}
					device_comps.TimeSegData.store_addr=StoreAddr;

					
                	temp[0]=0x20;
                	temp[1]=rtc_valve.year;
                	temp[2]=rtc_valve.month;
                	temp[3]=rtc_valve.day;
                	temp[4]=rtc_valve.hour;
                    temp[5]=rtc_valve.min;
                	temp[6]=rtc_valve.sec;
					
					memcpy(device_comps.TimeSegData.lastSampleTime,&temp,sizeof(device_comps.TimeSegData.lastSampleTime));
					device_comps.TimeSegData.cs=Check_Sum_5A(&device_comps.TimeSegData, &device_comps.TimeSegData.cs-(unsigned char *)&device_comps.TimeSegData);
					device_comps.save_time_seg_data_param(&device_comps.TimeSegData,sizeof(device_comps.TimeSegData));
				}
				else
				{
					StoreAddr=MD_TIME_SEG_DATA_START_ADDR;
					device_comps.TimeSegData.store_addr=StoreAddr;
					device_comps.TimeSegData.cs=Check_Sum_5A(&device_comps.TimeSegData, &device_comps.TimeSegData.cs-(unsigned char *)&device_comps.TimeSegData);
					device_comps.save_time_seg_data_param(&device_comps.TimeSegData,sizeof(device_comps.TimeSegData));
				}
			}
		}
	}
}

static long format_all_set_unit()
{
    long num;
    if(device_comps.air_leak_param.work_mode==0)
    {
       if(device_comps.air_leak_param.unit==2)//psi
       {
             num=device_comps.air_leak_param.Constant_pressure_value*100/145.0377439;
       }
       else if(device_comps.air_leak_param.unit==0)
       {
            if((device_comps.calibration_param.unit&0x0f)==1)
            {
                if(device_comps.calibration_param.dot==3)
                {
                    num=device_comps.air_leak_param.Constant_pressure_value*10;
                }
            }
            else
            {
                num=device_comps.air_leak_param.Constant_pressure_value;
            }
       }
       else
       {
            num=device_comps.air_leak_param.Constant_pressure_value;
       }
    }
    else if(device_comps.air_leak_param.work_mode==1)
    {
       if(device_comps.air_leak_param.unit==2)//psi
       {
             num=device_comps.air_leak_param.buck_delta_value*100/145.0377439;
       }
       else if(device_comps.air_leak_param.unit==0)
       {
            if((device_comps.calibration_param.unit&0x0f)==1)
            {
                if(device_comps.calibration_param.dot==3)
                {
                    num=device_comps.air_leak_param.buck_delta_value*10;
                }
            }
            else
            {
                num=device_comps.air_leak_param.buck_delta_value;
            }
       }
       else
       {
            num=device_comps.air_leak_param.buck_delta_value;
       }
       
       num=device_comps.air_leak.ref_press-num;
       
    }
    else if(device_comps.air_leak_param.work_mode==2)
    {
        num=device_comps.air_leak.ref_press-device_comps.air_leak.ref_press*device_comps.air_leak_param.buck_percent/1000.;;
    }
    return num;
}
static int air_leak_mode_check_warn()//return 1,warn
{
    long press_set_format_valve=device_comps.air_leak.press_set_format_valve;
    long current_press_format=device_comps.current_press/10;
    return current_press_format<=press_set_format_valve;
}

void _1s_task_handle(void)
{
    R_WDT_Restart();
    if(hum_comps.current_mode!=EM_SELF_TEST_MODE)
    {
        device_comps._1s_timr_acc++;
    	if(device_comps._1s_timr_acc>9)
    	{
    		
    		 device_comps._1s_timr_acc=0;
    	}
    	
        R_RTC_Get_CounterValue(&rtc_valve);
       #if(MD_PRODUCT_NAME==MD_NBIOT)
	    Timing_interval_report();
	   #endif
	    if(rtc_valve.min==0x21&&rtc_valve.sec==0x21)
	    {
             //save systemtime();
	    }
	    hum_comps.dis_oper_mark._bit.refresh_time=1;
	    hum_comps.dis_oper_mark._bit.refresh_date=1; 
        if( (ircComps.op_window_time>0)&&(hum_comps.current_mode!=EM_CAL_MODIFY_MODE))
		{
			ircComps.op_window_time--;
			if(ircComps.op_window_time==0)
			{
				ircComps.sw._bit.runing=0;

				#ifndef MD_MODBUS
    				disable_irc_receive();
    				disable_irc_send();
				#endif
				MD_IR_VCM_OFF; 
			}
		}
	
//		if(protocolComps.timer>0)
//		{
//		    protocolComps.timer--;
//		}

//	    if(netComps.op_window_time>0)
//	    {
//	        netComps.op_window_time--;
//	    }
//
//	    if(netComps.AckTmr>0)
//	    {
//	        netComps.AckTmr--;
//	    }

	    if(hum_comps.current_mode==EM_LORA_MODE||hum_comps.current_mode==EM_AIR_LEAK_MODE
	       ||hum_comps.current_mode==EM_NORMAL_MODE)
	    {
	        if(mode_comps[hum_comps.current_mode].displayTimer>0&&mode_comps[hum_comps.current_mode].dis_option!=0)
	        {
	            mode_comps[hum_comps.current_mode].displayTimer--;
	            if(!mode_comps[hum_comps.current_mode].displayTimer)
	            {
	                  #if(MD_PRODUCT_NAME==MD_LORA)
            		  {
            			  enter_lora_mode();
            		  }
                      #elif (MD_PRODUCT_NAME==MD_AIR_LEAK)
                      {
            			  enter_air_leak_mode();
            		  }
            		  #elif (MD_PRODUCT_NAME==MD_NORMAL)
            		  {
                            //enter_normal_mode();
            		  }
            		  #endif
	            }
	        }
	    }
	    
	    if(hum_comps.current_mode==EM_DEBUG_MODE)
	    {
            if(mode_comps[hum_comps.current_mode].displayTimer>0)
	        {
                mode_comps[hum_comps.current_mode].displayTimer--;
                if(!mode_comps[hum_comps.current_mode].displayTimer)
                {
	                 #if(MD_PRODUCT_NAME==MD_LORA)
            		  {
            			  enter_lora_mode();
            		  }
                      #elif (MD_PRODUCT_NAME==MD_AIR_LEAK)
                      {
            			  enter_air_leak_mode();
            		  }
            		  #elif (MD_PRODUCT_NAME==MD_NORMAL)
            		  {
                            enter_normal_mode();
            		  }
            		  #endif
	            }
	        }
	    }
	    
	    
	    if(device_comps.air_leak.sw._bit.count_en)
	    {
	            if(device_comps.air_leak.delay_timer>0)
	            {
	                device_comps.air_leak.delay_timer--;
	                if(device_comps.air_leak.delay_timer==0)
	                {
	                    device_comps.air_leak.ref_press=device_comps.current_press/10;
	                    device_comps.air_leak.press_set_format_valve=format_all_set_unit();
	                }
	            }
	            else
	            {
	    	        if(device_comps.air_leak_param.count_direction==0)//up count
	                {
	                    
	                    if(device_comps.air_leak.timer<device_comps.air_leak_param.timer)
	                    {
                            if(!air_leak_mode_check_warn())
                            {
	                            device_comps.air_leak.timer++;
	                        }
	                        else
	                        {
                                device_comps.air_leak.sw._bit.count_en=0;
                                device_comps.air_leak.sw._bit.isWarn=1;
                                device_comps.air_leak.sw._bit.test_finished=1;
	                        }
	                    }
	                    else
	                    {
	                        device_comps.air_leak.sw._bit.count_en=0;
	                        device_comps.air_leak.sw._bit.isWarn=0;
	                        device_comps.air_leak.sw._bit.test_finished=1;
	                    }
	                }
	                else if(device_comps.air_leak_param.count_direction==1)//down count
	                {
	                    if(device_comps.air_leak.timer>0)
	                    {
	                        if(!air_leak_mode_check_warn())
                            {
	                            device_comps.air_leak.timer--;
	                        }
	                        else
	                        {
                                device_comps.air_leak.sw._bit.count_en=0;
                                device_comps.air_leak.sw._bit.isWarn=1;
                                device_comps.air_leak.sw._bit.test_finished=1;
	                        }
	                    }
	                    else
	                    {
	                        device_comps.air_leak.sw._bit.count_en=0;
	                        device_comps.air_leak.sw._bit.isWarn=0;
	                        device_comps.air_leak.sw._bit.test_finished=1;
	                    }
	                }
	            }
		    hum_comps.dis_oper_mark._bit.air_leak_mode_refresh_timer=1;
		}
	}
}