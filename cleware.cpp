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
	CUSBaccess CWusb;
	printf("Usage: [0|1|s] [X]\n");
	printf("Par1:  0 means power off(only 1 parm will power off all;\n");
	printf("       1 means power on (only 1 parm will power on all;\n");
	printf("       s means show all status\n");
	printf("Par2:  0 means 1(1st) connected cleware in hex(max f for cleware 16)\n");
	CWusb.CloseCleware();

	exit(1);
}

int check_status()
{
	CUSBaccess CWshow;
	int id = 0, USBcnt = 0;
	enum CUSBaccess::SWITCH_IDs switchID = CUSBaccess::SWITCH_0;

	USBcnt = CWshow.OpenCleware();
	for (id = 0; id < USBcnt; id++) {
		//switchID = (enum CUSBaccess::SWITCH_IDs)(CUSBaccess::SWITCH_0 + id);
		switchID = (enum CUSBaccess::SWITCH_IDs)CUSBaccess::SWITCH_0;
		CWshow.GetSwitch(id, switchID);
		//cleware 5 or more get wrong status in 10 pecentage, work around way
		if (id >= 5) {
			usleep(50 * 1000);
			CWshow.GetSeqSwitch(id, switchID, 0);
			CWshow.GetSwitch(id, switchID);
		}
		printf("Cleware %x power status = %d\n",
				id, CWshow.GetSeqSwitch(id, switchID, 0));
	}
	CWshow.CloseCleware();

	return 0;
}


int main(int argc, char* argv[]) {
	CUSBaccess CWusb;
	int cle_id = 0, devType, devID = 0, USBcount = 0;

	USBcount = CWusb.OpenCleware();
	if (argc == 2) {
		printf("argc=%d,argv[1][0]=%c\n", argc, argv[1][0]);
		if (argv[1][0] == 'h' || argv[1][1] == 'h')
			usage();
		if (argv[1][0] == 's') {
			check_status();
			return 0;
		}
	} else if (argc == 3) {
		printf("argc=%d,argv[1][0]=%c, argv[2]:%s\n",
			argc, argv[1][0], argv[2]);
		sscanf(argv[2], "%x", &cle_id);
		if ((cle_id < 0) || (cle_id >= USBcount)) {
			printf("argv[2]:0x%x is not in Cleware max range 0~%d present\n",
				cle_id, USBcount-1);
			return 2;
		}
	} else
		usage();

	if (!((argv[1][0] == '0') || (argv[1][0] == '1'))) {
		printf("argv[1][0] is not 0 or 1:%c\n", argv[1][0]);
		usage();
	}

	printf("Open %d clewares\n", USBcount);

	printf("***** Before action, clewares status is as below *****\n");
	check_status();

	// power off/on specific cleware 0-0xf
	if (argc == 3) {
		USBcount = CWusb.OpenCleware();

		devType = CWusb.GetUSBType(cle_id);
		printf("Device %d: Type=%d, Version=%d, SerNum=%d\n\n", cle_id,
				devType, CWusb.GetVersion(cle_id),
				CWusb.GetSerialNumber(cle_id));

		if (argv[1][0] == '0') {
			printf("-> Power off cleware_id:0x%x\n", cle_id);
			CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 0);
			//usleep(30 * 1000);
			//state =CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 0);
		} else if (argv[1][0] == '1') {
			printf("-> Power on cleware_id:0x%x\n", cle_id);
			CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 1);
			usleep(30 * 1000);
			//state =CWusb.SetSwitch(cle_id, CUSBaccess::SWITCH_0, 1);
		} else {
			printf("Invalid argv[1][0]:%c not 0 or 1\n", argv[1][0]);
			usage();
		}
	}

	// power off/on all found cleware
	if (argc == 2) {
		USBcount = CWusb.OpenCleware();

		for (devID = 0; devID < USBcount; devID++) {
			devType = CWusb.GetUSBType(devID);
			printf("Device %d: Type=%d, Version=%d, SerNum=%d\n", devID,
				devType, CWusb.GetVersion(devID),
				CWusb.GetSerialNumber(devID));

			if (devType == CUSBaccess::SWITCH1_DEVICE) {
				if (argv[1][0] == '0') {
					printf(" -> Power OFF cleware_id %x\n", devID);
						CWusb.SetSwitch(devID, CUSBaccess::SWITCH_0, 0);
				} else if (argv[1][0] == '1') {
					printf(" -> Power ON cleware_id %x\n", devID);
						CWusb.SetSwitch(devID, CUSBaccess::SWITCH_0, 1);
				} else {
					printf("Invalid argv[1][0] for cleware:%c\n", argv[1][0]);
					printf("./cleware 1 to power on, 0 to power off\n");
				}
			}
		}
	}

	usleep(50 * 1000);
	printf("\n***** After action, clewares status is as below *****\n");
	check_status();

	CWusb.CloseCleware();

	return 0;
}
