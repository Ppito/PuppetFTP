/*
 * ServerConfWrapper.h
 *
 *  Created on: 6 janv. 2013
 *      Author: laplace
 */

#ifndef SERVERCONFWRAPPER_H_
#define SERVERCONFWRAPPER_H_

#include <QObject>
#include <QStringList>
#include "Daemon.h"

namespace UI {

/**
 * This class allows you to use a IServerConfigurationProvider with
 * the Qt's Meta Object System only for reading properties. This class
 * has been created in order to construct the UI Widgets in the same
 * way that the Model.
 *
 * This class does not inherit from IServerConfigurationProvider because
 * it must only allow property reading and does not need any behavioral
 * features.
 */
class ServerConfWrapper: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString                                                         server_name                    READ getServerName                WRITE setServerName                     )
    Q_PROPERTY(QString                                                         server_addr                    READ getServerAddr                WRITE setServerAddr                     )
    Q_PROPERTY(quint16                                                         server_port                    READ getServerPort                WRITE setServerPort                     )
    Q_PROPERTY(QString                                                         internet_protocol              READ getInternetProtocol          WRITE setInternetProtocol               )
    Q_PROPERTY(quint16                                                         idle_timeout                   READ getIdleTimeout               WRITE setIdleTimeout                    )
    Q_PROPERTY(quint16                                                         data_timeout                   READ getDataConnectionTimeout     WRITE setDataConnectionTimeout          )
    Q_PROPERTY(QString                                                         welcome_message                READ getWelcomeMessage            WRITE setWelcomeMessage                 )
    Q_PROPERTY(QString                                                         log_file                       READ getLogFile                   WRITE setLogFile                        )
    Q_PROPERTY(bool                                                            anonymous_allowed              READ isAnonymousAllowed           WRITE enabledAnonymousAllowed           )
    Q_PROPERTY(bool                                                            anonymous_upload_allowed       READ isAnonymousUploadAllowed     WRITE enabledAnonymousUploadAllowed     )
    Q_PROPERTY(bool                                                            anonymouse_create_dir_allowed  READ isAnonymousCreateDirAllowed  WRITE enabledAnonymousCreateDirAllowed  )
    Q_PROPERTY(quint16                                                         virtual_user_auth              READ getVirtualUserAuthentication WRITE setVirtualUserAuthentication      )
//    Q_PROPERTY(QStringList                                                     virtual_users                  READ virtualUsers                 WRITE setVirtualUsers                   )

private:
    ServerConfWrapper();
    Daemon* _daemon;

public:
    ServerConfWrapper(Daemon* daemon);
    virtual ~ServerConfWrapper();

    /*** GETTER ***/
    // Misc
    QString         getServerName()                 const;
    QString         getServerAddr()                 const;
    quint16         getServerPort()                 const;
    QString         getInternetProtocol()           const;
    quint16         getIdleTimeout()                const;
    quint16         getDataConnectionTimeout()      const;
    QString         getWelcomeMessage()             const;
    QString         getLogFile()                    const;
    // Anonymous
    bool            isAnonymousAllowed()            const;
    bool            isAnonymousUploadAllowed()      const;
    bool            isAnonymousCreateDirAllowed()   const;
    // User
    quint16         getVirtualUserAuthentication()  const;
    //QStringList   virtualUsers()                  const;

    /*** SETTER ***/
    // Misc
    void            setServerName(const QString& name);
    void            setServerPort(const quint16& port);
    void            setServerAddr(const QString& addr);
    void            setInternetProtocol(const QString& internetProtocol);
    void            setIdleTimeout(const quint16& idleTimeout);
    void            setDataConnectionTimeout(const quint16& dataConnectionTimeout);
    void            setWelcomeMessage(const QString& welcomeMessage);
    void            setLogFile(const QString& logName);
    // Anonymous
    void            enabledAnonymousAllowed(const bool& enabled);
    void            enabledAnonymousUploadAllowed(const bool& enabled);
    void            enabledAnonymousCreateDirAllowed(const bool& enabled);
    // User
    void            setVirtualUserAuthentication(const quint16& user);
//    void            setVirtualUsers(const QString& user);


};

} // namespace UI

#endif /* SERVERCONFWRAPPER_H_ */
