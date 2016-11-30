// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:

#include <windows.h>
#include <windowsx.h>	

// ����� ���������� C RunTime
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
// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
