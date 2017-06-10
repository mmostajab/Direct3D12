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

		uint32_t displayCount = 0;
		IDXGIOutput* output = nullptr;
		while (adapter->EnumOutputs(displayCount, &output) != DXGI_ERROR_NOT_FOUND) {
			DXGI_OUTPUT_DESC desc;
			output->GetDesc(&desc);

			wchar_t idStr[4];
			_itow_s(displayCount, idStr, 10);

			std::wstring text = L"\tDisplay ";
			text += idStr;
			text += L" \t";
			text += desc.DeviceName;
			text += L"\n";

			std::clog << std::string(text.begin(), text.end());
			
			++displayCount;

			DXGI_FORMAT displayFormat = DXGI_FORMAT_R8G8B8A8_UINT;
			uint32_t displayModeCount = 0;
			uint32_t flags = 0;
			uint32_t modeCount;

			output->GetDisplayModeList(displayFormat, flags, &modeCount, nullptr);

			std::vector<DXGI_MODE_DESC> modeList(modeCount);
			output->GetDisplayModeList(displayFormat, flags, &modeCount, modeList.data());

			uint32_t modeId = 0;
			for (auto& m : modeList) {
				uint32_t n = m.RefreshRate.Numerator;
				uint32_t d = m.RefreshRate.Denominator;

				std::wstring text = L"\t\tMode ";
				text += std::to_wstring(modeId);
				text += L" \t";
				text += L"Width = " + std::to_wstring(m.Width) + L" Height = " + std::to_wstring(m.Height) + L" Referesh = " + std::to_wstring(n) + L"/" + std::to_wstring(d) + L"\n";

				std::clog << std::string(text.begin(), text.end());

				modeId++;
			}

		}

	}
}