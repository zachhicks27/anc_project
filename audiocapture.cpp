#include <Audioclient.h>
#include <mmdeviceapi.h>
#include <objbase.h>
#include <iostream>

#define REFTIMES_PER_SEC 10000000

#pragma comment(lib, "Ole32.lib")

int main() {
    HRESULT hr;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    IAudioClient *pAudioClient = NULL;
    WAVEFORMATEX *pwfx = NULL;
    REFERENCE_TIME hnsRequestedDuration = REFTIMES_PER_SEC;
    UINT32 bufferFrameCount;
    IAudioCaptureClient *pCaptureClient = NULL;
    IAudioRenderClient *pRenderClient = NULL;
    BYTE *pData;
    UINT32 framesAvailable;

    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "Initialization of COM library failed." << std::endl;
        return 1;
    }

    // Create device enumerator.
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL,
                          __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) {
        std::cerr << "CoCreateInstance failed." << std::endl;
        return 1;
    }

    // Get default audio endpoint.
    hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice);
    if (FAILED(hr)) {
        std::cerr << "Getting default audio endpoint failed." << std::endl;
        return 1;
    }

    // Initialize audio client.
    hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL,
                           (void**)&pAudioClient);
    if (FAILED(hr)) {
        std::cerr << "Initializing audio client failed." << std::endl;
        return 1;
    }

    // Set audio stream format.
    hr = pAudioClient->GetMixFormat(&pwfx);
    if (FAILED(hr)) {
        std::cerr << "Getting mix format failed." << std::endl;
        return 1;
    }

    // Other initialization and capture code...
    
    CoUninitialize();

    return 0;
}






