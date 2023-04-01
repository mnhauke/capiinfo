## capiinfo.exe

CLI version of capiinfo for win32.
It shows supported features of installed CAPI2.0 controllers.

## TODOs

* Handle multiple CAPI controllers
* Decode more information from CAPI_VERSION
* Add information which "Supplementary Services" are supported (via FACILITY_REQ)

## Examples

Teldat Surf USB, Windows XP

```
C:\> capiinfo.exe

Manufacturer: Eicon 32Bit CAPI 2.0 DLL for Windows NT
CAPI Version: 2.0
Manufacturer Version: 2.10
Serial Number:
Installed Controllers: 1
Supported B-Channels:  2

Controller 1:
Global:
   internal controller supported
   DTMF supported
   Supplementary Services supported
   channel allocation supported (leased lines)
B1-Protocols:
   64 kbit/s with HDLC framing
   64 kbit/s bit-transparent operation
   56 kbit/s bit-transparent operation
B2-Protocols:
   ISO 7776 (X.75 SLP)
   Transparent
   LAPD with Q.921 for D channel X.25 (SAPI 16)
   ISO 7776 (X.75 SLP) with V.42bis compression
   V.120 asyncronous mode
   V.120 bit-transparent mode
   LAPD with Q.921 including free SAPI selection
B3-Protocols:
   Transparent
   T.90NL, T.70NL, T.90
   ISO 8208 (X.25 DTE-DTE)
```

Gerdes PrimuX USB II (No. 2110), Windows 10

```
C:\> capiinfo.exe

Manufacturer: PrimuX ISDN 3.10.9-gd9e34276 (c) 1995-2023 Gerdes AG
CAPI Version: 2.0
Manufacturer Version: 3.10
Serial Number:
Installed Controllers: 1
Supported B-Channels:  2

Controller 1:
Global:
   internal controller supported
   DTMF supported
   Supplementary Services supported
B1-Protocols:
   64 kbit/s with HDLC framing
   64 kbit/s bit-transparent operation
   V.110 asynconous operation with start/stop byte framing
   V.110 synconous operation with HDLC framing
   T.30 modem for fax group 3
B2-Protocols:
   ISO 7776 (X.75 SLP)
   Transparent
   LAPD with Q.921 for D channel X.25 (SAPI 16)
   T.30 for fax group 3
   Transparent (ignoring framing errors of B1 protocol)
   LAPD with Q.921 including free SAPI selection
B3-Protocols:
   Transparent
   T.90NL, T.70NL, T.90
   ISO 8208 (X.25 DTE-DTE)
   T.30 for fax group 3
   T.30 for fax group 3 with extensions
```


