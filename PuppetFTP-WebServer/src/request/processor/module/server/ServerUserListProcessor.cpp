#include "ServerUserListProcessor.h"
#include "DefaultPageRenderer.h"
#include "ModelWidgetFactory.h"
#include "DatabaseManager.h"
#include "Widget.h"
#include "Helper.h"
#include "Translate.h"

ServerUserListProcessor::ServerUserListProcessor() : AbstractRequestProcessor() {
}

ServerUserListProcessor::~ServerUserListProcessor() {
}

void ServerUserListProcessor::process(HTTPRequest& request) {
}

QByteArray ServerUserListProcessor::render() const {
    UI::DefaultPageRenderer page;

    page.body()->addWidget(_notify);
    Translate::instance()->group("server");

    // Content
    UI::Container* divBreadcrumb = new UI::Container();
    {
        divBreadcrumb->setId("breadcrumb");

        // Icon
        UI::Container* divIcon = new UI::Container();
        {
            divIcon->addClass("icon users");
            UI::Image* imgContent = new UI::Image("/img/icon_ftp.png", Translate::instance()->tr("icon"));
            imgContent->setAttribute("width", "60");
            divIcon->addWidget(imgContent);
        }
        divBreadcrumb->addWidget(divIcon);

        Translate::instance()->group("breadcrumb");
        // Breadcrumbs
        UI::Title* title = new UI::Title();
        {
            UI::Breadcrumb* link = new UI::Breadcrumb();
            link->addLink(Translate::instance()->tr("server_home"), Helper::gen_url("index"));
            link->addLink(Translate::instance()->tr("server_manage"), "");
            title->addWidget(link);
        }
        divBreadcrumb->addWidget(title);
    }
    page.body()->addWidget(divBreadcrumb);

    Translate::instance()->group("server_user_list");
    page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

    // Content
    UI::Container* divContent = new UI::Container();
    {
        divContent->setId("server");

        // Editing
//        divContent->addWidget(_table->getContent());

        // Clear
        UI::Container* divClear = new UI::Container();
        divClear->setAttribute("style", "clear:both;visibility:hidden;");
        divContent->addWidget(divClear);
    }
    page.body()->addWidget(divContent);
    return page.render();

}
