//*****************************************************************************
//
// exosite.h - Prototypes for the Exosite Cloud API
//
// Copyright (c) 2012-2016 Exosite LLC.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

//  * Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of Exosite LLC nor the names of its contributors may
//    be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#ifndef Exosite_h
#define Exosite_h
#include <Arduino.h>
#include <WiFi.h>

#define ACTIVATOR_VERSION   "2.5.2"

// Select a Debug Level:
//#define EXOSITEDEBUG 1
//#define EXOSITEDEBUG 2
//#define EXOSITEDEBUG 3

// Enable or Disable Direct from ROM Sending
// Disabled on ESP because of performance issue and lack of need.
#if defined(ESP8266) or defined(NO_FLASH_NET_STRINGS)
    #define G(x) x
#else
    #define G(x) F(x)
#endif

// Enable Memory Debugging: (requires MemoryFree library)
//#define EXOSITEDEBUGMEM

#ifndef CIK_EEPROM_ADDRESS
  #define CIK_EEPROM_ADDRESS 0 //Takes Addresses 0 - 39 (dec)
#endif

// Do not Edit Past This Point

#ifndef SL_DRIVER_VERSION // SimpleLink on CC3200
#include <SPI.h>
#include <EEPROM.h>
#endif
#include <Client.h>

#ifdef SL_DRIVER_VERSION
#define boolean bool
#endif

#ifdef EXOSITEDEBUGMEM
#include <MemoryFree.h>
#endif

class Exosite
{
  private:
    class Client* client;
    char cik[41];
    char rxdata[200];
    char aliasList[50];
    const String serverName("m2.exosite.com");
    const String productID;
    char* varPtr;
    char* varPtr2;
    boolean ret;
    int stringPos;
    boolean DataRx;
    boolean RxLoop;
    char c;
    unsigned long timeout_time;
    unsigned long time_now;
    unsigned long timeout;

    // Helpers
    boolean isHex(char *str, int len);


  public:
    // Murano Constructors
    Exosite(Client *_client, const char *productID);
    Exosite(Client *_client, const String productID);

    // OnePlatform Constructors
    Exosite(Client *_client);
    Exosite(const char *_cik, Client *_client);
    Exosite(const String _cik, Client *_client);

#if defined(ESP8266) || defined(SL_DRIVER_VERSION)
    void begin();
#endif

    // Current Methods

    void setDomain(const char *domain);

    boolean writeRead(const char* writeString,const char* readString, char** returnString);
    boolean writeRead(const String &writeString, const String &readString, String &returnString);

    // Murano Provision request
    boolean provision(const char* snString);

    // OnePlatform Provision request
    boolean provision(const char* vendorString, const char* modelString, const char* snString);

    boolean saveNVCIK();
    boolean fetchNVCIK();

    unsigned long time();

    // Depreciated Methods
    int sendToCloud(String res, int value);
    int readFromCloud(String res ,String* pResult);

};

#endif
