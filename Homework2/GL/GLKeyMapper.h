#pragma once

#include <unordered_map>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

using GLKeyMap = std::pair<int, std::string>;
using GLKeycodeMap = std::pair<std::string, int>;

const int GLKeyUp = GLUT_KEY_UP + 128;
const int GLKeyDown = GLUT_KEY_DOWN + 128;
const int GLKeyLeft = GLUT_KEY_LEFT + 128;
const int GLKeyRight = GLUT_KEY_RIGHT + 128;
const int GLKeyF1 = GLUT_KEY_F1 + 128;
const int GLKeyF2 = GLUT_KEY_F2 + 128;
const int GLKeyF3 = GLUT_KEY_F3 + 128;
const int GLKeyF4 = GLUT_KEY_F4 + 128;
const int GLKeyF5 = GLUT_KEY_F5 + 128;
const int GLKeyF6 = GLUT_KEY_F6 + 128;
const int GLKeyF7 = GLUT_KEY_F7 + 128;
const int GLKeyF8 = GLUT_KEY_F8 + 128;
const int GLKeyF9 = GLUT_KEY_F9 + 128;
const int GLKeyF10 = GLUT_KEY_F10 + 128;
const int GLKeyF11 = GLUT_KEY_F11 + 128;
const int GLKeyF12 = GLUT_KEY_F12 + 128;
const int GLKeyLShift = GLUT_KEY_SHIFT_L + 128;
const int GLKeyRShift = GLUT_KEY_SHIFT_R + 128;
const int GLKeyLCtrl = GLUT_KEY_CTRL_L + 128;
const int GLKeyRCtrl = GLUT_KEY_CTRL_R + 128;
const int GLKeyLAlt = GLUT_KEY_ALT_L + 128;
const int GLKeyRAlt = GLUT_KEY_ALT_R + 128;
const int GLKeyDelete = GLUT_KEY_DELETE + 128;
const int GLKeyInsert = GLUT_KEY_INSERT + 128;
const int GLKeyPageUp = GLUT_KEY_PAGE_UP + 128;
const int GLKeyPageDown = GLUT_KEY_PAGE_DOWN + 128;
const int GLKeyHome = GLUT_KEY_HOME + 128;
const int GLKeyEnd = GLUT_KEY_END + 128;
const int GLKeyNumLock = GLUT_KEY_NUM_LOCK + 128;
const int GLKeyBegin = GLUT_KEY_BEGIN + 128;
const int GLKeyRepeatDefault = GLUT_KEY_REPEAT_DEFAULT + 128;
const int GLKeyRepeatOff = GLUT_KEY_REPEAT_OFF + 128;
const int GLKeyRepeatOn = GLUT_KEY_REPEAT_ON + 128;

class GLKeyMapper
{
public:
	GLKeyMapper()
	{
		for (char ch = 1; ch < 127; ++ch)
		{
			std::string keyString = std::string(1, ch);

			if (ch == 8)
			{
				keyString = "Backspace";
			}
			else if (ch == 9)
			{
				keyString = "Tab";
			}
			else if (ch == 13)
			{
				keyString = "Enter";
			}
			else if (ch == ' ')
			{
				keyString = "Space";
			}
			else if (ch < 32)
			{
				continue;
			}

			this->KeyMapper[ch] = keyString;
			this->KeycodeMapper[keyString] = ch;
		}
	}

	std::string operator[](const int& key)
	{
		return this->KeyMapper[key];
	}

	int operator[](const std::string& key)
	{
		return this->KeycodeMapper[key];
	}

