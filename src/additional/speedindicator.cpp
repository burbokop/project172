#include "speedindicator.h"

SpeedIndicator::SpeedIndicator()
{

}

void SpeedIndicator::render(e172::AbstractRenderer *renderer) {

    if(lastNumber != number) {
        auto top = std::to_string(number);
        auto bottom = std::to_string(lastNumber);

        renderer->drawString(top, e172::Vector(), 0);
    }
}
