/*
 * DaemonManager.cpp
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#include <QDebug>
#include "DaemonManager.h"
#include "CommunicationService.h"
#include "CORBAImpl/Provider.h"

DaemonManager* DaemonManager::_instance = 0;

DaemonManager* DaemonManager::instance() {
	if (_instance == 0) {
		_instance = new DaemonManager();
	}
	return _instance;
}

void DaemonManager::destroy() {
	if (_instance != 0) {
		delete _instance;
		_instance = 0;
	}
}

DaemonManager::DaemonManager() : _configured(false) {
}

DaemonManager::~DaemonManager() {
	for (QHash<QString, Daemon*>::iterator it = _daemons.begin(); it != _daemons.end(); it++) {
		delete it.value();
	}
	CommunicationService::dispose();
}

bool DaemonManager::configure(const QMap<QString, QString>& options) {
	if (_configured == false) {
		CommunicationService::setProvider(new CORBA::Impl::Provider());
		CommunicationService::configure(INetworkAccessProvider::MODE::SERVER, options);
		_configured = true;
	}
	return true;
}

Daemon* DaemonManager::getDaemon(const QString& name) {
	Daemon* daemon = 0;
	if (_daemons.contains(name)) {
		daemon = _daemons.value(name);
	}
	else {
		IServerConfigurationProvider* client = CommunicationService::provider()->getServiceClient(name);
		if (client != 0) {
            daemon = new Daemon(client);
			_daemons[name] = daemon;
		}
		else {
			qCritical() << "Unable to find " << name;
		}
	}
	return daemon;
}
