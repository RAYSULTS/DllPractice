// AudioDevice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iostream>
#include <vector>
#include <regex>
#include <Windows.h>
#include <ObjBase.h>
#include <Mmsystem.h>
#include <devpropdef.h>
#include <atlbase.h>
#include <atlstr.h>

#include <stdio.h>
#include <tchar.h>
#include "PolicyConfig.h"
#include "DllPractice.h"


//-----------------------------------------------------------
// This function enumerates all active (plugged in) audio
// rendering endpoint devices. It prints the friendly name
// and endpoint ID string of each endpoint device.
//-----------------------------------------------------------
#define EXIT_ON_ERROR(hres)  \
              if (FAILED(hres)) { goto Exit; }
#define SAFE_RELEASE(isok)  \
              if ((isok) != NULL)  \
                { (isok)->Release(); (isok) = NULL; }

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
IMMDeviceEnumerator* pEnumerator = NULL;
IMMDeviceCollection* pCollection = NULL;
IMMDevice* pEndpoint = NULL;
IPropertyStore* pProps = NULL;
ERole role = eMultimedia;
std::string isroleName = "unknown";


//const LPCWSTR is_deviceID = L"{0.0.0.00000000}.{1c5d88b5-2564-4521-ba64-ed9630e9bc53}";

//beats headset correct one
//const LPCWSTR is_deviceID = L"{0.0.0.00000000}.{ff4f7326-16b9-45ec-9f78-6c1ea610d688}";


void IseRoleSwitch(int input=0)
{
    #pragma region eRole Switch
    
        if (input == 0)
        {
            isroleName = "eConsole";
            role = eConsole;
        }
        else if (input == 1)
        {
            isroleName = "eMultimedia";
            role = eMultimedia;
        }
        else if (input == 2)
        {
            isroleName = "eCommunications";
            role = eCommunications;
        }
    #pragma endregion eRole Switch
}


/// <summary>
/// Invoke COM object IMMDeviceEnumerator with single instance
/// </summary>
/// <param name="pEnumerator"></param>
/// <returns></returns>
void InvokeIMMDeviceEnumeratorCOM()
{
    HRESULT hr = S_OK;
    LPWSTR pwszID = NULL;

    //IMMDeviceEnumerator* pEnumerator = NULL;
    //IMMDeviceCollection* pCollection = NULL;
    //IMMDevice* pEndpoint = NULL;
    //IPropertyStore* pProps = NULL;
  
    #pragma region Create COM
        hr = CoCreateInstance
        (
            CLSID_MMDeviceEnumerator,
            NULL,
            CLSCTX_ALL,
            IID_IMMDeviceEnumerator,
            (void**)&pEnumerator
        );
    
       
    #pragma endregion 
}


