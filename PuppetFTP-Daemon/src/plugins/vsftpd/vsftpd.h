#ifndef VSFTPD_H
#define VSFTPD_H

#include "vsftpdconfig.h"
#include "serverconfig.h"
#include "metaplugin.h"

class Vsftpd : public MetaPlugin
{
    Q_OBJECT

public:
    Vsftpd();

    // Plugin default config loading from file deprecated soon !
    void initialize(ServerConfig & config);

    MetaConfig * getMetaConfigInstance();

private:
    // Deprecated Soon !
    QString         m_configFile;
    QString         m_binPath;
    QString         m_serverName;
    QString         m_serverAddr;
};

#endif // VSFTPD_H
