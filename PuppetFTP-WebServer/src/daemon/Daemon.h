/*
 * Daemon.h
 *
 *  Created on: 11 sept. 2013
 *      Author: laplace
 */

#ifndef DAEMON_H_
#define DAEMON_H_

#include "IServerConfigurationProvider.h"

class Daemon {
private:
    IServerConfigurationProvider* _remoteDaemon;

protected:
    QString _pluginId;

public:
	Daemon(IServerConfigurationProvider* remoteDaemon);
	virtual ~Daemon();

    void        loadPlugin(const QString& pluginId, const QString& pluginName);
    void        unloadPlugin();
    bool        isCommandAvailabled(const QString& exec) const;
    void        exec(const QString& cmd);

    QString     getServerName()                 const;
    quint16     getServerPort()                 const;
    QString     getServerAddr()                 const;
    QString     getInternetProtocol()           const;
    quint16     getIdleTimeout()                const;
    quint16     getDataConnectionTimeout()      const;
    QString     getWelcomeMessage()             const;
    QString     getLogFile()                    const;
    bool        isAnonymousAllowed()            const;
    bool        isAnonymousUploadAllowed()      const;
    bool        isAnonymousCreateDirAllowed()   const;
    quint16     getVirtualUserAuthentication()  const;
    QStringList virtualUsers()                  const;


    void        setServerName(const QString& name);
    void        setServerPort(const quint16& port);
    void        setServerAddr(const QString& addr);
    void        setInternetProtocol(const QString& internetProtocol);
    void        setIdleTimeout(const quint16& idleTimeout);
    void        setDataConnectionTimeout(const quint16& dataConnectionTimeout);
    void        setWelcomeMessage(const QString& welcomeMessage);
    void        setLogFile(const QString& logName);
    void        setVirtualUserAuthentication(const quint16& user);

    void        enabledAnonymousAllowed(const bool& enabled);
    void        enabledAnonymousUploadAllowed(const bool& enabled);
    void        enabledAnonymousCreateDirAllowed(const bool& enabled);

    QString     getLastError() const;
    void        setParserFilename(const QString& name);

private:
	Daemon() : _remoteDaemon(0) {}
};

#endif /* DAEMON_H_ */
