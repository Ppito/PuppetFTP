/*
 * ServerConfEditor.cpp
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#include "ServerConfEditor.h"
#include "Helper.h"
#include "Translate.h"

namespace UI {

ServerConfEditor::ServerConfEditor() : ModelEntityEditor< ::UI::ServerConfWrapper >() {
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

ServerConfEditor::~ServerConfEditor() {
}

void ServerConfEditor::initCustomField() {
    getForm()->removeWidget("internet_protocol");
    getForm()->removeWidget("virtual_user_auth");

    InputChoice* selectProtocol = new InputChoice("internet_protocol", InputChoice::SELECT);
    {
        selectProtocol->addOption("IPv4", "IPv4");
        selectProtocol->addOption("IPv6", "IPv6");
    }
    getForm()->addWidget("editor", selectProtocol);

    InputChoice* selectVirtual = new InputChoice("virtual_user_auth", InputChoice::SELECT);
    {
        selectVirtual->addOption("0", "Anonymous");
    }
    getForm()->addWidget("editor", selectVirtual);

    Input* hidden = new Input("type", Input::HIDDEN);
    {
        hidden->setValue("general");
        hidden->setLabel("");
    }
    getForm()->addWidget("editor", hidden);

    // Set attribute
    getContent()->removeAttribute("class");
}

void ServerConfEditor::initOrder() {

    getForm()->removeAllSections();
    getForm()->addSection("network",    "Network Management");
    getForm()->addSection("miscs",      "Miscs");
    getForm()->addSection("submit",     "");

    QList<QString> order;
    order << "server_name" << "server_port" << "internet_protocol" << "idle_timeout" << "data_timeout";
    getForm()->setFieldOrder("network", order);
    order.clear();
    order << "welcome_message" << "log_file" << "type";
    getForm()->setFieldOrder("miscs", order);
}

} // namespace UI
