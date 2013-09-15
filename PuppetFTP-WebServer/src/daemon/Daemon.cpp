/*
 * Daemon.cpp
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#include <QDebug>
#include <QString>
#include <QVariant>
#include <QStringList>
#include "Daemon.h"

Daemon::Daemon(IServerConfigurationProvider* remoteDaemon) :
	_remoteDaemon(remoteDaemon) {
}

Daemon::~Daemon() {
	if (_remoteDaemon != 0) {
		delete _remoteDaemon;
	}
}

void    Daemon::loadPlugin(const QString& pluginId, const QString& pluginName) {
    _remoteDaemon->loadPlugin(pluginId, pluginName);
    _pluginId = pluginId;
}
void    Daemon::unloadPlugin() {
    _remoteDaemon->unloadPlugin(_pluginId);
}

void    Daemon::setParserFilename(const QString& name) {
    _remoteDaemon->set(_pluginId, "parserFilename", name);
}

QString Daemon::getLastError() const {
    return _remoteDaemon->lastErrorString();
}

bool Daemon::isCommandAvailabled(const QString& exec) const {
    QStringList cmd;
    cmd << "start" << "stop" << "restart";
    return cmd.contains(exec);
}

void Daemon::exec(const QString& cmd) {
    _remoteDaemon->exec(_pluginId, cmd);
}

/*** GETTER ***/
// MISC
QString Daemon::getServerName()                 const { return _remoteDaemon->get(_pluginId, "serverNameProperty").toString();  }
quint16 Daemon::getServerPort()                 const { return _remoteDaemon->get(_pluginId, "serverPort").toUInt();            }
QString Daemon::getServerAddr()                 const { return _remoteDaemon->get(_pluginId, "serverAddr").toString();          }
QString Daemon::getInternetProtocol()           const { return _remoteDaemon->get(_pluginId, "internetProtocol").toString();    }
quint16 Daemon::getIdleTimeout()                const { return _remoteDaemon->get(_pluginId, "idleTimeout").toUInt();           }
quint16 Daemon::getDataConnectionTimeout()      const { return _remoteDaemon->get(_pluginId, "dataConnectionTimeout").toUInt(); }
QString Daemon::getWelcomeMessage()             const { return _remoteDaemon->get(_pluginId, "welcomeMessage").toString();      }
QString Daemon::getLogFile()                    const { return _remoteDaemon->get(_pluginId, "logFile").toString();             }
// USER
quint16 Daemon::getVirtualUserAuthentication()  const { return _remoteDaemon->get(_pluginId, "serverPort").toUInt();            }
QStringList Daemon::virtualUsers()              const { return _remoteDaemon->get(_pluginId, "virtualUser").toStringList();     }
// ANONYMOUS
bool Daemon::isAnonymousAllowed()               const { return _remoteDaemon->get(_pluginId, "anonymousEnable").toBool();       }
bool Daemon::isAnonymousUploadAllowed()         const { return _remoteDaemon->get(_pluginId, "anonUploadEnable").toBool();      }
bool Daemon::isAnonymousCreateDirAllowed()      const { return _remoteDaemon->get(_pluginId, "anonMkdirWriteEnable").toBool();  }

/*** SETTER ***/
// MISC
void        Daemon::setServerName(const QString& name)                              { _remoteDaemon->set(_pluginId, "serverNameProperty", name);                     }
void        Daemon::setServerPort(const quint16& port)                              { _remoteDaemon->set(_pluginId, "serverPort", port);                             }
void        Daemon::setServerAddr(const QString& addr)                              { _remoteDaemon->set(_pluginId, "serverAddr", addr);                             }
void        Daemon::setInternetProtocol(const QString& internetProtocol)            { _remoteDaemon->set(_pluginId, "internetProtocol", internetProtocol);           }
void        Daemon::setIdleTimeout(const quint16& idleTimeout)                      { _remoteDaemon->set(_pluginId, "idleTimeout", idleTimeout);                     }
void        Daemon::setDataConnectionTimeout(const quint16& dataConnectionTimeout)  { _remoteDaemon->set(_pluginId, "dataConnectionTimeout", dataConnectionTimeout); }
void        Daemon::setWelcomeMessage(const QString& welcomeMessage)                { _remoteDaemon->set(_pluginId, "welcomeMessage", welcomeMessage);               }
void        Daemon::setLogFile(const QString& logName)                              { _remoteDaemon->set(_pluginId, "logFile", logName);                             }
// USER
void        Daemon::setVirtualUserAuthentication(const quint16& user)               { _remoteDaemon->set(_pluginId, "serverPort", user);                             }
// ANONYMOUS
void        Daemon::enabledAnonymousAllowed(const bool& enabled)                    { _remoteDaemon->set(_pluginId, "anonymousEnable", enabled);                     }
void        Daemon::enabledAnonymousUploadAllowed(const bool& enabled)              { _remoteDaemon->set(_pluginId, "anonUploadEnable", enabled);                    }
void        Daemon::enabledAnonymousCreateDirAllowed(const bool& enabled)           { _remoteDaemon->set(_pluginId, "anonMkdirWriteEnable", enabled);                }
