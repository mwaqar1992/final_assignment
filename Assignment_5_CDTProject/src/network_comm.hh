
#ifndef NETWORK_COMM_HH
#define NETWORK_COMM_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace network_comm
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal connect_req() const;
        UMLRTInSignal disconnect_req() const;
        UMLRTInSignal send_data() const;
        UMLRTInSignal time_over() const;
        UMLRTOutSignal acknowledge_data() const;
        UMLRTOutSignal con_ok() const;
        UMLRTOutSignal disconnect_ok() const;
        UMLRTOutSignal go_back() const;
        UMLRTOutSignal time_is_finished() const;
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal connect_req() const;
        UMLRTOutSignal disconnect_req() const;
        UMLRTOutSignal send_data( char * data ) const;
        UMLRTOutSignal time_over() const;
        UMLRTInSignal acknowledge_data() const;
        UMLRTInSignal con_ok() const;
        UMLRTInSignal disconnect_ok() const;
        UMLRTInSignal go_back() const;
        UMLRTInSignal time_is_finished() const;
    };
    enum SignalId
    {
        signal_connect_req = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_disconnect_req,
        signal_send_data,
        signal_time_over,
        signal_acknowledge_data,
        signal_con_ok,
        signal_disconnect_ok,
        signal_go_back,
        signal_time_is_finished
    };
};

#endif

