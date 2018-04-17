
#include "Top.hh"

#include "D1.hh"
#include "D2.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, d1( &slot->parts[part_d1] )
, d2( &slot->parts[part_d2] )
{
}




void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "d1",
        &D1,
        1,
        1,
        false,
        false
    },
    {
        "d2",
        &D2,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_d1].slots[0]->ports[Capsule_D1::borderport_network_comm], 0, &slot->parts[Capsule_Top::part_d2].slots[0]->ports[Capsule_D2::borderport_network_comm], 0 );
    D1.instantiate( NULL, slot->parts[Capsule_Top::part_d1].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_d1].slots[0], D1.numPortRolesBorder ) );
    D2.instantiate( NULL, slot->parts[Capsule_Top::part_d2].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_d2].slots[0], D2.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

