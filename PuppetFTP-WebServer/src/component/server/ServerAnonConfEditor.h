/*
 * ServerAnonConfEditor.h
 *
 *  Created on: 19 feb. 2013
 *      Author: mtonnelier
 */

#ifndef SERVERANONCONFEDITOR_H
#define SERVERANONCONFEDITOR_H

#include "ModelEntityEditor.h"
#include "ServerConfWrapper.h"

namespace UI {

class ServerAnonConfEditor : public ModelEntityEditor< ::UI::ServerConfWrapper > {
public:
    ServerAnonConfEditor();
    virtual ~ServerAnonConfEditor();

private:
    void initCustomField();
    void initOrder();
};

} // namespace UI

#endif // SERVERANONCONFEDITOR_H
