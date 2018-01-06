#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "CsgPrimitive.h"
#include "CsgDisk.h"
#include "CsgRegularPolygon.h"
#include "BoundingBox.h"
#include "CsgTree.h"
#include "renderImg.h"

#include <QFileDialog>
#include <QTextCursor>

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
    m_currentNode(NULL),
    m_prim(NULL),
    m_oper(NULL),
	m_graphTextEdit(NULL),
	m_stopSignal(false)

{
	ui->setupUi(this);

    //m_render = new RenderImg();
    m_render = new RenderImg(this->m_bb);

	ui->HLayout->insertWidget(0,m_render,99);
	m_render->setFocusPolicy(Qt::ClickFocus);

	ui->translationX->setMinimum(-100);
	ui->translationX->setMaximum(100);
	ui->translationY->setMinimum(-100);
	ui->translationY->setMaximum(100);
	
	ui->scale->setMinimum(-100);
	ui->scale->setMaximum(100);
	
    //ui->currentNode->setMaximum(0);
    //ui->id_filsGauche->setMaximum(0);
    //ui->id_filsDroit->setMaximum(0);
	
	connect(ui->create_oper,SIGNAL(clicked()),SLOT(createOperation()));
	connect(ui->create_prim,SIGNAL(clicked()),SLOT(createPrimtive()));
	connect(ui->resetTransfo,SIGNAL(clicked()),SLOT(resetTransfo()));
	connect(ui->applyTransfo,SIGNAL(clicked()),SLOT(applyTransfo()));

	connect(ui->translationX,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->translationY,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->rotation,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));
	connect(ui->scale,SIGNAL(valueChanged(int)),SLOT(transfoSliderChanged()));

	connect(ui->dsb_tx,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_ty,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_Rot,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));
	connect(ui->dsb_s,SIGNAL(valueChanged(double)),SLOT(transfoSpinChanged()));

	connect(ui->actionLoadIMG, SIGNAL(triggered()), this, SLOT(loadImage()));
	connect(ui->actionSaveIMG, SIGNAL(triggered()), this, SLOT(saveImage()));
	connect(ui->actionDrawSobel, SIGNAL(triggered()), this, SLOT(drawSobel()));

	connect(ui->actionLoadCSG, SIGNAL(triggered()), this, SLOT(loadCSG()));
	connect(ui->actionSaveCSG, SIGNAL(triggered()), this, SLOT(saveCSG()));
	connect(ui->actionAppendCSG, SIGNAL(triggered()), this, SLOT(appendCSG()));
	connect(ui->actionClearCSG, SIGNAL(triggered()), this, SLOT(clearCSG()));

	connect(ui->actionClone, SIGNAL(triggered()), this, SLOT(clone()));
	connect(ui->actionSwapLRRoot, SIGNAL(triggered()), this, SLOT(swapLRRoot()));
	connect(ui->actionUnjoinRoot, SIGNAL(triggered()), this, SLOT(unjoinRoot()));

	connect(ui->currentNode, SIGNAL(valueChanged(int)), this, SLOT(currentNodeChanged(int)));
	connect(ui->checkBox_drawCurrent, SIGNAL(toggled(bool)), this, SLOT(updateTreeRender()));

	connect(ui->id_filsGauche, SIGNAL(valueChanged(int)), this, SLOT(updateTreeRender()));
	connect(ui->id_filsDroit, SIGNAL(valueChanged(int)), this, SLOT(updateTreeRender()));


	m_graphTextEdit = new GraphTextEdit();
	m_graphTextEdit->show();
	connect(m_graphTextEdit,SIGNAL(copyAvailable(bool)),SLOT(nodeTextSelected(bool)));
	update();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::updateTreeRender()
{
	drawTree();
	m_render->update();
}



void MainWindow::closeEvent(QCloseEvent* /*event*/)
{
	m_graphTextEdit->close();
}

