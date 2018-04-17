
#ifndef D1_HH
#define D1_HH

#include "network_comm.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttimerid.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

class Capsule_D1 : public UMLRTCapsule
{
public:
    Capsule_D1( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    UMLRTLogProtocol_baserole log;
    network_comm::Conj network_comm;
public:
    enum BorderPortId
    {
        borderport_network_comm
    };
protected:
    UMLRTTimerProtocol_baserole timer;
public:
    enum InternalPortId
    {
        internalport_timer,
        internalport_log
    };
    enum PartId
    {
    };
    enum PortId
    {
        port_log,
        port_network_comm,
        port_timer
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    UMLRTTimerId timerID;
    char * Data;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        Failed_to_manage_tasks_in_the_specified_time,
        disconnection_has_been_successful,
        waiting_for_connection_to_establish,
        waiting_for_the_data_to_be_ack,
        waiting_for_the_date_to_be_sent,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    void update_state( State newState );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____transition1( const UMLRTMessage * msg );
    void transitionaction_____transition2( const UMLRTMessage * msg );
    void transitionaction_____transition3( const UMLRTMessage * msg );
    void transitionaction_____transition4( const UMLRTMessage * msg );
    void transitionaction_____transition5( const UMLRTMessage * msg );
    void transitionaction_____transition6( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____transition1( const UMLRTMessage * msg );
    void actionchain_____transition2( const UMLRTMessage * msg );
    void actionchain_____transition3( const UMLRTMessage * msg );
    void actionchain_____transition4( const UMLRTMessage * msg );
    void actionchain_____transition5( const UMLRTMessage * msg );
    void actionchain_____transition6( const UMLRTMessage * msg );
    void actionchain_____transition7( const UMLRTMessage * msg );
    State state_____Failed_to_manage_tasks_in_the_specified_time( const UMLRTMessage * msg );
    State state_____disconnection_has_been_successful( const UMLRTMessage * msg );
    State state_____waiting_for_connection_to_establish( const UMLRTMessage * msg );
    State state_____waiting_for_the_data_to_be_ack( const UMLRTMessage * msg );
    State state_____waiting_for_the_date_to_be_sent( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass D1;

#endif

