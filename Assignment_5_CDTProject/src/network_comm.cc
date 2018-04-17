
#include "network_comm.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_connect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_connect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_connect_req
};

static UMLRTObject_field fields_disconnect_req[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_req = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_req
};

static UMLRTObject_field fields_send_data[] = 
{
    {
        "data",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_send_data = 
{
    sizeof( char * ),
    1,
    fields_send_data
};

static UMLRTObject_field fields_time_over[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_time_over = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_time_over
};

static UMLRTObject_field fields_acknowledge_data[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_acknowledge_data = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_acknowledge_data
};

static UMLRTObject_field fields_con_ok[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_con_ok = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_con_ok
};

static UMLRTObject_field fields_disconnect_ok[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_disconnect_ok = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_disconnect_ok
};

static UMLRTObject_field fields_go_back[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_go_back = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_go_back
};

static UMLRTObject_field fields_time_is_finished[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_time_is_finished = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_time_is_finished
};

network_comm::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTInSignal network_comm::Base::connect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTInSignal network_comm::Base::disconnect_req() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTInSignal network_comm::Base::send_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data );
    return signal;
}

UMLRTInSignal network_comm::Base::time_over() const
{
    UMLRTInSignal signal;
    signal.initialize( "time_over", signal_time_over, srcPort, &payload_time_over );
    return signal;
}

UMLRTOutSignal network_comm::Base::acknowledge_data() const
{
    UMLRTOutSignal signal;
    signal.initialize( "acknowledge_data", signal_acknowledge_data, srcPort, &payload_acknowledge_data );
    return signal;
}

UMLRTOutSignal network_comm::Base::con_ok() const
{
    UMLRTOutSignal signal;
    signal.initialize( "con_ok", signal_con_ok, srcPort, &payload_con_ok );
    return signal;
}

UMLRTOutSignal network_comm::Base::disconnect_ok() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTOutSignal network_comm::Base::go_back() const
{
    UMLRTOutSignal signal;
    signal.initialize( "go_back", signal_go_back, srcPort, &payload_go_back );
    return signal;
}

UMLRTOutSignal network_comm::Base::time_is_finished() const
{
    UMLRTOutSignal signal;
    signal.initialize( "time_is_finished", signal_time_is_finished, srcPort, &payload_time_is_finished );
    return signal;
}

network_comm::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
}

UMLRTOutSignal network_comm::Conj::connect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "connect_req", signal_connect_req, srcPort, &payload_connect_req );
    return signal;
}

UMLRTOutSignal network_comm::Conj::disconnect_req() const
{
    UMLRTOutSignal signal;
    signal.initialize( "disconnect_req", signal_disconnect_req, srcPort, &payload_disconnect_req );
    return signal;
}

UMLRTOutSignal network_comm::Conj::send_data( char * data ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "send_data", signal_send_data, srcPort, &payload_send_data, &data );
    return signal;
}

UMLRTOutSignal network_comm::Conj::time_over() const
{
    UMLRTOutSignal signal;
    signal.initialize( "time_over", signal_time_over, srcPort, &payload_time_over );
    return signal;
}

UMLRTInSignal network_comm::Conj::acknowledge_data() const
{
    UMLRTInSignal signal;
    signal.initialize( "acknowledge_data", signal_acknowledge_data, srcPort, &payload_acknowledge_data );
    return signal;
}

UMLRTInSignal network_comm::Conj::con_ok() const
{
    UMLRTInSignal signal;
    signal.initialize( "con_ok", signal_con_ok, srcPort, &payload_con_ok );
    return signal;
}

UMLRTInSignal network_comm::Conj::disconnect_ok() const
{
    UMLRTInSignal signal;
    signal.initialize( "disconnect_ok", signal_disconnect_ok, srcPort, &payload_disconnect_ok );
    return signal;
}

UMLRTInSignal network_comm::Conj::go_back() const
{
    UMLRTInSignal signal;
    signal.initialize( "go_back", signal_go_back, srcPort, &payload_go_back );
    return signal;
}

UMLRTInSignal network_comm::Conj::time_is_finished() const
{
    UMLRTInSignal signal;
    signal.initialize( "time_is_finished", signal_time_is_finished, srcPort, &payload_time_is_finished );
    return signal;
}