void PrintEndpointNames()
{
    HRESULT hr = S_OK;
    //IMMDeviceEnumerator* pEnumerator = NULL;
    //IMMDeviceCollection* pCollection = NULL;
    //IMMDevice* pEndpoint = NULL;
    //IPropertyStore* pProps = NULL;
    LPWSTR pwszID = NULL;

    
    //Using Method EnumAudioEndpoints as it requires _Out_  IMMDeviceCollection
    if (pEnumerator == NULL)
    {
        std::cout << "Invoking COM...\n";
        InvokeIMMDeviceEnumeratorCOM();
    }
    else
    {
        std::cout << "COM Already exists....skipping...\n";
    }
    //hr = CoCreateInstance
    //(
    //    CLSID_MMDeviceEnumerator,
    //    NULL,
    //    CLSCTX_ALL,
    //    IID_IMMDeviceEnumerator,
    //    (void**)&pEnumerator
    //);

    EXIT_ON_ERROR(hr)

        // Only displays active devices
        //hr = pEnumerator->EnumAudioEndpoints(
        //    eRender, DEVICE_STATE_ACTIVE,
        //    &pCollection);

        // Displays all devices
        //hr = pEnumerator->EnumAudioEndpoints
        //                    (
        //                        eRender,
        //                        DEVICE_STATEMASK_ALL,
        //                        &pCollection
        //                    );


    // Alternate method to arrow operator
    hr = (*pEnumerator).EnumAudioEndpoints
    (
        eRender,
        DEVICE_STATEMASK_ALL,
        &pCollection
    );


      



    EXIT_ON_ERROR(hr)

        UINT  count;

    //hr = pCollection->GetCount(&count);
    // Alternate method to arrow operator
    hr = (*pCollection).GetCount(&count);

    EXIT_ON_ERROR(hr)

        if (count == 0)
        {
            printf("No endpoints found.\n");
        }

    // Each loop prints the name of an endpoint device.
    for (ULONG i = 0; i < count; i++)
    {
        // Get pointer to endpoint number i.
        //hr = pCollection->Item(i, &pEndpoint);
        hr = (*pCollection).Item(i, &pEndpoint);
        EXIT_ON_ERROR(hr)

            // Get the endpoint ID string.
            //hr = pEndpoint->GetId(&pwszID);
            hr = (*pEndpoint).GetId(&pwszID);
        EXIT_ON_ERROR(hr)

            //hr = pEndpoint->OpenPropertyStore(
            //    STGM_READ, &pProps);
            hr = (*pEndpoint).OpenPropertyStore
            (
                STGM_READ,
                &pProps
            );
        EXIT_ON_ERROR(hr)

            PROPVARIANT varName;
        // Initialize container for property value.
        PropVariantInit(&varName);

        // Get the endpoint's friendly-name property.
        //hr = pProps->GetValue(
        //    PKEY_Device_FriendlyName, &varName);
        hr = (*pProps).GetValue
        (
            PKEY_Device_FriendlyName,
            &varName
        );

        EXIT_ON_ERROR(hr)

            PROPVARIANT varInstallstate;
        //Initialize container for property value.
        PropVariantInit(&varInstallstate);

        // Get the endpoint's install state property.
        hr = pProps->GetValue(
            PKEY_Device_EnumeratorName,
            //PKEY_Device_DeviceDesc,
            &varInstallstate);
        EXIT_ON_ERROR(hr)


            // GetValue succeeds and returns S_OK if PKEY_
            // 
            // Device_FriendlyName is not found.
            // In this case vartName.vt is set to VT_EMPTY.      
            if (varName.vt != VT_EMPTY)
            {
                // Print endpoint friendly name and endpoint ID.
                //printf("Endpoint Index: %d: \"%S\" (%S)\n",
                //    i, varName.pwszVal, pwszID);

                printf("Endpoint Index: %d\n", i);

                printf("Endpoint FriendlyName: \"%S\" \n", varName.pwszVal);

                printf("Endpoint Guid: \"%S\"\n", pwszID);

                printf("Endpoint InstallState: \"%S\" \n", varInstallstate.pwszVal);
            }
        //ENDPOINT_SYSFX_ENABLED



        CoTaskMemFree(pwszID);
        pwszID = NULL;
        PropVariantClear(&varName);
        SAFE_RELEASE(pProps)
            SAFE_RELEASE(pEndpoint)
    }
    SAFE_RELEASE(pEnumerator)
        SAFE_RELEASE(pCollection)
        return;

Exit:
    printf("Error!\n");
    CoTaskMemFree(pwszID);
    SAFE_RELEASE(pEnumerator)
        SAFE_RELEASE(pCollection)
        SAFE_RELEASE(pEndpoint)
        SAFE_RELEASE(pProps)
}


void PrintDevices()
{
    std::cout << "Hello World!\n";
    CoInitialize(NULL);

    OleInitialize(NULL);

    PrintEndpointNames();

    CoUninitialize();
    OleUninitialize();

}


