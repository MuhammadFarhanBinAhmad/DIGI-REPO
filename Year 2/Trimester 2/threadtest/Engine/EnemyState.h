#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H
#include "StateHandler.h"

class EnemyState: public StateHandler
{

public:
    void EventHandler() const override;

};
#endif // ENEMYSTATE_H
