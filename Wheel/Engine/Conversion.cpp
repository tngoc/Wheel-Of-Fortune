#include "Conversion.h"

wchar_t* wchar(const char* org) {
	const size_t origsize = strlen(org) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize,org, _TRUNCATE);
	return _wcsdup(wcstring);
}