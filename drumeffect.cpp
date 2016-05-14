#include "drumeffect.h"

DrumEffect::DrumEffect()
{
    this->setOpacity(0.0);
}
void DrumEffect::VisibleOn()
{
    this->setOpacity(1.0);
}
void DrumEffect::VisibleOff()
{
    this->setOpacity(0.0);
}
