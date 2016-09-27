/*
 * KeyStroke.h
 *
 *  Created on: Sep 21, 2016
 *      Author: nuc
 */

#ifndef KEYSTROKE_H_
#define KEYSTROKE_H_

#include <iostream>
#include <termios.h>
#include <cstdlib>

class CKeyStroke {
public:
	CKeyStroke();
	virtual ~CKeyStroke();

	void Hide();
	void Show();
	void Wait(const char &pKey);
	void Wait();
protected:
	termios m_Default;
	bool m_IsHide;
	bool m_IsWait;
};

#endif /* KEYSTROKE_H_ */
