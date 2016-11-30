// stdafx.h: включаемый файл для стандартных системных включаемых файлов
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:

#include <windows.h>
#include <windowsx.h>	

// Файлы заголовков C RunTime
#include <stdlib.h>
#include <commctrl.h>
#include <commdlg.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <vector>

#include "CourseProject.h"
#include "BitmapModificator.h"
#include "Block.h"
#include "FieldBlock.h"
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

#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib,"msimg32")
// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
