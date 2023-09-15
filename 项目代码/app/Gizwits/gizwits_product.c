/**
************************************************************
* @file         gizwits_product.c
* @brief        Control protocol processing, and platform-related hardware initialization
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         閺堢儤娅ゆ禍锟�.閸欘亙璐熼弲楦垮厴绾兛娆㈤懓宀�鏁�
*               Gizwits Smart Cloud  for Smart Products
*               闁剧偓甯磡婢х偛锟借淳绁欏锟介弨绶楁稉顓犵彌|鐎瑰鍙弢閼奉亝婀亅閼奉亞鏁眧閻㈢喐锟斤拷
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "driver/hal_key.h"
#define HC595_SCK(x) GPIO_OUTPUT_SET(GPIO_ID_PIN(14), x)
#define HC595_RCK(x) GPIO_OUTPUT_SET(GPIO_ID_PIN(13), x)
#define HC595_DATA(x) GPIO_OUTPUT_SET(GPIO_ID_PIN(12), x)
/** User area The current device state structure */
dataPoint_t currentDataPoint;
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
uint8_t relay_data[]={0,0,0,0,0,0,0,0};
void Ctrl_74hc595(uint8_t data[]){
	int i=7;
	HC595_RCK(0);
	os_delay_us(1);
	for(i=8;i>=0;i--){
		HC595_SCK(0);
		os_delay_us(1);
		if(data[i]==0){
			HC595_DATA(0);
		}else{
			HC595_DATA(1);
		}
		os_delay_us(1);
		HC595_SCK(1);
	}
	os_delay_us(1);
	HC595_RCK(1);
}
void All_relay_on(uint8_t data[]){
	int i=0;
	for(i=0;i<8;i++){
		data[i]=1;
	}
}
int8_t ICACHE_FLASH_ATTR gizwitsEventProcess(eventInfo_t *info, uint8_t *data, uint32_t len)
{
    uint8_t i = 0;
    dataPoint_t * dataPointPtr = (dataPoint_t *)data;
    moduleStatusInfo_t * wifiData = (moduleStatusInfo_t *)data;

    if((NULL == info) || (NULL == data))
    {
        GIZWITS_LOG("!!! gizwitsEventProcess Error \n");
        return -1;
    }

    for(i = 0; i < info->num; i++)
    {
        switch(info->event[i])
        {
        case EVENT_ALL_RELAY_ON :
            currentDataPoint.valueALL_RELAY_ON = dataPointPtr->valueALL_RELAY_ON;
            GIZWITS_LOG("Evt: EVENT_ALL_RELAY_ON %d \n", currentDataPoint.valueALL_RELAY_ON);
            if(0x01 == currentDataPoint.valueALL_RELAY_ON)
            {
                //user handle
            	All_relay_on(relay_data);
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueRELAY_1_ONOFF=1;
            	currentDataPoint.valueRELAY_2_ONOFF=1;
            	currentDataPoint.valueRELAY_3_ONOFF=1;
            	currentDataPoint.valueRELAY_4_ONOFF=1;
            	currentDataPoint.valueRELAY_5_ONOFF=1;
            	currentDataPoint.valueRELAY_6_ONOFF=1;
            	currentDataPoint.valueRELAY_7_ONOFF=1;
            	currentDataPoint.valueRELAY_8_ONOFF=1;
            }
            else
            {
                //user handle
            }
            break;
        case EVENT_RELAY_1_ONOFF :
            currentDataPoint.valueRELAY_1_ONOFF = dataPointPtr->valueRELAY_1_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_1_ONOFF %d \n", currentDataPoint.valueRELAY_1_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_1_ONOFF)
            {
                //user handle
            	relay_data[0]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
            	relay_data[0]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
                //user handle
            }
            break;
        case EVENT_RELAY_2_ONOFF :
            currentDataPoint.valueRELAY_2_ONOFF = dataPointPtr->valueRELAY_2_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_2_ONOFF %d \n", currentDataPoint.valueRELAY_2_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_2_ONOFF)
            {
                //user handle
            	relay_data[1]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[1]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_3_ONOFF :
            currentDataPoint.valueRELAY_3_ONOFF = dataPointPtr->valueRELAY_3_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_3_ONOFF %d \n", currentDataPoint.valueRELAY_3_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_3_ONOFF)
            {
                //user handle
            	relay_data[2]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[2]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_4_ONOFF :
            currentDataPoint.valueRELAY_4_ONOFF = dataPointPtr->valueRELAY_4_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_4_ONOFF %d \n", currentDataPoint.valueRELAY_4_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_4_ONOFF)
            {
                //user handle
            	relay_data[3]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[3]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_5_ONOFF :
            currentDataPoint.valueRELAY_5_ONOFF = dataPointPtr->valueRELAY_5_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_5_ONOFF %d \n", currentDataPoint.valueRELAY_5_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_5_ONOFF)
            {
                //user handle
            	relay_data[4]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[4]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_6_ONOFF :
            currentDataPoint.valueRELAY_6_ONOFF = dataPointPtr->valueRELAY_6_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_6_ONOFF %d \n", currentDataPoint.valueRELAY_6_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_6_ONOFF)
            {
                //user handle
            	relay_data[5]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[5]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_7_ONOFF :
            currentDataPoint.valueRELAY_7_ONOFF = dataPointPtr->valueRELAY_7_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_7_ONOFF %d \n", currentDataPoint.valueRELAY_7_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_7_ONOFF)
            {
                //user handle
            	relay_data[6]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[6]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;
        case EVENT_RELAY_8_ONOFF :
            currentDataPoint.valueRELAY_8_ONOFF = dataPointPtr->valueRELAY_8_ONOFF;
            GIZWITS_LOG("Evt: EVENT_RELAY_8_ONOFF %d \n", currentDataPoint.valueRELAY_8_ONOFF);
            if(0x01 == currentDataPoint.valueRELAY_8_ONOFF)
            {
                //user handle
            	relay_data[7]=1;
            	Ctrl_74hc595(relay_data);
            }
            else
            {
                //user handle
            	relay_data[7]=0;
            	Ctrl_74hc595(relay_data);
            	currentDataPoint.valueALL_RELAY_ON=0;
            }
            break;



        case WIFI_SOFTAP:
            break;
        case WIFI_AIRLINK:
            break;
        case WIFI_STATION:
            break;
        case WIFI_CON_ROUTER:
            GIZWITS_LOG("@@@@ connected router\n");
            GPIO_OUTPUT_SET(GPIO_ID_PIN(5), 0);
            break;
        case WIFI_DISCON_ROUTER:
            GIZWITS_LOG("@@@@ disconnected router\n");
            break;
        case WIFI_CON_M2M:
            GIZWITS_LOG("@@@@ connected m2m\n");
            setConnectM2MStatus(0x01);
            break;
        case WIFI_DISCON_M2M:
            GIZWITS_LOG("@@@@ disconnected m2m\n");
            setConnectM2MStatus(0x00);
            break;
        
        case WIFI_RSSI:
            GIZWITS_LOG("@@@@ RSSI %d\n", wifiData->rssi);
            break;
        case TRANSPARENT_DATA:
            GIZWITS_LOG("TRANSPARENT_DATA \n");
            //user handle , Fetch data from [data] , size is [len]
            break;
        
        case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
            break;
            
        default:
            break;
        }
    }
    system_os_post(USER_TASK_PRIO_2, SIG_UPGRADE_DATA, 0);
  
    return 0; 
}


/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void ICACHE_FLASH_ATTR userHandle(void)
{
	//GIZWITS_LOG("test\n");
}


/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void ICACHE_FLASH_ATTR userInit(void)
{
    gizMemset((uint8_t *)&currentDataPoint, 0, sizeof(dataPoint_t));

 	/** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 

        currentDataPoint.valueALL_RELAY_ON = 0;
        currentDataPoint.valueRELAY_1_ONOFF = relay_data[0];
        currentDataPoint.valueRELAY_2_ONOFF = relay_data[1];
        currentDataPoint.valueRELAY_3_ONOFF = relay_data[2];
        currentDataPoint.valueRELAY_4_ONOFF = relay_data[3];
        currentDataPoint.valueRELAY_5_ONOFF = relay_data[4];
        currentDataPoint.valueRELAY_6_ONOFF = relay_data[5];
        currentDataPoint.valueRELAY_7_ONOFF = relay_data[6];
        currentDataPoint.valueRELAY_8_ONOFF = relay_data[7];
        Ctrl_74hc595(relay_data);

}


