/*
 * Context.cpp
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#include "Context.h"

Context::Context() : _session(0) {
}

Context::~Context() {
}

Session* Context::getSession() const {
	return _session;
}

void Context::setSession(Session* session) {
	_session = session;
}

bool Context::hasGlobal(const QString& name) const {
	return _globals.contains(name);
}

QVariant Context::getGlobal(const QString& name) const {
	if (_globals.contains(name)) {
		return _globals.value(name);
	}
	return QVariant();
}

void Context::setGlobal(const QString& name, const QVariant& value) {
	_globals[name] = value;
}