void MainWindow::createPrimtive()
{
	int prim =  ui->prim_type->currentIndex();
    int sides = ui->nb_sides->value();

    std::cout << "create primitive" << std::endl;

    // VOTRE CODE ICI : primitive creation
    //	m_currentNode = ??

    Vec2f center; center[0] = 512; center[1] = 512;

    switch (prim)
    {
        // disque
        case 0:
            std::cout << "adding new disk primitive" << std::endl;
            m_tree.addPrimitive(new CsgDisk(center, 2.f));
            break;;
        // polygone régulier
        case 1:
            std::cout << "adding new regular polygon primitive" << std::endl;
            m_tree.addPrimitive(new CsgRegularPolygon(sides, center, 2.f));
            break;
        default:
            std::cout << "unknown primitive..." << std::endl;
            break;
    }
    m_currentNode = m_tree.getLastInsertedNode();
    std::cout << "id current node : " << m_currentNode->getId() << std::endl;

    // mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit
    int max = m_tree.getLastNodeId();
    std::cout << "max is " << max << std::endl;
    ui->currentNode->setMaximum(max);
    ui->id_filsGauche->setMaximum(max);
    ui->id_filsDroit->setMaximum(max);

	drawTree();

    // récupère l'id du noeud crée
    ui->currentNode->setValue(m_tree.getLastNodeId());
	updateTextGraph();

}


void MainWindow::createOperation()
{
	int typeOp = ui->Operation->currentIndex();
	int left = ui->id_filsGauche->value();
	int right = ui->id_filsDroit->value();

	std::cout << "createOperation  ";
	std::cout << "type "<< typeOp;
	std::cout << " child: "<< left << " & "<< right;
	std::cout << std::endl;

    CsgOperation* oper=NULL;
	switch(typeOp)
	{
        // union
		case 0:
            std::cout << "adding new union" << std::endl;
            oper = new CsgOperation(operationTypes::UNION);
			break;
        // intersection
		case 1:
            std::cout << "adding new intersection" << std::endl;
            oper = new CsgOperation(operationTypes::INTERSECTION);
			break;
        // différence
		case 2:
            std::cout << "adding new difference" << std::endl;
            oper = new CsgOperation(operationTypes::DIFFERENCE);
			break;
		default:
			std::cerr << "unknown operation" << std::endl;
			return;
			break;
	};

    if (oper == NULL)
        return;

    // regroupement des deux primitives/opérations

    // rechercher le noeud correspondant à left
    CsgNode *leftChild = m_tree.getNode(left);

    // rechercher le noeud correspondant à right
    CsgNode *rightChild = m_tree.getNode(right);

    // regrouper les deux avec joinPrimitives
    m_tree.joinPrimitives(oper, leftChild, rightChild);

    // mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit
    int max = m_tree.getLastNodeId();
    ui->currentNode->setMaximum(max);
    ui->id_filsGauche->setMaximum(max);
    ui->id_filsDroit->setMaximum(max);

    m_transfo = Matrix33d();
    m_centerSelection = oper->getBoundingBox().center();
    m_currentNode = m_tree.getLastInsertedNode();

	updateTreeRender();

	updateTextGraph();

}


void MainWindow::applyTransfo()
{
//	m_transfo = m_currentNode->getTransfo();
	resetTransfoWidgets();
	updateTreeRender();
}


void MainWindow::resetTransfoWidgets()
{
	m_stopSignal=true;
	ui->translationX->setValue(0);
	ui->translationY->setValue(0);
	ui->scale->setValue(0);
	ui->rotation->setValue(0);
	m_stopSignal=false;
	transfoSliderChanged();

}


void MainWindow::resetTransfo()
{
//	m_currentNode->setTransfo(m_transfo);
	resetTransfoWidgets();
}

#define S1_FACTOR 20.0
#define S2_FACTOR 40.0

