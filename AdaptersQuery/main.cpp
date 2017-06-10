// STD
#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

// DXGI
#include <d3d12.h>
#include <dxgi.h>



void main() {

	HRESULT hr;

	IDXGIFactory* dxgiFactory = nullptr;
	if (!SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&dxgiFactory))) {
		std::clog << "cannot create dxgi.\n";
		return;
	}

	uint32_t adapterCount = 0;
	IDXGIAdapter* adapter = nullptr;
	std::vector<IDXGIAdapter*> adapterList;
	while (dxgiFactory->EnumAdapters(adapterCount, &adapter) != DXGI_ERROR_NOT_FOUND) {
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);

		wchar_t idStr[4];
		_itow_s(adapterCount, idStr, 10);

		std::wstring text = L"Adapter ";
		text += idStr;
		text += L" \t";
		text += desc.Description;
		text += L"\n";

		std::clog << std::string(text.begin(), text.end());

		adapterList.push_back(adapter);
		++adapterCount;
	}
}