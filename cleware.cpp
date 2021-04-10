/*
 * cleware.c
 *
 * Copyright (C) 2018, Intel - http://www.intel.com/
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * Contributors:
 *      - Reference from http://www.cleware.info/data/linux_E.html
 *      - Pengfei, Xu <pengfei.xu@intel.com>
 *      - Add print and format normalize
 */

/*****************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "USBaccess.h"


int usage(void)
{
	printf("Usage: [0|1] [X]\n");
	printf("Par1:  0 means power off, 1 means power off\n");
	printf("Par2:  0 means cleware 1 in hex(max f for cleware 16)\n");

	exit(1);
}


int main(int argc, char* argv[]) {
	CUSBaccess CWusb;
	int cnt = 0;
	int cle_id = 0, devType;
	unsigned int switch_id;

	int USBcount = CWusb.OpenCleware();
	if (argc == 2) {
		printf("Cleware argc=%d,argv[1][0]=%c\n",argc,argv[1][0]);
		if (argv[1][0] == 'h' || argv[1][1] == 'h')
			usage();
	} else if (argc == 3) {
		printf("Cleware argc=%d,argv[1][0]=%c, argv[2]:%s\n",
			argc, argv[1][0], argv[2]);
		sscanf(argv[2], "%x", &cle_id);
		if ((cle_id < 0) || (cle_id >= USBcount)) {
			printf("argv[2]:0x%x is not in cleware max range 0-0x%x present\n", 
				cle_id, USBcount-1);
			usage();
		}
	} else
		usage();

	if ((argv[1][0] == '0') || (argv[1][0] == '1')) {
		printf("argv[1][0]:%c\n", argv[1][0]);
	} else {
		printf("argv[1][0] is not 0 or 1:%c\n", argv[1][0]);
		usage();
	}

	printf("OpenCleware %d USBcount\n", USBcount);

	if (argc == 3) {
		switch_id = 0x10 + cle_id;
		devType = CWusb.GetUSBType(cle_id);
		printf("Device %d: Type=%d, Version=%d, SerNum=%d\n", cle_id,
				devType, CWusb.GetVersion(cle_id),
				CWusb.GetSerialNumber(cle_id));
		switch (switch_id) {
			case CUSBaccess::SWITCH_0:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 1);
				}
				CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_0);
				printf("Cleware 0x%x seqswitch status = %d\n",
						cle_id, CWusb.GetSeqSwitch(cle_id, CUSBaccess::SWITCH_0, 0));
				CWusb.GetSwitch(cle_id+1, CUSBaccess::SWITCH_1);
				printf("Cleware 0x%x seqswitch status = %d\n",
						cle_id+1, CWusb.GetSeqSwitch(cle_id+1, CUSBaccess::SWITCH_1, 1));
			}
				break;
			case CUSBaccess::SWITCH_1:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_1, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_1, 1);
				}
				CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_1);
				printf("Cleware 0x%x seqswitch status = %d\n",
						cle_id, CWusb.GetSeqSwitch(cle_id, CUSBaccess::SWITCH_1, 0));

				CWusb.GetSwitch(cle_id-1, CUSBaccess::SWITCH_0);
				printf("Cleware 0x%x seqswitch status = %d\n",
						cle_id-1, CWusb.GetSeqSwitch(cle_id-1, CUSBaccess::SWITCH_0, 0));
			}
				break;
			case CUSBaccess::SWITCH_2:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_2, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_2, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_2));
			}
				break;
			case CUSBaccess::SWITCH_3:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_3, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_3, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_3));
			}
				break;
			case CUSBaccess::SWITCH_4:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_4, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_4, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_4));
			}
				break;
			case CUSBaccess::SWITCH_5:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_5, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_5, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_5));
			}
				break;
			case CUSBaccess::SWITCH_6:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_6, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_6, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_6));
			}
				break;
			case CUSBaccess::SWITCH_7:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_7, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_7, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_7));
			}
				break;
			case CUSBaccess::SWITCH_8:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_8, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_8, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_8));
			}
				break;
			case CUSBaccess::SWITCH_9:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_9, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_9, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_9));
			}
				break;
			case CUSBaccess::SWITCH_10:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_10, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_10, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_10));
			}
				break;
			case CUSBaccess::SWITCH_11:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_11, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_11, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_11));
			}
				break;
			case CUSBaccess::SWITCH_12:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_12, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_12, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_12));
			}
				break;
			case CUSBaccess::SWITCH_13:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_13, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_13, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_13));
			}
				break;
			case CUSBaccess::SWITCH_14:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_14, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_14, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_14));
			}
				break;
			case CUSBaccess::SWITCH_15:
			{
				if (argv[1][0] == '0') {
					printf("Power off Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_15, 0);
				} else if (argv[1][0] == '1') {
					printf("Power on Cleware:0x%x\n", cle_id);
					CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_15, 1);
				}
				printf("Cleware 0x%x switch status:%d\n",
					cle_id, CWusb.GetSwitch(cle_id, CUSBaccess::SWITCH_15));
			}
				break;
			default:
				printf("In default\n");
				break;
		}
	}

	for (int devID=0; devID < USBcount; devID++) {
		devType = CWusb.GetUSBType(devID);

		if (argc == 2) {
			printf("Device %d: Type=%d, Version=%d, SerNum=%d\n", devID,
					devType, CWusb.GetVersion(devID),
					CWusb.GetSerialNumber(devID));
			if (devType == CUSBaccess::SWITCH1_DEVICE) {
				printf("argv=%c <0x%02x>\n", argv[1][0], argv[1][0]);
				if (argv[1][0] == '0')
					CWusb.SetSwitch(devID, CUSBaccess::SWITCH_0, 0);
				else if (argv[1][0] == '1')
					CWusb.SetSwitch(devID, CUSBaccess::SWITCH_0, 1);
				else {
					printf("Invalid argv[1][0] for cleware:%c\n", argv[1][0]);
					printf("./cleware 1 to power on, 0 to power off\n");
				}
				CWusb.GetSwitch(devID, CUSBaccess::SWITCH_0);
				printf("Cleware 0x%x seqswitch status = %d\n",
						devID, CWusb.GetSeqSwitch(devID, CUSBaccess::SWITCH_0, 0));
				CWusb.GetSwitch(devID+1, CUSBaccess::SWITCH_1);
				printf("Cleware 0x%x seqswitch status = %d\n",
						devID+1, CWusb.GetSeqSwitch(devID+1, CUSBaccess::SWITCH_1, 1));
				break;
			}
			else
				continue;		// die anderen Interessieren uns nicht
		}


		if (devType == CUSBaccess::TEMPERATURE_DEVICE || devType == CUSBaccess::TEMPERATURE2_DEVICE) {
			CWusb.ResetDevice(devID);
			usleep(300*1000);		// etwas warten

			// nun 10 Messwerte abfrage
			for (int cnt=0; cnt < 10; cnt++) {
				double temperatur;
				int	   zeit;
				if (!CWusb.GetTemperature(devID, &temperatur, &zeit)) {
					printf("GetTemperature(%d) fehlgeschlagen\n", devID);
					break;
				}
				printf("Messwert %lf Grad Celsius, Zeit = %d\n", temperatur, zeit);
				usleep(1200 * 1000);
			}
		}
		if (devType == CUSBaccess::HUMIDITY1_DEVICE) {
			CWusb.ResetDevice(devID);
			usleep(100*1000);		// etwas warten

			CWusb.StartDevice(devID);
			usleep(300*1000);		// etwas warten
			// nun 10 Messwerte abfrage
			for (int cnt=0; cnt < 10; cnt++) {
				double temperatur, humidity;
				int	   zeit;
				if (!CWusb.GetTemperature(devID, &temperatur, &zeit))
					printf("GetTemperature(%d) fehlgeschlagen\n", devID);
				else
					printf("Messwert %lf Grad Celsius, Zeit = %d\n", temperatur, zeit);
				if (!CWusb.GetHumidity(devID, &humidity, &zeit))
					printf("GetHumidity(%d) fehlgeschlagen\n", devID);
				else
					printf("Messwert %lf %% RH, Zeit = %d\n", humidity, zeit);
				usleep(1200 * 1000);
			}
		}
	}

	CWusb.CloseCleware();

	return 0;
}
