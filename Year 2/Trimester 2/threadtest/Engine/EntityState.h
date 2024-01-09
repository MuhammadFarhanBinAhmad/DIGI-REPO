#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H
#include "StateHandler.h"
#include <vector>

class EntityState: public StateHandler
{
public:

    void EventHandler() const override;
};
#endif
