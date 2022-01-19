#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
    this->setWindowTitle("Untitled - Notepad");
    this->setWindowIcon(QIcon(":/img/icons/icon.png"));

    font = ui->textEdit->font();
    font.setPixelSize(20);
    ui->textEdit->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText("");
}

void MainWindow::on_actionoOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Text files (*.txt)"));
    QFile file(fileName);


    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        return;
    }

    QString title = currentFile = fileName;

    int i = 0;
    for (int j = 0; j < title.length(); j++)
    {
        if (title[j] == '/') i = j;
    }
    title.erase(title.begin(), title.begin() + i + 1);
    this->setWindowTitle(title + " - Notepad");

    QTextStream its(&file);
    ui->textEdit->setText(its.readAll());

    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Text files (*.txt)"));
    QFile file(fileName);


    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        return;
    }

    QString title = currentFile = fileName;

    int i = 0;
    for (int j = 0; j < title.length(); j++)
    {
        if (title[j] == '/') i = j;
    }
    title.erase(title.begin(), title.begin() + i + 1);
    this->setWindowTitle(title + " - Notepad");

    QTextStream ots(&file);
    ots << ui->textEdit->toPlainText();

    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if (currentFile.length())
    {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly | QFile::Text))
        {
            return;
        }

        QTextStream ots(&file);
        ots << ui->textEdit->toPlainText();

        file.close();
    }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("Text files (*.txt)"));
        QFile file(fileName);


        if (!file.open(QIODevice::WriteOnly | QFile::Text))
        {
            return;
        }

        QString title = currentFile = fileName;

        int i = 0;
        for (int j = 0; j < title.length(); j++)
        {
            if (title[j] == '/') i = j;
        }
        title.erase(title.begin(), title.begin() + i + 1);
        this->setWindowTitle(title + " - Notepad");

        QTextStream ots(&file);
        ots << ui->textEdit->toPlainText();

        file.close();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
     ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
     ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionZoom_In_triggered()
{
    fontSize += 5;
    if (fontSize > 100) fontSize = 100;
    font.setPixelSize(fontSize);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionZoom_Out_triggered()
{
    fontSize -= 5;
    if (fontSize < 5) fontSize = 10;
    font.setPixelSize(fontSize);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionRestore_Default_Zoom_triggered()
{
    fontSize = 20;
    font.setPixelSize(fontSize);
    ui->textEdit->setFont(font);
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionDate_Time_triggered()
{
    ui->textEdit->insertPlainText(QDateTime::currentDateTime().toString("hh:mm dd.MM.yyyy"));
}
