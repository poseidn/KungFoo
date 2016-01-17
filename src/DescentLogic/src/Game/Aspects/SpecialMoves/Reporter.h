/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

class InputContainer;

namespace special_move {

class DirectionReport {
public:

	DirectionReport() :
			m_dir(InputItem::DirectionEnum::Undefined) {
	}

	DirectionReport(InputItem::DirectionEnum dir) :
			m_dir(dir) {
	}

	void report(InputItem & inp) const {
		inp = InputItem(m_dir);
	}
private:
	InputItem::DirectionEnum m_dir;
};

class KeyPressReport {
public:
	/*KeyPressReport(KeyPressReport const & other) :
	 m_key(other.m_key) {
	 }*/

	KeyPressReport() :
			m_key(InputItem::KeyPressEnum::Undefined) {
	}

	KeyPressReport(InputItem::KeyPressEnum key) :
			m_key(key) {
	}

	void report(InputItem & inp) const {
		inp = InputItem(m_key);
	}
private:
	InputItem::KeyPressEnum m_key;
};

template<class TReport>
class Reporter {
public:
	typedef std::function<bool(InputContainer const&)> InputCheck;

	Reporter() :
			m_lmbInputCheck([](InputContainer const& ) {
					// has to be overwritten in any case
					assert( false);
					return false;}), m_reportedAlready(false) {
	}

	Reporter(InputCheck check, TReport report) :
			m_lmbInputCheck(check), m_reportedAlready(false), m_report(report) {
	}

	bool report(InputContainer const& cont, InputItem & inp) {
		if (m_lmbInputCheck(cont)) {
			if (!m_reportedAlready) {
				m_reportedAlready = true;
				m_report.report(inp);
				return true;
			}
		} else {
			m_reportedAlready = false;
		}

		return false;
	}

private:
	InputCheck m_lmbInputCheck;
	bool m_reportedAlready;
	TReport m_report;
};

}
