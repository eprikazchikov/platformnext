#ifndef TST_MATH_H
#define TST_MATH_H

#include <QObject>

class MathTest : public QObject {
    Q_OBJECT

private slots:
    void Euler_angles();
};

#endif // TST_MATH_H