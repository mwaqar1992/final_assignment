
#include "D2.hh"

#include "network_comm.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_D2::Capsule_D2( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, network_comm( borderPorts[borderport_network_comm] )
, timer( internalPorts[internalport_timer] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[getting_connected] = "getting_connected";
    stateNames[recieving_data] = "recieving_data";
    stateNames[starting_comm] = "starting_comm";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_D2::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_network_comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_network_comm, index, true );
            break;
        }
}

void Capsule_D2::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_network_comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_network_comm, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_network_comm], index );
            break;
        }
}

void Capsule_D2::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case starting_comm:
        currentState = state_____starting_comm( &message );
        break;
    case getting_connected:
        currentState = state_____getting_connected( &message );
        break;
    case recieving_data:
        currentState = state_____recieving_data( &message );
        break;
    default:
        break;
    }
}

void Capsule_D2::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = starting_comm;
}

const char * Capsule_D2::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_D2::update_state( Capsule_D2::State newState )
{
    currentState = newState;
}

void Capsule_D2::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition subvertex0,starting comm */
    log.log("D2 ready for Connection Request");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition starting comm,getting connected,connect_req:network_comm */
    log.log("D2 received connect_req()");
    if ( network_comm.con_ok().send() ) {
    log.log( "Connection is successful");
    } else {
    log.log( "Connection is not successful!");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define data ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition getting connected,recieving data,send_data:network_comm */
    log.log("D1 is sending data to d2");
    if ( network_comm.acknowledge_data().send() ) {
    log.log( "d2 has acknowleged ");
    } else {
    log.log( "Error in acknowledging by d2");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef data
}

void Capsule_D2::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition recieving data,starting comm,disconnect_req:network_comm */
    log.log("D2 receive disconnect_req()");
    if ( network_comm.disconnect_ok().send() ) {
    log.log( "D1 and D2 got disconnected!");
    } else {
    log.log( "not Disconnected yet cuz of unknown error ");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::transitionaction_____transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition starting comm,starting comm,time_over:network_comm */
    network_comm.go_back().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition getting connected,starting comm,time_over:network_comm */
    network_comm.go_back().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::transitionaction_____transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D2 transition recieving data,starting comm,time_over:network_comm */
    network_comm.go_back().send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D2::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( starting_comm );
}

void Capsule_D2::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( getting_connected );
}

void Capsule_D2::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( recieving_data );
}

void Capsule_D2::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( starting_comm );
}

void Capsule_D2::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition4( msg );
    update_state( starting_comm );
}

void Capsule_D2::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( starting_comm );
}

void Capsule_D2::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition6( msg );
    update_state( starting_comm );
}

Capsule_D2::State Capsule_D2::state_____getting_connected( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_send_data:
            actionchain_____transition2( msg );
            return recieving_data;
        case network_comm::signal_time_over:
            actionchain_____transition5( msg );
            return starting_comm;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_D2::State Capsule_D2::state_____recieving_data( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_disconnect_req:
            actionchain_____transition3( msg );
            return starting_comm;
        case network_comm::signal_time_over:
            actionchain_____transition6( msg );
            return starting_comm;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_D2::State Capsule_D2::state_____starting_comm( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_connect_req:
            actionchain_____transition1( msg );
            return getting_connected;
        case network_comm::signal_time_over:
            actionchain_____transition4( msg );
            return starting_comm;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_D2::port_network_comm,
        "network_comm",
        "network_comm",
        "",
        1,
        true,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_D2::port_timer,
        "Timing",
        "timer",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_D2::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_D2( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &D2 );
    slot->capsule = new Capsule_D2( &D2, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass D2 = 
{
    "D2",
    NULL,
    instantiate_D2,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

