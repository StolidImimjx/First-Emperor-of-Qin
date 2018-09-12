#include "regeditmanagetool.h"
#include "ui_regeditmanagetool.h"

RegeditManageTool::RegeditManageTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegeditManageTool)
{
    ui->setupUi(this);

    /*--------------动作--------------*/
    //添加右键工具
    QAction* AddToRM = new QAction(tr("添加工具到桌面右键菜单"), this);
    AddToRM->setShortcut(Qt::CTRL|Qt::Key_A);
    //AddToRM->setStatusTip("添加工具到桌面右键菜单");

    /*--------------菜单--------------*/
    //工具
    QMenu* pToolMenu = new QMenu(tr("工具"));
    pToolMenu->addAction(AddToRM);


    /*--------------菜单栏--------------*/
    QMenuBar* pMenuBar = ui->menuBar;
    pMenuBar->addMenu(pToolMenu);

    connect(pMenuBar, QMenuBar::triggered,
            this, RegeditManageTool::onTrigerMenu);

    //QGridLayout* glyt = ui->gLyAddRBTool;

    connect(ui->pBtnGetIconPath, QPushButton::clicked,
            this, RegeditManageTool::onBrowseFileClicked);
    connect(ui->pBtnGetExecPath, QPushButton::clicked,
            this, RegeditManageTool::onBrowseFileClicked);
    connect(ui->pBtnAddTool, QPushButton::clicked,
            this, RegeditManageTool::onAddToolClicked);
    connect(ui->pBtnDelTool, QPushButton::clicked,
            this, RegeditManageTool::onDelToolClicked);



}

RegeditManageTool::~RegeditManageTool()
{
    delete ui;
}

void RegeditManageTool::onTrigerMenu(QAction* act)
{
    if(0 == act->text().compare(tr("添加工具到桌面右键菜单")))
        qDebug()<< "onAddToolToRM" << endl;

}

void RegeditManageTool::onBrowseFileClicked()
{
    QString path = QFileDialog::getOpenFileName(this,           // 指定父组件
                                                tr("获取路径"),  // 对话框的标题
                                                tr("E:\\Apps"), // 对话框显示时默认打开的目录
                                                tr("Icon or Exe file(*.ico *.exe)")  // 后缀名过滤器
                                                );
    path.replace(QString("/"), QString("\\")); // 替换'/'为'\'

    if(path.length() > 0)
    {
        QPushButton *pSender = static_cast<QPushButton*>(sender());
        if(pSender == ui->pBtnGetIconPath)
            ui->lEdtIconPath->setText(path);
        if(pSender == ui->pBtnGetExecPath)
            ui->lEdtExecPath->setText(path);
    }

}

void RegeditManageTool::onAddToolClicked()
{
    QString toolName = ui->lEdtTooName->text();
    QString toolIconPath = ui->lEdtIconPath->text();
    QString toolExecPath = ui->lEdtExecPath->text();
    if(toolName.isEmpty() || toolExecPath.isEmpty())
    {
        QMessageBox::information(this,
                                 tr("【添加失败】"),
                                 tr("请选择添加的工具名称及执行文件路径."));
        return;
    }

    if(RegeditManager::GetInstance()->AddToolToRightMenu(toolName,
                                             toolIconPath, toolExecPath))
    {
        QMessageBox::information(this,
                                 tr("【添加成功】"),
                                 tr("添加工具 %1 到桌面右键菜单成功.").arg(toolName));
    }
    else
    {
        QMessageBox::information(this,
                                 tr("【添加失败】"),
                                 tr("添加工具 %1 到桌面右键菜单失败.").arg(toolName));
    }
}

void RegeditManageTool::onDelToolClicked()
{
    QString toolName = ui->lEdtTooName->text();
    if(toolName.isEmpty() || toolName.isNull())
    {
        QMessageBox::information(this,
                                 tr("【添加失败】"),
                                 tr("工具不存在或输出错误."));
        return;
    }
    if(0 == toolName.compare(QString(".")))
    {
        int ret = QMessageBox::warning(this,
                             tr("【删除警告】"),
                             tr("你确定删除所有工具吗？"),
                             QMessageBox::Yes,     //ret ==  16384
                             QMessageBox::Cancel); // ret == 4194304
        qDebug() << ret << endl;
        return;
    }
    if(RegeditManager::GetInstance()->DelToolFromRightMenu(toolName))
    {
        QMessageBox::information(this,
                                 tr("【删除成功】"),
                                 tr("从桌面右键菜单删除工具 %1 成功.").arg(toolName));
    }
    else
    {
        QMessageBox::information(this,
                                 tr("【删除失败】"),
                                 tr("从桌面右键菜单删除工具 %1 失败.").arg(toolName));
    }
}
