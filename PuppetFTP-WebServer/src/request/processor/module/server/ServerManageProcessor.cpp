#include <QMetaProperty>
#include <exception>
#include "ServerManageProcessor.h"
#include "DefaultPageRenderer.h"
#include "CORBAImpl/Provider.h"
#include "CommunicationService.h"
#include "IServerConfigurationProvider.h"
#include "RuntimeException.h"
#include "processor/AbstractRequestProcessor.h"
#include "ModelWidgetFactory.h"
#include "DatabaseManager.h"
#include "Widget.h"
#include "Helper.h"
#include "ITable.h"
#include "Server.h"
#include "Session.h"
#include "SessionManager.h"
#include "CommunicationException.h"
#include "Translate.h"
#include "DaemonManager.h"
#include "ServerConfWrapper.h"

ServerManageProcessor::ServerManageProcessor() : AbstractRequestProcessor() {
}

ServerManageProcessor::~ServerManageProcessor() {
}

void ServerManageProcessor::process(HTTPRequest& request) {
    _id        = request.getParameter("id").toInt();
    Session* s = SessionManager::instance()->getSession(request.getSessionId());
    addNotify(s->getNotification("edit"));
    addNotify(s->getNotification("service"));

    QMap<QString, QVariant> param;
    param.insert("id", _id);

    _form = UI::ModelWidgetFactory::instance()->getEditorWidget("serverConfigurationEditor");
    if (_form == NULL){
        s->setNotification("edit", "Model Form Entity 'serverConfiguration' doesn't exists.", UI::Notify::ERROR);
        request.redirect(Helper::gen_url("serverList", param));
        return;
    }
    _form->getForm()->setAction(Helper::gen_url("serverManage", param));

    _formAnon = UI::ModelWidgetFactory::instance()->getEditorWidget("serverAnonConfigurationEditor");
    if (_formAnon == NULL){
        s->setNotification("edit", "Model Form Entity 'serverAnonConfiguration' doesn't exists.", UI::Notify::ERROR);
        request.redirect(Helper::gen_url("serverList", param));
        return;
    }
    _formAnon->getForm()->setAction(Helper::gen_url("serverManage", param));

    try {
        Model::Server* server = dynamic_cast<Model::Server*>(DatabaseManager::instance()->getTable("server")->get("id", _id));
        if (server == NULL) {
            s->setNotification("edit", "ServerConfiguration id " + QString::number(_id) + " doesn't exists.", UI::Notify::ERROR);
            request.redirect(Helper::gen_url("serverList", param));
            return;
        }
        // Get a client for the previously added handler...
        Daemon* daemon = DaemonManager::instance()->getDaemon(server->getDaemonId());
        if (daemon == NULL) {
            addNotify("ClientProvider '" + server->getDaemonId() + "' doesn't exists.", UI::Notify::ERROR);
            return;
        }
        daemon->loadPlugin("server", server->getType());
        daemon->setParserFilename(server->getConfigPath());
        if (!request.getParameter("submit").isNull()) {

            if (request.getParameter("type").toString() == "general") {
                daemon->setServerName(request.getParameter("server_name").toString());
                daemon->setServerPort(request.getParameter("server_port").toUInt());
                daemon->setInternetProtocol(request.getParameter("internet_protocol").toString());
                daemon->setIdleTimeout(request.getParameter("idle_timeout").toUInt());
                daemon->setDataConnectionTimeout(request.getParameter("data_timeout").toUInt());
                daemon->setWelcomeMessage(request.getParameter("welcome_message").toString());
                daemon->setLogFile(request.getParameter("log_file").toString());
            } else if (request.getParameter("type").toString() == "anonymous") {
                daemon->enabledAnonymousAllowed(request.getParameter("anonymous_allowed").toBool());
                daemon->enabledAnonymousUploadAllowed(request.getParameter("anonymous_upload_allowed").toBool());
                daemon->enabledAnonymousCreateDirAllowed(request.getParameter("anonymouse_create_dir_allowed").toBool());
            }
            //client->useSystemUser(request.getParameter("use_system_user").toBool());
            //client->setVirtualUserAuthentication(request.getParameter("virtual_user_auth"));
            addNotify("Update success.", UI::Notify::INFO);
        }
        QObject* object = new UI::ServerConfWrapper(daemon);
        if (object == NULL) {
            addNotify("Server configuration '" + server->getDaemonId() + "' cannot be load.", UI::Notify::ERROR);
            return;
        }
        _form->bind(object);
        _formAnon->bind(object);
        daemon->unloadPlugin();
        delete object;
        delete server;
    } catch (const RuntimeException& e) {
        addNotify("Internal Runtime Error: '" + e.message()+".", UI::Notify::ERROR);
    } catch (const CommunicationException& e) {
        addNotify("Communication Error: '" + e.message()+".", UI::Notify::ERROR);
    } catch (...) {
        addNotify("Internal Fatal Error.", UI::Notify::ERROR);
    }
}

