#include <qt/loginoverlay.h>
#include <qt/forms/ui_loginoverlay.h>

#include <qt/guiutil.h>

#include <QResizeEvent>
#include <QPropertyAnimation>

LoginOverlay::LoginOverlay(QWidget *parent) :
QWidget(parent),
ui(new Ui::LoginOverlay),
layerIsVisible(true),
userClosed(false)
{
    ui->setupUi(this);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    setWindowFlags(Qt::WindowStaysOnTopHint);
=======
>>>>>>> QT: require password to access wallet
=======
    setWindowFlags(Qt::WindowStaysOnTopHint);
>>>>>>> QT: style the overlays and askpassphrasedialog
=======
    setWindowFlags(Qt::WindowStaysOnTopHint);
>>>>>>> cdc8a216bef63d8a8c917d68bb9916a0aeb8e30a
    if (parent) {
        parent->installEventFilter(this);
        raise();
    }
    setVisible(true);
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
    // apply style
    // XXX: Use local path for development
    // XXX: To remove before for release
    QString strPath(QCoreApplication::applicationDirPath() + "/res/style.qss");
    QFile f(strPath);
    //QFile f(":/style");
    f.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&f);
    setStyleSheet(ts.readAll());
    f.close();
>>>>>>> QT: style the overlays and askpassphrasedialog
=======
>>>>>>> QT: cleanup wallet login implementation
=======
>>>>>>> cdc8a216bef63d8a8c917d68bb9916a0aeb8e30a
}

LoginOverlay::~LoginOverlay()
{
    delete ui;
}

bool LoginOverlay::eventFilter(QObject * obj, QEvent * ev) {
    if (obj == parent()) {
        if (ev->type() == QEvent::Resize) {
            QResizeEvent * rev = static_cast<QResizeEvent*>(ev);
            resize(rev->size());
            if (!layerIsVisible)
                setGeometry(0, height(), width(), height());

        }
        else if (ev->type() == QEvent::ChildAdded) {
            raise();
        }
    }
    return QWidget::eventFilter(obj, ev);
}

//! Tracks parent widget changes
bool LoginOverlay::event(QEvent* ev) {
    if (ev->type() == QEvent::ParentAboutToChange) {
        if (parent()) parent()->removeEventFilter(this);
    }
    else if (ev->type() == QEvent::ParentChange) {
        if (parent()) {
            parent()->installEventFilter(this);
            raise();
        }
    }
    return QWidget::event(ev);
}

void LoginOverlay::toggleVisibility()
{
    showHide(layerIsVisible, true);
    if (!layerIsVisible)
        userClosed = true;
}

void LoginOverlay::showHide(bool hide, bool userRequested)
{
    if ( (layerIsVisible && !hide) || (!layerIsVisible && hide) || (!hide && userClosed && !userRequested))
        return;

    if (!isVisible() && !hide)
        setVisible(true);

    setGeometry(0, hide ? 0 : height(), width(), height());

    QPropertyAnimation* animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(400);
    animation->setStartValue(QPoint(0, hide ? 0 : this->height()));
    animation->setEndValue(QPoint(0, hide ? this->height() : 0));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    layerIsVisible = !hide;
<<<<<<< HEAD
<<<<<<< HEAD
}
=======
}
>>>>>>> QT: require password to access wallet
=======
}
>>>>>>> cdc8a216bef63d8a8c917d68bb9916a0aeb8e30a
