#include <QtTest>

#include "tst_common.h"
#include "tst_variant.h"
#include "tst_object.h"
#include "tst_objectsystem.h"
#include "tst_serialization.h"
#include "tst_threadpool.h"
#include "tst_uri.h"
#include "tst_animation.h"

inline int aExec(QObject &ts, int argc, char *argv[]) {
    QStringList args;
    for(int i = 0; i < argc; i++) {
        args.append(argv[i]);
    }

    int result  = 0;
    int index   = args.indexOf("-t");
    if(index != -1) {
        args.removeAt(index);
        if(index < argc) {
            QString arg = args.at(index);
            arg.replace('*', ts.metaObject()->className());

            args.removeAt(index);
            args.append("-o");
            args.append(arg);

            result  = QTest::qExec(&ts, args);

            args.removeLast();
            args.removeLast();
        }
    } else {
        result  = QTest::qExec(&ts, args);
    }

    return result;
}

int main(int argc, char *argv[]) {
    int status = 0;

    PROFILE_START

    ObjectSystem system;
    TestObject::registerClassFactory(&system);
    {
        VariantTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        SerializationTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        UriTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        ObjectTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        ObjectSystemTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        AnimationTest ts;
        status |= aExec(ts, argc, argv);
    }
    {
        ThreadPoolTest ts;
        status |= aExec(ts, argc, argv);
    }

    PROFILE_STOP

    return status;
}