void GetDefaultAudioEndpoint(int input=0)
{
    IseRoleSwitch(input);

#pragma region  Set Variables
    HRESULT hr = S_OK;
    LPWSTR pwszID = NULL;

#pragma region Using single instance
    //IMMDeviceEnumerator* pEnumerator = NULL;
    //IMMDeviceCollection* pCollection = NULL;
    //IMMDevice* pEndpoint = NULL;
    //IPropertyStore* pProps = NULL;
    

    

#pragma endregion
  
#pragma region Create COM
    //hr = CoCreateInstance
    //(
    //    CLSID_MMDeviceEnumerator,
    //    NULL,
    //    CLSCTX_ALL,
    //    IID_IMMDeviceEnumerator,
    //    (void**)&pEnumerator
    //);
    
    ///Inialize COM
    InvokeIMMDeviceEnumeratorCOM();
#pragma endregion 

    EXIT_ON_ERROR(hr)

#pragma region Get Default Audio Endpoint
    hr = (*pEnumerator).GetDefaultAudioEndpoint
    (
        eRender,
        role,
        &pEndpoint
    );


    hr = (pEndpoint->GetId(&pwszID));
#pragma endregion 

#pragma region Get Audio Endpoint Properties

    hr = (*pEndpoint).OpenPropertyStore
    (
        STGM_READ,
        &pProps
    );
    EXIT_ON_ERROR(hr)

    PROPVARIANT varName;
    // Initialize container for property value.
    PropVariantInit(&varName);

    // Get the endpoint's friendly-name property.
    //hr = pProps->GetValue(
    //    PKEY_Device_FriendlyName, &varName);
    hr = (*pProps).GetValue
    (        
        PKEY_Device_FriendlyName,
        &varName
    );
    // testing 
    ///if (varName.vt != VT_EMPTY)
    ///{
    ///    std::cout << "VarName not empty";
    ///}
#pragma endregion Get Audio Endpoint Properties
    
#pragma region Output Data  
    std::cout<<"Role: "<<role << "\n" "Role FriendlyName : "<<isroleName<< "\n";

    ///std:cout cannot convert LPWSTR to readable text///
    ///std::cout << " via cout Endpoint FriendlyName: " << varName.pwszVal<< "\n";
    printf(" Endpoint FriendlyName: \"%S\" \n", varName.pwszVal);
    
    //printf(" Endpoint FriendlyName : \"%S\"\n", pwszID);

    printf(" Endpoint Guid: \"%S\"\n", pwszID);
#pragma endregion Output Data

    SAFE_RELEASE(pEndpoint)
        //SAFE_RELEASE(pCollection)
    CoTaskMemFree(pwszID);
        return;

Exit:
    printf("Error!\n");
    CoTaskMemFree(pwszID);
    SAFE_RELEASE(pEnumerator)
        SAFE_RELEASE(pCollection)
        SAFE_RELEASE(pEndpoint)
        SAFE_RELEASE(pProps)

}

void PrintDefaultAudioEndpoint(int input=0)
{
    std::cout << "Hello World!\n";
    CoInitialize(NULL);

    OleInitialize(NULL);


    std::cout << "Executing COM...\n";
    GetDefaultAudioEndpoint(input);

    CoUninitialize();
    OleUninitialize();

}


HRESULT RegisterDevice(LPCWSTR devID, int erole=0)
{
    IseRoleSwitch(erole);
    IPolicyConfig* pPolicyConfig = nullptr;

    HRESULT hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfig), (LPVOID*)&pPolicyConfig);
    if (pPolicyConfig == nullptr) {
        hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfig10), (LPVOID*)&pPolicyConfig);
    }
    if (pPolicyConfig == nullptr) {
        hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfig7), (LPVOID*)&pPolicyConfig);
    }
    if (pPolicyConfig == nullptr) {
        hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfigVista), (LPVOID*)&pPolicyConfig);
    }
    if (pPolicyConfig == nullptr) {
        hr = CoCreateInstance(__uuidof(CPolicyConfigClient), NULL, CLSCTX_ALL, __uuidof(IPolicyConfig10_1), (LPVOID*)&pPolicyConfig);
    }

    if (pPolicyConfig != NULL) 
    {
        hr = pPolicyConfig->SetDefaultEndpoint(devID, role);
        SAFE_RELEASE(pPolicyConfig);
    }

    return hr;
}

void SetDefaultDevices(LPCWSTR devID, int erole=0)
{
    
    CoInitialize(NULL);

    OleInitialize(NULL);

    HRESULT isresult;

    //isresult = RegisterDevice(is_deviceID
    isresult = RegisterDevice(devID,erole);


   CoUninitialize();
    OleUninitialize();

    std::string message = std::system_category().message(isresult);

    std::cout << "Results: "<< message <<"\n";

}

