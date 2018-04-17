
#include "D1.hh"

#include "network_comm.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtsignal.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_D1::Capsule_D1( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, network_comm( borderPorts[borderport_network_comm] )
, timer( internalPorts[internalport_timer] )
, Data( "AAAAAAAAAAAAAAAA" )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[Failed_to_manage_tasks_in_the_specified_time] = "Failed_to_manage_tasks_in_the_specified_time";
    stateNames[disconnection_has_been_successful] = "disconnection_has_been_successful";
    stateNames[waiting_for_connection_to_establish] = "waiting_for_connection_to_establish";
    stateNames[waiting_for_the_data_to_be_ack] = "waiting_for_the_data_to_be_ack";
    stateNames[waiting_for_the_date_to_be_sent] = "waiting_for_the_date_to_be_sent";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}








void Capsule_D1::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_network_comm:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_network_comm, index, true );
            break;
        }
}

void Capsule_D1::unbindPort( bool isBorder, int portId, int index )
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



void Capsule_D1::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case waiting_for_connection_to_establish:
        currentState = state_____waiting_for_connection_to_establish( &message );
        break;
    case waiting_for_the_date_to_be_sent:
        currentState = state_____waiting_for_the_date_to_be_sent( &message );
        break;
    case waiting_for_the_data_to_be_ack:
        currentState = state_____waiting_for_the_data_to_be_ack( &message );
        break;
    case disconnection_has_been_successful:
        currentState = state_____disconnection_has_been_successful( &message );
        break;
    case Failed_to_manage_tasks_in_the_specified_time:
        currentState = state_____Failed_to_manage_tasks_in_the_specified_time( &message );
        break;
    default:
        break;
    }
}

void Capsule_D1::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = waiting_for_connection_to_establish;
}

const char * Capsule_D1::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_D1::update_state( Capsule_D1::State newState )
{
    currentState = newState;
}

void Capsule_D1::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition subvertex0,waiting for connection to establish */
    // Initate the communication
    log.log("D1 ready for initiating communication");
    timerID=timer.informEvery(UMLRTTimespec(60,0));
    if ( network_comm.connect_req().send() ) {
    log.log( "connect_req_is_being_sent");
    } else {
    log.log( "Unexpected connection error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition1( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for connection to establish,waiting for the date to be sent,con_ok:network_comm */
    network_comm.send_data(Data).send();
    log.log( "D1 is sending data");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition2( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for the date to be sent,waiting for the data to be ack,acknowledge_data:network_comm */
    log.log("Data has been succsessfuly received by D2");
    if ( network_comm.disconnect_req().send() ) {
    log.log( "D1 is now initiating disconnection");
    } else {
    log.log( "Error in initiating disconnection ");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition3( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for the data to be ack,disconnection has been successful,disconnect_ok:network_comm */
    //String data = Data;
    log.log(Data);
    log.log("Successful transfer!");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition4( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for connection to establish,Failed to manage tasks in the specified time,rtUnbound:network_comm/acknowledge_data:network_comm/disconnect_ok:network_comm/go_back:network_comm/time_is_finished:network_comm/rtBound:network_comm */
    if ( network_comm.time_over().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition5( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for the date to be sent,Failed to manage tasks in the specified time,rtUnbound:network_comm/con_ok:network_comm/disconnect_ok:network_comm/go_back:network_comm/time_is_finished:network_comm/rtBound:network_comm */
    if ( network_comm.time_over().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::transitionaction_____transition6( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/Assignment_5/Assignment_5.uml Assignment_5::D1 transition waiting for the data to be ack,Failed to manage tasks in the specified time,rtUnbound:network_comm/con_ok:network_comm/acknowledge_data:network_comm/go_back:network_comm/time_is_finished:network_comm/rtBound:network_comm */
    if ( network_comm.time_over().send() ) {
    log.log( "Unsuccessful transfer!");
    } else {
    log.log( "Unsuccessful transfer Error");
    }
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_D1::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( waiting_for_connection_to_establish );
}

void Capsule_D1::actionchain_____transition1( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition1( msg );
    update_state( waiting_for_the_date_to_be_sent );
}

void Capsule_D1::actionchain_____transition2( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition2( msg );
    update_state( waiting_for_the_data_to_be_ack );
}

void Capsule_D1::actionchain_____transition3( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition3( msg );
    update_state( disconnection_has_been_successful );
}

void Capsule_D1::actionchain_____transition4( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition4( msg );
    update_state( Failed_to_manage_tasks_in_the_specified_time );
}

void Capsule_D1::actionchain_____transition5( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition5( msg );
    update_state( Failed_to_manage_tasks_in_the_specified_time );
}

void Capsule_D1::actionchain_____transition6( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____transition6( msg );
    update_state( Failed_to_manage_tasks_in_the_specified_time );
}

void Capsule_D1::actionchain_____transition7( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( waiting_for_connection_to_establish );
}

Capsule_D1::State Capsule_D1::state_____Failed_to_manage_tasks_in_the_specified_time( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_go_back:
            actionchain_____transition7( msg );
            return waiting_for_connection_to_establish;
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

Capsule_D1::State Capsule_D1::state_____disconnection_has_been_successful( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_D1::State Capsule_D1::state_____waiting_for_connection_to_establish( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_con_ok:
            actionchain_____transition1( msg );
            return waiting_for_the_date_to_be_sent;
        case UMLRTSignal::rtUnbound:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_acknowledge_data:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_disconnect_ok:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_go_back:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_time_is_finished:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case UMLRTSignal::rtBound:
            actionchain_____transition4( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
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

Capsule_D1::State Capsule_D1::state_____waiting_for_the_data_to_be_ack( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_disconnect_ok:
            actionchain_____transition3( msg );
            return disconnection_has_been_successful;
        case UMLRTSignal::rtUnbound:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_con_ok:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_acknowledge_data:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_go_back:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_time_is_finished:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case UMLRTSignal::rtBound:
            actionchain_____transition6( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
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

Capsule_D1::State Capsule_D1::state_____waiting_for_the_date_to_be_sent( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_network_comm:
        switch( msg->getSignalId() )
        {
        case network_comm::signal_acknowledge_data:
            actionchain_____transition2( msg );
            return waiting_for_the_data_to_be_ack;
        case UMLRTSignal::rtUnbound:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_con_ok:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_disconnect_ok:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_go_back:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case network_comm::signal_time_is_finished:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
        case UMLRTSignal::rtBound:
            actionchain_____transition5( msg );
            return Failed_to_manage_tasks_in_the_specified_time;
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
        Capsule_D1::port_network_comm,
        "network_comm",
        "network_comm",
        "",
        1,
        true,
        true,
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
        Capsule_D1::port_timer,
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
        Capsule_D1::port_log,
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

static void instantiate_D1( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &D1 );
    slot->capsule = new Capsule_D1( &D1, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass D1 = 
{
    "D1",
    NULL,
    instantiate_D1,
    0,
    NULL,
    1,
    portroles_border,
    2,
    portroles_internal
};

