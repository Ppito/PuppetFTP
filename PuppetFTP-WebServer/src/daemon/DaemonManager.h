/*
 * DaemonManager.h
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#ifndef DAEMONMANAGER_H_
#define DAEMONMANAGER_H_

#include <QString>
#include <QMap>
#include <QHash>
#include "Daemon.h"


class DaemonManager {
public:
	static DaemonManager* instance();
	static void           destroy();

	bool configure(const QMap<QString, QString>& options);
	Daemon* getDaemon(const QString& name);

private:
	DaemonManager();
	DaemonManager(const DaemonManager& dm);
	virtual ~DaemonManager();
	DaemonManager& operator=(const DaemonManager& dm);

	static DaemonManager* _instance;
	bool _configured;
	QHash<QString, Daemon*> _daemons;
};

#endif /* DAEMONMANAGER_H_ */
