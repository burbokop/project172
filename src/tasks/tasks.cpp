#include "tasks.h"

#include "../additional/taskconsole.h"
#include "buywaretask.h"
#include "dockingtask.h"
#include "sellwaretask.h"
#include "tradetask.h"

void proj172::core::registerConsoleTasks(TaskConsole &console)
{
    console.registerTask<DockingTask>();
    console.registerTask<BuyWareTask>();
    console.registerTask<SellWareTask>();
    console.registerTask<TradeTask>();
}
