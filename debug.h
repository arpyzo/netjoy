#define _WINSOCKAPI_    // stops windows.h from including winsock.h

#include <wx/wxprec.h>	// wxWidgets precompiled / standard headers

// Provides file name and line number for memory leaks
#ifdef _DEBUG
#include <crtdbg.h>

#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DEBUG_NEW

#else
#define DEBUG_NEW new
#endif