QByteArray ServerManageProcessor::render() const {
    UI::DefaultPageRenderer page;
    QMap<QString, QVariant> param;

    page.body()->addWidget(_notify);

    Translate::instance()->group("breadcrumb");
    // Breadcrumbs
    UI::Title* title = new UI::Title();
    {
        title->addClass("editServer");
        UI::Breadcrumb* link = new UI::Breadcrumb();
        link->addLink(Translate::instance()->tr("server_home"), Helper::gen_url("index"));
        link->addLink(Translate::instance()->tr("server_manage"), Helper::gen_url("serverList"));
        link->addLink(Translate::instance()->tr("server_config"), "");
        title->addWidget(link);
    }
    page.body()->addWidget(title);

    Translate::instance()->group("server_manage");
    page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

    // Add button
    UI::Container* buttons = new UI::Container();
    buttons->addClass("btn-group");
    {
        buttons->addClass("buttons");
        param["id"] = _id;
        param["name"] = "start";
        UI::Link* linkStart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_start")));
        linkStart->addClass("btn");
        linkStart->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkStart);

        param["name"] = "stop";
        UI::Link* linkStop = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_stop")));
        linkStop->addClass("btn");
        linkStop->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkStop);

        param["name"] = "restart";
        UI::Link* linkRetart = new UI::Link(Helper::gen_url("serverService", param), new UI::Text(Translate::instance()->tr("button_restart")));
        linkRetart->addClass("btn");
        linkRetart->setAttribute("rel", "shadowbox; width=500;height=110");
        buttons->addWidget(linkRetart);
    }
    page.body()->addWidget(buttons);

    // Content
    UI::Container* divContent = new UI::Container();
    {
        divContent->setId("server");

        Translate::instance()->group("server");
        // Icon
        UI::Container* divIcon = new UI::Container();
        {
            divIcon->addClass("icon users");
            UI::Image* imgContent = new UI::Image("/img/icon_ftp.png", Translate::instance()->tr("icon"));
            imgContent->setAttribute("width", "60");
            divIcon->addWidget(imgContent);
        }
        divContent->addWidget(divIcon);

        Translate::instance()->group("server_manage");
        // Menu
        UI::Menu* menu = new UI::Menu(UI::Container::NAV);
        {
            menu->setAttribute("id", "menu");
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverUserList", param), new UI::Text(Translate::instance()->tr("menu_user"))));
            menu->addMenu("menu", new UI::Link(Helper::gen_url("serverList"), new UI::Text(Translate::instance()->tr("menu_server"))));
        }
        divContent->addWidget(menu);

        UI::Container* rightCol = new UI::Container(UI::Container::DIV);
        {
            rightCol->addClass("rightCol");
            UI::Container* tabbable = new UI::Container(UI::Container::DIV);
            {
                tabbable->addClass("tabbable");
                // Tab
                UI::List* tab = new UI::List();
                {
                    tab->addClass("nav nav-tabs");
                    UI::Link* gen = new UI::Link("#general", new UI::Text("General"));
                    gen->setAttribute("data-toggle", "tab");
                    tab->addWidget(gen);

                    UI::Link* anon = new UI::Link("#anonymous", new UI::Text("Anonymous"));
                    anon->setAttribute("data-toggle", "tab");
                    tab->addWidget(anon);

//                    UI::Link* extra = new UI::Link("#extra", new UI::Text("Extra"));
//                    extra->setAttribute("data-toggle", "tab");
//                    tab->addWidget(extra);
                }
                tabbable->addWidget(tab);

                UI::Container* contentTab = new UI::Container(UI::Container::DIV);
                {
                    contentTab->addClass("tab-content");

                    // Editing General
                    UI::Container* generalTab = new UI::Container(UI::Container::DIV);
                    {
                        generalTab->setId("general");
                        generalTab->addClass("tab-pane active");
                        generalTab->addWidget(_form->getContent());
                    }
                    contentTab->addWidget(generalTab);

                    // Editing Anonymous
                    UI::Container* anonTab = new UI::Container(UI::Container::DIV);
                    {
                        anonTab->setId("anonymous");
                        anonTab->addClass("tab-pane");
                        anonTab->addWidget(_formAnon->getContent());
                    }
                    contentTab->addWidget(anonTab);

                    // Editing Extra
//                    UI::Container* extraTab = new UI::Container(UI::Container::DIV);
//                    {
//                        extraTab->setId("extra");
//                        extraTab->addClass("tab-pane");
//                        extraTab->addWidget(_form->getContent());
//                    }
//                    contentTab->addWidget(extraTab);
                }
                tabbable->addWidget(contentTab);
            }
            rightCol->addWidget(tabbable);
        }
        divContent->addWidget(rightCol);

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);
    return page.render();
}
