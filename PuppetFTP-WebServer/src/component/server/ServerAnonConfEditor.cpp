/*
 * ServerAnonConfEditor.cpp
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#include "ServerAnonConfEditor.h"
#include "Helper.h"
#include "Translate.h"

namespace UI {

ServerAnonConfEditor::ServerAnonConfEditor() : ModelEntityEditor< ::UI::ServerConfWrapper >() {
    // Create Custom Field
    initCustomField();

    // Change order
    initOrder();
    QString label;
    QString help;
    QList<IWidgetForm*> widget = getForm()->getWidgets();

    for (QList<IWidgetForm*>::iterator it = widget.begin(); it != widget.end(); it++) {
        Translate::instance()->group("server_editor_label");
        label = Translate::instance()->tr((*it)->getName());
        Translate::instance()->group("server_editor_help");
        help = Translate::instance()->tr((*it)->getName());
        (*it)->setLabel(label, help);
    }
    getForm()->getWidget("type")->setLabel("");
}

ServerAnonConfEditor::~ServerAnonConfEditor() {
}

void ServerAnonConfEditor::initCustomField() {

    getForm()->removeWidget("anonymous_allowed");
    getForm()->removeWidget("anonymous_upload_allowed");
    getForm()->removeWidget("anonymouse_create_dir_allowed");

    InputChoice* anonymousAllowed = new InputChoice("anonymous_allowed", InputChoice::CHECKBOX);
    {
        anonymousAllowed->addOption("true", "");
    }
    getForm()->addWidget("editor", anonymousAllowed);

    InputChoice* anonymousUploadAllowed = new InputChoice("anonymous_upload_allowed", InputChoice::CHECKBOX);
    {
        anonymousUploadAllowed->addOption("true", "");
    }
    getForm()->addWidget("editor", anonymousUploadAllowed);

    InputChoice* anonymousCreateDirAllowed = new InputChoice("anonymouse_create_dir_allowed", InputChoice::CHECKBOX);
    {
        anonymousCreateDirAllowed->addOption("true", "");
    }
    getForm()->addWidget("editor", anonymousCreateDirAllowed);

    Input* hidden = new Input("type", Input::HIDDEN);
    {
        hidden->setValue("anonymous");
        hidden->setLabel("");
    }
    getForm()->addWidget("editor", hidden);

    // Set attribute
    getContent()->removeAttribute("class");
}

void ServerAnonConfEditor::initOrder() {

    getForm()->removeAllSections();
    getForm()->addSection("anonymous",  "Anonymous User");
    getForm()->addSection("submit",     "");

    QList<QString> order;
    order << "anonymous_allowed" << "anonymous_upload_allowed" << "anonymouse_create_dir_allowed" << "type";
    getForm()->setFieldOrder("anonymous", order);
}

} // namespace UI
