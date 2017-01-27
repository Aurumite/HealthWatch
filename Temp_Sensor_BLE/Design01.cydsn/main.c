#include "project.h"

//int getCelsius();
//int getFarenheit();

CYBLE_CONN_HANDLE_T connectionHandle; 

uint8 deviceConnected = 0; 
uint8 restartAdvertisement = 0 ; 
uint8 busyStatus = 0; 

uint8 SW_PRESS = 0;
uint8 whatToDo = 0;
uint8 started = 0;

int tempNotify;
int tempNotify2;

float value = 0;

void StackEventHandler( uint32 eventCode, void *eventParam )
{
    
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    
    switch( eventCode )
    {

        case CYBLE_EVT_STACK_ON:       
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:            
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(BLED_Read() == 1)
                BLED_Write(0);
        
        break;

        /* GAP Peripheral events */

//        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
//            if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED){
//                restartAdvertisement = 0;
//            }
//        break;

        /* GATT events */

        case CYBLE_EVT_GATT_CONNECT_IND:
            connectionHandle = *(CYBLE_CONN_HANDLE_T*)eventParam;
            deviceConnected = 1; 
            BLED_Write(1);
            
            break;

        case CYBLE_EVT_GATT_DISCONNECT_IND:
            deviceConnected = 0;            
            break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:				
			/*When this event is triggered, the peripheral has received 
			* a write command on the custom characteristic */
			
			/* Extract the write value from the event parameter */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			
			/* Check if the returned handle is matching to Random Data Client custom configuration*/
            if(CYBLE_TEMPSENSOR_TEMPERATURE_TEMP1CCCD_DESC_HANDLE  == wrReqParam->handleValPair.attrHandle)
            {
                whatToDo = wrReqParam->handleValPair.value.val[CYBLE_TEMPSENSOR_TEMPERATURE_CHAR_INDEX];
                /* Set flag so that application can start sending notifications.*/
                started = 1;
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                tempNotify = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
			}
            if(CYBLE_TEMPSENSOR_TEMPERATURE2_TEMP2CCCD_DESC_HANDLE  == wrReqParam->handleValPair.attrHandle)
            {
                whatToDo = wrReqParam->handleValPair.value.val[CYBLE_TEMPSENSOR_TEMPERATURE_CHAR_INDEX];
                /* Set flag so that application can start sending notifications.*/
                started = 1;
                CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
                tempNotify2 = wrReqParam->handleValPair.value.val[0] & 0x01;
                CyBle_GattsWriteRsp(cyBle_connHandle);
			}

            break; 
        
        /* default catch-all case */
        case CYBLE_EVT_STACK_BUSY_STATUS:
            busyStatus = *(uint8*) eventParam;
            
        default:
        break;
        
    }
}

void sendNotification1(uint16 value)
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationHandle;
    
    
    
    if(busyStatus == CYBLE_STACK_STATE_FREE)
    {
        notificationHandle.attrHandle = CYBLE_TEMPSENSOR_TEMPERATURE_CHAR_HANDLE;
        notificationHandle.value.val = (uint8 *)&value;
        notificationHandle.value.len = 2;
        
        CyBle_GattsNotification(cyBle_connHandle, &notificationHandle);
    }
}
void sendNotification2(uint16 value)
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationHandle;
    
    
    
    if(busyStatus == CYBLE_STACK_STATE_FREE)
    {
        notificationHandle.attrHandle = CYBLE_TEMPSENSOR_TEMPERATURE_CHAR_HANDLE;
        notificationHandle.value.val = (uint8 *)&value;
        notificationHandle.value.len = 2;
        CyBle_GattsNotification(cyBle_connHandle, &notificationHandle);
    }
}

