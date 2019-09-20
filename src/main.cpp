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


#include <TApplication>
#include "vlvt_io.h"
#include <tutil.h>
#include <X11/Xlib.h>
#include <QX11Info>
#include <QSplashScreen>

#define CVSVERSION "$Name:  $"
/* uncomment to set application color */
#include <elettracolors.h>

int main( int argc, char ** argv ) {

    TApplication a( argc, argv );
    /* setup some TApplication parameters */
    a.setPalette(EPalette("fermi"));
    a.setOrganizationName("Elettra");
    a.setApplicationName("VlvtIo");
    a.setProperty("author", "Giacomo");
    a.setProperty("hwReferent", "Graziano");
    QString version(CVSVERSION);
    a.setApplicationVersion(version);
    
    TUtil::instance()->setLoggingTarget(argv[0]);

    QPixmap pix(200,40);
    pix.fill(a.palette().color(QPalette::Window));
    QSplashScreen splash(pix);
    QFont f = splash.font();
    f.setPointSize(12);
    splash.setFont(f);
    splash.showMessage("Connecting to devices...", Qt::AlignCenter);
    splash.show();

    VlvtIo mw;
    if (argc > 1)
        mw.setWindowTitle(a.arguments()[1].split('/').last());
    else
        mw.setWindowTitle("VlvtIo");
    mw.show();

    splash.finish(&mw);

    /* register to window manager */
    Display *disp = QX11Info::display();
    Window root_win = (Window) mw.winId();
    XSetCommand(disp, root_win, argv, argc);
	
    return a.exec();
}
