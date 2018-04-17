
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_d1,
    InstId_Top_d2
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Top_d1[];
extern UMLRTCommsPort internalports_Top_d1[];
extern UMLRTCommsPort borderports_Top_d2[];
extern UMLRTCommsPort internalports_Top_d2[];
extern UMLRTSlot Top_slots[];

#endif

