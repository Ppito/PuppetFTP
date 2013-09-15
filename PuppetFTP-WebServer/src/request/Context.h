/*
 * Context.h
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <QString>
#include <QVariant>
#include <QVariantHash>
#include "Session.h"

class Context {
public:
	Context();
	virtual ~Context();

	Session* getSession() const;
	void setSession(Session* session);

	bool hasGlobal(const QString& name) const;
	QVariant getGlobal(const QString& name) const;
	void setGlobal(const QString& name, const QVariant& value);

private:
	Session* _session;
	QVariantHash _globals;
};

#endif /* CONTEXT_H_ */
