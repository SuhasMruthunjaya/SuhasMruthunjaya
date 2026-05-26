/*
 * logFile.c
 *
 *  Created on: 14.08.2025
 *      Author: SESA807379
 */


#include "logFile.h"
#include "CurrentSenseVerification.h"
#include "ff.h"

static FATFS fs;
static FIL   fil;
static FRESULT fr;
static UINT bw;


void file__init(){

	fr = f_mount(&fs, "1:/", 1);
		if(fr != FR_OK){
			 xil_printf("Failed to mount SD card: %d\r\n", fr);
			 return;
		}

		 // Open file for writing (create or overwrite)
		 fr = f_open(&fil, "1:/errors.txt", FA_WRITE | FA_CREATE_ALWAYS);
		 if (fr != FR_OK) {
			 xil_printf("Failed to open file: %d\r\n", fr);
			 return;
		 }

}


void file__write(char* buffer)
{
    // Write to file
	fr = f_write(&fil, buffer, strlen(buffer), &bw);
	if (fr != FR_OK || bw == 0) {
		xil_printf("Failed to write file: %d\r\n", fr);
	}


    // Force commit to SD card
    f_sync(&fil);

}

void file__deinit()
{
	// Close file
	f_close(&fil);


}