void MainWindow::transfoChanged()
{
	// recupere la primitive courante et lui applique les transformations
	// VOTRE CODE ICI

    double transx = ui->translationX->value();
    double transy = ui->translationY->value();
    double angle = ui->rotation->value();
    double scale;
    int ss = ui->scale->value();
    if (ss >= 0)
        scale = 1.0 + (double)ss/S1_FACTOR;
    else
        scale = 1.0 / (1.0 - (double)ss/S2_FACTOR);

    // récupération du noeud courant (opération ou primitive)
    CsgNode *node = m_tree.getNode(ui->currentNode->value());
    // récupération de la matrice de translation
    Matrix33d trans = trans.staticTranslation(transx, transy);
    // récupération de la matrice de rotation
    Matrix33d rot = rot.staticRotation(angle);
    // récupération de la matrice d'homothétie
    Matrix33d homo = homo.staticShrink(scale, scale);

    std::cout << trans(0,0) << " " << trans(0,1) << " " << trans(0,2) << std::endl;
    std::cout << trans(1,0) << " " << trans(1,1) << " " << trans(1,2) << std::endl;
    std::cout << trans(2,0) << " " << trans(2,1) << " " << trans(2,2) << std::endl << std::endl;

    std::cout << rot(0,0) << " " << rot(0,1) << " " << rot(0,2) << std::endl;
    std::cout << rot(1,0) << " " << rot(1,1) << " " << rot(1,2) << std::endl;
    std::cout << rot(2,0) << " " << rot(2,1) << " " << rot(2,2) << std::endl << std::endl;

    std::cout << homo(0,0) << " " << homo(0,1) << " " << homo(0,2) << std::endl;
    std::cout << homo(1,0) << " " << homo(1,1) << " " << homo(1,2) << std::endl;
    std::cout << homo(2,0) << " " << homo(2,1) << " " << homo(2,2) << std::endl << std::endl;

    // construction de la matrice de transformation
    //Matrix33d transfo = homo * trans * rot;
    Matrix33d transfo = trans * rot;
    transfo = homo * transfo;

    std::cout << transfo(0,0) << " " << transfo(0,1) << " " << transfo(0,2) << std::endl;
    std::cout << transfo(1,0) << " " << transfo(1,1) << " " << transfo(1,2) << std::endl;
    std::cout << transfo(2,0) << " " << transfo(2,1) << " " << transfo(2,2) << std::endl;

    node->setMatrix(transfo);

    // mise à jour de la bounding box
    if (node->getOperation().getOperationType() == operationTypes::NONE)
    {
        CsgPrimitive *prim = node->getPrimitive();
        prim->updateBoundingBox(transx, transy, angle, scale);
        node->getOperation().setBoundingBox(prim->getBoundingBox());
    }
    else
    {
        // on verra
    }


	// de même avec un noeud Operation !

	updateTreeRender();
}

void MainWindow::transfoSliderChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->dsb_tx->setValue(ui->translationX->value());
	ui->dsb_ty->setValue(ui->translationY->value());
	ui->dsb_Rot->setValue(ui->rotation->value());

	int ss = ui->scale->value();
	if (ss>=0)
		ui->dsb_s->setValue(1.0+ss/S1_FACTOR);
	else
		ui->dsb_s->setValue(1.0/(1.0-ss/S2_FACTOR));

	m_stopSignal = false;

	transfoChanged();
}

void MainWindow::transfoSpinChanged()
{
	if (m_stopSignal)
		return;

	m_stopSignal = true;

	ui->translationX->setValue(ui->dsb_tx->value());
	ui->translationY->setValue(ui->dsb_ty->value());
	ui->rotation->setValue(ui->dsb_Rot->value());

	double ss = ui->dsb_s->value();
	if (ss>=1.0)
		ui->scale->setValue((ss-1.0)*S1_FACTOR);
	else
		ui->scale->setValue((1.0-1.0/ss)*S2_FACTOR);

	m_stopSignal = false;

	transfoChanged();
}

#undef S1_FACTOR
#undef S2_FACTOR


void MainWindow::loadImage()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();
		// load texture
		m_render->loadTexture(strFN);
		update();
	}
}

void MainWindow::saveImage()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save Image"), QDir::currentPath(),tr("pgm (*.pgm);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();
        //m_render->getImg().savePGMascii(strFN);
        m_render->getImg().save(strFN);
	}
}


void MainWindow::drawSobel()
{
	m_render->toggleSobel();
}


void MainWindow::loadCSG()
{
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

		std::ifstream in(strFN.c_str());
		if (!in.good())
		{
			std::cerr << "Unable to open file " << strFN << std::endl;
			return;
		}

	// VOTRE CODE ICI

		 updateTextGraph();

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
	}
}

