
#include "TopControllers.hh"

#include "D1.hh"
#include "D2.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, NULL, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_d1],
    &Top_slots[InstId_Top_d2]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_d1,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_d2,
        1,
        &slots_Top[1]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_d1[] = 
{
    {
        0,
        &borderports_Top_d2[Capsule_D2::borderport_network_comm]
    }
};

UMLRTCommsPort borderports_Top_d1[] = 
{
    {
        &D1,
        Capsule_D1::borderport_network_comm,
        &Top_slots[InstId_Top_d1],
        1,
        borderfarEndList_Top_d1,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_d1_ptrs[] = 
{
    &borderports_Top_d1[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_d1[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_d1[] = 
{
    {
        &D1,
        Capsule_D1::internalport_timer,
        &Top_slots[InstId_Top_d1],
        1,
        &internalfarEndList_Top_d1[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &D1,
        Capsule_D1::internalport_log,
        &Top_slots[InstId_Top_d1],
        1,
        internalfarEndList_Top_d1,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_d1_ptrs[] = 
{
    &internalports_Top_d1[0],
    &internalports_Top_d1[1]
};

static Capsule_D1 top_d1( &D1, &Top_slots[InstId_Top_d1], borderports_Top_d1_ptrs, internalports_Top_d1_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_d2[] = 
{
    {
        0,
        &borderports_Top_d1[Capsule_D1::borderport_network_comm]
    }
};

UMLRTCommsPort borderports_Top_d2[] = 
{
    {
        &D2,
        Capsule_D2::borderport_network_comm,
        &Top_slots[InstId_Top_d2],
        1,
        borderfarEndList_Top_d2,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_d2_ptrs[] = 
{
    &borderports_Top_d2[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_d2[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_d2[] = 
{
    {
        &D2,
        Capsule_D2::internalport_timer,
        &Top_slots[InstId_Top_d2],
        1,
        &internalfarEndList_Top_d2[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &D2,
        Capsule_D2::internalport_log,
        &Top_slots[InstId_Top_d2],
        1,
        internalfarEndList_Top_d2,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_d2_ptrs[] = 
{
    &internalports_Top_d2[0],
    &internalports_Top_d2[1]
};

static Capsule_D2 top_d2( &D2, &Top_slots[InstId_Top_d2], borderports_Top_d2_ptrs, internalports_Top_d2_ptrs, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        2,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.d1",
        0,
        &D1,
        &Top,
        Capsule_Top::part_d1,
        &top_d1,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_d1,
        NULL,
        true,
        false
    },
    {
        "Top.d2",
        0,
        &D2,
        &Top,
        Capsule_Top::part_d2,
        &top_d2,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_d2,
        NULL,
        true,
        false
    }
};