	std::unordered_map<int, std::string> KeyMapper =
	{
		GLKeyMap(GLKeyUp, "Up"),
		GLKeyMap(GLKeyDown, "Down"),
		GLKeyMap(GLKeyLeft, "Left"),
		GLKeyMap(GLKeyRight, "Right"),
		GLKeyMap(GLKeyF1, "F1"),
		GLKeyMap(GLKeyF2, "F2"),
		GLKeyMap(GLKeyF3, "F3"),
		GLKeyMap(GLKeyF4, "F4"),
		GLKeyMap(GLKeyF5, "F5"),
		GLKeyMap(GLKeyF6, "F6"),
		GLKeyMap(GLKeyF7, "F7"),
		GLKeyMap(GLKeyF8, "F8"),
		GLKeyMap(GLKeyF9, "F9"),
		GLKeyMap(GLKeyF10, "F10"),
		GLKeyMap(GLKeyF11, "F11"),
		GLKeyMap(GLKeyF12, "F12"),
		GLKeyMap(GLKeyLShift, "LShift"),
		GLKeyMap(GLKeyRShift, "RShift"),
		GLKeyMap(GLKeyLCtrl, "LCtrl"),
		GLKeyMap(GLKeyRCtrl, "RCtrl"),
		GLKeyMap(GLKeyLAlt, "LAlt"),
		GLKeyMap(GLKeyRAlt, "RAlt"),
		GLKeyMap(GLKeyDelete, "Delete"),
		GLKeyMap(GLKeyInsert, "Insert"),
		GLKeyMap(GLKeyPageUp, "PageUp"),
		GLKeyMap(GLKeyPageDown, "PageDown"),
		GLKeyMap(GLKeyHome, "Home"),
		GLKeyMap(GLKeyEnd, "End"),
		GLKeyMap(GLKeyNumLock, "NumLock"),
		GLKeyMap(GLKeyBegin, "Begin"),
		GLKeyMap(GLKeyRepeatDefault, "RepeatDefault"),
		GLKeyMap(GLKeyRepeatOff, "RepeatOff"),
		GLKeyMap(GLKeyRepeatOn, "RepeatOn")
	};

	std::unordered_map<std::string, int> KeycodeMapper =
	{
		GLKeycodeMap("Up", GLKeyUp),
		GLKeycodeMap("DOWN", GLKeyDown),
		GLKeycodeMap("Left", GLKeyLeft),
		GLKeycodeMap("Right", GLKeyRight),
		GLKeycodeMap("F1", GLKeyF1),
		GLKeycodeMap("F2", GLKeyF2),
		GLKeycodeMap("F3", GLKeyF3),
		GLKeycodeMap("F4", GLKeyF4),
		GLKeycodeMap("F5", GLKeyF5),
		GLKeycodeMap("F6", GLKeyF6),
		GLKeycodeMap("F7", GLKeyF7),
		GLKeycodeMap("F8", GLKeyF8),
		GLKeycodeMap("F9", GLKeyF9),
		GLKeycodeMap("F10", GLKeyF10),
		GLKeycodeMap("F11", GLKeyF11),
		GLKeycodeMap("F12", GLKeyF12),
		GLKeycodeMap("LShift", GLKeyLShift),
		GLKeycodeMap("RShift", GLKeyRShift),
		GLKeycodeMap("LCtrl", GLKeyLCtrl),
		GLKeycodeMap("RCtrl", GLKeyRCtrl),
		GLKeycodeMap("LAlt", GLKeyLAlt),
		GLKeycodeMap("RAlt", GLKeyRAlt),
		GLKeycodeMap("Delete", GLKeyDelete),
		GLKeycodeMap("Insert", GLKeyInsert),
		GLKeycodeMap("PageUp", GLKeyPageUp),
		GLKeycodeMap("PageDown", GLKeyPageDown),
		GLKeycodeMap("Home", GLKeyHome),
		GLKeycodeMap("End", GLKeyEnd),
		GLKeycodeMap("NumLock", GLKeyNumLock),
		GLKeycodeMap("Begin", GLKeyBegin),
		GLKeycodeMap("RepeatDefault", GLKeyRepeatDefault),
		GLKeycodeMap("RepeatOff", GLKeyRepeatOff),
		GLKeycodeMap("RepeatOn", GLKeyRepeatOn)
	};
};