/*
 * ServerConfEditor.h
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#ifndef SERVERCONFEDITOR_H
#define SERVERCONFEDITOR_H

#include "ModelEntityEditor.h"
#include "ServerConfWrapper.h"

namespace UI {

class ServerConfEditor : public ModelEntityEditor< ::UI::ServerConfWrapper > {
public:
    ServerConfEditor();
    virtual ~ServerConfEditor();

private:
    void initCustomField();
    void initOrder();
};

} // namespace UI

#endif // SERVERCONFEDITOR_H