void updateCharacteristic1(uint16 value) //updateCharacteristic(uint8* currData, uint8 len);
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
   
    CYBLE_GATT_HANDLE_VALUE_PAIR_T CCCDHandle; 

    CCCDHandle.attrHandle = CYBLE_TEMPSENSOR_TEMPERATURE_CHAR_HANDLE;
    CCCDHandle.value.val = (uint8 *)&value; //CCCDHandle.value.val = currVals;
    CCCDHandle.value.len = 2;  //CCCDHandle.value.len = len;
    
    CyBle_GattsWriteAttributeValue(&CCCDHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    CyBle_GattsReadAttributeValue(&CCCDHandle, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    if(tempNotify)
        CyBle_GattsNotification(cyBle_connHandle, &CCCDHandle);
}

void updateCharacteristic2(uint16 value) //updateCharacteristic(uint8* currData, uint8 len);
{
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
   
    CYBLE_GATT_HANDLE_VALUE_PAIR_T CCCDHandle; 

    CCCDHandle.attrHandle = CYBLE_TEMPSENSOR_TEMPERATURE2_CHAR_HANDLE;
    CCCDHandle.value.val = (uint8 *)&value; //CCCDHandle.value.val = currVals;
    CCCDHandle.value.len = 2;  //CCCDHandle.value.len = len;
    
    CyBle_GattsWriteAttributeValue(&CCCDHandle, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    CyBle_GattsReadAttributeValue(&CCCDHandle, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
    if(tempNotify2)
        CyBle_GattsNotification(cyBle_connHandle, &CCCDHandle);
}



int main(void)
{
    CyGlobalIntEnable;
    CyBle_Start( StackEventHandler );
    ADC_1_Start();
    ADC_1_StartConvert();
    BLED_Write(1);
    
    // Get the first voltage index, a[i], that is less than 
        // the current voltage reading. Also, get the previous 
        // index to know between which two indicies our reading is.
		int i;
		
		// Floats used because the calculation for m and b
		// were equating to zero.
		float V1, V2, T1, T2;
		
		// Need to be floats to properly calculate temperature
		float m = 0, b = 0;
    
    // Voltage index (mVolts)
    int a[] = {1375, 1350, 1300, 1250, 1199, 1149, 1097, 
        1046, 995, 943, 891, 838, 786, 733, 680, 627, 
        574, 520, 466, 412, 358, 302};
    // Temperature index (C)
    int c[] = {-55, -50, -40, -30, -20, -10, 0, 
        10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
        110, 120, 130, 140, 150};
    
    uint16 temp_ADC;
    uint16 temp_mVolts;
    value = 0;
    deviceConnected = 0;
    
    for(;;)
    {
        
        CyBle_ProcessEvents();
        if(deviceConnected && busyStatus == CYBLE_STACK_STATE_FREE){
            // Read from ADC
            temp_ADC = ADC_1_GetResult16(0);
            // Convert from 'ADC format' to millivolts
            // temperature values: typically 0x03 0xAF
            temp_mVolts = ADC_1_CountsTo_mVolts(0,temp_ADC);
    		for(i=0; i < sizeof(a)/sizeof(a[0]); i++)
            {

                if (temp_mVolts > a[i])
                {
                    // Voltage index below current reading
                    V1 = a[i];
                    // Voltage index above current reading
                    V2 = a[i-1];
                    
                    // Temp above
                    T1 = c[i];
                    // Temp below
                    T2 = c[i-1];
                    
                    // Slope calculation
                    // In case we want to reduce the number
                    // of variables, we can use the equation 
                    // below.
                    // m = (c[i-1] - c[i]) / (a[i-1] - a[i]);
                    m = (float)((T1 - T2) / (V1 - V2));
                    
                    // Intercept calculation
                    b = T1 - (m * V1);
                    
                    // Temperature calculation
                    value = m * temp_mVolts + b;
    			}
    		}
            updateCharacteristic1(temp_mVolts);
            updateCharacteristic2(temp_mVolts);
            CyDelay(100);
        }
    }
}




/* [] END OF FILE */
