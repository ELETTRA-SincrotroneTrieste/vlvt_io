/***************************************************************************
 *   Copyright (C) 2007 by Vincenzo Forchi`,,,   *
 *   vincenzo.forchi@elettra.trieste.it   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "vlvt_io.h"
#include <qtango.h>
#include <elettracolors.h>

VlvtIo::VlvtIo(QWidget *parent) : QWidget(parent)
{
    /* Porting to QTango3 means setStateColor global through Config::instance() */
    Config::instance()->setStateColor(Tango::OPEN, EColor(Elettra::green));
    Config::instance()->setStateColor(Tango::CLOSE, EColor(Elettra::darkYellow));

    ui.setupUi(this);

    ui.tabWidget->widget(1)->layout()->setSpacing(3);
    ui.tabWidget->widget(1)->layout()->setMargin(4);
    on_tabWidget_currentChanged(0);
    /* Temporary hack to show a temporary vlvt_io state. Inside the .ui the temporary vlvt_io is configured
  * through the bit 2. If the panel was not launched with --temptest parameter, then remove the information
  * related to the bit number 2.
  */
    if(!qApp->arguments().contains("--temptest"))
    {
        ui.tVlvtIoStat->setBooleanDisplay(2, "---", "---", EColor(Elettra::white), EColor(Elettra::white));
    }
    if(qApp->arguments().contains("--fastvlvt_io"))
    {
	ui.tLabel_3->hide();
        ui.tVlvtIoStat->setBooleanDisplay(2, "---", "INRUSH", EColor(Elettra::white), EColor(Elettra::red));
        foreach(TPushButton *pb, findChildren<TPushButton *>())
            pb->setHidden(true);
    }
}

VlvtIo::~VlvtIo()
{
}    

void VlvtIo::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
    on_tabWidget_currentChanged(ui.tabWidget->currentIndex());
}

void VlvtIo::on_tabWidget_currentChanged(int idx)
{
    resize(sizeHint());
}


