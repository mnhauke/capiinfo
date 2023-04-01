// capiinfo utility for win32
//
// (C) 2023 by Martin Hauke <mardnh@gmx.de>
//
// SPDX-License-Identifier: GPL-2.0-or-later


#include <windows.h>
#include <stdio.h>

int main() {
	HINSTANCE hDLL;

	// Load the CAPI2032.dll library
	hDLL = LoadLibrary("CAPI2032.dll");

	// Check for any errors
	if (hDLL == NULL) {
		printf("Error loading CAPI2032.dll\n");
	return 0;
	}


/***********************************************************************
 * CAPI_GET_VERSION
 ***********************************************************************/

	FARPROC capi_get_version;

	int get_capi_get_version() {
		capi_get_version = GetProcAddress(hDLL, "CAPI_GET_VERSION");
	
		if (capi_get_version == NULL) {
			printf("Error getting address of CAPI_GET_VERSION\n");
			FreeLibrary(hDLL);
		return 0;
		}

		static WORD	wCapiRet;

		static WORD	wCAPIMajor;
		static WORD	wCAPIMinor;
		static WORD	wCAPIManufacturerMajor;
		static WORD	wCAPIManufacturerMinor;

		wCapiRet = (capi_get_version) (&wCAPIMajor, &wCAPIMinor, &wCAPIManufacturerMajor, &wCAPIManufacturerMinor);
		if (wCapiRet == 0)
		{
			printf( "CAPI Version: %u.%u\n", wCAPIMajor, wCAPIMinor);
			printf( "Manufacturer Version: %u.%u\n", wCAPIManufacturerMajor, wCAPIManufacturerMinor);
		}
		else
		{
			printf("CAPI error\n");
		}

		return 0;
	}


/***********************************************************************
 * CAPI_GET_MANUFACTURER
 ***********************************************************************/

	FARPROC capi_get_manufacturer;

	int get_capi_get_manufacturer() {
		capi_get_manufacturer = GetProcAddress(hDLL, "CAPI_GET_MANUFACTURER");

		if (capi_get_manufacturer == NULL) {
			printf("Error getting address of CAPI_GET_MANUFACTURER\n");
			FreeLibrary(hDLL);
		return 0;
		}

		char *buffer;
		int buffer_size = 128;

		buffer = (char *)malloc(buffer_size);

		if (buffer == NULL) {
			printf("Error allocating memory\n");
			FreeLibrary(hDLL);
		return 0;
		}

		capi_get_manufacturer(buffer, buffer_size);

		printf("Manufacturer: %s\n", buffer);

		free(buffer);

		return 0;
	}


/*************************
 * CAPI_GET_SERIAL_NUMBER
 *************************/

	FARPROC capi_get_serial_number;

	int get_capi_get_serial_number() {
		capi_get_serial_number = GetProcAddress(hDLL, "CAPI_GET_SERIAL_NUMBER");

		if (capi_get_serial_number == NULL) {
			printf("Error getting address of CAPI_GET_SERIAL_NUMBER\n");
			FreeLibrary(hDLL);
		return 0;
		}

		char *buffer;
		int buffer_size = 256;
	
		buffer = (char *)malloc(buffer_size);

		if (buffer == NULL) {
			printf("Error allocating memory\n");
			FreeLibrary(hDLL);
		return 0;
		}

		capi_get_serial_number(buffer, buffer_size);

		printf("Serial Number: %s\n", buffer);

		free(buffer);

		return 0;
	}


/*******************
 * CAPI_GET_PROFILE
 *******************/

	FARPROC capi_get_profile;

	int get_capi_get_profile() {
		capi_get_profile = GetProcAddress(hDLL, "CAPI_GET_PROFILE");

		if (capi_get_profile == NULL) {
			printf("Error getting address of CAPI_GET_PROFILE\n");
			FreeLibrary(hDLL);
		return 0;
		}

		#define BIT_0  0x0001
		#define BIT_1  0x0002
		#define BIT_2  0x0004
		#define BIT_3  0x0008
		#define BIT_4  0x0010
		#define BIT_5  0x0020
		#define BIT_6  0x0040
		#define BIT_7  0x0080
		#define BIT_8  0x0100
		#define BIT_9  0x0200
		#define BIT_10 0x0400
		#define BIT_11 0x0800
		#define BIT_12 0x1000

		typedef struct {
			WORD	wController;
			WORD	wChannel;
			DWORD	dwGlobal;
			DWORD	dwB1Prot;
			DWORD	dwB2Prot;
			DWORD	dwB3Prot;
			DWORD	dwReserved1;
			DWORD	dwReserved2;
			DWORD	dwReserved3;
		} CAPI_PROFILE;

		WORD wCapiRet;
		CAPI_PROFILE	tCapiProfile;
		WORD wCtrlNr = 1;       /* only for the first controller */

		wCapiRet = (capi_get_profile) (&tCapiProfile, wCtrlNr);
		if (wCapiRet == 0)
		{
		printf("Installed Controllers: %u\n", tCapiProfile.wController);
		printf("Supported B-Channels:  %u\n", tCapiProfile.wChannel);

		printf("\n");
		printf("Controller 1:\n");

		/* Global */
		printf("Global:\n");
		if( tCapiProfile.dwGlobal & BIT_0 )
			printf("   internal controller supported\n");
		if( tCapiProfile.dwGlobal & BIT_1 )
			printf("   external equipment supported\n");
		if( tCapiProfile.dwGlobal & BIT_2 )
			printf("   handset supported\n");
		if( tCapiProfile.dwGlobal & BIT_3 )
			printf("   DTMF supported\n");
		if( tCapiProfile.dwGlobal & BIT_4 )
			printf("   Supplementary Services supported\n");
		if( tCapiProfile.dwGlobal & BIT_5 )
			printf("   channel allocation supported (leased lines)\n");

		/* B1 protocol support */
		printf("B1-Protocols:\n");
		if( tCapiProfile.dwB1Prot & BIT_0 )
			printf("   64 kbit/s with HDLC framing\n");
		if( tCapiProfile.dwB1Prot & BIT_1 )
			printf("   64 kbit/s bit-transparent operation\n");
		if( tCapiProfile.dwB1Prot & BIT_2 )
			printf("   V.110 asynconous operation with start/stop byte framing\n");
		if( tCapiProfile.dwB1Prot & BIT_3 )
			printf("   V.110 synconous operation with HDLC framing\n");
		if( tCapiProfile.dwB1Prot & BIT_4 )
			printf("   T.30 modem for fax group 3\n");
		if( tCapiProfile.dwB1Prot & BIT_5 )
			printf("   64 kbit/s inverted with HDLC framing\n");
		if( tCapiProfile.dwB1Prot & BIT_6 )
			printf("   56 kbit/s bit-transparent operation\n");
		if( tCapiProfile.dwB1Prot & BIT_7 )
			printf("   Modem with all negotiations\n");
		if( tCapiProfile.dwB1Prot & BIT_8 )
			printf("   Modem asyncronous operation with start/stop byte framing\n");
		if( tCapiProfile.dwB1Prot & BIT_9 )
			printf("   Modem syncronous operation with HDLC framing\n");

		/* B2 protocol support */
		printf("B2-Protocols:\n");
		if( tCapiProfile.dwB2Prot & BIT_0 )
			printf("   ISO 7776 (X.75 SLP)\n");
		if( tCapiProfile.dwB2Prot & BIT_1 )
			printf("   Transparent\n");
		if( tCapiProfile.dwB2Prot & BIT_2 )
			printf("   SDLC\n");
		if( tCapiProfile.dwB2Prot & BIT_3 )
			printf("   LAPD with Q.921 for D channel X.25 (SAPI 16)\n");
		if( tCapiProfile.dwB2Prot & BIT_4 )
			printf("   T.30 for fax group 3\n");
		if( tCapiProfile.dwB2Prot & BIT_5 )
			printf("   Point-to-Point Protocol (PPP)\n");
		if( tCapiProfile.dwB2Prot & BIT_6 )
			printf("   Transparent (ignoring framing errors of B1 protocol)\n");
		if( tCapiProfile.dwB2Prot & BIT_7 )
			printf("   Modem error correction and compression (V.42bis or MNP5)\n");
		if( tCapiProfile.dwB2Prot & BIT_8 )
			printf("   ISO 7776 (X.75 SLP) with V.42bis compression\n");
		if( tCapiProfile.dwB2Prot & BIT_9 )
			printf("   V.120 asyncronous mode\n");
		if( tCapiProfile.dwB2Prot & BIT_10 )
			printf("   V.120 asyncronous mode with V.42bis compression\n");
		if( tCapiProfile.dwB2Prot & BIT_11 )
			printf("   V.120 bit-transparent mode\n");
		if( tCapiProfile.dwB2Prot & BIT_12 )
			printf("   LAPD with Q.921 including free SAPI selection\n");

		/* B3 protocol support */
		printf("B3-Protocols:\n");
		if( tCapiProfile.dwB3Prot & BIT_0 )
			printf("   Transparent\n");
		if( tCapiProfile.dwB3Prot & BIT_1 )
			printf("   T.90NL, T.70NL, T.90\n");
		if( tCapiProfile.dwB3Prot & BIT_2 )
			printf("   ISO 8208 (X.25 DTE-DTE)\n");
		if( tCapiProfile.dwB3Prot & BIT_3 )
			printf("   X.25 DCE\n");
		if( tCapiProfile.dwB3Prot & BIT_4 )
			printf("   T.30 for fax group 3\n");
		if( tCapiProfile.dwB3Prot & BIT_5 )
			printf("   T.30 for fax group 3 with extensions\n");
		if( tCapiProfile.dwB3Prot & BIT_6 )
			printf("   reserved\n");
		if( tCapiProfile.dwB3Prot & BIT_7 )
			printf("   Modem\n");
		}
		else
		{
			printf("CAPI error\n");
		}
	return 0;
}


/*********
 * Run it
 *********/
	get_capi_get_manufacturer();
	get_capi_get_version();
	get_capi_get_serial_number();
	get_capi_get_profile();

	// Clean up
	FreeLibrary(hDLL);

	return 0;
}
