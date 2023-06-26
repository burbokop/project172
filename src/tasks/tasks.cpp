#include "tasks.h"

#include "buywaretask.h"
#include "dockingtask.h"
#include "sellwaretask.h"
#include "tradetask.h"
#include <src/additional/taskconsole.h>

void proj172::core::registerConsoleTasks(TaskConsole &console)
{
    console.registerTask<DockingTask>();
    console.registerTask<BuyWareTask>();
    console.registerTask<SellWareTask>();
    console.registerTask<TradeTask>();
}
