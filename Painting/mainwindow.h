#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

// Painting Area used to paint the image
class ScribbleArea;

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow();

protected:
    // Function to close an event
    void closeEvent(QCloseEvent *event) override;

// The events to be triggered
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();

    // Will check if changes have occurred since last save
    bool maybeSave();

    // Opens the Save dialog and saves
    bool saveFile(const QByteArray &fileFormat);

    // What we'll draw on
    ScribbleArea *scribbleArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *openAct;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif
