
#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

typedef int EventType;

#define DEFINE_EVENT_TYPE(e) static const EventType e = __COUNTER__

class Event
{
public:
    Event(EventType t) : _type(t), _target(NULL) { }

    inline EventType type() { return _type; }

    template <typename T>
    inline T * get() { return static_cast<T *>(this); }

    template <typename T>
    inline T * target() { return reinterpret_cast<T *>(_target); }

    void * target() { return _target; }

    inline void target(void * t) { _target = t; }

private:
    EventType _type;
    void * _target;
    friend class EventDispatcher;

public:

    DEFINE_EVENT_TYPE( ENTER_FRAME );

};

class TouchEvent : public Event
{
public:
    TouchEvent(EventType t, float lx, float ly, float sx, float sy, uint id) :
        Event(t), _localX(lx), _localY(ly), _stageX(sx), _stageY(sy), _id(id) { }

    inline float localX() { return _localX; }
    inline float localY() { return _localY; }
    inline float stageX() { return _stageX; }
    inline float stageY() { return _stageY; }

    inline uint id() { return _id; }

private:

    friend class DisplayObjectContainer; // so it can set _localX
    float _localX, _localY, _stageX, _stageY;
    uint _id;

public:

    DEFINE_EVENT_TYPE( DOWN );
    DEFINE_EVENT_TYPE( MOVE );
    DEFINE_EVENT_TYPE( UP );
};


#endif
