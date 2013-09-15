/*
 * Server.h
 *
 *  Created on: 4 oct. 2012
 *      Author: laplace
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <QObject>
#include <QString>

namespace Model {

class Server : public QObject {
    Q_OBJECT
    Q_PROPERTY(quint32     id          READ getId         WRITE setId         )
    Q_PROPERTY(QString     name        READ getName       WRITE setName       )
    Q_PROPERTY(QString     address     READ getAddress    WRITE setAddress    )
    Q_PROPERTY(quint16     port        READ getPort       WRITE setPort       )
    Q_PROPERTY(QString     daemon_id   READ getDaemonId   WRITE setDaemonId   )
    Q_PROPERTY(QString     type        READ getType       WRITE setType       )
    Q_PROPERTY(QString     config_path READ getConfigPath WRITE setConfigPath )

protected:
    quint32     _id;
    QString     _name;
    QString     _address;
    quint16     _port;
    QString     _daemon_id;
    QString     _type;
    QString     _config_path;

public:
    Server();
    virtual ~Server();

    Q_INVOKABLE quint32     getId()         const;
    Q_INVOKABLE QString     getName()       const;
    Q_INVOKABLE QString     getAddress()    const;
    Q_INVOKABLE quint16     getPort()       const;
    Q_INVOKABLE QString     getDaemonId()   const;
    Q_INVOKABLE QString     getType()       const;
    Q_INVOKABLE QString     getConfigPath() const;

    Q_INVOKABLE void        setId(quint32 id);
    Q_INVOKABLE void        setName(const QString& name);
    Q_INVOKABLE void        setAddress(const QString& address);
    Q_INVOKABLE void        setPort(quint16 port);
    Q_INVOKABLE void        setDaemonId(const QString& daemonId);
    Q_INVOKABLE void        setType(const QString& type);
    Q_INVOKABLE void        setConfigPath(const QString& configPath);
};

} // namespace Model

#endif /* SERVER_H_ */
