/*
 * KeyStroke.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: nuc
 */

#include "KeyStroke.h"

CKeyStroke::CKeyStroke() {
	m_IsHide = false;
	m_IsWait = false;
	tcgetattr(0, &m_Default);
}

CKeyStroke::~CKeyStroke() {
	if ( m_IsHide || m_IsWait )
		tcsetattr(0, TCSANOW, &m_Default);
}

void CKeyStroke::Hide() {
	if ( !m_IsHide ) {
		termios tty;
		tcgetattr(0, &tty);
		/* disable echo */
		tty.c_lflag &= ~ECHO;
		tcsetattr(0, TCSANOW, &tty);

		m_IsHide = true;
	}
}

void CKeyStroke::Show() {
	if ( m_IsHide ) {
		termios tty;
		tcgetattr(0, &tty);
		/* re-enable echo */
		tty.c_lflag |= ECHO;
		tcsetattr(0, TCSANOW, &tty);

		m_IsHide = false;
	}
}

void CKeyStroke::Wait(const char& pKey) {
	if ( !m_IsWait ) {
		while (std::cin.get() != pKey)
			continue;
		return;
	}
}

/*Any key*/
void CKeyStroke::Wait() {
	if ( !m_IsWait ) {
		termios tty_new;
		termios tty_old;
		tcgetattr(0, &tty_old);

		tty_new = tty_old;					/* backup*/
		tty_new.c_lflag &= ~ICANON;      	/* disable canonical mode */
		tty_new.c_cc[VMIN] = 1;          	/* wait until at least one keystroke available */
		tty_new.c_cc[VTIME] = 0;         	/* no timeout */
		tcsetattr(0, TCSANOW, &tty_new);

		Hide();
		std::cin.get();
		Show();

		tcsetattr(0, TCSANOW, &tty_old);	/* restore old*/
	}
	return;
}