// same as load but no clear before readind the tree
void MainWindow::appendCSG()
{
	QString fileName = QFileDialog::getOpenFileName(this,
									tr("Open File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

	// VOTRE CODE ICI


		 updateTextGraph();
		updateTreeRender();

// mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode

	}
}

void MainWindow::saveCSG()
{
	QString fileName = QFileDialog::getSaveFileName(this,
									tr("Save File"), QDir::currentPath(),tr("csg (*.csg);;all (*.*)"));
	if (!fileName.isEmpty())
	{
		std::string strFN = fileName.toStdString();

	// VOTRE CODE ICI

	}
}

void MainWindow::clearCSG()
{
    m_tree.clear();
	updateTextGraph();
	updateTreeRender();
    // mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode
}


void MainWindow::clone()
{
	// VOTRE CODE ICI

	updateTextGraph();
	updateTreeRender();

    // mettre a jour ui->currentNode ui->id_filsGauche ui->id_filsDroit ui->currentNode

}


void MainWindow::drawTree()
{
	m_render->clean();
    m_tree.drawInImage( m_render->getImg() );

	if (ui->checkBox_drawCurrent->isChecked()/* && m_currentNode!=NULL*/)
	{
		// OPTION: trace le noeud courant dans l'image de m_render
		// VOTRE CODE ICI

        m_render->setBBDraw(true);
//		m_bb = m_currentNode->getBBox();
	}
	else
	{
		m_render->setBBDraw(false);
	}

// trace les 2 fils de l'operation avec 2 niveau de gris pour vizu
/*	int idf = ui->id_filsGauche->value();
	if (idf != 0)
	{
		CsgNode* fNode = m_tree.fromId(idf);
		if (fNode->isRoot())
			m_tree.drawInImage(fNode, m_render->getImg(),175);
	}

	idf = ui->id_filsDroit->value();
	if (idf != 0)
	{
		CsgNode* fNode = m_tree.fromId(idf);
		if (fNode->isRoot())
			m_tree.drawInImage(fNode, m_render->getImg(),200);
	}
*/
	m_render->updateDataTexture();
}


void MainWindow::nodeTextSelected(bool sel)
{
	if (!sel)
		return;

	QTextCursor cursor = m_graphTextEdit->textCursor();
	std::string nodeLabel = cursor.selectedText().toStdString();

	if (nodeLabel.size() !=5)
		return;

	// get id from label string
	std::string strId = nodeLabel.substr(2,4);
	std::stringstream ss(strId);
	unsigned int id;
	ss >> id;

	ui->currentNode->setValue(id);

	if (m_graphTextEdit->pressed() == 'l')
	{
		ui->id_filsGauche->setValue(id);
	}
	else if (m_graphTextEdit->pressed() == 'r'	)
	{
		ui->id_filsDroit->setValue(id);
	}
	else
	{
		ui->currentNode->setValue(id);
	}

}


void MainWindow::updateTextGraph()
{
	// update Graph in TextWindow
	m_graphTextEdit->clear();
    //std::string str = m_tree.asciiArtGraph();
    //m_graphTextEdit->appendPlainText(str.c_str());
}


void MainWindow::currentNodeChanged(int id)
{
    //	m_currentNode = m_tree.fromId(id);

    // VOTRE CODE ICI
    m_currentNode = m_tree.getNode(id);

	resetTransfoWidgets();

}


void MainWindow::swapLRRoot()
{
    // VOTRE CODE ICI
	updateTextGraph();
	updateTreeRender();
}



void MainWindow::unjoinRoot()
{
    // VOTRE CODE ICI

    //	m_currentNode = NULL;
	updateTextGraph();
	updateTreeRender();
}


GraphTextEdit::GraphTextEdit()
{
	this->resize(800,800);
	this->setWindowTitle("CSG-Graph");
	this->setReadOnly(true);
	this->setWordWrapMode(QTextOption::NoWrap);

	QFont font = QFont ("Courier");
	font.setStyleHint(QFont::TypeWriter);
	font.setPointSize(11);
	font.setFixedPitch (true);
	this->setFont(font);
}

