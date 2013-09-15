/*
 * ServerForm.cpp
 *
 *  Created on: 15 nov. 2012
 *      Author: mtonnelier
 */

#include "ServerModelEditor.h"
#include "IWidget.h"
#include "Translate.h"

namespace UI {

ServerModelEditor::ServerModelEditor() : ModelEntityEditor< ::Model::Server >() {
    Translate::instance()->group("editor_server");
    getForm()->removeWidget("id");
    getForm()->getWidget("name")->setLabel(Translate::instance()->tr("name"));
    getForm()->getWidget("address")->setLabel(Translate::instance()->tr("address"));
    getForm()->getWidget("port")->setLabel(Translate::instance()->tr("port"));
    getForm()->getWidget("daemon_id")->setLabel(Translate::instance()->tr("ref_id"));
    getForm()->getWidget("config_path")->setLabel(Translate::instance()->tr("config_path"));
    getForm()->removeWidget("type");

    InputChoice* type = new InputChoice("type", InputChoice::SELECT);
    {
        type->addOption("Proftpd", "ProFTPd");
        type->addOption("Vsftpd", "vsFTPd");
        type->setLabel(Translate::instance()->tr("type"));
    }
    getForm()->addWidget("editor", type);


}

ServerModelEditor::~ServerModelEditor() {
}

} // namespace UI
