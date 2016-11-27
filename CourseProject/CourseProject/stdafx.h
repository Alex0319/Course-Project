// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <windows.h>
#include <windowsx.h>	

// Файлы заголовков C RunTime
#include <stdlib.h>
#include <commctrl.h>
#include <commdlg.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <ctime>
#include <map>

#include "CourseProject.h"
#include "BitmapModificator.h"
#include "Block.h"
#include "Figure.h"
#include "Square.h"
#include "HorizontalLine.h"
#include "VerticalLine.h"
#include "Angle.h"

#include "FigureFactory.h"
#include "SquareFactory.h"
#include "HorizontalLineFactory.h"
#include "VerticalLineFactory.h"
#include "AngleFactory.h"

#include "PlayingField.h"
#include "Button.h"
#include "ButtonController.h"

// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
