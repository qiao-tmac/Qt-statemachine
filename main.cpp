#include <QApplication>
#include <QState>
#include <QStateMachine>
#include <QPushButton>
#include <QObject>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QMessageBox>

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    QPushButton button("StateMachine");
    //创建状态机和3个状态，并将3个状态添加到状态机
    QStateMachine machine;
    QState *state1 = new QState(&machine);
    QState *state2 = new QState(&machine);
    QState *state3 = new QState(&machine);

    //为按钮的geometry属性分配一个值，当进入该状态是会设置该值
    state1->assignProperty(&button,"geometry",QRect(100,100,120,50));
    state2->assignProperty(&button,"geometry",QRect(300,100,120,50));
    state3->assignProperty(&button,"geometry",QRect(200,100,120,50));

    //使用按钮的单击信号完成3个状态的切换
//    state1->addTransition(&button,SIGNAL(clicked()),state2);
//    state2->addTransition(&button,SIGNAL(clicked()),state3);
//    state3->addTransition(&button,SIGNAL(clicked()),state1);

    QSignalTransition *transtion1 = state1->addTransition(&button,SIGNAL(clicked()),state2);
    QSignalTransition *transtion2 = state2->addTransition(&button,SIGNAL(clicked()),state3);
    QSignalTransition *transtion3 = state3->addTransition(&button,SIGNAL(clicked()),state1);

    QPropertyAnimation *animation = new QPropertyAnimation(&button,"geometry");
//    transtion1->addAnimation(animation);
//    transtion2->addAnimation(animation);
//    transtion3->addAnimation(animation);
    machine.addDefaultAnimation(animation);

    //设置状态机开始并启动状态机
    machine.setInitialState(state1);
    machine.start();
    button.show();
//    QObject::connect(state3,&QState::entered,&button,&QPushButton::showMinimized);
    return app.exec();
}
