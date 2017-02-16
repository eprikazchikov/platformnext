#include "ametaobject.h"

#include "aobject.h"

AMetaObject::AMetaObject(const char *name, const AMetaObject *super, const Constructor constructor, const AMetaMethod::Table *methods, const AMetaProperty::Table *props) :
        m_pName(name),
        m_pSuper(super),
        m_Constructor(constructor),
        m_pMethods(methods),
        m_pProperties(props),
        m_MethodCount(0),
        m_PropCount(0) {

    while(methods && methods[m_MethodCount].name) {
        m_MethodCount++;
    }
    while(props && props[m_PropCount].type) {
        m_PropCount++;
    }
}

const char *AMetaObject::name() const {
    return m_pName;
}

const AMetaObject *AMetaObject::super() const {
    return m_pSuper;
}

AObject *AMetaObject::createInstance(AObject *parent) const {
    return (*m_Constructor)(parent);
}

int AMetaObject::indexOfMethod(const char *signature) const {
    const AMetaObject *s    = this;

    while(s) {
        for(int i = 0; i < s->m_MethodCount; ++i) {
            if(AMetaMethod(m_pMethods + i).signature() == signature) {
                return i + s->methodOffset();
            }
        }
        s = s->m_pSuper;
    }
    return -1;
}

int AMetaObject::indexOfSignal(const char *signature) const {
    const AMetaObject *s    = this;

    while(s) {
        for(int i = 0; i < s->m_MethodCount; ++i) {
            AMetaMethod m(m_pMethods + i);
            if(m.type() == AMetaMethod::Signal && m.signature() == signature) {
                return i + s->methodOffset();
            }
        }
        s = s->m_pSuper;
    }
    return -1;
}

int AMetaObject::indexOfSlot(const char *signature) const {
    const AMetaObject *s    = this;

    while(s) {
        for(int i = 0; i < s->m_MethodCount; ++i) {
            AMetaMethod m(m_pMethods + i);
            if(m.type() == AMetaMethod::Slot && m.signature() == signature) {
                return i + s->methodOffset();
            }
        }
        s = s->m_pSuper;
    }
    return -1;
}

AMetaMethod AMetaObject::method(int index) const {
    int i = index - methodOffset();
    if(i < 0 && m_pSuper) {
        return m_pSuper->method(index);
    }

    if(i >= 0 && i < m_MethodCount) {
        return AMetaMethod(m_pMethods + index);
    }
    return AMetaMethod(nullptr);
}

int AMetaObject::methodCount() const {
    int count               = m_MethodCount;
    const AMetaObject *s    = m_pSuper;
    while(s) {
        count  += s->m_MethodCount;
        s       = s->m_pSuper;
    }
    return count;
}

int AMetaObject::methodOffset() const {
    int offset              = 0;
    const AMetaObject *s    = m_pSuper;
    while(s) {
        offset += s->m_MethodCount;
        s       = s->m_pSuper;
    }
    return offset;
}

int AMetaObject::indexOfProperty(const char *name) const {
    const AMetaObject *s    = this;

    while(s) {
        for(int i = 0; i < s->m_PropCount; ++i) {
            if(strcmp(s->m_pProperties[i].name, name) == 0) {
                return i + propertyOffset();
            }
        }
        s   = s->m_pSuper;
    }
    return -1;
}

AMetaProperty AMetaObject::property(int index) const {
    int i = index - propertyOffset();
    if(i < 0 && m_pSuper) {
        return m_pSuper->property(index);
    }
    if(i >= 0 && i < m_PropCount) {
        return AMetaProperty(m_pProperties + index);
    }
    return AMetaProperty(nullptr);
}

int AMetaObject::propertyCount() const {
    int count               = m_PropCount;
    const AMetaObject *s    = m_pSuper;
    while(s) {
        count  += s->m_PropCount;
        s       = s->m_pSuper;
    }
    return count;
}

int AMetaObject::propertyOffset() const {
    int offset              = 0;
    const AMetaObject *s    = m_pSuper;
    while(s) {
        offset += s->m_PropCount;
        s       = s->m_pSuper;
    }
    return offset;
}