/*
 * ServerConfWrapper.cpp
 *
 *  Created on: 6 janv. 2013
 *      Author: laplace
 */

#include "ServerConfWrapper.h"

namespace UI {

ServerConfWrapper::ServerConfWrapper(Daemon* daemon) : _daemon(daemon) {
}

ServerConfWrapper::~ServerConfWrapper() {
}

QString     ServerConfWrapper::getServerName()                  const { return _daemon->getServerName();                }
QString     ServerConfWrapper::getServerAddr()                  const { return _daemon->getServerAddr();                }
quint16     ServerConfWrapper::getServerPort()                  const { return _daemon->getServerPort();                }
QString     ServerConfWrapper::getInternetProtocol()            const { return _daemon->getInternetProtocol();          }
quint16     ServerConfWrapper::getIdleTimeout()                 const { return _daemon->getIdleTimeout();               }
quint16     ServerConfWrapper::getDataConnectionTimeout()       const { return _daemon->getDataConnectionTimeout();     }
bool        ServerConfWrapper::isAnonymousAllowed()             const { return _daemon->isAnonymousAllowed();           }
bool        ServerConfWrapper::isAnonymousUploadAllowed()       const { return _daemon->isAnonymousUploadAllowed();     }
bool        ServerConfWrapper::isAnonymousCreateDirAllowed()    const { return _daemon->isAnonymousCreateDirAllowed();  }
quint16     ServerConfWrapper::getVirtualUserAuthentication()   const { return _daemon->getVirtualUserAuthentication(); }
//QStringList ServerConfWrapper::virtualUsers()                   const { return _daemon->virtualUsers();                 }
QString     ServerConfWrapper::getWelcomeMessage()              const { return _daemon->getWelcomeMessage();            }
QString     ServerConfWrapper::getLogFile()                     const { return _daemon->getLogFile();                   }


void        ServerConfWrapper::setServerName(const QString& name)                           { _daemon->setServerName(name);                         }
void        ServerConfWrapper::setServerAddr(const QString& addr)                           { _daemon->setServerAddr(addr);                         }
void        ServerConfWrapper::setServerPort(const quint16& port)                           { _daemon->setServerPort(port);                         }
void        ServerConfWrapper::setInternetProtocol(const QString& intenetProtocol)          { _daemon->setInternetProtocol(intenetProtocol);        }
void        ServerConfWrapper::setIdleTimeout(const quint16& idleTimeout)                   { _daemon->setIdleTimeout(idleTimeout);                 }
void        ServerConfWrapper::setDataConnectionTimeout(const quint16& dataTimeout)         { _daemon->setDataConnectionTimeout(dataTimeout);       }
void        ServerConfWrapper::enabledAnonymousAllowed(const bool& enabled)                 { _daemon->enabledAnonymousAllowed(enabled);            }
void        ServerConfWrapper::enabledAnonymousUploadAllowed(const bool& enabled)           { _daemon->enabledAnonymousUploadAllowed(enabled);      }
void        ServerConfWrapper::enabledAnonymousCreateDirAllowed(const bool& enabled)        { _daemon->enabledAnonymousCreateDirAllowed(enabled);   }
void        ServerConfWrapper::setVirtualUserAuthentication(const quint16& user)            { _daemon->setVirtualUserAuthentication(user);          }
//void        ServerConfWrapper::setVirtualUsers(const QStringList& user)                     { _daemon->setVirtualUsers(user);                       }
void        ServerConfWrapper::setWelcomeMessage(const QString& welcomeMessage)             { _daemon->setWelcomeMessage(welcomeMessage);           }
void        ServerConfWrapper::setLogFile(const QString& logfile)                           { _daemon->setLogFile(logfile);                         }

} // namespace UI
