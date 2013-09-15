/*
 * Server.cpp
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#include "Server.h"

namespace Model {

Server::Server() {
    _id = 0;
}

Server::~Server() {
}

quint32     Server::getId()         const                    { return _id;                }
QString     Server::getName()       const                    { return _name;              }
QString     Server::getAddress()    const                    { return _address;           }
quint16     Server::getPort()       const                    { return _port;              }
QString     Server::getDaemonId()   const                    { return _daemon_id;         }
QString     Server::getType()       const                    { return _type;              }
QString     Server::getConfigPath() const                    { return _config_path;       }

void        Server::setId(quint32 id)                        { _id       = id;            }
void        Server::setName(const QString& name)             { _name     = name;          }
void        Server::setAddress(const QString& address)       { _address  = address;       }
void        Server::setPort(quint16 port)                    { _port     = port;          }
void        Server::setDaemonId(const QString& daemonId)     { _daemon_id = daemonId;     }
void        Server::setType(const QString& type)             { _type = type;              }
void        Server::setConfigPath(const QString& configPath) { _config_path = configPath; }
} // namespace Model
